! This Fortran code tests the OpenACC serial construct with a private clause.
! It aims to confirm the correct behavior of private variables within a serial region.
! It returns 0 if the serial construct private clause is implemented correctly, and nonzero otherwise.

MODULE testModule
    USE openacc
    IMPLICIT NONE
CONTAINS
    LOGICAL FUNCTION testSerialPrivate() RESULT(isCorrect)
        INTEGER :: x, y
        INTEGER :: errors
        errors = 0
        x = 5
        y = 10
        !$acc enter data copyin(x, y)
        !$acc serial private(y)
            y = x + 2
        !$acc end serial
        !$acc exit data copyout(x, y)
        ! After the serial region, y should still be 10 if private worked, not 7.
        IF (y /= 10) errors = errors + 1
        IF (errors == 0) THEN
            isCorrect = .TRUE.
        ELSE
            isCorrect = .FALSE.
        END IF
    END FUNCTION testSerialPrivate
END MODULE testModule

PROGRAM main
    USE testModule
    IMPLICIT NONE
    LOGICAL :: failed
    INTEGER :: failcode, testrun

    failcode = 0
    failed = .FALSE.

    DO testrun = 1, 1 ! Assuming NUM_TEST_CALLS = 1 for simplicity
        failed = failed .OR. .NOT. testSerialPrivate()
    END DO
    IF (failed) THEN
        failcode = 1
    END IF

    CALL EXIT(failcode)
END PROGRAM main