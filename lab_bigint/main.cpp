#include <iostream>
#include "bigint.hpp"
using namespace std;


int main() {
    bigint x("179"), y(57);
    cout << boolalpha
    << (x - y) << endl;
    
    ++x;
    x++;
    x--;
    --x;
    cout << x << endl;
    
    cout << x.to_string() << endl;
    bigint h;
    cin >> h;
    cout << h << endl;
}
