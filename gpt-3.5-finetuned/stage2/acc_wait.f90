!T1:acc wait,V:2.7-2.3
      LOGICAL FUNCTION test1()
        USE OPENACC
        IMPLICIT NONE
        INCLUDE "acc_testsuite.Fh"
        
        INTEGER :: errors = 0

        ! Complete test here
        CALL acc_init(acc_device_default)   

        !$acc enter data create(a[1:4])
        !$acc enter data create(b[1:4])
        !$acc enter data create(c[1:4])

        !y1 = a + b,
        !$acc parallel loop async(1)
        DO i = 1, n
          a(i) = i
        END DO

        !$acc parallel loop async(2)
        DO i = 1, n
          b(i) = a(i) * 2
        END DO

        CALL acc_wait(1)
        !$acc parallel loop async(2)
        DO i = 1, n
          c(i) = b(i) * 2
        END DO
  
        !$acc exit data copyout(c[1:4])
        
        DO i = 1, n
          IF (c(i) .ne. (i * 4)) THEN
            errors = errors + 1
          END IF
        END DO
  
        CALL acc_remove_device(a)
        CALL acc_remove_device(b)
        !$acc exit data delete(a[1:n], b[1:n])

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