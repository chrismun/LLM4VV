!T1:acc delete,V:2.7-2.3
      LOGICAL FUNCTION test1()
        USE OPENACC
        IMPLICIT NONE
        INCLUDE "acc_testsuite.Fh"

        INTEGER, PARAMETER :: n = 1024
        REAL, DIMENSION(n) :: a, a_host
        INTEGER :: i, errors = 0

        ! Initialize host array
        DO i = 1, n
          a(i) = REAL(i)
        END DO

        ! Allocate and initialize device array
        !$acc enter data copyin(a(1:n))

        ! Modify array on the device
        !$acc parallel loop present(a)
        DO i = 1, n
          a(i) = a(i) + 1.0
        END DO

        ! Copyout array to host and delete from device
        !$acc exit data copyout(a(1:n))

        ! Validate modification was successful
        errors = 0
        DO i = 1, n
          IF (a(i) /= REAL(i) + 1.0) THEN
            errors = errors + 1
          END IF
        END DO

        ! Use acc_delete to remove the data from the device
        CALL acc_delete(a, SIZEOF(a))

        IF (errors .eq. 0) THEN
          test1 = .FALSE.
        ELSE
          test1 = .TRUE.
        END IF
      END FUNCTION test1

      PROGRAM main
        IMPLICIT NONE
        INTEGER :: failcode, testrun
        LOGICAL :: failed
        INCLUDE "acc_testsuite.Fh"
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
      END PROGRAM