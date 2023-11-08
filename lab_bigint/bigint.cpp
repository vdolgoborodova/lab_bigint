#include "bigint.hpp"

bigint::bigint(){
    
}

// создает длинное целое число из строки
bigint::bigint(std::string str) {
    for (long long i = str.length(); i > 0; i -= 9) {
        if (i < 9)
            this->_digits.push_back(atoi(str.substr(0, i).c_str()));
        else
            this->_digits.push_back(atoi(str.substr(i - 9, 9).c_str()));
    }

    this->_remove_leading_zeros();
}

// преобразует unsigned int к bigint
bigint::bigint(unsigned int i) {
    this->_digits.push_back(i % bigint::BASE);
    i /= bigint::BASE;
    if (i != 0) this->_digits.push_back(i);
}

// удаляет ведущие нули
void bigint::_remove_leading_zeros() {
    while (this->_digits.size() > 1 && this->_digits.back() == 0) {
        this->_digits.pop_back();
    }

}

// печатает число в поток вывода
std::ostream& operator <<(std::ostream& os, const bigint& bi) {
    if (bi._digits.empty()) os << 0;
    else {
        os << bi._digits.back();
        char old_fill = os.fill('0');
        for (long long i = static_cast<long long>(bi._digits.size()) - 2; i >= 0; --i) os << std::setw(9) << bi._digits[i];
        os.fill(old_fill);
    }

    return os;
}

std::istream& operator >>(std::istream& in, bigint &bi){
    std::string s;
    in >> s;
    bi = bigint(s);
    return in;
}

// сравнивает два числа на равенство
bool operator ==(const bigint& left, const bigint& right) {
    if (left._digits.empty()) {
        if (right._digits.empty() || (right._digits.size() == 1 && right._digits[0] == 0)) return true;
        else return false;
    }
    
    if (right._digits.empty()) {
        if (left._digits.size() == 1 && left._digits[0] == 0) return true;
        else return false;
    }

    if (left._digits.size() != right._digits.size()) return false;
    for (size_t i = 0; i < left._digits.size(); ++i) if (left._digits[i] != right._digits[i]) return false;

    return true;
}

// возвращает копию переданного числа
const bigint bigint::operator +() const {
    return bigint(*this);
}

// возвращает переданное число с другим знаком
const bigint bigint::operator -() const {
    bigint copy(*this);
    return copy;
}

// проверяет, является ли левый операнд меньше правого
bool operator <(const bigint& left, const bigint& right) {
    if (left == right) return false;
    else {
        if (left._digits.size() != right._digits.size()) {
            return left._digits.size() < right._digits.size();
        }
        else {
            for (long long i = left._digits.size() - 1; i >= 0; --i) {
                if (left._digits[i] != right._digits[i]) return left._digits[i] < right._digits[i];
            }
            
            return false;
        }
    }
}

// сравнивает два числа на неравенство
bool operator !=(const bigint& left, const bigint& right) {
    return !(left == right);
}

// проверяет, является ли левый операнд меньше либо равен правого
bool operator <=(const bigint& left, const bigint& right) {
    return (left < right || left == right);
}

// проверяет, является ли левый операнд больше правого
bool operator >(const bigint& left, const bigint& right) {
    return !(left <= right);
}

// проверяет, является ли левый операнд больше либо равен правого
bool operator >=(const bigint& left, const bigint& right) {
    return !(left < right);
}

// складывает два числа
const bigint operator +(bigint left, const bigint& right) {
    int carry = 0;
    for (size_t i = 0; i < std::max(left._digits.size(), right._digits.size()) || carry != 0; ++i) {
        if (i == left._digits.size()) left._digits.push_back(0);
        left._digits[i] += carry + (i < right._digits.size() ? right._digits[i] : 0);
        carry = left._digits[i] >= bigint::BASE;
        if (carry != 0) left._digits[i] -= bigint::BASE;
    }

    return left;
}

// прибавляет к текущему числу новое
bigint& bigint::operator +=(const bigint& value) {
    return *this = (*this + value);
}

// префиксный инкремент
const bigint bigint::operator++() {
    return (*this += 1);
}

// преобразует число к строке
std::string bigint::to_string() const{
    std::stringstream ss;
    ss << *this;
    return ss.str();
}



// постфиксный инкремент
const bigint bigint::operator ++(int) {
    *this += 1;
    return *this - 1;
}

// префиксный декремент
const bigint bigint::operator --() {
    return *this -= 1;
}

// постфиксный декремент
const bigint bigint::operator --(int) {
    *this -= 1;
    return *this + 1;
}

// вычитает два числа
const bigint operator -(bigint left, const bigint& right) {
    
    if (left < right) return -(right - left);
    int carry = 0;
    for (size_t i = 0; i < right._digits.size() || carry != 0; ++i) {
        left._digits[i] -= carry + (i < right._digits.size() ? right._digits[i] : 0);
        carry = left._digits[i] < 0;
        if (carry != 0) left._digits[i] += bigint::BASE;
    }

    left._remove_leading_zeros();
    return left;
}

// вычитает из текущего числа новое
bigint& bigint::operator -=(const bigint& value) {
    return *this = (*this - value);
}

// сдвигает все разряды на 1 вправо (домножает на BASE)
void bigint::_shift_right() {
    if (this->_digits.size() == 0) {
        this->_digits.push_back(0);
        return;
    }
    this->_digits.push_back(this->_digits[this->_digits.size() - 1]);
    for (size_t i = this->_digits.size() - 2; i > 0; --i) this->_digits[i] = this->_digits[i - 1];
    this->_digits[0] = 0;
}

