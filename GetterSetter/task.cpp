#include <iostream>
#include "cat.h"
using namespace std;

int main(int argc, char *argv[])
{
    Cat mut_cat("cat2", 4);
    mut_cat.name() = "mimi";
    mut_cat.age() += 1;
    mut_cat.print_object();

    const Cat cat("cat1", 2);
    cout << cat.name() << endl;
    // cat.name() = "mimi";
    cat.print_object();
    return 0;
}
