#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <acc_runtime.h>

int main() {
    acc_device_t device_type;
    int device_id;

    // Get the device type and device ID
    device_type = acc_get_device_type();
    device_id = acc_get_device_id();

    // Print the device type and device ID
    printf("Device type: %s\n", acc_device_type_to_string(device_type));
    printf("Device ID: %d\n", device_id);

    // Check if the device type is supported
    if (device_type == acc_device_none) {
        printf("Device type is not supported\n");
        return 1;
    }

    // Check if the device ID is valid
    if (device_id < 0 || device_id >= acc_get_num_devices()) {
        printf("Device ID is not valid\n");
        return 1;
    }

    // Check if the device is available
    if (!acc_device_is_available(device_id)) {
        printf("Device is not available\n");
        return 1;
    }

    // Check if the device is a GPU
    if (device_type == acc_device_gpu) {
        printf("Device is a GPU\n");
    } else {
        printf("Device is not a GPU\n");
    }

    // Check if the device is a CPU
    if (device_type == acc_device_cpu) {
        printf("Device is a CPU\n");
    } else {
        printf("Device is not a CPU\n");
    }

    // Check if the device is a NVIDIA GPU
    if (device_type == acc_device_nvidia_gpu) {
        printf("Device is a NVIDIA GPU\n");
    } else {
        printf("Device is not a NVIDIA GPU\n");
    }

    // Check if the device is a AMD GPU
    if (device_type == acc_device_amd_gpu) {
        printf("Device is a AMD GPU\n");
    } else {
        printf("Device is not a AMD GPU\n");
    }

    // Check if the device is a Intel GPU
    if (device_type == acc_device_intel_gpu) {
        printf("Device is a Intel GPU\n");
    } else {
        printf("Device is not a Intel GPU\n");
    }

    // Check if the device is a ARM GPU
    if (device_type == acc_device_arm_gpu) {
        printf("Device is a ARM GPU\n");
    } else {
        printf("Device is not a ARM GPU\n");
    }

    // Check if the device is a IBM GPU
    if (device_type == acc_device_ibm_gpu) {
        printf("Device is a IBM GPU\n");
    } else {
        printf("Device is not a IBM GPU\n");
    }

    // Check if the device is a NVIDIA GPU with CUDA
    if (device_type == acc_device_nvidia_gpu_cuda) {
        printf("Device is a NVIDIA GPU with CUDA\n");
    } else {
        printf("Device is not a NVIDIA GPU with CUDA\n");
    }

    // Check if the device is a AMD GPU with OpenCL
    if (device_type == acc_device_amd_gpu_opencl) {
        printf("Device is a AMD GPU with OpenCL\n");
    } else {
        printf("Device is not a AMD GPU with OpenCL\n");
    }

    // Check if the device is a Intel GPU with OpenCL
    if (device_type == acc_device_intel_gpu_opencl) {
        printf("Device is a Intel GPU with OpenCL\n");
    } else {
        printf("Device is not a Intel GPU with OpenCL\n");
    }

    // Check if the device is a ARM GPU with OpenCL
    if (device_type == acc_device_arm_gpu_opencl) {
        printf("Device is a ARM GPU with OpenCL\n");
    } else {
        printf("Device is not a ARM GPU with OpenCL\n");
    }

    // Check if the device is a IBM GPU with OpenCL
    if (device_type == acc_device_ibm_gpu_opencl) {
        printf("Device is a IBM GPU with OpenCL\n");
    } else {
        printf("Device is not a IBM GPU with OpenCL\n");
    }

    return 0;
}