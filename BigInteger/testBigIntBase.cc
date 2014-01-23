#include "BigIntBase.h"

void test(const char* label, int testValue, int rightValue){
    printf("%s<%s>: \tIt outputs [%d], \n\t\tthe expected value is [%d]\n", 
            (testValue==rightValue?"Right":"Wrong"), label, testValue, rightValue);
}
void test(const char* label, string test, const char* rightValue){
    const char* testValue = test.c_str();
    printf("%s<%s>: \tIt outputs [%s], \n\t\tthe expected value is [%s]\n", 
            (strcmp(testValue,rightValue)==0?"Right":"Wrong"), label, testValue, rightValue);
}
void problem20(){
    BigIntBase res(1);
    for (int i = 2; i <= 100; i++){
        BigIntBase a(i);
        res *= a;
    }
    int total = 0;
    for (ui i = 0; i < res.size; i++){
        total += res[i];
    }
    test("p20", total, 648);
}
int main(){
    //  use results of euler problems to test
    problem20();
    BigIntBase a;
    test("1", a.capacity, 0);   //1
    BigIntBase b("123"), b1("1234"), b2("122");
    test("2", b.compare(b1), -1); //2
    test("3", b.compare(b2), 1); //3
    test("4", b.compare(b), 0); //4

    BigIntBase c("99999999999999999999999999999999999"), c1("1");
    BigIntBase c2 = c+c1;
    test("5", c2.toStringInBase(10), "100000000000000000000000000000000000"); //5

    BigIntBase d("83484225211392112511446123117807668296927154000788"), d1("46376937677490009712648124896970078050417018260538"); 
    BigIntBase d2 = d - d1;
    test("6", d2.toStringInBase(10) , "37107287533902102798797998220837590246510135740250"); //6

    BigIntBase f1("37107287533902102798797998220837590246510135740250");
    BigIntBase f2("46376937677490009712648124896970078050417018260538");
    BigIntBase f3 = f1 + f2;
    test("7", f3.toStringInBase(10), "83484225211392112511446123117807668296927154000788"); //7
    //multiply
    BigIntBase e1("123098787980787"), e2("1231298789708088"), e = e1 * e2;
    test("8", e.toStringInBase(10), "151571388655275562950682505256");
    BigIntBase e3("129387128974897812"), e4 = e3 * 1234;
    test("9", e4.toStringInBase(10), "159663717155023900008");
    //substract
    BigIntBase e5("129387128974897812"), e6("22341234123"), e8 = e5/e6, e7 = e5 - e6;
    test("10", e7.toStringInBase(10), "129387106633663689");
    //one big int appears at both left side and right side
    e7 = e7 - e6;
    test("11", e7.toStringInBase(10), "129387084292429566");
    e7 -= e6;
    test("12", e7.toStringInBase(10), "129387061951195443");
    //division
    test("13", e8.toStringInBase(10), "5791404");
    BigIntBase g1("123"), g2("123123124123123123123"), g3("987988767");
    g1 = g1 / g1;
    test("14", g1.toStringInBase(10), "1");
    g2 /= g3;
    test("15", g2.toStringInBase(10), "124619963541");
    g2 %= g3;
    test("16", g2.toStringInBase(10), "133378899");
}




