! Ensure the OpenACC module is available
MODULE openacc_module
    USE OPENACC
END MODULE openacc_module

!T1:reference counters,V:2.7-2.3
      LOGICAL FUNCTION test1()
        USE openacc_module
        IMPLICIT NONE
        INCLUDE "acc_testsuite.Fh"

        INTEGER :: errors = 0
        INTEGER, DIMENSION(:), ALLOCATABLE :: host_array
        INTEGER :: devptr
        INTEGER :: arrsize
        
        arrsize = 100
        ALLOCATE(host_array(arrsize))

        ! Mimic device allocation and reference counting
        host_array = 1
        ! Increment dynamic ref counter
        devptr = acc_copyin(host_array, arrsize * SIZEOF(host_array(1)))

        ! Mimic modification within a data region, then exit it
        ! Supposedly no effect on dynamic ref counter
        !$acc data present(host_array)
        host_array = 2
        !$acc end data

        ! Decrement dynamic ref counter
        CALL acc_delete(host_array, arrsize * SIZEOF(host_array(1)))

        ! Check if the array is still present on the device
        ! Since dynamic counter is decremented to 0, array should not be present
        IF (acc_is_present(host_array, arrsize * SIZEOF(host_array(1)))) THEN
          errors = errors + 1
        END IF

        DEALLOCATE(host_array)
        
        ! Evaluating test result based on errors
        IF (errors .eq. 0) THEN
          test1 = .FALSE.
        ELSE
          test1 = .TRUE.
        END IF
      END FUNCTION test1

      PROGRAM main
        USE openacc_module
        IMPLICIT NONE
        INTEGER :: failcode, testrun
        LOGICAL :: failed
        INCLUDE "acc_testsuite.Fh"
        EXTERNAL :: test1
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