#ifndef bigint_hpp
#define bigint_hpp

#include <vector>
#include <string>
#include <iomanip>
#include <sstream>
#include <iostream>

class bigint {
    static const int BASE = 1000000000;

    // внутреннее хранилище числа
    std::vector<int> _digits;


    void _remove_leading_zeros();
    void _shift_right();

public:

    bigint();
    bigint(std::string);
    bigint(unsigned int);

    friend std::ostream& operator <<(std::ostream&, const bigint&);
    friend std::istream& operator >>(std::istream&, bigint&);
    
    const bigint operator +() const;
    const bigint operator -() const;
    
    const bigint operator ++();
    const bigint operator ++(int);
    const bigint operator --();
    const bigint operator --(int);
    
    friend bool operator ==(const bigint&, const bigint&);
    friend bool operator <(const bigint&, const bigint&);
    friend bool operator !=(const bigint&, const bigint&);
    friend bool operator <=(const bigint&, const bigint&);
    friend bool operator >(const bigint&, const bigint&);
    friend bool operator >=(const bigint&, const bigint&);
    
    friend const bigint operator +(bigint, const bigint&);
    bigint& operator +=(const bigint&);
    
    friend const bigint operator -(bigint, const bigint&);
    bigint& operator -=(const bigint&);
    
    std::string to_string() const;

};

#endif
