!T1:host_data construct use_device clause,V:2.7-2.3
      LOGICAL FUNCTION test1()
        USE OPENACC
        IMPLICIT NONE
        INCLUDE "acc_testsuite.Fh"
        
        INTEGER :: errors = 0

        REAL(8), DIMENSION(LOOPCOUNT):: a, b, c
        REAL(8), DIMENSION(LOOPCOUNT):: a_host, b_host
        INTEGER :: x
        LOGICAL(4) :: isHost

        !Initialize
        SEEDDIM(1) = 1
        SEEDDIM(1) = USE_SEED
        CALL RANDOM_SEED(PUT=SEEDDIM)

        CALL RANDOM_NUMBER(a)
        CALL RANDOM_NUMBER(b)
        c = 0
        a_host = a
        b_host = b

        !$acc enter data create(a(1:LOOPCOUNT), b(1:LOOPCOUNT))
        !$acc host_data use_device(a(1:LOOPCOUNT), b(1:LOOPCOUNT), c(1:LOOPCOUNT)) 
          !$acc parallel
            !$acc loop
            DO x = 1, LOOPCOUNT
              c(x) = a(x) + b(x)
            END DO
          !$acc end parallel
        !$acc end host_data

        DO x = 1, LOOPCOUNT
          IF (abs(c(x) - (a_host(x) + b_host(x))) .gt. PRECISION) THEN
            errors = errors + 1
          END IF
        END DO

        !$acc exit data delete(a(1:LOOPCOUNT), b(1:LOOPCOUNT))

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