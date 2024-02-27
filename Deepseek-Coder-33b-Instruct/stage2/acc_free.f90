!T1:acc free,V:2.7-2.3
      LOGICAL FUNCTION test1()
        USE OPENACC
        USE ISO_C_BINDING
        IMPLICIT NONE
        INCLUDE "acc_testsuite.Fh"
        
        INTEGER :: errors = 0
        TYPE(C_PTR) :: data_dev
        INTEGER(C_SIZE_T) :: num_bytes
        INTEGER :: stat

        ! Allocate memory on the device
        num_bytes = 100 * SIZEOF(1)
        stat = acc_malloc(data_dev, num_bytes)
        IF (stat .ne. 0) THEN
          errors = errors + 1
        END IF

        ! Free the memory
        CALL acc_free(data_dev)

        ! Check if the memory has been freed
        stat = acc_is_present(data_dev, num_bytes)
        IF (stat .eq. 0) THEN
          errors = errors + 1
        END IF

        IF (errors .eq. 0) THEN
          test1 = .FALSE.
        ELSE
          test1 = .TRUE.
        END IF
      END

      PROGRAM main
        IMPLICIT NONE
        INTEGER :: failcode, testrun
        LOGICAL :: failed
        INCLUDE "acc_testsuite.Fh"
        LOGICAL :: test1
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
      END PROGRAM