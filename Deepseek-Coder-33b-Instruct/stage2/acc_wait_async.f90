!T1:acc wait async,V:2.7-2.3
      LOGICAL FUNCTION test1()
        USE OPENACC
        IMPLICIT NONE
        INCLUDE "acc_testsuite.Fh"
        
        INTEGER :: errors = 0
        INTEGER, PARAMETER :: N = 1000
        INTEGER :: i, async1, async2
        REAL :: a(N), b(N), c(N)

        ! Initialize arrays
        DO i = 1, N
          a(i) = i * 1.0
          b(i) = i * 2.0
          c(i) = 0.0
        END DO

        ! Create async queues
        CALL acc_create_async(async1)
        CALL acc_create_async(async2)

        ! Enqueue tasks on each queue
        CALL acc_enqueue_async(async1)
        CALL acc_enqueue_async(async2)

        ! Enqueue data on each queue
        CALL acc_copyin_async(a, N, async1)
        CALL acc_copyin_async(b, N, async2)

        ! Enqueue kernels on each queue
        CALL acc_kernels_async(async1)
        CALL acc_kernels_async(async2)

        ! Wait for tasks to complete
        CALL acc_wait_async(async1)
        CALL acc_wait_async(async2)

        ! Enqueue data copyout on each queue
        CALL acc_copyout_async(c, N, async1)
        CALL acc_copyout_async(c, N, async2)

        ! Wait for data copyout to complete
        CALL acc_wait_async(async1)
        CALL acc_wait_async(async2)

        ! Check results
        DO i = 1, N
          IF (c(i) .ne. a(i) + b(i)) THEN
            errors = errors + 1
          END IF
        END DO

        IF (errors .eq. 0) THEN
          test1 = .FALSE.
        ELSE
          test1 = .TRUE.
        END IF
      END
