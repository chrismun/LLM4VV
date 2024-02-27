! Test for OpenACC async clause
!T1:async clause,V:2.7-2.3
      MODULE async_test_mod
        USE OPENACC
        IMPLICIT NONE
      CONTAINS
        LOGICAL FUNCTION test_async()
          INTEGER, DIMENSION(1024) :: a, b, c
          INTEGER :: i, async_val
          LOGICAL :: isAsyncComplete
          test_async = .TRUE.
          async_val = 1

          ! Initialize arrays
          a = 1
          b = 2

          ! Test async execution
          !$acc parallel loop copyout(c) copyin(a,b) async(async_val)
          DO i = 1, SIZE(a)
            c(i) = a(i) + b(i)
          END DO

          ! Check for completion of async operation
          !$acc wait(async_val)
          isAsyncComplete = .TRUE.
          DO i = 1, SIZE(c)
            IF (c(i) /= 3) THEN
              isAsyncComplete = .FALSE.
              EXIT
            END IF
          END DO

          IF (.NOT. isAsyncComplete) THEN
            test_async = .FALSE.
          END IF
        END FUNCTION test_async
      END MODULE async_test_mod

      PROGRAM main
        USE async_test_mod
        IMPLICIT NONE
        INTEGER :: failcode, testrun
        LOGICAL :: failed
        failed = .FALSE.
        failcode = 0

        DO testrun = 1, NUM_TEST_CALLS
          failed = failed .or. .NOT. test_async()
        END DO
        IF (failed) THEN
          failcode = failcode + 2 ** 0
        END IF

        CALL EXIT(failcode)
      END PROGRAM main
