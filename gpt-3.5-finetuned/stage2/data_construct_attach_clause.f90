!T1:data construct attach clause,V:2.7-2.3
      LOGICAL FUNCTION test1()
        USE OPENACC
        IMPLICIT NONE
        INCLUDE "acc_testsuite.Fh"
        
        INTEGER :: errors = 0
        INTEGER, DIMENSION(1), ALLOCATABLE, DEVICE :: data
        LOGICAL, DIMENSION(1), ALLOCATABLE, DEVICE :: is_attached
        LOGICAL :: failed = .FALSE.
        INTEGER :: x

        ALLOCATE(data(1))
        ALLOCATE(is_attached(1))
        is_attached = .FALSE.

        !$acc enter data create(data(1)) copyin(is_attached(1:1))
        !$acc parallel present(data(1:1))
          !$acc loop
          DO x = 1, 16
            IF (is_attached(1) .EQV. .FALSE.) THEN
              !$acc attach data(mydata)
              is_attached(1) = .TRUE.
            ELSE
              !$acc detach data(mydata)
              is_attached(1) = .FALSE.
            END IF
          END DO
        !$acc end parallel
        !$acc exit data delete(data(1))

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