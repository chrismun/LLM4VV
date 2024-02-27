! Testing OpenACC loop construct auto clause
! -----------------------------------------------------
!T1:loop construct auto clause,V:2.7-2.3
      MODULE openacc_module
        IMPLICIT NONE
        INCLUDE 'openacc.fh'
      CONTAINS
        LOGICAL FUNCTION test1()
          USE openacc_module
          INTEGER, PARAMETER :: N = 10000
          INTEGER :: i
          REAL, DIMENSION(N) :: a, b
          REAL :: start, finish
          INTEGER :: errors = 0

          ! Initialize arrays
          DO i = 1, N
            a(i) = REAL(i)
            b(i) = 0.0
          END DO

          ! Test the loop with the auto clause
          !$acc kernels loop auto
          DO i = 1, N
            b(i) = a(i) + 1.0
          END DO
          !$acc end kernels

          ! Verification (simple correctness check)
          DO i = 1, N
            IF (b(i) /= a(i) + 1.0) THEN
              errors = errors + 1
            END IF
          END DO

          IF (errors .eq. 0) THEN
            test1 = .FALSE.
          ELSE
            test1 = .TRUE.
          END IF
        END FUNCTION test1
      END MODULE openacc_module

      PROGRAM main
        USE openacc_module
        IMPLICIT NONE
        INTEGER :: failcode, testrun
        LOGICAL :: failed
        ! Include or define acc_testsuite.Fh if it defines specific setup for the test e.g., NUM_TEST_CALLS
        INCLUDE 'acc_testsuite.Fh'
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
        CALL EXIT(failcode)
      END PROGRAM main