#ifndef T1
!T1:exit data directive,V:2.7-2.3
      LOGICAL FUNCTION test1()
        USE OPENACC
        IMPLICIT NONE
        INCLUDE "acc_testsuite.Fh"
        
        INTEGER :: errors = 0
        REAL(8), DIMENSION(:), ALLOCATABLE :: a, b
        INTEGER :: n

        n = 1024
        ALLOCATE(a(n), b(n))

        !$acc enter data copyin(a(1:n), b(1:n))
        !$acc parallel present(a, b)
          !$acc loop
          DO i = 1, n
            a(i) = 3.14
            b(i) = 2.71
          END DO
        !$acc end parallel

        !$acc exit data delete(a(1:n), b(1:n))

        !$acc enter data copyin(a(1:n), b(1:n))
        !$acc parallel present(a, b)
          !$acc loop
          DO i = 1, n
            a(i) = a(i) + b(i)
          END DO
        !$acc end parallel

        !$acc exit data delete(a(1:n), b(1:n))

        !$acc update host(a(1:n))

        DO i = 1, n
          IF (a(i) .ne. 5.85) THEN
            errors = errors + 1
          END IF
        END DO

        DEALLOCATE(a, b)

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