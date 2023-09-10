#ifndef T1
!T1:parallel construct num_gangs clause,V:2.7-2.3
      LOGICAL FUNCTION test1()
        USE OPENACC
        IMPLICIT NONE
        INCLUDE "acc_testsuite.Fh"

        INTEGER :: errors = 0
        INTEGER, DIMENSION(:), ALLOCATABLE :: array
        INTEGER :: size = 1000
        INTEGER :: i, parallel_gang_number
        ALLOCATE (array (size))

        DO i = 1, size
          array(i) = -1
        END DO

        parallel_gang_number = 10
        !$acc parallel num_gangs(parallel_gang_number) copy(array)
        DO i = 1, size
          array(i) = i
        END DO
        !$acc end parallel

        DO i = 1, size
          IF (array(i) /= i) THEN
            errors = errors + 1
          END IF
        END DO

        DEALLOCATE(array)

        IF (errors .eq. 0) THEN
          test1 = .FALSE.
        ELSE
          test1 = .TRUE.
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