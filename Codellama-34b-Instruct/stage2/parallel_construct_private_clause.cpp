#include <iostream>
#include <cstdlib>
#include <cmath>
#include <acc/acc.h>

int main() {
    int err = 0;
    srand(SEED);

    // Declare a private variable for each gang in all dimensions
    int private_var = 0;

    // Create a parallel region with 4 gangs in all dimensions
    #pragma acc parallel num_gangs(4) private(private_var)
    {
        // Each gang has its own copy of the private variable
        private_var = rand();

        // Do some work with the private variable
        std::cout << "Gang " << acc_get_gang_id() << " has private variable " << private_var << std::endl;
    }

    return err;
}