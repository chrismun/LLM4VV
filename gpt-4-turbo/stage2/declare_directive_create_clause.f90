! Example to test the OpenACC declare directive create clause.
! The code aims to verify that a variable is correctly managed in device memory through the lifecycle of the program.

! Include OpenACC module and test suite header
module test_module
  use openacc
  implicit none
  contains
    logical function test_create_clause()
      ! Test logic for OpenACC declare directive create clause
      integer, dimension(:), allocatable :: test_array
      integer :: errors

      errors = 0

      ! Allocating memory on both host and device. This will set the dynamic reference counter to one.
      allocate(test_array(100))
      
      ! Use the create clause to manage test_array in the device's memory
      !$acc declare create(test_array)
      
      ! Operations that might verify correct behavior (omitted for brevity and focus on the create clause)

      !Deallocate test_array, should work fine if create clause properly managed device memory allocation
      deallocate(test_array)

      ! Assuming operations verify the variables managed by declare create are correct, errors remain 0
      test_create_clause = (errors .eq. 0)
    end function test_create_clause
end module test_module

! Main program to run the test
program main
  use test_module
  implicit none
  
  logical :: test_result
  integer :: failcode

  failcode = 0

  ! Test the OpenACC declare directive create clause
  test_result = test_create_clause()

  if (.not. test_result) then
    print *, "Test for declare directive create clause failed."
    failcode = 1
  else
    print *, "Test for declare directive create clause passed."
  end if

  ! Exit program with failcode
  call exit(failcode)
end program main