#ifndef T1
!T1:exit data directive,V:2.7-2.3
      LOGICAL FUNCTION test1()
        USE OPENACC
        IMPLICIT NONE
        INCLUDE "acc_testsuite.Fh"
        
        INTEGER :: errors = 0
        INTEGER, PARAMETER :: N = 100
        INTEGER :: i, a(N), b(N)

        ! Initialize arrays
        DO i = 1, N
          a(i) = i
          b(i) = 0
        END DO

        ! Copy array to device
        CALL acc_enter_data(a, N)

        ! Modify array on device
        !$acc parallel loop copyout(a)
        DO i = 1, N
          a(i) = a(i) * 2
        END DO

        ! Copy array back to host
        !$acc exit data copyout(a)

        ! Check results
        DO i = 1, N
          IF (a(i) .ne. i * 2) THEN
            errors = errors + 1
          END IF
        END DO

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