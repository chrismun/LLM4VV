! make sure to adapt the include path to your specific case
#include "acc_testsuite.F"

! you can tune the array size if the test lasts too long on your system, but be sure to make it fairly large
#define N 1000000

logical function test_serial_if_clause()
implicit none

! declare variables
real, dimension(N) :: test
integer, dimension(N) :: seq
integer :: i
integer :: errors = 0
integer :: deviceNum

! initialize host array
do i=1,N
  seq(i) = i
End do

deviceNum = get_current_device_num()

! if clause with true condition; computation will execute on the device
! making sure your device is present or this line will cause an error
! the region will execute on the current device
#pragma acc parallel copyin(seq) copyout(test) if(deviceNum == get_current_device_num())
do i = 1, N
    test(i) = seq(i) * 2.0
end do

! host verification step; add errors for incorrect results
do i=1,N
    if (abs(test(i) - 2.0*seq(i)) > 1e-4) then
        errors = errors + 1
    end if
end do

! if clause with false condition; computation will execute on the host
! the local thread will execute the region
#pragma acc parallel copyin(seq) copyout(test) if(.false.)
do i = 1, N
    test(i) = seq(i) * 3.0
end do

! host verification step; add errors for incorrect results
do i=1,N
    if (abs(test(i) - 3.0*seq(i)) > 1e-4) then
        errors = errors + 1
    end if
end do

if (errors==0) then
    test_serial_if_clause = .true.
else
    test_serial_if_clause = .false.
end if

end function test_serial_if_clause

program main
implicit none
integer :: failcode = 0

if (.not. test_serial_if_clause()) then
  failcode = failcode + 1
end if

call exit(failcode)
end program main