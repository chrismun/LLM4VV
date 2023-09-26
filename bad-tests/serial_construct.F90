!T1:serial construct,V:2.7-2.3
      LOGICAL FUNCTION test1()
        USE OPENACC
        IMPLICIT NONE
        INCLUDE "acc_testsuite.Fh"
        
        INTEGER :: errors = 0
        INTEGER, DIMENSION(10) :: A, B, C
        INTEGER :: i

        A = (/ (i, i = 1, 10) /)
        B = (/ (i, i = 1, 10) /)
        
        !$acc serial
            DO i = 1, 10
              C(i) = A(i) + B(i)
            END DO
        !$acc end serial

        DO i = 1, 10
            IF (C(i) .ne. A(i) + B(i)) THEN
                errors = errors + 1
            END IF
        END DO
 
        IF (errors .eq. 0) THEN
          test1 = .TRUE.
        ELSE
          test1 = .FALSE.
        END IF
      END FUNCTION test1
      
      PROGRAM main
        IMPLICIT NONE
        INTEGER :: failcode = 0
        INTEGER :: num_test_calls = 10
        LOGICAL :: failed = .FALSE.
        LOGICAL :: test1

        DO testrun = 1, num_test_calls
          failed = failed .or. test1()
        END DO

        IF (failed) THEN
          failcode = failcode + 2 ** 0
        END IF

        CALL EXIT (failcode)
      END PROGRAM main