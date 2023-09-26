!T1:acc attach,V:2.7-2.3
      LOGICAL FUNCTION test1()
        USE OPENACC
        IMPLICIT NONE
        INCLUDE "acc_testsuite.Fh"
        
        INTEGER, POINTER :: testData
        INTEGER, DEVICE :: deviceData
        INTEGER :: errors = 0

        ! Allocate host memory
        ALLOCATE (testData)

        ! Initialize host memory
        testData = 5

        ! Attach the pointer to the device
        CALL acc_attach (testData)

        ! Verify that the data is present in the device.
        DEVICEData = testData

        IF (deviceData /= 5) errors = errors + 1

        ! Detach the pointer from the device
        CALL acc_detach (testData)

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
#ifndef T1
        LOGICAL :: test1
#endif
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
      END PROGRAM main