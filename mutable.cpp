#include <iostream>

class Example {
private:
    int regularVariable;   // Regular non-mutable variable
    mutable int mutableVariable;   // Mutable variable

public:
    Example(int regular, int mutableVar) : regularVariable(regular), mutableVariable(mutableVar) {}

    // Member function that does not modify any member variables
    void printRegular() const {
        //regularVariable++; error!!!!!
        std::cout << "Regular Variable: " << regularVariable << std::endl;
    }

    // Member function that can modify the mutable variable
    void modifyMutable() const {
        mutableVariable++;  // Okay, even in a const member function
        std::cout << "Mutable Variable (modified): " << mutableVariable << std::endl;
    }
};

int main() {
    Example example(42, 10);

    example.printRegular();   // Regular Variable: 42
    example.modifyMutable();  // Mutable Variable (modified): 11

    return 0;
}
