!T1:acc deviceptr,V:2.7-2.3
      LOGICAL FUNCTION test1()
        USE OPENACC
        IMPLICIT NONE
        INCLUDE "acc_testsuite.Fh"
        
        INTEGER :: errors = 0

        REAL(8),DIMENSION(LOOPCOUNT):: a, b
	      INTEGER :: x
        REAL(8),DIMENSION(LOOPCOUNT):: device_a, device_b
        
        ! Allocate device memory
        CALL acc_create(device_a(1:LOOPCOUNT)) 
        CALL acc_create(device_b(1:LOOPCOUNT)) 

        ! initialize host arrays
        SEEDDIM(1) = 1
        SEEDDIM(1) = SEED
        CALL RANDOM_SEED(PUT=SEEDDIM)

        CALL RANDOM_NUMBER(a)
        CALL RANDOM_NUMBER(b)
        !$acc enter data copyin(a(1:LOOPCOUNT), b(1:LOOPCOUNT)) create(device_a(1:LOOPCOUNT), device_b(1:LOOPCOUNT)) 
        !$acc parallel present(device_a(1:LOOPCOUNT),  device_b(1:LOOPCOUNT))
          !$acc loop
          DO x = 1, LOOPCOUNT
            device_a(x) = a(x)
            device_b(x) = b(x)
          END DO
        !$acc end parallel 
             
            
        ! run deviceptr test for a 
        IF (size(acc_deviceptr(device_a(1:LOOPCOUNT))) .ne. C_SIZE_T) THEN
          errors = errors + 1
        END IF
        ! run deviceptr test for b
        IF (size(acc_deviceptr(device_b(1:LOOPCOUNT))) .ne. C_SIZE_T) THEN
           errors = errors + 1
        END IF
        ! cleanup
        CALL acc_delete(device_a(1:LOOPCOUNT))
        CALL acc_delete(device_b(1:LOOPCOUNT))

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