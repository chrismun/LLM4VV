!acc_testsuite.Fh
! Mock include file for the purposes of this example.
! Defines NUM_TEST_CALLS.
INTEGER, PARAMETER :: NUM_TEST_CALLS = 1

!T1:serial construct reduction clause,V:2.7-2.3
      LOGICAL FUNCTION test1()
        USE openacc
        IMPLICIT NONE

        INTEGER, PARAMETER :: n = 100
        INTEGER :: i
        INTEGER :: result_acc, result_serial
        INTEGER, DIMENSION(n) :: data

        ! Initialize array.
        DO i = 1, n
           data(i) = i
        END DO

        result_acc = 0
        result_serial = 0

        ! Using OpenACC serial construct with reduction clause.
        !$acc serial reduction(+:result_acc)
        DO i = 1, n
           result_acc = result_acc + data(i)
        END DO

        ! Serial computation for verification.
        DO i = 1, n
           result_serial = result_serial + data(i)
        END DO

        ! Compare the results.
        IF (result_acc == result_serial) THEN
          test1 = .FALSE.
        ELSE
          test1 = .TRUE.
        END IF
      END FUNCTION test1

      PROGRAM main
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
          failcode = failcode + 2**0
          failed = .FALSE.
        END IF

        CALL EXIT(failcode)
      END PROGRAM main