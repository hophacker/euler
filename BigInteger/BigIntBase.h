#ifndef BIGINTBASE_H
#define BIGINTBASE_H
#include "../euler.h"
typedef unsigned char BigUnit;

/*
 * 1.Due to the following reasons, I created BigIntBase as the array type for BigInteger:
 *   A.vector has so many problems when used as class member, ex,
 *     when you use push_back(), When you call std::vector::push_back(), a copy 
 *     of the argument is made before adding it to the vector. 
 *   B.The expansion speed for BigInteger's array is very different from the default
 *     expansion speed of STL::vector, I need to control the expansion.
 *   C.The type for BigUnit is still changing, if I use bit instead of "usnsigned char",
 *     the implementation mechanism may very different, which is difficult to employ
 *     the funcionality of STL::vector.
 * 2.Representation of ingeter:
 *   A. If size==0, the value is 0.
 *   B. If size>0, the value is one positive integer.
 */

class BigIntBase{
private:
    const static ui defaultCapacity = 20;
    /* This constructor is convenient when an object with specific capacity is needed inside the class
     */
    BigIntBase(bool forCapacity, ui _capacity);
    void setCapacity(ui length);
    //This is a member function Initializing unsigned int which is shared by "BigIntBase(ui)" and "BigIntBase(int)"
    //I was so sad that C++ does not support calling constructor inside of another constructor, which is convenient,
    //if wrote "BigIntBase(int n)" as "assert(n >= 0); BigIntBase((ui)(n));".
    //However, there is another choice, which is to delegate constructor by using  "BigIntBase(int n):BigIntBase((ui)(n)){}".
    //But, every time the compiler compiles with annoying warning message:"delegating constructors only available with -std=c++11 or -std=gnu++11".
    void initializeUI(ui n);
public:
    ui size;
    ui capacity;
    BigUnit* data = NULL;
    static const BigUnit digitMul[][10];
public:
    BigIntBase();
    BigIntBase(ui n){initializeUI(n);}
    BigIntBase(int n){assert(n >= 0); initializeUI((ui)n);}
    /* 
     * The input char array can only contain "0-9", for example, 
     * (1) "987643"
     * (3) "00987643"
     * otherwise the result is not defined.
     */
    BigIntBase(const char* numStr);
    BigIntBase(const BigIntBase& rhs);

    /* This constructor method is used when you need a object to be copied with the capacity you want.
     * for example, when multiplication occurs.
     */
    BigIntBase(const BigIntBase& rhs, int rhsCapacity);
    void assign(BigIntBase& lhs, const BigIntBase& rhs, int newCapacity);
    void setCapacity();
    void clear(ui length, BigUnit value);
    void expand(int newCapacity);
    BigUnit& operator[](const ui idx);
    int compare(BigIntBase &b);
    void add(BigIntBase &a, BigIntBase &b);
    void subtract(BigIntBase &a, BigIntBase &b);
    void multiply(BigIntBase &A, BigIntBase &B);
    BigIntBase square();
    BigIntBase pow(ui n);
    BigIntBase& operator=(const BigIntBase &rhs);
    void operator*=(BigIntBase& b);
    BigIntBase operator*(BigIntBase &b);
    BigIntBase operator+(BigIntBase& b);
    BigIntBase operator+=(BigIntBase& b);
    BigIntBase operator-(BigIntBase& b);
    string toStringInBase(ui base);
};
ostream& operator <<(ostream &os, BigIntBase& n);
#endif
