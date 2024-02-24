#include <stdio.h>
#include <stdlib.h>
#include <openacc.h>

int main() {
    int *ptr = (int*)malloc(sizeof(int));
    *ptr = 10;

    // Attach the pointer to the device
    acc_attach((void**)&ptr);

    // Check the attachment counter
    int count = acc_get_attachment_count(ptr);
    printf("Attachment counter after attaching: %d\n", count);

    // Detach the pointer from the device
    acc_detach((void**)&ptr);

    // Check the attachment counter
    count = acc_get_attachment_count(ptr);
    printf("Attachment counter after detaching: %d\n", count);

    free(ptr);

    return 0;
}