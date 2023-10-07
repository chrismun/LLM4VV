#ifndef T1
!T1:acc async test,V:2.7-2.3
      LOGICAL FUNCTION test1()
        USE OPENACC
        IMPLICIT NONE
        INCLUDE "acc_testsuite.Fh"
        
        INTEGER :: errors = 0
        INTEGER(ACC_HANDLE_KIND) :: async1, async2
        REAL(8), DIMENSION(:), ALLOCATABLE :: a, b, c
        INTEGER :: i

        ALLOCATE(a(10), b(10), c(10))
        a = 1.0
        b = 2.0
        c = 0.0

        !$acc enter data copyin(a, b, c)

        !$acc parallel async(async1)
        DO i = 1, 10
          c(i) = a(i) + b(i)
        END DO
        !$acc end parallel

        !$acc parallel async(async2)
        DO i = 1, 10
          c(i) = c(i) * 2
        END DO
        !$acc end parallel

        !$acc wait(async1)
        !$acc wait(async2)

        !$acc update self(c)

        DO i = 1, 10
          IF (c(i) .ne. (a(i) + b(i)) * 2) THEN
            errors = errors + 1
          END IF
        END DO

        !$acc exit data delete(a, b, c)

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