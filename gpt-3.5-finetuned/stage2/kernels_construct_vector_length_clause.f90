!T1:kernels construct vector_length clause,V:2.7-2.3
      LOGICAL FUNCTION test1()
        USE OPENACC
        IMPLICIT NONE
        INCLUDE "acc_testsuite.Fh"
        
        INTEGER :: errors = 0

        REAL(8), DIMENSION(LOOPCOUNT):: a, b, c
        INTEGER :: x
        REAL(8) :: device_timing
        REAL(8),DIMENSION(LOOPCOUNT)::host_array
        
        !$acc data copyin(host_array(1:LOOPCOUNT)) copy(a(1:LOOPCOUNT), c(1:LOOPCOUNT)) copyout(b(1:LOOPCOUNT))
          !$acc kernels loop vector_length(16)
          DO x = 1, LOOPCOUNT
            b(x) = a(x) + c(x) + host_array(x)
          END DO
        !$acc end data

        DO x = 1, LOOPCOUNT
          IF (abs(b(x) - (a(x) + c(x) + host_array(x))) .gt. PRECISION) THEN
            errors = errors + 1
          END IF
        END DO
        
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