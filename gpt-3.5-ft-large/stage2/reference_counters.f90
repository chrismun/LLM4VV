#ifndef T1
!T1:reference counters,V:2.7-2.3
      LOGICAL FUNCTION test1()
        USE OPENACC
        IMPLICIT NONE
        INCLUDE "acc_testsuite.Fh"
        
        INTEGER :: errors = 0
        REAL(8), ALLOCATABLE, DIMENSION(:,:) :: a, b, c, d
        INTEGER :: x, y
      
        ALLOCATE(a(10, 10), b(10, 10), c(10, 10), d(10, 10))
        !initiliaze arrays
        a = 0
        b = 0
        c = 0
        d = 0
        a(1, 1) = 1
        b(1, 1) = 1
        c(1, 1) = 1

        !$acc enter data copyin(a(1:10, 1:10), b(1:10, 1:10), c(1:10, 1:10)) create(d(1:10, 1:10))
        DO x = 1, 10
          DO y = 1, 10
            d(x, y) = a(x, y) + b(x, y) + c(x, y)
          END DO
        END DO
        !$acc exit data delete(d(1:10, 1:10))
        DO x = 1, 10
          DO y = 1, 10
            IF (d(x, y) .NE. a(x, y) + b(x, y) + c(x, y)) THEN
              errors = errors + 1
            END IF
          END DO
        END DO

        DEALLOCATE(a, b, c, d)

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