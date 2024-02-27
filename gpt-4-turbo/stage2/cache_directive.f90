! Include OpenACC module
MODULE acc_module
    USE OPENACC
END MODULE acc_module

! Test function header
!T1:cache directive,V:2.7-2.3
      LOGICAL FUNCTION test1()
        USE acc_module
        IMPLICIT NONE
        INTEGER :: errors = 0
        INTEGER, DIMENSION(100) :: array
        INTEGER :: i, sum_without_cache, sum_with_cache

        ! Initialize array
        DO i = 1, 100
          array(i) = i
        END DO

        ! Calculate sum without cache directive
        sum_without_cache = 0
        !$acc parallel loop reduction(+:sum_without_cache)
        DO i = 1, 100
          sum_without_cache = sum_without_cache + array(i)
        END DO

        ! Calculate sum with cache directive
        sum_with_cache = 0
        !$acc parallel loop reduction(+:sum_with_cache)
        !$acc cache(array(1:100))
        DO i = 1, 100
          sum_with_cache = sum_with_cache + array(i)
        END DO

        ! Check for correctness
        IF (sum_with_cache .eq. sum_without_cache) THEN
          errors = errors
        ELSE
          errors = errors + 1
        END IF

        ! Return result
        IF (errors .eq. 0) THEN
          test1 = .FALSE.
        ELSE
          test1 = .TRUE.
        END IF
      END FUNCTION test1

! Main program, include test function calls
      PROGRAM main
        USE acc_module
        
        IMPLICIT NONE
        INTEGER :: failcode, testrun
        LOGICAL :: failed

        LOGICAL :: test1

        failed = .FALSE.
        failcode = 0

        DO testrun = 1, 1  ! Single test run assuming caching works identically across runs
          failed = failed .OR. test1()
        END DO

        IF (failed) THEN
          failcode = failcode + 2 ** 0
          failed = .FALSE.
        END IF

        CALL EXIT(failcode)
      END PROGRAM main