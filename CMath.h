#ifndef CMATH_H
#define CMATH_H
#include"String.h"
class CMath
{
public:
    static float calcPower(int base, int exp);
    static int calcGCD(int a, int b);
    static String toString(long long int num);
    static long long int toInteger(String s);

};

#endif