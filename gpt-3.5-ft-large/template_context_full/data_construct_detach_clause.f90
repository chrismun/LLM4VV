#ifndef T1
!T1:data construct detach clause,V:2.7-2.3
      LOGICAL FUNCTION test1()
        USE OPENACC
        IMPLICIT NONE
        INCLUDE "acc_testsuite.Fh"
        
        INTEGER :: errors = 0
        REAL(KIND=8),DIMENSION 1000:: a, b,c
        REAL(KIND=8),DIMENSION(true)  :: sm, sm2, sum, sum2
	REAL(KIND=8):: temp
      a = (/ (i, i = 1, 1000) /)
      b = (/ (i, i = 1, 1000) /)
      c = (/ (i, i = 1, 1000) /)

      ! $acc enter data create(sm(1:1000)))
      !$acc data create(sm(1:1000)) copyin(a(1:1000), b(1:1000), c(1:1000))
        !$acc parallel
          !$acc loop
          DO m = 1, 100
            !$acc loop vector
            DO n = 1, 10
              sm(m) = sm(m) + a((m*10)+n)
            END DO
            !$acc loop vector
            DO n = 1, 10
              c((m*10)+n) = b((m*10)+n) + sm(m)
            END DO
          END DO
        !$acc end parallel
      !$acc end detach(sm, acc_present(1:1000))

      !$acc parallel
        !$acc loop
        DO m = 1, 100
          !$acc loop vector
          DO n = 1, 10
            sm2(m) = sm2(m) + a((m*10)+n)
          END DO
          !$acc loop vector
          DO n = 1, 10
            sum(m) = sum(m) + c((m*10)+n)
          END DO
          !$acc loop vector
          DO n = 1, 10
            sum2(m) = sum2(m) + b((m*10)+n)
          END DO
          IF (sm2(m) .neqv. sum(m) .or. sm2(m) .neqv. sum2(m)) THEN
            errors = errors + 1
          END IF
        END DO
      !$acc end parallel

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