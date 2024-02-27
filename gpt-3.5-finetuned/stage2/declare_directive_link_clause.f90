!T1:declare directive link clause,V:2.7-2.3
      LOGICAL FUNCTION test1()
        USE OPENACC
        IMPLICIT NONE
        INCLUDE "acc_testsuite.Fh"
        
        INTEGER :: errors = 0

        INTEGER, PARAMETER :: N = 1000
        INTEGER :: device_array(N)
        INTEGER :: global_array(N)
        INTEGER :: idx
        
        !$acc declare create(global_array)
        !$acc parallel num_gangs(1) num_workers(1)
          !$acc loop
          DO idx = 1, N
            global_array(idx) = idx
          END DO
        !$acc end parallel

        !$acc update device_array(1:N) link(global_array(1:N))

        !$acc parallel loop
        DO idx = 1, N
          device_array(idx) = global_array(idx)*2
        END DO

        !$acc end parallel loop

        DO idx = 1, N
          IF (device_array(idx) .ne. idx*2) THEN
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