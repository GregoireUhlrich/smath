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
    if (a > 100000) return 1; // too big number
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
    
bool operator>(string a, string b)
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
    
bool operator<(string a, string b)
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

bool operator>=(string a, string b)
{
    return (a > b or a == b);
}

bool operator<=(string a, string b)
{
    return (a < b or a == b);
}
