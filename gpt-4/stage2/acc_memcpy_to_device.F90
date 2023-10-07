#ifndef T1
!T1:acc memcpy to device,V:2.7-2.3
  LOGICAL FUNCTION test1()
    USE ISO_C_BINDING
    USE OPENACC
    IMPLICIT NONE
    INCLUDE "acc_testsuite.Fh"
    INTEGER, DIMENSION(:), ALLOCATABLE :: host_array
    INTEGER, TARGET, DIMENSION(100) :: dev_array
    INTEGER(C_SIZE_T) :: bytes, i
    TYPE(C_PTR) :: ptr
    INTEGER :: errors = 0
    bytes = 100
    ALLOCATE(host_array(bytes))
    DO i = 1, bytes
      host_array(i) = i
    END DO
    ptr = acc_deviceptr(dev_array) 
    CALL acc_memcpy_to_device(ptr, host_array, bytes*C_SIZEOF(host_array(1)))

    ! Check if the data was copied correctly
    errors = errors + sum((dev_array - host_array) ** 2)
    DEALLOCATE(host_array)

    IF (errors .eq. 0) THEN
      test1 = .FALSE.
    ELSE
      test1 = .TRUE.
    END IF
  END
#endif

PROGRAM main
  IMPLICIT NONE
  INTEGER :: failcode, testrun
  LOGICAL :: failed
  INCLUDE "acc_testsuite.Fh"
#ifndef T1
  LOGICAL :: test1
#endif
  failed = .FALSE.
  failcode = 0
#ifndef T1
  DO testrun = 1, NUM_TEST_CALLS
    failed = failed .or. test1()
  END DO
  IF (failed) THEN
    failcode = failcode + 2 ** 0
    failed = .FALSE.
  END IF
#endif
  CALL EXIT (failcode)
END PROGRAM main