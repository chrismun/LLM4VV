#ifndef T1
!T1:acc copyin,V:2.7-2.7
      LOGICAL FUNCTION test1()
        USE OPENACC
        IMPLICIT NONE

        INTEGER, DIMENSION(:), ALLOCATABLE :: h_data
        INTEGER, DEVICE :: d_data(10)

        INCLUDE "acc_testsuite.Fh"

        INTEGER :: errors = 0
        INTEGER :: bytes = 10 * 4  ! Array size * sizeof(int)
        INTEGER :: i
        ALLOCATE(h_data(10))

        DO i = 1, 10
          h_data(i) = i
        END DO

        CALL acc_copyin(h_data, bytes)

        IF (ANY(d_data /= h_data)) THEN
          errors = errors + 1
        END IF

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
      END PROGRAM main