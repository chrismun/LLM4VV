!T1:data construct attach clause,V:2.7-2.3
      LOGICAL FUNCTION test1()
        USE OPENACC
        IMPLICIT NONE
        INCLUDE "acc_testsuite.Fh"
        
        INTEGER :: errors = 0
        INTEGER, ALLOCATABLE :: data(:)
        INTEGER :: N = 1024
        INTEGER :: i

        ALLOCATE(data(N))
        data = 1 ! Initialize the data to 1

        !$acc enter data copyin(data(:)) attach(data)
        !$acc parallel loop
        DO i=1,N
          data(i) = data(i) + 1
        ENDDO
        !$acc exit data copyout(data(:)) detach(data)

        DO i=1,N
          IF(data(i) /= 2) THEN
            errors = errors + 1
          END IF
        ENDDO

        DEALLOCATE(data)

        IF (errors .eq. 0) THEN
          test1 = .FALSE.
        ELSE
          test1 = .TRUE.
        END IF
      END FUNCTION test1

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