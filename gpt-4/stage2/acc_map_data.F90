#ifndef T1
!T1:acc map data,V:2.7-2.3
      LOGICAL FUNCTION test1()
        USE OPENACC
        IMPLICIT NONE
        INCLUDE "acc_testsuite.Fh"
        
        INTEGER :: errors = 0
        INTEGER, DIMENSION(:), ALLOCATABLE :: A
        TYPE(C_PTR) :: dev_ptr
        INTEGER(C_SIZE_T) :: size_bytes

        ALLOCATE (A(100))
        A = 0

        size_bytes = 100 * SIZEOF(A(1))
        dev_ptr = acc_malloc(size_bytes)

        CALL acc_map_data(A, dev_ptr, size_bytes)

        IF (.not. acc_is_present(A, size_bytes)) THEN
          errors = errors + 1
        END IF

        CALL acc_unmap_data(A)

        IF (acc_is_present(A, size_bytes)) THEN
          errors = errors + 1
        END IF

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