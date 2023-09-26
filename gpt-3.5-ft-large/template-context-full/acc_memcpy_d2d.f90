#ifndef T1
!T1:acc memcpy d2d,V:2.7-2.3
      LOGICAL FUNCTION test1()
        USE OPENACC
        IMPLICIT NONE
        INCLUDE "acc_testsuite.Fh"
        
        INTEGER :: errors = 0
        REAL(3),DIMENSION(10):: a, b, c
        INTEGER, DIMENSION(1) :: devtest
        REAL(8)
        INTEGER :: device_num
        
        devtest(1) = 1
        acc_create(devtest, 1)

        !host variable initialization
        SEEDDIM(1) = 1
        #ifndef LOOPCOUNT
        LOOPCOUNT = 10
        #endif
        #ifdef SEED
        SEEDDIM(1) = SEED
        #endif
        CALL RANDOM_SEED(PUT=SEEDDIM)

        CALL RANDOM_NUMBER(a)
        CALL RANDOM_NUMBER(b)
        c = 0
        
        !$acc enter data copyin(c(1:10)), create(a(1:10), b(1:10))
        
        !$acc parallel present(c(1:10), a(1:10), b(1:10))
          !$acc loop
          DO testrun = 1, NUM_TEST_CALLS
            !$acc memcpy(d2d, c(1:10), 10 * sizeof(c(1))), async(1)
            c(testrun) = a(testrun) + b(testrun)
            !$acc update device(c(1:10))
          END DO
          test1 = testrun
          IF (testrun.mod.2. eq. 0) THEN
            DO WHILE (acc_async_test_all() .eqv. .FALSE.)
            END DO
          END IF
        !$acc end parallel
        DO testrun = 1, NUM_TEST_CALLS
          IF (abs(c(testrun) - (a(testrun) + b(testrun))).gt. PRECISION) THEN
            errors = errors + 1
          END IF
        END DO

        test1 = (errors .eq. 0)
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