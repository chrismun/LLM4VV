#include <stdbool.h>
#include <stddef.h>

#define ACC_DEVICE_HOST 0
#define ACC_DEVICE_NOT_HOST 1
#define ACC_DEVICE_DEFAULT 2

bool acc_on_device(int dev_type) {
    switch (dev_type) {
        case ACC_DEVICE_HOST:
            return true;
        case ACC_DEVICE_NOT_HOST:
            return false;
        case ACC_DEVICE_DEFAULT:
            return true;
        default:
            return false;
    }
}