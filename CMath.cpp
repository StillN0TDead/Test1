#include<iostream>
#include"CMath.h"

using namespace std;

    float CMath::calcPower(int base, int exp)
    {
        float result = 1;
        int n = (exp < 0) ? -exp : exp;
        for (int i = 0; i < n; i++) result *= base;
        return (exp < 0) ? 1 / result : result;
    }

    int CMath::calcGCD(int a, int b)
    {
        if (a < 0) a = -a;
        if (b < 0) b = -b;
        while (b != 0)
        {
            int t = a % b;
            a = b;
            b = t;
        }
        return a;
    }

    String CMath::toString(long long int num)
    {
        String s;
        s.setNumber(num);
        return s;
    }

    long long int CMath::toInteger(String s)
    {
        return s.convertToInteger();
    }