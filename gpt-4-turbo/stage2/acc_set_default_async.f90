! Assuming acc_testsuite.Fh defines necessary testing infrastructure such as constants.
! If it does not exist, the core logic here can still be understood and implemented
! in accordance with one's testing framework.

!T1: acc_set_default_async, V:2.7-2.3
      LOGICAL FUNCTION test1()
        USE OPENACC
        IMPLICIT NONE
        INCLUDE "acc_testsuite.Fh"
        
        INTEGER :: errors = 0
        INTEGER, DIMENSION(:), ALLOCATABLE :: a
        INTEGER :: i
        INTEGER, PARAMETER :: N = 1000
        INTEGER :: async_queue

        ALLOCATE(a(N))
        a = 0

        ! Set a non-default async queue to test the functionality
        async_queue = 1
        CALL acc_set_default_async(async_queue)

        ! Operations in this region should execute on the async_queue
        !$acc parallel loop async
        DO i = 1, N
          a(i) = i
        END DO

        ! Wait on the specified async queue to ensure operation completion before verification
        CALL acc_wait(async_queue)

        ! Verify operation executed asynchronously as expected
        DO i = 1, N
          IF (a(i) .ne. i) THEN
            errors = errors + 1
          END IF
        END DO

        ! Reset default async queue to initial value, this part is mainly preventive
        ! for not affecting other tests, not actively part of the verification
        CALL acc_set_default_async(acc_async_default)

        ! Verification if any error has occurred
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
        EXTERNAL :: test1
        failed = .FALSE.
        failcode = 0
        DO testrun = 1, NUM_TEST_CALLS
          failed = failed .or. test1()
        END DO
        IF (failed) THEN
          failcode = failcode + 2 ** 0
          failed = .FALSE.
        END IF
        PRINT *, "Test Suite Finished with Fail Code: ", failcode
        CALL EXIT (failcode)
      END PROGRAM