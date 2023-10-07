!T1:acc detach,V:2.7-2.3
      LOGICAL FUNCTION test1()
        USE OPENACC
        IMPLICIT NONE
        INCLUDE "acc_testsuite.Fh"
        
        INTEGER :: errors = 0
        INTEGER, DIMENSION(:), ALLOCATABLE :: arr
        INTEGER :: n, i, async_arg

        n = 100
        ALLOCATE(arr(n))

        ! Initialize array
        arr = [(i, i = 1, n)]

        ! Attach array to device
        call acc_attach(arr)
        
        ! Perform computation on device
        !$ACC PARALLEL LOOP
        DO i = 1, n
          arr(i) = arr(i) * 2
        END DO

        ! Detach array from device
        call acc_detach(arr)
        
        ! Check result on host
        DO i = 1, n
          IF (arr(i) .ne. i*2) THEN
            errors = errors + 1
          END IF
        END DO

        DEALLOCATE(arr)

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
      END PROGRAM main