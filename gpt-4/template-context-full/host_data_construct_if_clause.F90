#ifndef T1
!T1:host_data construct if clause,V:2.7-2.3
      LOGICAL FUNCTION test1()
        USE OPENACC
        IMPLICIT NONE
        INCLUDE "acc_testsuite.Fh"
        
        INTEGER :: errors = 0
        INTEGER, DIMENSION(:), ALLOCATABLE, HOST :: a
        INTEGER, DIMENSION(:), ALLOCATABLE, DEVICE :: b
        LOGICAL :: is_present

        ALLOCATE(a(100), b(100))

        ! Initialize array
        a = 1
        b = 0

        !$ACC HOST_DATA USE_DEVICE(b) IF (.false.)
          b = a
        !$ACC END HOST_DATA

        ! Check if data present on device
        is_present = acc_is_present(b, SIZEOF(b))

        IF (.not. is_present) THEN
          errors = errors + 1
        ENDIF

        DEALLOCATE(a, b)

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