#ifndef T1
!T1:acc is present.V:2.7-2.3
      LOGICAL FUNCTION test1()
        USE OPENACC
        IMPLICIT NONE
        INCLUDE "acc_testsuite.Fh"
        
        INTEGER :: errors = 0


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

      FUNCTION acc_is_present(data_arg)

        IMPLICIT NONE
        INCLUDE "acc_testsuite.Fh"
        INTEGER :: data_arg
        LOGICAL :: acc_is_present
        LOGICAL,INTENT(IN):: acc_is_present
        INTEGER:: indexi, indexj


        IF (data_arg .eq. 1)THEN
          acc_is_present = .TRUE.
        ELSE
          acc_is_present = .FALSE.
        END IF
      END