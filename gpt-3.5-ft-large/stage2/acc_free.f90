#ifndef T1
!T1:acc free,V:2.7-2.3
      LOGICAL FUNCTION test1()
        USE OPENACC
        IMPLICIT NONE
        INCLUDE "acc_testsuite.Fh"
        
        INTEGER :: errors = 0
        REAL(8), ALLOCATABLE :: a, a_copy
        INTEGER :: n 
        n = 100
        ALLOCATE(a(n), a_copy(n))

        CALL srand48(SEED)
        a = 4365.3244 * drand48()
        a_copy = a

        !$acc enter data copyin(a(1:n))
        !$acc parallel present(a(1:n))
          !$acc loop
          DO test_loop = 1, n
            a(test_loop) = a(test_loop) * TEST_LOOP
          END DO
        !$acc end parallel

        CALL acc_free(a(1))

        DO test_loop = 1, n
          IF (abs(a(test_loop) - a_copy(test_loop)) gt PRECISION) THEN
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