program test_acc_wait_any
  use openacc
  implicit none

  integer, parameter :: n = 1000
  integer :: i, async1, async2, wait_arg(2), count, dev_num
  real :: a(n), b(n), c(n)

  ! Initialize data
  do i = 1, n
    a(i) = i
    b(i) = i * 2
  end do

  ! Start asynchronous tasks
  !$acc parallel async(1) copyin(a) copyout(c)
  async1 = acc_get_async_info()
  c(:) = a(:)
  !$acc end parallel

  !$acc parallel async(2) copyin(b) copyout(c)
  async2 = acc_get_async_info()
  c(:) = c(:) + b(:)
  !$acc end parallel

  ! Wait for any of the tasks to complete
  wait_arg(1) = async1
  wait_arg(2) = async2
  count = 2
  dev_num = acc_get_device_num(acc_device_nvidia)
  call acc_wait_any_device(count, wait_arg, dev_num)

  ! Check the result
  do i = 1, n
    if (c(i) .ne. 3 * i) then
      print *, "Test failed"
      stop 1
    end if
  end do

  print *, "Test passed"
end program test_acc_wait_any