!T1:wait directive,V:2.7-2.3
      LOGICAL FUNCTION test1()
        USE OPENACC
        IMPLICIT NONE
        INCLUDE "acc_testsuite.Fh"
        
        INTEGER :: errors = 0

        !$acc data copyin(a(1:n), b(1:n)) copyout(c(1:n))
        REAL(8), DIMENSION(LOOPCOUNT, 896) :: rands
        REAL(8) :: mult
        INTEGER :: x, y

        SEEDDIM(1) = 1
        {
          int seed = LOOPCOUNT;
          for (int _y = 0; _y < 896; _y++) {
            rands[1][_y] = (REAL(8))(nrand48(&seed))/4503599627370496.;
          }
        }
        DO x = 2, LOOPCOUNT
          SEEDDIM(1) = SEEDDIM(1) + 1
          SEEDDIM(x) = SEEDDIM(1)
          !$acc loop
          DO y = 0, 896
            rands(x, y) = rands(x - 1, y)
          END DO
        END DO
        !$acc end data
  

        CALL RANDOM_SEED(PUT=_seeds)
        CALL RANDOM_SEED(GET=_seeds)
        IF (SEED /= _seeds(1)) THEN
          errors = errors + 1
        END IF
  
      !$acc data copyin(m) copyout(scalar)
    !$acc wait(m)
    !$acc end data

    !$acc wait(host_copy)
    !$acc update host(data) wait(host_copy) copyin(data[0:N]) wait(data)

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