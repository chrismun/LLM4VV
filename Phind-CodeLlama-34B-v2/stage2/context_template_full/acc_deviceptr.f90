#ifndef T1
!T1:acc deviceptr,V:2.7-2.3
      LOGICAL FUNCTION test1()
        USE OPENACC
        IMPLICIT NONE
        INCLUDE "acc_testsuite.Fh"
        
        INTEGER :: errors = 0
        REAL(8), DIMENSION(:), ALLOCATABLE :: host_array, device_array
        TYPE(C_PTR) :: device_ptr

        ALLOCATE(host_array(10))
        host_array = 1.0

        !$acc enter data copyin(host_array)
        !$acc parallel present(host_array)
          device_ptr = acc_deviceptr(host_array)
          IF (C_ASSOCIATED(device_ptr)) THEN
            ALLOCATE(device_array(SIZE(host_array)))
            !$acc enter data create(device_array)
            !$acc update device(device_array)
            device_array = 2.0
            !$acc update host(device_array)
            !$acc exit data delete(device_array)
          ELSE
            errors = errors + 1
          END IF
        !$acc end parallel
        !$acc exit data delete(host_array)

        IF (ALLOCATED(device_array)) THEN
          IF (ALL(device_array == 2.0)) THEN
            DEALLOCATE(device_array)
          ELSE
            errors = errors + 1
          END IF
        END IF

        IF (errors .eq. 0) THEN
          test1 = .FALSE.
        ELSE
          test1 = .TRUE.
        END IF
      END FUNCTION test1
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
      END PROGRAM