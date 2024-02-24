program main
  use openacc
  implicit none
  integer, parameter :: N = 100
  integer :: a(N), i, errors
  logical :: failed

  ! Initialize the array
  do i = 1, N
    a(i) = i
  end do

  !$acc data copyin(a) copyout(a)
  !$acc declare present(a)
  !$acc parallel loop
  do i = 1, N
    a(i) = a(i) * 2
  end do
  !$acc end parallel loop
  !$acc end data

  ! Check the results
  errors = 0
  do i = 1, N
    if (a(i) /= i*2) then
      errors = errors + 1
    end if
  end do

  if (errors == 0) then
    print *, "Test passed."
  else
    print *, "Test failed with ", errors, " errors."
  end if

end program main