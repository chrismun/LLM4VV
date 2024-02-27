! This Fortran code tests the OpenACC kernels construct wait clause
!T1:kernels construct wait clause,V:2.7-2.3
      MODULE test_module
        USE OPENACC
        IMPLICIT NONE
        INTEGER, PARAMETER :: N = 100
        REAL, DIMENSION(N) :: test_array
      CONTAINS
        LOGICAL FUNCTION test1()
        IMPLICIT NONE
        INTEGER :: i
        LOGICAL :: passed
        INTEGER :: errors = 0

        ! Initialize array
        test_array = 1.0

        ! First kernels region to modify test_array
        !$acc kernels
        DO i = 1, N
          test_array(i) = test_array(i) * 2.0
        END DO
        !$acc end kernels

        ! Implementing a wait clause here
        !$acc kernels wait

        ! Second kernels region to further modify test_array
        !$acc kernels
        DO i = 1, N
          ! This operation should only be correct if the wait ensured previous modifications completed
          test_array(i) = test_array(i) + 1.0
        END DO
        !$acc end kernels

        ! Check if modifications are as expected indicating the wait worked
        DO i = 1, N
          IF (test_array(i) /= 3.0) THEN
            errors = errors + 1
          END IF
        END DO

        IF (errors .eq. 0) THEN
          test1 = .TRUE.
        ELSE
          test1 = .FALSE.
        END IF
      END FUNCTION test1
      END MODULE test_module

      PROGRAM main
        USE test_module
        IMPLICIT NONE
        INTEGER :: failcode, testrun
        LOGICAL :: failed
        failed = .FALSE.
        failcode = 0
        LOGICAL :: test_function
        test_function = test1()
        failed = failed .or. test_function
        IF (failed) THEN
          failcode = failcode + 2 ** 0
        END IF

        CALL EXIT (failcode)
      END PROGRAM