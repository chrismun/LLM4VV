! This code example is designed to test the OpenACC 'parallel construct num_gangs clause'.
! It initializes an array and uses an OpenACC parallel region to modify the array
! elements. The success of various operations indicates proper handling of the num_gangs clause.

module testsuite_helpers
  use openacc
  implicit none
contains
  logical function test1()
    implicit none
    integer, parameter :: N = 1024
    integer :: i
    integer, dimension(N) :: a
    integer :: num_gangs_tested
    integer :: errors = 0
    
    ! Initialize array
    a = 0
    
    ! Choose an arbitrary number of gangs for test purposes
    num_gangs_tested = 128
    
    ! Use OpenACC parallel construct with num_gangs clause
    !$acc parallel loop num_gangs(num_gangs_tested)
    do i = 1, N
      a(i) = i
    end do
    
    ! Check results -- Simplistic check assuming uniform distribution of work
    do i = 1, N
      if (a(i) /= i) errors = errors + 1
    end do
    
    ! Determine the outcome based on errors found
    if (errors == 0) then
      test1 = .false.
    else
      test1 = .true.
    end if
  end function test1
  
end module testsuite_helpers

program main
  use testsuite_helpers
  implicit none
  logical :: failed
  integer :: failcode, testrun
  
  failed = .false.
  failcode = 0
  
  do testrun = 1, 1   ! Assuming a singular test run for this example
    failed = failed .or. test1()
  end do
  
  if (failed) then
    failcode = failcode + 2 ** 0
  end if
  
  call exit(failcode)
end program main