! OpenACC test for loop construct with collapse clause in Fortran
module acc_testsuite
  implicit none
  integer, parameter :: N = 10, M = 10
  ! This constant defines the expected dimension for the collapsed loop
contains
  logical function test1()
    use openacc
    implicit none
    real, dimension(N, M) :: A
    integer :: i, j, errors

    ! Initialize errors count
    errors = 0

    ! Parallelize and collapse the nested loops
    !$acc parallel loop collapse(2)
    do i = 1, N
      do j = 1, M
        A(i, j) = real(i * j)
      end do
    end do

    ! Verification
    do i = 1, N
      do j = 1, M
        ! Check if each element in A matches the expected value
        if (A(i, j) /= real(i * j)) then
          errors = errors + 1
        end if
      end do
    end do

    ! Determine the result based on error count
    if (errors == 0) then
      test1 = .false.
    else
      test1 = .true.
    end if
  end function test1
end module acc_testsuite

program main
  use acc_testsuite
  implicit none
  logical :: failed
  integer :: failcode

  ! Initialize
  failed = .false.
  failcode = 0

  ! Running test1 and updating failed flag based on its return
  failed = test1()

  ! Set failcode based on the failed flag
  if (failed) then
    failcode = failcode + 1
  end if

  ! Exit the program with the failcode
  call exit(failcode)
end program main