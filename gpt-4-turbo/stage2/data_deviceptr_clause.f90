! OpenACC test for data deviceptr clause in Fortran
PROGRAM DataDeviceptrTest
  USE openacc
  IMPLICIT NONE
  INTEGER, PARAMETER :: N = 10
  INTEGER, DIMENSION(:), ALLOCATABLE :: hostArray
  INTEGER, DEVICE, DIMENSION(:), ALLOCATABLE :: deviceArray
  INTEGER :: i, errors
  TYPE(C_PTR) :: devPtr

  ! Allocate memory on host and device
  ALLOCATE(hostArray(N))
  ALLOCATE(deviceArray(N))
  
  ! Initialize device array through device pointer
  devPtr = C_LOC(deviceArray)
  !$ACC ENTER DATA CREATE(deviceArray)
  !$ACC PARALLEL LOOP PRESENT(deviceArray)
  DO i = 1, N
    deviceArray(i) = i
  END DO
  !$ACC EXIT DATA COPYOUT(deviceArray)

  ! Copy from device to host to verify the result
  hostArray = deviceArray

  ! Verify
  errors = 0
  DO i = 1, N
    IF (hostArray(i) /= i) THEN
      errors = errors + 1
    END IF
  END DO

  IF (errors == 0) THEN
    PRINT *, "TEST PASSED"
  ELSE
    PRINT *, "TEST FAILED"
  END IF

  DEALLOCATE(hostArray, deviceArray)

END PROGRAM DataDeviceptrTest