! This Fortran program demonstrates a test for the acc_set_device_type functionality in OpenACC.

module openacc_test
  use openacc
  implicit none

contains
  logical function test_set_device_type()
    integer(acc_device_kind) :: devType
    integer :: iError

    test_set_device_type = .false.

    ! Attempt to set the device type to an NVIDIA GPU.
    devType = acc_device_nvidia
    call acc_set_device_type(devType)

    ! Check for errors.
    iError = acc_get_device_type()
    if (iError /= devType) then
      print*, "Error: acc_set_device_type couldn't set the device to NVIDIA GPU."
      test_set_device_type = .true.
    end if

  end function test_set_device_type

end module openacc_test

program main
  use openacc_test
  implicit none
  logical :: testResult

  ! Run the test for acc_set_device_type.
  testResult = test_set_device_type()

  ! Based on the result, exit with 0 (success) or non-zero (failure).
  if (testResult) then
    print*, "Test FAILED"
    stop 1
  else
    print*, "Test PASSED"
    stop 0
  endif

end program main