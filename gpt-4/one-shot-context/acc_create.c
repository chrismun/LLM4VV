python
import ctypes
import numpy as np
import os

# Load the OpenACC shared libraries
lib = ctypes.CDLL('libopenacc.so')

# Create a numpy array (native Python object)
data_in_host = np.ones(10000, dtype=np.float32)

# Get the pointer to the data in host memory
data_ptr = data_in_host.ctypes.data_as(ctypes.POINTER(ctypes.c_float))

# Define the size of the data
size_of_data = ctypes.c_size_t(data_in_host.nbytes)

# Using acc_create, create space on the device without initializing
lib.acc_create(data_ptr, size_of_data)

# Using acc_copyin, copy the data from the host to the device
lib.acc_copyin(data_ptr, size_of_data)

# Validate if the implementation works, by checking the data on the device
# First allocate array in host memory to hold the result
result_on_host = np.zeros_like(data_in_host)

# Get a pointer to the result
result_ptr = result_on_host.ctypes.data_as(ctypes.POINTER(ctypes.c_float))

# Copy the data from device to host
lib.acc_copyout(result_ptr , size_of_data)

# Now 'result_on_host' should contain same values as 'data_in_host'
# Validate if this is true
if np.array_equal(data_in_host, result_on_host):
    print("Test Passed")
else:
    print("Test Failed")

# Clear the device memory
lib.acc_delete(data_ptr, size_of_data)