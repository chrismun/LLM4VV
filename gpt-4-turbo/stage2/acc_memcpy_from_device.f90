!--------------------------------------------------------------------------------
! Test Code: acc_memcpy_from_device in Fortran
! Description: This program tests the OpenACC acc_memcpy_from_device function
!              by copying an array from device memory back to the host and
!              verifying its contents.
!--------------------------------------------------------------------------------

! File: acc_memcpy_from_device_test.F90
program acc_memcpy_from_device_test
    use iso_c_binding
    use openacc
    implicit none
    integer, parameter :: n = 10
    integer, dimension(n) :: host_array
    type(c_ptr) :: device_ptr
    integer(c_size_t) :: bytes
    integer :: i, errors

    ! Initialization
    errors = 0
    do i = 1, n
        host_array(i) = 0
    end do
    
    ! Allocate memory on the device
    bytes = n*size_of(host_array(1))
    device_ptr = acc_malloc(bytes)

    ! Prepare data on the device
    !$acc parallel loop copyout(host_array) deviceptr(device_ptr)
    do i = 1, n
        host_array(i) = i
    end do

    ! Copy data from device to host
    call acc_memcpy_from_device(host_array, device_ptr, bytes)
    
    ! Verify the copied data
    do i = 1, n
        if (host_array(i) /= i) then
            errors = errors + 1
            print*, "Mismatch at index ", i, ": Expected ", i, ", Found ", host_array(i)
        endif
    end do

    ! Clean up
    call acc_free(device_ptr)

    ! Report results
    if (errors == 0) then
        print*, "Test PASSED: all elements match."
    else
        print*, "Test FAILED: there were ", errors, " mismatches."
    endif

end program acc_memcpy_from_device_test