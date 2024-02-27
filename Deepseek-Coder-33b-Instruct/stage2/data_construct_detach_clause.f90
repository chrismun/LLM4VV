!T1:data construct detach clause,V:2.7-2.3
      LOGICAL FUNCTION test1()
        USE OPENACC
        IMPLICIT NONE
        INCLUDE "acc_testsuite.Fh"
        
        INTEGER :: errors = 0
        INTEGER, TARGET :: a(10)
        INTEGER, POINTER :: p(:)

        ! Initialize the array
        a = 1

        ! Associate the pointer with the array
        p => a

        !$acc data copy(p)
        !$acc parallel loop
        DO i = 1, 10
          p(i) = i
        END DO
        !$acc end parallel loop
        !$acc end data

        ! Detach the pointer
        !$acc detach(p)

        ! Try to access the array through the pointer
        ! This should not crash the program
        ! If the detach clause is working properly, this should not cause a segfault
        DO i = 1, 10
          IF (p(i) .ne. i) THEN
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