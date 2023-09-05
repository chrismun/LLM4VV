int test_host_data_if_present() {
    int err = 0;
    int *a, *b;
    int size = 10;

    a = (int*)malloc(size * sizeof(int));
    b = (int*)malloc(size * sizeof(int));

    for (int i = 0; i < size; i++) {
        a[i] = i;
        b[i] = 0;
    }

    // Host_data directive with if_present clause
    #pragma acc host_data use_device(a[0:size]) if_present(b[0:size])
    {
        for (int i = 0; i < size; i++) {
            b[i] = a[i] * 2;
        }
    }

    for (int i = 0; i < size; i++) {
        if (b[i] != a[i] * 2) {
            printf("Mismatch at index %d\n", i);
            err++;
        }
    }

    free(a);
    free(b);

    return err;
}

int main() {
    int fail = 0;
    fail += test_host_data_if_present();
    return fail;
}