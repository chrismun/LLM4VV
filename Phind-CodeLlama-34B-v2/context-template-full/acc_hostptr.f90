#ifndef T1
!T1:acc hostptr,V:2.7-2.3
      LOGICAL FUNCTION test1()
        USE OPENACC
        IMPLICIT NONE
        INCLUDE "acc_testsuite.Fh"
        
        INTEGER :: errors = 0
        TYPE(C_PTR) :: host_ptr, device_ptr
        REAL, POINTER :: host_array(:)
        INTEGER :: i

        ALLOCATE(host_array(10))
        DO i = 1, 10
          host_array(i) = i
        END DO

        device_ptr = acc_copyin(host_array, SIZEOF(host_array))
        host_ptr = acc_hostptr(device_ptr)

        IF (C_ASSOCIATED(host_ptr)) THEN
          IF (C_LOC(host_array) .NE. C_LOC(host_ptr)) THEN
            errors = errors + 1
          END IF
        ELSE
          errors = errors + 1
        END IF

        CALL acc_delete(device_ptr, SIZEOF(host_array))
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
      END PROGRAM