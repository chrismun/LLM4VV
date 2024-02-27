! Example to test OpenACC copyout clause functionality
!T1:data construct copyout clause,V:2.7-2.3
      LOGICAL FUNCTION test1()
        USE OPENACC
        IMPLICIT NONE
        ! INCLUDE "acc_testsuite.Fh" ! Include this if you have a specific test suite header; adjust the path as needed.
        
        INTEGER :: errors = 0
        INTEGER, DIMENSION(10) :: a_host, a_expected
        INTEGER :: i
        
        ! Inititalize expected values
        DO i = 1, 10
            a_expected(i) = i
        END DO
        
        ! OpenACC region to initialize device array and copy it out to host
        !$acc data copyout(a_host)
        !$acc parallel loop
        DO i = 1, 10
            a_host(i) = i
        END DO
        !$acc end data
        
        ! Check if the data copied out matches the expected values
        DO i = 1, 10
            IF (a_host(i) /= a_expected(i)) THEN
                errors = errors + 1
            END IF
        END DO

        IF (errors .eq. 0) THEN
          test1 = .FALSE. ! If no errors, return FALSE (0).
        ELSE
          test1 = .TRUE.  ! If there are errors, return TRUE (nonzero).
        END IF
      END FUNCTION test1

      PROGRAM main
        IMPLICIT NONE
        INTEGER :: failcode, testrun
        LOGICAL :: failed
        ! INCLUDE "acc_testsuite.Fh" ! Include this if applicable for overarching test infrastructure.
        EXTERNAL :: test1
        failed = .FALSE.
        failcode = 0
        failed = test1() ! Run test1, check if it fails
        IF (failed) THEN
          failcode = failcode + 2 ** 0
        END IF
        CALL EXIT(failcode)
      END PROGRAM main