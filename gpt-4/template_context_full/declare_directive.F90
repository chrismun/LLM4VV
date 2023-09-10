! Test implementation of declare directive with create clause in OpenACC
#ifndef T1
      MODULE acc_test1
        USE OPENACC
        IMPLICIT NONE
        INTEGER, DIMENSION(:), ALLOCATABLE :: a
        !$acc declare create(a)
      END MODULE acc_test1

      SUBROUTINE t1_sub(errors)
        USE acc_test1
        INTEGER, INTENT(INOUT) :: errors
        INTEGER :: SIZE_A = 100, i
        ALLOCATE(a(SIZE_A))

        !$acc parallel loop copyin(a)
        DO i=1, SIZE_A
          a(i) = i
        END DO

        DO i=1, SIZE_A
          IF(a(i) /= i) THEN
            errors = errors + 1
          END IF
        END DO
      END SUBROUTINE t1_sub

      LOGICAL FUNCTION test1()
        IMPLICIT NONE
        INTEGER :: errors = 0

        CALL t1_sub(errors)

        IF (errors .eq. 0) THEN
          test1 = .TRUE.
        ELSE
          test1 = .FALSE.
        END IF
      END FUNCTION test1
#endif

      PROGRAM main
        IMPLICIT NONE
        INTEGER :: failcode = 0
        LOGICAL :: failed = .FALSE.
        LOGICAL :: test1
        INTEGER :: NUM_TEST_CALLS = 3, testrun

        DO testrun = 1, NUM_TEST_CALLS
          failed = failed .or. .NOT. test1()
        END DO
        
        IF (failed) THEN
          failcode = 1
        END IF
        
        CALL EXIT (failcode)
      END PROGRAM main