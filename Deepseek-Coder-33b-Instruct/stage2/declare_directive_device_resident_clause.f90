!T1:declare directive device_resident clause,V:2.7-2.3
      LOGICAL FUNCTION test1()
        USE OPENACC
        IMPLICIT NONE
        INCLUDE "acc_testsuite.Fh"
        
        INTEGER :: errors = 0
        INTEGER, DIMENSION(:), ALLOCATABLE :: a
        INTEGER, DIMENSION(:), ALLOCATABLE :: a_dev
        INTEGER :: i

        ! Allocate host memory
        ALLOCATE(a(10))
        a = 1

        !$acc data copyin(a) create(a_dev)
        !$acc declare create(a_dev) device_resident(a_dev)

        !$acc parallel loop present(a, a_dev)
        DO i = 1, 10
          a_dev(i) = a(i)
        END DO

        !$acc end data

        ! Check if the data is in device memory
        !$acc data copy(a_dev)
        !$acc parallel loop present(a_dev)
        DO i = 1, 10
          IF (a_dev(i) .ne. 1) THEN
            errors = errors + 1
          END IF
        END DO
        !$acc end data

        ! Deallocate host memory
        DEALLOCATE(a)

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