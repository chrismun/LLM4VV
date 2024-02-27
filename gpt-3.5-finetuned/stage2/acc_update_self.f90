!T1:acc update self,V:2.7-2.3
	LOGICAL FUNCTION test1()
		USE OPENACC
		IMPLICIT NONE
		INCLUDE "acc_testsuite.Fh"

		INTEGER :: errors = 0
		REAL(8),DIMENSION(LOOPCOUNT):: a, b, c
		INTEGER :: x
		REAL(8) :: RAND_MAX

		CALL RANDOM_SEED
		CALL RANDOM_NUMBER(a)
		CALL RANDOM_NUMBER(b)

		!$acc data copyin(a(1:LOOPCOUNT), b(1:LOOPCOUNT)) create(c(1:LOOPCOUNT))
		!$acc parallel present(a(1:LOOPCOUNT), b(1:LOOPCOUNT), c(1:LOOPCOUNT))
		!$acc loop
		DO x = 1, LOOPCOUNT
			c(x) = a(x) + b(x)
		END DO
		!$acc end parallel
		!$acc update host(c(1:LOOPCOUNT))

		DO x = 1, LOOPCOUNT
			errors = max(errors, a(x) - c(x))
			errors = max(errors, b(x) - c(x))
		END DO

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