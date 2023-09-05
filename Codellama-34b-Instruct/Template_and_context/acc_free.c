#include <stdlib.h>
#include <stdio.h>

void acc_free(void *data_dev) {
    if (data_dev == NULL) {
        return;
    }

    free(data_dev);
}

int main() {
    void *data_dev = malloc(100);
    acc_free(data_dev);
    return 0;
}