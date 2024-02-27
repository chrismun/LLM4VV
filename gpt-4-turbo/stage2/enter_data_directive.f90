module test_utilities
  use openacc
  implicit none
contains
  ! Function to check if arrays are equal
  logical function arrays_equal(a, b)
    integer, dimension(:), intent(in) :: a, b
    arrays_equal = all(a == b)
  end function arrays_equal
end module test_utilities

!T1:enter data directive,V:2.7-2.3
logical function test_enter_data()
  use openacc
  use test_utilities
  implicit none
  include "acc_testsuite.Fh"

  integer, dimension(10) :: host_array, device_array
  integer :: i, errors

  ! Initialize test variables
  errors = 0
  host_array = [(i, i=1, 10)]
  device_array = 0

  ! Enter data to device
  !$acc enter data copyin(host_array)

  ! Perform a dummy operation on the device array
  !$acc parallel loop copy(device_array)
  do i=1, 10
    device_array(i) = host_array(i) + 1
  end do
 
  ! Copy back the modified array to the host
  !$acc exit data copyout(device_array)
  
  ! Check if the operation succeeded
  if (.not. arrays_equal(device_array, host_array + 1)) then
    errors = errors + 1
  endif
  
  ! Return 0 if no errors, non-zero otherwise
  if (errors == 0) then
    test_enter_data = .false.
  else
    test_enter_data = .true.
  end if
end function test_enter_data

program main
  use test_utilities
  implicit none
  integer :: failcode, testrun
  logical :: failed
  include "acc_testsuite.Fh"

  failed = .false.
  failcode = 0

  ! Execute the test for 'enter data' directive
  failed = failed .or. test_enter_data()
  
  if (failed) then
    failcode = failcode + 2**0
    failed = .false.
  endif
  
  call exit(failcode)
end program main