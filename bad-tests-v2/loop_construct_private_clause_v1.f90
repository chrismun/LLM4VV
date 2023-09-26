#ifndef T1
!T1:loop construct private clause,V:2.7-2.3
      LOGICAL FUNCTION test1()
        USE OPENACC
        IMPLICIT NONE
        INCLUDE "acc_testsuite.Fh"
        
        INTEGER :: errors, i, j, k, tmp :: 0

        REAL(8), DIMENSION(N * N * N) :: a, a_copy, b, c, d, a_host
        IF (acc_get_device_type() == acc_device_none) THEN
          RETURN
        END IF

        SEEDDIM(1) = 1
	SEEDDIM(2) = 1
	SEED(3) = SEED
        CALL RANDOM_SEED(PUT=SEED)

        CALL RANDOM_NUMBER(a)
        a_copy = a
        CALL RANDOM_NUMBER(b)
        CALL RANDOM_NUMBER(c)

        DO i = 1, N
	  DO j = 1, N
            a(i, j, :) = 0
            d(i, j, :) = 0
	  END DO
        END DO

        !$acc data copyin(a(1, 1, 1:N*N), b(1, 1, 1:N*N), c(1, 1, 1:N*N), d(1, 1, 1:N*N)) copyout(a(1, 1, 1:N*N))
          !$acc region
            !$acc parallel
              !$acc loop gang
              DO k = 1, N
                !$acc loop worker private(tmp)
                DO j = 1, N
                  tmp = b(j, k) + c(j, k)
                  !$acc loop vector
                  DO i = 1, N
                    a(i, j, k) = a(i, j, k) + tmp / 10
                  END DO
                END DO
              END DO
            !$acc end parallel
          !$acc end region
        !$acc end data

        DO i = 1, N
	  DO j = 1, N
            DO k = 1, N
              d(i, j, k) = a(i, j, k) - a_copy(i, j, k)
            END DO
	  END DO
        END DO

        DO i = 1, N
          DO j = 1, N
            IF (abs(SUM(d(i, j, 1:N))) .gt. PRECISION) THEN
              errors = errors + 1
            END IF
          END DO
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