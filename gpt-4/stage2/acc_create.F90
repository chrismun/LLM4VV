#ifndef T1
!T1:acc create,V:2.7-2.3
      LOGICAL FUNCTION test1()
        USE OPENACC
        IMPLICIT NONE
        INCLUDE "acc_testsuite.Fh"

        ! Define variable and array
        INTEGER, DIMENSION(:), ALLOCATABLE :: data_host, data_device
        INTEGER :: dataSize, i, errors = 0

        dataSize = 100
        ALLOCATE(data_host(dataSize))
        ALLOCATE(data_device(dataSize))

        DO i=1, dataSize
            data_host(i) = 1
            data_device(i) = 0
        END DO

        ! Create space on the device for data_device
        CALL acc_create(data_device, dataSize * 4)  ! 4 bytes for each integer

        ! Allocate data
        !$ACC PARALLEL LOOP COPYIN(data_host) COPYOUT(data_device)
        DO i=1, dataSize
            data_device(i) = data_host(i)
        END DO

        ! Check if data was copied correctly
        DO i=1, dataSize
          IF (data_device(i) .NE. data_host(i)) THEN
            errors = errors + 1
          END IF
        END DO

        DEALLOCATE(data_host, data_device)

        IF (errors .eq. 0) THEN
            test1 = .FALSE.
        ELSE
            test1 = .TRUE.
        END IF
      END FUNCTION test1
#endif

      PROGRAM main
        USE OPENACC
        IMPLICIT NONE
        INTEGER :: failcode, testrun
        LOGICAL :: failed
        INCLUDE "acc_testsuite.Fh"
#ifndef T1
        EXTERNAL :: test1
#endif
        failed = .FALSE.
        failcode = 0
#ifndef T1
        DO testrun = 1, NUM_TEST_CALLS
            failed = failed .or. test1()
        END DO
        IF (failed) THEN
            failcode = failcode + 1
            WRITE(*,*) 'test1 failed'
        END IF
#endif
        CALL EXIT (failcode)
      END PROGRAM main