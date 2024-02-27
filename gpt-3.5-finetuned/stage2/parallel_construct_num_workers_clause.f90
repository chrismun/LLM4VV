!T1:parallel construct num_workers clause,V:2.7-2.3
      LOGICAL FUNCTION test1()
        USE OPENACC
        IMPLICIT NONE
        INCLUDE "acc_testsuite.Fh"
        
        INTEGER :: errors = 0
        REAL(8),DIMENSION(LOOPCOUNT):: a, b
        REAL(8):: total, host_total, x, y, z
        INTEGER :: x10, x20, x30, x40, x50, x60
        INTEGER :: temp
        REAL(8),DIMENSION(6,LOOPCOUNT):: a6, b6, c6
        LOGICAL:: present
        
        SEEDDIM(1) = 1
        SEEDDIM(1) = SEED
        CALL RANDOM_SEED(PUT=SEEDDIM)

        CALL RANDOM_NUMBER(a)
        CALL RANDOM_NUMBER(b)

        x = 56.1
        y = 784.37
        z = 122.05

        a = x / 10
        b = y / 20
        
        !$acc enter data copyin(a(1:LOOPCOUNT), b(1:LOOPCOUNT), c6(1:6,1:LOOPCOUNT))
        
        !$acc parallel num_workers(16)
        !$acc loop
        DO x10 = 1, LOOPCOUNT
          c6(1,x10) = a(x10) + b(x10)
        END DO
        !$acc parallel num_workers(16)
        !$acc loop
        DO x20 = 1, LOOPCOUNT
          c6(2,x20) = a(x20) + b(x20)
        END DO
        !$acc parallel num_workers(16)
        !$acc loop
        DO x30 = 1, LOOPCOUNT
          c6(3,x30) = a(x30) + b(x30)
        END DO
        !$acc parallel num_workers(16)
        !$acc loop
        DO x40 = 1, LOOPCOUNT
          c6(4,x40) = a(x40) + b(x40)
        END DO
        !$acc parallel num_workers(16)
        !$acc loop
        DO x50 = 1, LOOPCOUNT
          c6(5,x50) = a(x50) + b(x50)
        END DO
        !$acc parallel num_workers(16)
        !$acc loop
        DO x60 = 1, LOOPCOUNT
          c6(6,x60) = a(x60) + b(x60)
        END DO
        
        
        present = .TRUE.
        !$acc host_data use_device(c6)
        !$acc end host_data
          DO temp = 1, 6
            DO x10 = 1, LOOPCOUNT
              IF (c6(temp, x10) .ne. (a(x10) + b(x10))) THEN
                present = .FALSE.
              END IF
            END DO
          END DO
        
        IF (present .eq. .FALSE.) THEN
          errors = errors + 1
        END IF
  
        !$acc exit data delete(a(1:LOOPCOUNT), b(1:LOOPCOUNT), c6(1:6,1:LOOPCOUNT))

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