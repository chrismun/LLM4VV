#ifndef T1
!T1:kernels construct if clause,V:2.7-2.3
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

      FUNCTION random_number()
        REAL :: random_number
        REAL, PARAMETER :: seed = 35723.0
        CALL RANDOM_SEED(PUT=(/seed/))
        CALL RANDOM_NUMBER(random_number)
      END FUNCTION

c1:TARGET
      SUBROUTINE fix_seed(A, seed, n)
        INTEGER, DIMENSION(n) :: A
        INTEGER, VALUE :: seed, n, i
        INTEGER :: return_val
        return_val = 0

        DO i = 1, n
          A(i) = 1
        END DO

      END SUBROUTINE fix_seed

      SUBROUTINE assign(A, n)
        INTEGER, INTENT(OUT), DIMENSION(n) :: A
        INTEGER, INTENT(IN) :: n
        INTEGER :: iterator

        DO iterator = 1, n
          A(iterator) = 1
        END DO
      END SUBROUTINE assign

c254:TARGET
      LOGICAL FUNCTION test254(A)
        USE OPENACC
        IMPLICIT NONE
        INCLUDE "acc_testsuite.Fh"
        INTEGER, TARGET :: A(10)
        INTEGER :: total, total_is
        INTEGER :: errors = 0
        INTEGER :: mult_val, temp_total
        LOGICAL(IS_DEV_PTR) :: dev_test
        dev_test = .TRUE.

        IF (dev_test .eq. 0) THEN
         !$acc enter data copyin(A(1:10))
        END IF
        mult_val = 2
        temp_total = 0

        !$acc data copyout(A(1:10))
          !$acc kernels if(total .gt. 256) present(A(1:10))
          !$acc end data

        !$acc exit data copyout(A(1:10))

        IF (errors .gt. 0) THEN
          test254 = .TRUE.
        ELSE
          test254 = .FALSE.
        END IF
      END