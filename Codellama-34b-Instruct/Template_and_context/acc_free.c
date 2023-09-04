#include <stdlib.h>
#include <stdio.h>

void acc_free(void *data_dev) {
    if (data_dev == NULL) {
        return;
    }

    free(data_dev);
}

int main() {
    void *data_dev = acc_malloc(100);
    if (data_dev == NULL) {
        printf("Error: failed to allocate memory\n");
        return 1;
    }

    acc_free(data_dev);

    return 0;
}