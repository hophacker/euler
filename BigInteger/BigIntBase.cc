#include "BigIntBase.h"

const BigUnit BigIntBase::digitMul[][10]={
    {0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0},
    {0x0,0x1,0x2,0x3,0x4,0x5,0x6,0x7,0x8,0x9},
    {0x0,0x2,0x4,0x6,0x8,0x10,0x12,0x14,0x16,0x18},
    {0x0,0x3,0x6,0x9,0x12,0x15,0x18,0x21,0x24,0x27},
    {0x0,0x4,0x8,0x12,0x16,0x20,0x24,0x28,0x32,0x36},
    {0x0,0x5,0x10,0x15,0x20,0x25,0x30,0x35,0x40,0x45},
    {0x0,0x6,0x12,0x18,0x24,0x30,0x36,0x42,0x48,0x54},
    {0x0,0x7,0x14,0x21,0x28,0x35,0x42,0x49,0x56,0x63},
    {0x0,0x8,0x16,0x24,0x32,0x40,0x48,0x56,0x64,0x72},
    {0x0,0x9,0x18,0x27,0x36,0x45,0x54,0x63,0x72,0x81}
}; 
BigIntBase::BigIntBase(bool forCapacity, ui _capacity){
    setCapacity(_capacity);
}
BigIntBase::BigIntBase(): size(0){
    setCapacity();
}

void BigIntBase::initializeUI(ui n){
    setCapacity();
    if (n == 0){
        data[0] = 0;
        size = 1;
    }else{
        size = 0;
        while(n != 0){
            data[size++] = n % 10;
            n /= 10;
        }
    }
}
BigIntBase::BigIntBase(const char* numStr){
    size = strlen(numStr);
    setCapacity(size*2);
    for (ui i = 0; i < size; i++){
        data[i] = numStr[size-1-i] - '0';
    }
}
BigIntBase::BigIntBase(const BigIntBase& rhs){
    //cout << "Operator copy has been called" << endl;
    assign(*this, rhs, rhs.size);
}
BigIntBase::BigIntBase(const BigIntBase& rhs, int rhsCapacity){
    assign(*this, rhs, rhsCapacity);
}
void BigIntBase::assign(BigIntBase& lhs, const BigIntBase& rhs, int newCapacity){
    lhs.size = rhs.size;
    lhs.setCapacity(newCapacity);
    memcpy(lhs.data, rhs.data, sizeof(BigUnit) * lhs.capacity);
}

void BigIntBase::setCapacity(){
    setCapacity(defaultCapacity);
}

void BigIntBase::setCapacity(ui _capacity){
    free(data);
    data = new BigUnit[capacity=_capacity];
}
void BigIntBase::clear(ui length, BigUnit value){
    if (capacity < length)
        setCapacity(length);
    for (ui i = 0; i < length; i++)
        (*this)[i] = value;
}
void BigIntBase::expand(int newCapacity){
    cout << "expand here" << endl;
    BigUnit* newData = new BigUnit[newCapacity];
    BigUnit* temp = data;
    memcpy(newData, data, sizeof(BigUnit)*capacity);
    data = newData;
    capacity = newCapacity;
    free(temp);
}
/*
 * If the requested idx >= capacity, it will expand the capacity twice.
 * The benefit is that the other part of the program does not need to consider expansion  issue.
 * Thus, this little trick can largely reduce the programming complexity. 
 * Also, in this way, the program is easier to read and to maintain.
 */
