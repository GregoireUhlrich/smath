#include <iostream>
#include "support.h"

using namespace std;

int PGCD(double a, double b)
{
    return PGCD((int)round(a), (int)round(b));
}

int PGCD(int a, int b)
{
    if (a < 0) a *= -1;
    if (b < 0) b *= -1;
    if (a < b)
    {
        int foo = a;
        a = b;
        b = foo;
    }
    //if (a > 1000000) return 1; // too big number
    if (b == 0) return 1;
    return internal_PGCD(a,b);
}

int internal_PGCD(int a, int b)
{
    int r = a%b;
    if (r == 0) return b;
    if (r == 1) return 1;
    return internal_PGCD(b,r);
}

int sgn(int a)
{
    return (a>0) - (a<0);
}
int sgn(double a)
{
    return (a>0) - (a<0);
}

double factorial(int n)
{
    if (n > 200) n = 200;
    if (n < 0) return 1;
    if (n == 0) return 1;
    return internal_factorial(n);
}

long long int internal_factorial(long long int n)
{
    if (n <= 2) return n;
    return n*internal_factorial(n-1);
}

int compare(string a, string b)
    // return 1 if  a > b
    // return 0 if  a = b
    // return -1 if a < b
{
    int size = min(a.length(), b.length());
    for (int i=0; i<size; i++)
    {
        if (a[i] > b[i])
            return 1;
        else if (a[i] < b[i])
            return -1;
    }
    if (a.length() > b.length())
        return 1;
    else if (a.length() < b.length())
        return -1;
    return 0;
}
    
bool operator>(const string& a, const string& b)
{
    int size = min(a.length(), b.length());
    for (int i=0; i<size; i++)
    {
        if (a[i] > b[i])
            return true;
        else if (a[i] < b[i])
            return false;
    }
    return (a.length() > b.length());
}
    
bool operator<(const string& a, const string& b)
{
    int size = min(a.length(), b.length());
    for (int i=0; i<size; i++)
    {
        if (a[i] < b[i])
            return true;
        else if (a[i] > b[i])
            return false;
    }
    return (a.length() < b.length());
}

bool operator>=(const string& a, const string& b)
{
    return (a > b or a == b);
}

bool operator<=(const string& a, const string& b)
{
    return (a < b or a == b);
}

aInt::aInt(): digits(vector<int>(1,0)){}

aInt::aInt(long long int value): digits((value <= 10) ?
        vector<int>(1) : vector<int>(1+floor(log10(value))))
{
    for (size_t i=0; i!=digits.size(); ++i) {
        int digit = value%10;
        digits[i] = digit;
        value -= digit;
        value /= 10;
    }
}

aInt::aInt(const vector<int>& t_digits): digits(t_digits){}

aInt& aInt::operator=(long long int value)
{
    *this = aInt(value);
    return *this;
}

aInt& aInt::operator=(const aInt& value)
{
    digits = value.digits;
    return *this;
}

ostream& operator<<(ostream& fout, const aInt& integer)
{
    for (auto digit=integer.digits.rbegin(); digit!=integer.digits.rend();
           ++digit)
       fout<<*digit; 

    return fout;
}

aInt operator+(long long int a, const aInt& b)
{
    return aInt(a)+b;
}

aInt operator+(const aInt& a, long long int b)
{
    return a+aInt(b);
}

aInt operator+(const aInt& a, const aInt& b)
{
    int retenue = 0;
    const int n = min(a.digits.size(), b.digits.size());
    vector<int> newDigits(0);

    for (int i=0; i<n; ++i) {
        int sum = retenue + a.digits[i] + b.digits[i];
        if (sum > 9) {
            retenue = sum/10;
            sum = sum%10;
        }
        else
            retenue = 0;
        newDigits.push_back(sum);
    }
    if (b.digits.size() == (size_t)n) {
        for (int i=n; i<(int)a.digits.size(); ++i) {
            int sum = retenue + a.digits[i];
            if (sum > 9) {
                retenue = sum/10;
                sum = sum%10;
            }
            else 
                retenue = 0;
            newDigits.push_back(sum);
        }
    }
    else {
        for (int i=n; i<(int)b.digits.size(); ++i) {
            int sum = retenue + b.digits[i];
            if (sum > 9) {
                retenue = sum/10;
                sum = sum%10;
            }
            else 
                retenue = 0;
            newDigits.push_back(sum);
        }
    }
    if (retenue != 0)
        newDigits.push_back(retenue);

    return aInt(newDigits);
}

