#ifndef T1
!T1:parallel construct vector_length clause,V:2.7-2.3
      LOGICAL FUNCTION test1()
        USE OPENACC
        IMPLICIT NONE
        INCLUDE "acc_testsuite.Fh"
        
        INTEGER :: errors = 0
        REAL(8),DIMENSION, ALLOCATABLE :: a, b, c
        INTEGER :: x

        ALLOCATE(a(10), b(10), c(10))

        a = 0
        b = 0

        !$acc data copyin(a(1:10), b(1:10)) copyout(c(1:10))
          !$acc parallel vector_length(4)
            !$acc loop vector
            DO x = 1, 10
              a(x) = x
            END DO
            !$acc loop vector
            DO x = 1, 10
              b(x) = x
            END DO
            !$acc loop vector_length(2) seq
            DO x = 1, 10
              c(x) = a(x) + b(x)
            END DO
          !$acc end parallel
        !$acc end data

        DO x = 1, 10
          IF (c(x) .ne. 2 * x) THEN
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