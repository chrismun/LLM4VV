#ifndef T1
!T1:acc is present,V:2.7-2.3
      LOGICAL FUNCTION test1()
        USE OPENACC
        IMPLICIT NONE
        INCLUDE "acc_testsuite.Fh"
        
        INTEGER :: errors = 0
        INTEGER, PARAMETER :: N = 100
        REAL(KIND=4), DIMENSION(N) :: a, b
        INTEGER :: i

        ! Initialize arrays
        DO i = 1, N
          a(i) = i * 1.0
          b(i) = 0.0
        END DO

        ! Copy array to device
        CALL acc_copyin(a)

        ! Check if array is present on device
        IF (.NOT. acc_is_present(a)) THEN
          errors = errors + 1
        END IF

        ! Copy array back to host
        CALL acc_copyout(a)

        ! Check if array is present on host
        IF (acc_is_present(a)) THEN
          errors = errors + 1
        END IF

        IF (errors .eq. 0) THEN
          test1 = .FALSE.
        ELSE
          test1 = .TRUE.
        END IF
      END
#endif

      PROGRAM main
        IMPLICIT NONE
        INTEGER :: failcode, testrun
        LOGICAL :: failed
        INCLUDE "acc_testsuite.Fh"
#ifndef T1
        LOGICAL :: test1
#endif
        failed = .FALSE.
        failcode = 0
#ifndef T1
        DO testrun = 1, NUM_TEST_CALLS
          failed = failed .or. test1()
        END DO
        IF (failed) THEN
          failcode = failcode + 2 ** 0
          failed = .FALSE.
        END IF
#endif
        CALL EXIT (failcode)
      END PROGRAM