aInt operator*(long long int a, const aInt& b)
{
    return aInt(a)*b;
}

aInt operator*(const aInt& a, long long int b)
{
    return a*aInt(b);
}

aInt operator*(const aInt& a, const aInt& b)
{
    vector<int> newDigits(0);
    aInt res;
    for (size_t i=0; i!=a.digits.size(); ++i) {
        vector<int> intermediateDigits(i,0);
        int retenue = 0;
        for (size_t j=0; j!=b.digits.size(); ++j) {
            int product = retenue + a.digits[i]*b.digits[j];
            if (product > 9) {
                retenue = product/10;
                product = product%10;
            }
            else 
                retenue = 0;
            intermediateDigits.push_back(product);
        }
        if (retenue != 0)
            intermediateDigits.push_back(retenue);

        res = res+aInt(intermediateDigits);
    }

    return res;
}

bool operator==(long long int a, const aInt& b)
{
    return aInt(a)==b;
}

bool operator==(const aInt& a, long long int b)
{
    return a==aInt(b);
}

bool operator==(const aInt& a, const aInt& b)
{
    if (a.digits.size() != b.digits.size())
        return false;
    if (a.digits.size() == 0)
        return true;
    for (size_t i=0; i!=a.digits.size(); ++i)
        if (a.digits[i] != b.digits[i])
            return false;
    return true;
}

bool operator!=(long long int a, const aInt& b)
{
    return aInt(a)!=b;
}

bool operator!=(const aInt& a, long long int b)
{
    return a!=aInt(b);
}

bool operator!=(const aInt& a, const aInt& b)
{
    return (not operator==(a,b));
}

bool operator<(long long int a, const aInt& b)
{
    return aInt(a)<b;
}

bool operator<(const aInt& a, long long int b)
{
    return a<aInt(b);
}

bool operator<(const aInt& a, const aInt& b)
{
    if (a.digits.size() < b.digits.size())
        return true;
    if (b.digits.size() < a.digits.size())
        return false;
    if (a.digits.size() == 0)
        return false;
    for (int i=a.digits.size()-1; i>=0; --i) {
        if (a.digits[i] < b.digits[i])
            return true;
        else if (b.digits[i] < a.digits[i])
            return false;
    }
    return false;
}

bool operator<=(long long int a, const aInt& b)
{
    return (a<b or a==b);
}

bool operator<=(const aInt& a, long long int b)
{
    return (a<b or a==b);
}

bool operator<=(const aInt& a, const aInt& b)
{
    return (a<b or a==b);
}

bool operator>(long long int a, const aInt& b)
{
    return aInt(a)>b;
}

bool operator>(const aInt& a, long long int b)
{
    return a>aInt(b);
}

bool operator>(const aInt& a, const aInt& b)
{
    if (a.digits.size() > b.digits.size())
        return true;
    if (b.digits.size() > a.digits.size())
        return false;
    if (a.digits.size() == 0)
        return false;
    for (int i=a.digits.size()-1; i>=0; --i) {
        if (a.digits[i] > b.digits[i])
            return true;
        else if (b.digits[i] > a.digits[i])
            return false;
    }
    return false;
}

bool operator>=(long long int a, const aInt& b)
{
    return (a>b or a==b);
}

bool operator>=(const aInt& a, long long int b)
{
    return (a>b or a==b);
}

bool operator>=(const aInt& a, const aInt& b)
{
    return (a>b or a==b);
}

aInt factorial(const aInt& number)
{
    aInt res(1);
    for (aInt i(2); i<=number; i=i+1) 
        res = i*res;

    return res;
}
