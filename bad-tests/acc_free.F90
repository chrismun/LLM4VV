!File: acc_free_test.f90
MODULE acc_free_test
    USE iso_c_binding, ONLY: c_ptr, c_null_ptr
    USE openacc
IMPLICIT NONE
END MODULE acc_free_test

#ifndef T1
!T1:acc free,V:2.7-2.7
      LOGICAL FUNCTION test1()
        USE OpenACC
        USE iso_c_binding
        IMPLICIT NONE
        INTEGER, PARAMETER :: N = 10
        INTEGER, DIMENSION(:), POINTER :: p
        TYPE(c_ptr) :: dev_mem
        INTEGER :: errors = 0
        INTEGER :: i

        p => NULL()

        ! Allocate memory on the device
        dev_mem = acc_malloc(8 * N)
        IF (dev_mem == c_null_ptr) THEN
            errors = errors + 1
        END IF

        p => c_f_pointer(dev_mem)

        ! Free the memory
        CALL acc_free(dev_mem)
        IF (associated(p)) THEN
            errors = errors + 1
        END IF

        IF (errors .eq. 0) THEN
          test1 = .FALSE.
        ELSE
          test1 = .TRUE.
        END IF
      END FUNCTION test1
#endif

      PROGRAM main
        USE acc_free_test
        IMPLICIT NONE
        INTEGER :: failcode, testrun
        LOGICAL :: failed
#ifndef T1
        LOGICAL :: test1
#endif
        failed = .FALSE.
        failcode = 0
#ifndef T1
        DO testrun = 1, 1
          failed = failed .or. test1()
        END DO
        IF (failed) THEN
          failcode = failcode + 1
          failed = .FALSE.
        END IF
#endif
        IF (failcode /= 0) THEN
          PRINT *, "ACC Free Test Failed"
        ELSE
          PRINT *, "ACC Free Test Success"
        END IF
        CALL EXIT (failcode)
      END PROGRAM main