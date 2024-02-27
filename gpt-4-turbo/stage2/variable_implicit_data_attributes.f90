! Example code to test OpenACC's implementation of variable implicit data attributes in Fortran compilers
      MODULE acc_testsuite_mod
        USE OPENACC
        INTEGER, PARAMETER :: NUM_TEST_CALLS = 1
      END MODULE acc_testsuite_mod

!T1:variable implicit data attributes,V:2.7-2.3
      FUNCTION test1()
        USE OPENACC
        USE acc_testsuite_mod
        IMPLICIT NONE
        LOGICAL :: test1
        INTEGER :: errors, x, y
        errors = 0
        x = 1
        y = 2

        ! Using parallel construct which implies 'firstprivate' for scalar variables by default
        !$acc parallel
        x = x + 1
        !$acc end parallel

        ! Test if value of x is unchanged outside the parallel region indicating 'firstprivate' behavior
        IF (x /= 1) errors = errors + 1

        ! Using kernels construct which implies 'copy' for scalar variables
        !$acc kernels
        y = y + 1
        !$acc end kernels

        ! Test if value of y is changed outside the kernels region indicating 'copy' behavior
        IF (y == 2) errors = errors + 1

        IF (errors .eq. 0) THEN
          test1 = .FALSE.
        ELSE
          test1 = .TRUE.
        END IF
      END FUNCTION test1

      PROGRAM main
        USE acc_testsuite_mod
        IMPLICIT NONE
        INTEGER :: failcode, testrun
        LOGICAL :: failed
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
        PRINT *, "Exit code:", failcode
      END PROGRAM main