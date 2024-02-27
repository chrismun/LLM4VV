MODULE acc_test_mod
  USE ISO_C_BINDING
  USE OPENACC
  IMPLICIT NONE
  CONTAINS
!T1:acc memcpy to device,V:2.7-2.3
  LOGICAL FUNCTION test1()
    INTEGER, PARAMETER :: N = 10
    REAL, DIMENSION(N) :: hostArray
    REAL, DIMENSION(:), POINTER :: deviceArray
    INTEGER(C_SIZE_T) :: bytes
    INTEGER :: i, errors

    ! Initialize test conditions
    errors = 0

    ! Initialize hostArray
    DO i = 1, N
      hostArray(i) = REAL(i)
    END DO

    ! Allocate memory on the device
    bytes = N * SIZEOF(hostArray(1))
    deviceArray = C_F_POINTER(acc_malloc(bytes), SHAPE=[N])

    ! Copy data from host to device
    CALL acc_memcpy_to_device(deviceArray, hostArray, bytes)

    ! Verify the copy using a device operation (pseudo code, relies on compiler/runtime support)
    !$acc parallel loop copyin(deviceArray(:N)) reduction(+:errors)
    DO i = 1, N
      IF (deviceArray(i) /= REAL(i)) THEN
        errors = errors + 1
      END IF
    END DO
    !$acc end parallel loop

    ! Cleanup
    CALL acc_free(C_LOC(deviceArray))

    ! Set return value based on errors count
    IF (errors == 0) THEN
      test1 = .FALSE.
    ELSE
      test1 = .TRUE.
    END IF
  END FUNCTION test1
END MODULE acc_test_mod

PROGRAM main
  USE acc_test_mod
  IMPLICIT NONE
  INTEGER :: failcode, testrun
  LOGICAL :: failed
  LOGICAL :: test1

  failed = .FALSE.
  failcode = 0

  DO testrun = 1, NUM_TEST_CALLS
    failed = failed .or. test1()
  END DO
  IF (failed) THEN
    failcode = failcode + 2 ** 0
    failed = .FALSE.
  END IF

  CALL EXIT(failcode)
END PROGRAM main