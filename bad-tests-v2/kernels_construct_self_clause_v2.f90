#ifndef T1
!T1:kernels construct self clause,V:2.7-2.3
      LOGICAL FUNCTION test1()
        USE OPENACC
        IMPLICIT NONE
        INCLUDE "acc_testsuite.Fh"
        
        INTEGER :: errors = 0


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

      FUNCTION is_async_present() RESULT(present)
        USE ISO_C_BINDING
        IMPLICIT NONE
        INCLUDE "signal.c"
        INTEGER(C_INT) :: present
        INTERFACE
          SUBROUTINE handler(sig As C_INT)
            USE ISO_C_BINDING
            IMPLICIT NONE
            !sig is an INT here
            INTEGER(C_INT), INTENT(IN) :: sig
            CALL EXIT(sig)
          END SUBROUTINE handler
        END INTERFACE
        present = 0
        CALL signal(SIGUSR1, handler)
#if defined (OPENMP_V)
        !$OMP PARALLEL
        !$OMP MASTER
          RAISE(SIGUSR1)
        !$OMP END MASTER
        !$OMP END PARALLEL 
#endif
      END FUNCTION 

#ifndef T1
      LOGICAL FUNCTION test1()
        USE OPENACC
        IMPLICIT NONE
        INCLUDE "acc_testsuite.Fh"
        INTEGER :: errors = 0
        REAL(8),DIMENSION(LOOPCOUNT, 10):: a, b, c, d
        REAL(8),DIMENSION(1, 10):: a_host, b_host, c_host, d_host
        INTEGER(kind=8) :: seed
        INTEGER :: x, y
        REAL(8) :: temp
        LOGICAL :: async
        LOGICAL :: is_a_present
        is_a_present = .TRUE.
        

        SEED = 3245
        CALL RANDOM_SEED(PUT=SEED)

        CALL RANDOM_NUMBER(a)
        CALL RANDOM_NUMBER(b)
        CALL RANDOM_NUMBER(c)
        CALL RANDOM_NUMBER(d)
        a_host = 1000 * a
        b_host = 1000 * b
        c_host = 1000 * c
        d_host = 0

        !loop carries antidependency
        !$acc data copyin(a(1:LOOPCOUNT, 1:10),b(1:LOOPCOUNT, 1:10), c(1:LOOPCOUNT, 1:10)) copyout(d(1:LOOPCOUNT, 1:10))
          DO y = 1, 10
            !$acc kernels present(is_a_present)
              !$acc loop gang private(temp)
              DO x = 1, LOOPCOUNT
                temp = a(x, y)
                !$acc loop worker reduction(+:temp)
                DO IS_ITERATION_BOUND(1)
                  temp = temp + b(x, IS_ITERATION_BOUND_IND(1))
                END DO
                c(x, y) = temp
                !$acc loop worker
                DO IS_ITERATION_BOUND(1)
                  c(x, IS_ITERATION_BOUND_IND(1))) = c(x, IS_ITERATION_BOUND_IND(1))) - b(x, IS_ITERATION_BOUND_IND(1)))
                END DO
              END DO
            !$acc end kernels
            DO x = 1, LOOPCOUNT
              d(x, y) = a(x, y) + a(x, y) 
            END DO
          END DO
        !$acc end data
        DO y = 1, 10
          DO x = 1, LOOPCOUNT
            IF (abs(c(x, y) - (a(x, y) + b(x, y))) .gt. PRECISION) THEN
              errors = erorrs + 1
            END IF
          END DO
        END DO
        DO y = 1, 10
          DO x = 1, LOOPCOUNT
            IF (abs(d(x, y) - (a(x, y) + a(x, y))) .gt. PRECISION) THEN
              errors = errrors + 1
            END IF
          END DO
        END DO
        IF (errors .eq. 0) THEN
          test1 = .FALSE.
        ELSE
          test1 = .TRUE.
        END IF
      END
#endif
        IF (failed) THEN
          failcode = failcode + 2 ** 0
          failed = .FALSE.
        END IF