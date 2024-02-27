      !T1:acc memcpy from device,V:2.7-2.3
      LOGICAL FUNCTION test1()
        USE OPENACC
        IMPLICIT NONE
        INCLUDE "acc_testsuite.Fh"
        
        INTEGER :: errors = 0
        INTEGER, PARAMETER :: N = 100
        REAL(KIND=4), DIMENSION(N) :: a, a_host, a_dev
        INTEGER :: i

        ! Initialize host array
        DO i = 1, N
          a_host(i) = REAL(i)
        END DO

        ! Copy host array to device
        CALL acc_copyin(a_host, N)

        ! Copy device array to host
        CALL acc_memcpy_from_device(a_dev, C_LOC(a_host), N*4)

        ! Compare host and device arrays
        DO i = 1, N
          IF (a_host(i) .ne. a_dev(i)) THEN
            errors = errors + 1
          END IF
        END DO

        IF (errors .eq. 0) THEN
          test1 = .FALSE.
        ELSE
          test1 = .TRUE.
        END IF
      END

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
        CALL EXIT (failcode)
      END PROGRAM