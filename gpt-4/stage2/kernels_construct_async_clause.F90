#ifndef T1
!T1:kernels construct async clause,V:2.7-2.3
      LOGICAL FUNCTION test1()
        USE OPENACC
        IMPLICIT NONE
        INCLUDE "acc_testsuite.Fh"
        INTEGER, PARAMETER :: N=1000
        INTEGER :: i
        REAL, DIMENSION(N) :: a, b, c, c_host

        ! Initialize data
        DO i = 1, N
          a(i) = REAL(i)
          b(i) = REAL(2*i)
        END DO

        !$acc enter data copyin(a, b) create(c)

        !$acc kernels async
        DO i = 1, N
          c(i) = a(i) * b(i)
        END DO
        !$acc wait

        !$acc exit data copyout(c)

        ! Check results on host
        DO i = 1, N
          c_host(i) = a(i) * b(i)
        END DO

        ! If any error found, return TRUE
        DO i = 1, N
          IF(ABS(c(i) - c_host(i)) > 1e-5) THEN
            test1 = .TRUE.
            RETURN
          END IF
        END DO

        test1 = .FALSE.    ! Return FALSE if no error
      END FUNCTION
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