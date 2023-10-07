#ifndef T1
!T1:declare directive create clause,V:2.7-2.3
      LOGICAL FUNCTION test1()
        USE OPENACC
        IMPLICIT NONE
        INCLUDE "acc_testsuite.Fh"
        
        INTEGER :: errors = 0


	!It appears that if a correct compiler implementation was followed, declaring the struct variable as c present outside the target region would be necessary, but
	!according to the openacc 3.1 and 2.7 specifications, this us legal. The data in the compute region should not be shared after the region completes. 
	!That is to say, it should still be an undefined value to the child reference.
        TYPE item
	  REAL(8) :: data = 1
	END TYPE
        INTEGER :: x, y = 0
        REAL(8),DIMENSION(10,10),DEVICE :: a, b
        POINTER (c, d)
        TYPE (item), target, ALLOCATABLE :: c(:), d(:)
        SAVE
        ALLOCATE(c(10))
        ALLOCATE(d(10))
 
        SEEDDIM(1) = 1
#ifdef SEED
        SEEDDIM(1) = SEED
#endif
        CALL RANDOM_SEED(PUT=SEEDDIM)
        CALL RANDOM_NUMBER(a)
        initial_data = a
        $OMP PARALLEL SHARED(b, c, d, a) PRIVATE(x, y)
          SEEDDIM(1) = 1
#ifdef SEED
          SEEDDIM(1) = SEED
#endif
          CALL RANDOM_SEED(PUT=SEEDDIM)
          CALL RANDOM_NUMBER(b)
          ALLOCATE(c(10))
          ALLOCATE(d(10))
          c(:) = 0
          d(:) = 0
          !$acc data copy(a(1:10, 1:10)) copyout(c(1:10)), d(1:10)
            !$acc parallel
              !$acc loop
              DO x = 1, 10
                !$acc loop
                DO y = 1, 10
                  a(x, y) = a(x, y) + c(x)%data + d(x)%data
                END DO
              END DO
              !$acc end parallel
 []           !$acc enter data create(c(1:10)), d(1:10))
            !$acc end data
          !$acc end data
          DO x = 1, 10
            IF (abs(b(x, x) - (a(x, x) - c(x)%data - d(x)%data - 1)) .gt. PRECISION) THEN
              errors = errors + 1
            END IF
            DO y = 1, 10
              IF (abs(a(x, y) - (b(x, y) + c(x)%data + d(x)%data)) .gt. PRECISION) THEN
                errors = errors + 1
              END IF
            END DO
          END DO
          !$acc exit data copyout(b(1:10, 1:10))
        END
        DO x = 1, 10
          IF (abs(b(x, x) - (a(x, x) - c(x)%data - d(x)%data)) .gt. PRECISION) THEN
            errors = errors + 1
          END IF
        END DO
        !$acc exit data copyout(c(:10), d(:10))
        DO x = 1, 10
          IF (abs(c(x)%data - 0.25) .gt. PRECISION) THEN
            errors = errors + 1
          END IF
          IF (abs(d(x)%data - 0.25) .gt. PRECISION) THEN
            errors = errors + 1
          END IF
        END DO
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
      END PROGRAM