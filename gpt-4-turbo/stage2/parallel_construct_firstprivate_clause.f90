! First, compile this code with an OpenACC-capable Fortran compiler
! Use the following command (assuming you are using the PGI compiler):
! pgfortran -acc -Minfo=acc -o test_firstprivate test_firstprivate.f90

module acc_testsuite
  use openacc
  implicit none
contains
  logical function test1()
    implicit none
    integer, parameter :: n = 100
    integer :: i, x, errors
    integer :: outArray(n)

    errors = 0
    x = 5

    ! Initialize array
    outArray(:) = 0

    ! Use firstprivate to ensure each thread gets its own private copy of x
    !$acc parallel loop firstprivate(x)
    do i = 1, n
      x = x + i  ! Modify x in each iteration
      outArray(i) = x
    end do
    !$acc end parallel loop

    ! Check if outArray elements match the expected values (x+index)
    ! This checks if `x` was firstprivate and its changes were local to each thread
    do i = 1, n
      if (outArray(i) /= 5 + i) then
        errors = errors + 1
      end if
    end do

    if (errors .eq. 0) then
      test1 = .true.
    else
      test1 = .false.
    end if
  end function test1
end module acc_testsuite

program main
  use acc_testsuite
  implicit none
  logical :: failed
  failed = .false.

  ! Running the test
  if (.not. test1()) then
    write(*,*) "Test failed"
    failed = .true.
  else
    write(*,*) "Test passed"
  endif

  if (failed) then
    stop 1
  else
    stop 0
  end if
end program main