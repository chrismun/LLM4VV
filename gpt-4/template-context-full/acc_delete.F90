#ifndef T1
!T1:acc delete,V:2.7-2.3
      LOGICAL FUNCTION test1()
        USE OPENACC
        IMPLICIT NONE
        INCLUDE "acc_testsuite.Fh"
        
        INTEGER, DIMENSION(:), ALLOCATABLE :: testArr
        INTEGER :: errors = 0
        INTEGER :: i

        ALLOCATE (testArr(100))
        FORALL (i = 1:100) testArr(i) = i

        !$ACC ENTER DATA COPYIN(testArr)

        FORALL (i = 1:100) testArr(i) = 0

        !$ACC UPDATE DEVICE(testArr)

        CALL acc_delete (testArr)

        IF (errors .eq. 0) THEN
          test1 = .TRUE.
        ELSE
          test1 = .FALSE.
        END IF
      END FUNCTION test1
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
      END PROGRAM main