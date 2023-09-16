This code tests the copyout clause in the OpenACC kernels directive. The copyout clause specifies an array to be copied from the device to the host upon exiting the kernels directive. This test copies an input array to the device, performs a simple operation (copying values to a new array), then copies the result back to the host. Then, the host checks the returned results against the expected ones, and increments an error counter if a mismatch is found. This test repeats for a number of calls, which can be adjusted by changing the NUM_TEST_CALLS value. The error counter is returned, so you'll know if there is any problem with the copyout clause implementation.

To compile and run this test, you'll need an OpenACC-capable compiler (like PGI's pgcc, or gnu's gcc with OpenACC support).

Compilation might look like this:
pgcc -acc -fast -ta=tesla:test -Minfo=accel test_copyout.c -o test_copyout.out

Run the test with:
./test_copyout.out

If it returns 0, the copyout clause is implemented correctly, if not, then there are problems with the current implementation of the copyout clause in the OpenACC kernels directive by the compiler.