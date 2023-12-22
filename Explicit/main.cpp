#include <iostream>
#include "product.h"
using namespace std;

bool compare(const Product &product1, const Product &product2)
{
    cout << *(product1.get_years()) << " : " << *(product2.get_years()) << endl;
    return (*(product1.get_years()) > *(product2.get_years())) ? true : false;
}

int main(int argc, char *argv[])
{
    Product p1("Box", "Toy", 2);
    Product p2("ff");
    std::string s1{"dd"};//If there is no explicit Product, you can just compare and pass in s1.
    cout << compare(p1, p2) << endl;
    return 0;
}
