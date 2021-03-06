/*! \file support.h
 * \author Grégoire Uhlrich
 * \version 1.0
 * \brief Some useful functions.
 */
#ifndef SUPPORT_H_INCLUDED
#define SUPPORT_H_INCLUDED

#include <cmath>
#include <string>
#include <vector>

/*! \fn int PGCD(double a, double b)
 * \brief Returns the PGCD of a and b.
 * \details If \a a and \a b are integers ( \a a == floor(\a a) and also for \a b)
 * this function calls PGCD(int a, int b).
 * \param a
 * \param b
 * \return PGCD(a,b) if \a a and \a b are integers.
 * \return \b 1 else.
 */
int PGCD(double a, double b);

/*! \fn int PGCD(int a, int b)
 * \brief Returns the PGCD of a and b.
 * \details Proceeds to verifications on \a a and \a b (sign, non zero, etc) and 
 * calls internal_PGCD(int a, int b) if everythiong is Ok.
 * \param a
 * \param b
 * \return PGCD(a,b)
 */
int PGCD(int a, int b);

/*! \fn int internal_PGCD(int a, int b)
 * \brief Returns the PGCD of a and b.
 * \details This function is called only by PGCD(int a, int b) that
 * do the nexessary checks on a and b before the calculation. Then the
 * algorithm implemented in internal_PGCD() is Euclid's (recursive). The
 * separation of the cjeck function PGCD() and the calculation function
 * internal_PGCD() allows to check only once \a a and \a b since the 
 * algorithm is recursive.
 * \param a
 * \param b
 * \return PGCD(a,b)
 */
int internal_PGCD(int a, int b);

/*! \fn int sgn(int a)
 * \brief Returns the sign of a.
 * \param a
 * \return sign(a)
 */
int sgn(int a); 

/*! \fn int sgn(double a)
 * \brief Returns the sign of a.
 * \param a
 * \return sign(a)
 */
int sgn(double a); 

/*! \fn int factorial(int a)
 * \brief Returns the factorial of a.
 * \param a
 * \return \b a!
 * \bug The factorial function returns a double for now and so is quickly
 * out of bounds for exact numerical precision. The limit is between 20! 
 * and 25!.
 */
double factorial(int n);

/*! \fn int internal_factorial(int a)
 * \brief Returns the factorial of a.
 * \param a
 * \return \b a!
 */
long long int internal_factorial(long long int n);

int compare(std::string a, std::string b);

bool operator>(const std::string& a, const std::string& b);

bool operator<(const std::string& a, const std::string& b);

bool operator>=(const std::string& a, const std::string& b);

bool operator<=(const std::string& a, const std::string& b);

class aInt{

    private:

    std::vector<int> digits;

    public:

    aInt();

    explicit aInt(long long int value);

    explicit aInt(const std::vector<int>& t_digits);

    ~aInt(){};

    aInt& operator=(long long int value);

    aInt& operator=(const aInt& value);

    friend std::ostream& operator<<(std::ostream& fout, const aInt& integer);

    friend aInt operator+(long long int a, const aInt& b);

    friend aInt operator+(const aInt& a, long long int b);

    friend aInt operator+(const aInt& a, const aInt& b);

    friend aInt operator*(long long int a, const aInt& b);

    friend aInt operator*(const aInt& a, long long int b);

    friend aInt operator*(const aInt& a, const aInt& b);

    friend bool operator==(long long int a, const aInt& b);

    friend bool operator==(const aInt& a, long long int b);

    friend bool operator==(const aInt& a, const aInt& b);

    friend bool operator!=(long long int a, const aInt& b);

    friend bool operator!=(const aInt& a, long long int b);

    friend bool operator!=(const aInt& a, const aInt& b);

    friend bool operator<(long long int a, const aInt& b);

    friend bool operator<(const aInt& a, long long int b);

    friend bool operator<(const aInt& a, const aInt& b);

    friend bool operator<=(long long int a, const aInt& b);
    
    friend bool operator<=(const aInt& a, long long int b);

    friend bool operator<=(const aInt& a, const aInt& b);

    friend bool operator>(long long int a, const aInt& b);

    friend bool operator>(const aInt& a, long long int b);

    friend bool operator>(const aInt& a, const aInt& b);

    friend bool operator>=(long long int a, const aInt& b);

    friend bool operator>=(const aInt& a, long long int b);

    friend bool operator>=(const aInt& a, const aInt& b);

    friend aInt factorial(const aInt& number);
};


#endif
