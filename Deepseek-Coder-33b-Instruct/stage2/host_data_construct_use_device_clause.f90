#ifndef T1
!T1:host_data construct use_device clause,V:2.7-2.3
      LOGICAL FUNCTION test1()
        USE OPENACC
        IMPLICIT NONE
        INCLUDE "acc_testsuite.Fh"
        
        INTEGER :: errors = 0
        INTEGER, PARAMETER :: N = 100
        REAL, DIMENSION(N) :: a, b
        REAL, DIMENSION(:), ALLOCATABLE :: c
        INTEGER :: i

        ! Initialize arrays
        DO i = 1, N
          a(i) = i * 1.0
          b(i) = i * 2.0
        END DO

        ! Allocate c on the device
        ALLOCATE(c(N))

        ! Copy a and b to the device
        !$acc data copyin(a, b) copy(c)

        ! Use the device address of c in a parallel region
        !$acc host_data use_device(c)
        !$acc parallel present(c)
        !$acc loop
        DO i = 1, N
          c(i) = a(i) + b(i)
        END DO
        !$acc end parallel
        !$acc end host_data

        !$acc end data

        ! Check the results
        DO i = 1, N
          IF (c(i) .ne. (a(i) + b(i))) THEN
            errors = errors + 1
          END IF
        END DO

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