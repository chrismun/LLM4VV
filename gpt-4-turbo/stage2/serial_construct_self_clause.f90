! This code tests the OpenACC serial construct self clause.
! It returns 0 if the test passes (the compiler correctly implements the feature),
! and a nonzero value otherwise.

MODULE acc_testsuite
    USE OPENACC
    IMPLICIT NONE
CONTAINS
    FUNCTION test1()
        LOGICAL :: test1
        INTEGER :: x, errors
        INTEGER :: expected_value

        errors = 0
        ! Initialize x with a value
        x = 10
        expected_value = 10 + 5  ! The expected result after the operation within the serial block

        !$acc serial copyin(x) self(x)
        x = x + 5
        !$acc end serial

        ! Check if the result is as expected
        IF (x /= expected_value) THEN
            errors = errors + 1
        END IF

        IF (errors == 0) THEN
            test1 = .FALSE.
        ELSE
            test1 = .TRUE.
        END IF
    END FUNCTION test1
END MODULE acc_testsuite

PROGRAM main
    USE acc_testsuite
    IMPLICIT NONE
    INTEGER :: failcode
    LOGICAL :: failed

    failcode = 0
    failed = test1()

    IF (failed) THEN
        failcode = failcode + 2 ** 0
    END IF

    CALL EXIT(failcode)
END PROGRAM main