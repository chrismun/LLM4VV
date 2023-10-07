#ifndef T1
!T1:acc memcpy device,V:2.7-2.3
      LOGICAL FUNCTION test1()
        USE OPENACC
        IMPLICIT NONE
        INCLUDE "acc_testsuite.Fh"
        
        INTEGER :: errors = 0
        !Initializing Data for testing
        INTEGER, DIMENSION(10) :: host_data
        INTEGER, DIMENSION(10) :: dev_data
        INTEGER, DIMENSION(10) :: new_data
        INTEGER :: x

        SEEDDIM(1) = 1
	SEEDDIM(2) = 1
#ifdef SEED
        SEEDDIM(1) = SEED
#endif
        CALL RANDOM_SEED(PUT=SEEDDIM)
        CALL RANDOM_NUMBER(host_data)
        
        !$acc data copyin(host_data(1:10)) copy(dev_data(1:10))
          !$acc parallel
            !$acc loop
            DO x = 1, 10
              dev_data(x) = host_data(x)
            END DO
          !$acc end parallel
        !$acc end data

        CALL acc_memcpy_devicr(new_data, dev_data, 10 * sizeof(INTEGER))

        DO x = 1, 10
          IF (host_data(x) .ne. new_data(x)) THEN
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