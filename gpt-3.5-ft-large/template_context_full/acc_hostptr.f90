#ifndef T1
!T1:acc hostptr,V:2.7-2.3
      LOGICAL FUNCTION test1()
        USE OPENACC
        IMPLICIT NONE
        INCLUDE "acc_testsuite.Fh"
        
        INTEGER :: errors = 0
        INTEGER, ALLOCATABLE, DEVICE :: a(:)
        INTEGER, ALLOCATABLE :: b(:)
        INTEGER, ALLOCATABLE :: c(:)
        INTEGER :: x

        ALLOCATE(a(10), b(10), c(10))
        SEEDDIM(1) = 1
        CALL RANDOM_SEED(PUT=SEEDDIM)        

        DO x = 1, 10
          a(x) = x
        END DO
        !$acc enter data create(b(10))
        !$acc enter data copyin(c(10))

        !$acc data present(b)
          !$acc parallel loop
          DO x = 1, 10
            c(x) = a(x) + b(x)
          END DO
        !$acc end data
        DO x = 1, 10
          IF (c(x) .ne. a(x) + b(x)) THEN
            errors = errors + 1
          END IF
        END DO

        DO x = 1, 10
          b(x) = c(x)
        END DO

        DO x = 1, 10
          IF (acc_hostptr(b(x)) .eq. C_LOC(c(x)))) THEN
            errors = errors + 1
          END IF
        END DO

        !$acc exit data copyout(b(10))

        IF (acc_delete(c, 10 * size(a(1)), 1) .ne. acc_update_host(a, 10 * size(a(1)))) THEN
          errors = errors + 1
        END IF

        IF (acc_hostptr(b) .ne. C_LOC(b(1))) THEN
          errors = errors + 1
        END IF

        IF (acc_delete(b, 10 * size(b(1)))) THEN
          errors = errors + 1
        END IF

        !$acc exit data copyout(b(10))
        
        IF (acc_hostptr(b) .ne. C_NULL_PTR) THEN
          errors = errors + 1
        END IF

        !$acc exit data copyout(c(10))
        DO x = 1, 10
          IF (c(x) .ne. a(x) + b(x)) THEN
            errors = errors + 1
          END IF
        END DO

        IF (acc_delete(c, 10 * size(c(1)))) THEN
          errors = errors + 1
        END IF

        !$acc exit data copyout(b(10))
        DO x = 1, 10
          IF (b(x) .ne. a(x)) THEN
            errors = errors + 1
          END IF
        END DO

        !$acc exit data copyout(b(10))
        IF (acc_delete(b, 10 * size(b(1)))) THEN
          errors = errors + 1
        END IF

        !$acc exit data copyout(b(10))

        IF (acc_delete(a, 10 * size(a(1))))) THEN
          errors = errors + 1
        END IF

        IF (errors .ne. 0) THEN
          test1 = .TRUE.
        ELSE
          test1 = .FALSE.
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
      END PROGRAM