BigUnit& BigIntBase::operator[](const ui idx) {
    if (idx >= capacity) expand(capacity << 1);
    return data[idx];
}
void BigIntBase::add(BigIntBase &a, BigIntBase &b){
    assert(a.size >= b.size);
    if (a.size == 0){
        operator = (b);
        return;
    } else if (b.size == 0) {
        operator = (a);
        return;
    }
    BigIntBase& c = *this;
    ui i;
    bool carry = 0;
    BigUnit t;
    for (i = 0; i < b.size; i++){
        t = a[i] + b[i] + carry;
        if (t >= 10) carry = 1, t = t - 10;
        else carry = 0;
        c[i] = t;
    }
    for (; i < a.size && carry; i++){
        t = a[i] + 1;
        if (t == 10) carry = 1, t = 0;
        else carry = 0;
        c[i] = t;
    }
    for (; i < a.size; i++)
        c[i] = a[i];
    if (carry){
        c[i] = 1;
        size = a.size + 1;
    }else size = a.size;
}
int BigIntBase::compare(BigIntBase &b) {
    BigIntBase& a = *this;
    if (a.size != b.size) return a.size - b.size;
    else{
        for (int i = a.size - 1; i >= 0; i--){
            if (a[i] == b[i]) continue;
            else return a[i] - b[i];
        }
        return 0;
    }
}
void BigIntBase::subtract(BigIntBase &a, BigIntBase &b){
    if (b.size == 0){
        operator = (a);
        return;
    }
    BigIntBase& c = *this;
    ui i;
    bool carry = 0;
    BigUnit t;
    for (i = 0; i < b.size; i++){
        t = carry + b[i];
        if (a[i] < t){
            c[i] = 10 + a[i] - t;
            carry = 1;
        }else{
            c[i] = a[i] - t;
            carry = 0;
        }
    }
    for (; i < a.size && carry; i++)
        if (a[i] == 0) c[i] = 9;
        else c[i] = a[i]-1, carry = 0;
    for (; i < a.size; i++)
        c[i] = a[i];

    size = a.size-1;
    while( c[size] == 0 && size >= 0) size--;
    size++;
}
void BigIntBase::multiply(BigIntBase &A, BigIntBase &B){
    if (A.size == 0 || B.size == 0)
        size = 0;
    else if (A.size == 1 && A[0] == 1){
        if (this != &B) operator = (B); //How about f1 *= f2 and f2 == BigIntBase(1)
        return;
    } else if (B.size == 1 && B[0] == 1) {
        if (this != &A) operator = (A);
        return;
    }
    BigIntBase *a, *b;
    if (this == &A) a = new BigIntBase(*this); else a = &A;
    if (this == &B) a = new BigIntBase(*this); else b = &B;

    clear(a->size * b->size, 0);
    BigIntBase& c = *this;
    BigUnit t, carry;
    for (ui i = 0; i < a->size; i++){
        carry = 0;
        for (ui j = 0; j < b->size; j++){
            t = c[i+j] + (*a)[i] * (*b)[j] + carry;
            c[i+j] = t % 10;
            carry = t / 10;
        }
        c[i+b->size] += carry;
    }
    carry = 0;
    for (ui i = 0; i < a->size + b->size; i++){
        t = c[i] + carry;
        c[i] = t % 10;
        carry /= 10;
    }
    size = a->size + b->size;
    while( size > 0 && c[size-1] == 0 ) size --;
}
BigIntBase BigIntBase::square(){
    return (*this)*(*this);
}
BigIntBase BigIntBase::pow(ui n){
    if (n == 0) return BigIntBase();
    else if (n == 1) return BigIntBase(*this);

    BigIntBase ret(*this, size);
    int i = 31;
    for (i = 31; i >= 0 && bit(n,i)==0; i--);
    for (i--; i >= 0; i--){
        ret = ret * ret;
        if (bit(n,i))
            ret *= (*this);
    }
    return ret;
}
BigIntBase& BigIntBase::operator=(const BigIntBase& rhs) {
    assign(*this, rhs, rhs.capacity);
    return *this;
}
BigIntBase BigIntBase::operator*(BigIntBase& b) {
    BigIntBase ret(true, size * b.size * 2);
    ret.multiply(*this, b);
    return ret;
}
void BigIntBase::operator*=(BigIntBase& b) {
    multiply(*this, b);
}
BigIntBase BigIntBase::operator+(BigIntBase& b) {
    BigIntBase ret(true, max(b.capacity, this->capacity)+2);
    if (this->size > b.size)
        ret.add(*this, b);
    else 
        ret.add(b, *this);
    return ret;
}

BigIntBase BigIntBase::operator-(BigIntBase& b){
    assert(compare(b) >= 0);
    BigIntBase ret(true, capacity);
    ret.subtract(*this, b);
    return ret;
}

string BigIntBase::toStringInBase(ui base){
    if (base == 10){
        string s(size, ' ');
        for (ui i = 0; i < size; i++)
            s[i] = (*this)[size-1-i]+'0';
        return s;
    }else{
        cout << "base " << base << " hasn't been implemented";
        return NULL;
    }
}

ostream& operator <<(ostream &os, BigIntBase& n) {
    os << n.toStringInBase(10);
    return os;
}
