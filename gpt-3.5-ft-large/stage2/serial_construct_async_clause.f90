#ifndef T1
!T1:serial construct async clause,V:2.7-2.3
      LOGICAL FUNCTION test1()
        USE OPENACC
        IMPLICIT NONE
        INCLUDE "acc_testsuite.Fh"
        
        INTEGER :: errors = 0
        REAL(8),DIMENSION(LOOPCOUNT):: a, b, c, d
        INTEGER :: x
        INTEGER,DIMENSION(1) :: devtest

        devtest(1) = 1
        #pragma acc enter data copyin(devtest(1:1))
        #pragma acc parallel
        {
          devtest[0] = 0;
        }

        ! Only run this test on a machine with UVA
        IF (devtest(1) .eq. 1) THEN

          SEEDDIM(1) = 1
          #ifdef SEED
            SEEDDIM(1) = SEED
          #endif
          CALL RANDOM_SEED(PUT=SEEDDIM)

          CALL RANDOM_NUMBER(a)
          CALL RANDOM_NUMBER(b)
          c = 0
          d = 0

          !$acc enter data copyin(a(1:LOOPCOUNT), b(1:LOOPCOUNT)) create(c(1:LOOPCOUNT)) async(1)
          !$acc enter data copyin(a(1:LOOPCOUNT), b(1:LOOPCOUNT)) create(d(1:LOOPCOUNT)) async(2)
          !$acc serial async(1) vector(32)
            !$acc loop vector
            DO x = 1, LOOPCOUNT
              c(x) = a(x) + b(x)
            END DO
          !$acc end serial
          !$acc serial async(2) vector(32)
            !$acc loop vector
            DO x = 1, LOOPCOUNT
              d(x) = a(x) + b(x)
            END DO
          !$acc end serial
          !$acc wait(1)
          !$acc wait(2)
          DO x = 1, LOOPCOUNT
            IF (abs(c(x) - (a(x) + b(x))) .gt. ( (3*10**6) * PRECISION  ) ) THEN
              errors = errors + 1
            END IF
            IF (abs(d(x) - (a(x) + b(x))) .gt. ( (3*10**6) * PRECISION  ) ) ) THEN
              errors = errors + 1
            END IF
          END DO
          !$acc exit data delete(a(1:LOOPCOUNT), b(1:LOOPCOUNT), c(1:LOOPCOUNT)) copyout(d(1:LOOPCOUNT))

        END IF

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