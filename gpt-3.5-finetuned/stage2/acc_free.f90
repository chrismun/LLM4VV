!T1:acc free,V:2.7-2.3
      LOGICAL FUNCTION test1()
        USE OPENACC
        IMPLICIT NONE
        INCLUDE "acc_testsuite.Fh"
        
        INTEGER :: errors = 0

        ! Allocate memory using acc_malloc
        REAL(8), DIMENSION(LOOPCOUNT) :: a
        INTEGER :: x
        DO x = 1, LOOPCOUNT
          a(x) = x
        END DO
        !$acc enter data copyin(a(1:LOOPCOUNT))
        !$acc enter data copyin(a(1:LOOPCOUNT))

        ! Free memory using acc_free
        CALL acc_free(acc_ptr(a(1)))

        !$acc exit data copyout(a(1:LOOPCOUNT))
        DO x = 1, LOOPCOUNT
          IF (a(x) .ne. x) THEN
            errors = errors + 1
          END IF
        END DO

        IF (errors .eq. 0) THEN
          test1 = .FALSE.
        ELSE
          test1 = .TRUE.
        END IF
      END

      PROGRAM main
        IMPLICIT NONE
        INTEGER :: failcode, testrun
        LOGICAL :: failed
        INCLUDE "acc_testsuite.Fh"
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
        CALL EXIT (failcode)
      END PROGRAM