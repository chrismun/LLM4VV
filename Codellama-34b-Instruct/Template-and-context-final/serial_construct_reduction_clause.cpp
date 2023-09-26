#include <iostream>
#include <cstdlib>

int main() {
    int arr[10];
    int sum = 0;

    #pragma acc serial reduction(+:sum)
    for (int i = 0; i < 10; i++) {
        arr[i] = i;
        sum += arr[i];
    }

    std::cout << "Sum: " << sum << std::endl;

    return 0;
}