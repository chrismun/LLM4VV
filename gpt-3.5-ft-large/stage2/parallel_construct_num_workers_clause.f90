#ifndef T1
!T1:parallel construct num_workers clause,V:2.7-2.3
      LOGICAL FUNCTION test1()
        USE OPENACC
        IMPLICIT NONE
        INCLUDE "acc_testsuite.Fh"
        
        INTEGER :: errors = 0
        REAL(8), DIMENSION:, = 0 :: a
        INTEGER :: x
        INTEGER :: y = 0
        LOGICAL :: device_num_workers, host_num_workers
        LOGICAL :: device_present = .FALSE.
        LOGICAL :: host_present = .FALSE.
        REAL(8),DIMENSION(128):temp

        !Initilization
        SEEDDIM(1) = 1
        #if LOOPCOUNT==1
            SEEDDIM(0) = 1
        #else
            SEEDDIM(0) = LOOPCOUNT
        #endif
        CALL RANDOM_SEED(PUT=SEEDDIM)

        CALL RANDOM_NUMBER(a)

        !$acc data copyin(a(1:LOOPCOUNT))
          !$acc parallel num_workers(8)
            y = 0
            !$acc loop worker
            DO x = 1, LOOPCOUNT
              y = y + 1
            END DO
            !$acc loop worker
            DO x = 1, LOOPCOUNT
              y = y - 1
            END DO
          !$acc end parallel
        !$acc end data
        DO x = 1, LOOPCOUNT
          host_present = .TRUE.
          host_num_workers = 8
        END DO

        !$acc data copyout(temp(1:10)) copyin(a(1:10))
          !$acc parallel num_workers(4)
            !$acc loop independent
            DO x = 1, 10
              temp(x) = a(x)
            END DO
            !$acc loop independent
            DO x = 1, 10
              a(x) = 1.0
            END DO
          !$acc end parallel
          !$acc parallel
            !$acc loop independent
            DO x = 1, 10
              a(x) = a(x) - temp(x)
            END DO
          !$acc end parallel
        !$acc end data
        DO x = 1, 10
          IF (abs(a(x) - (1.0 - temp(x))) .gt. PRECISION) THEN
            errors = errors + 1
          END IF
          device_present = .TRUE.
          device_num_workers = 4
        END DO
        IF (device_present .AND. host_present .AND. (device_num_workers .eqv. host_num_workers)) THEN
          errors = errors + 1
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