#ifndef T1
!T1:acc update self,V:2.7-2.3
      LOGICAL FUNCTION test1()
        USE OPENACC
        IMPLICIT NONE
        INCLUDE "acc_testsuite.Fh"
        
        INTEGER :: errors = 0
        INTEGER, DIMENSION(10) :: a, b
        INTEGER :: i

        ! Initialize arrays
        DO i = 1, 10
          a(i) = i
          b(i) = 0
        END DO

        !$acc enter data copyin(a(1:10))
        !$acc parallel present(a, b)
          !$acc loop
          DO i = 1, 10
            b(i) = a(i)
          END DO
        !$acc end parallel

        !$acc update self(b(1:10))

        !$acc exit data delete(a)

        ! Check if arrays are equal
        DO i = 1, 10
          IF (a(i) .NE. b(i)) THEN
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