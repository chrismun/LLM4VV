#ifndef T1
!T1:data construct copyin clause,V:2.7-2.3
      LOGICAL FUNCTION test1()
        USE OPENACC
        IMPLICIT NONE
        INCLUDE "acc_testsuite.Fh"
        
        INTEGER :: errors = 0
        INTEGER, DIMENSION(:), ALLOCATABLE :: data_host, data_device
        INTEGER, DIMENSION(:), POINTER :: data_pointer
        INTEGER :: num_errors = 0, i, data_size = 10000

        ALLOCATE(data_host(data_size))
        ALLOCATE(data_device(data_size))
        
        DO i = 1, data_size
            data_host(i) = i
            data_device(i) = 0
        END DO
        
        data_pointer => data_device

        !$ACC Data Copyin(data_pointer(1:data_size))

        !$ACC Parallel Loop
        DO i = 1, data_size
            data_pointer(i) = data_host(i)
        END DO

        !$ACC End Data

        num_errors = COUNT(data_host /= data_device)

        IF(num_errors /= 0) THEN
            errors = num_errors
        END IF

        DEALLOCATE(data_host)
        DEALLOCATE(data_device)

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
        LOGICAL, EXTERNAL :: test1
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