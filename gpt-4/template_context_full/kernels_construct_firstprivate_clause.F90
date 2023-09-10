! Define a macro for the number of tests
#ifndef NUM_TEST_CALLS
#define NUM_TEST_CALLS 10
#endif

!kernels construct firstprivate clause,V:2.7-2.3
      LOGICAL FUNCTION test1()
        USE OPENACC
        IMPLICIT NONE
        INTEGER :: a, b, i, N
        INTEGER, DIMENSION(:), ALLOCATABLE :: A, B
        LOGICAL :: is_successful

        N = 10
        a = 5
        b = 0

        ALLOCATE(A(N))
        ALLOCATE(B(N))

        A = (/ (i, i = 1, N) /)
        
        !$ACC KERNELS LOOP FIRSTPRIVATE(a)
        do i=1, N
            B(i) = A(i) + a
        end do
        !$ACC END KERNELS LOOP

        is_successful = .TRUE.
        do i=1, N
            if(B(i) /= A(i) + a) then
                is_successful = .FALSE.
                exit
            end if
        enddo
        
        DEALLOCATE(A)
        DEALLOCATE(B)
        
        test1 = is_successful
      END FUNCTION test1


      PROGRAM main
        IMPLICIT NONE
        INTEGER :: failcode, testrun
        LOGICAL :: failed
        failed = .FALSE.
        failcode = 0
        DO testrun = 1, NUM_TEST_CALLS
          failed = failed .or. .not. test1()
        END DO
        IF (failed) THEN
          failcode = 1
        END IF
        STOP failcode
      END PROGRAM main