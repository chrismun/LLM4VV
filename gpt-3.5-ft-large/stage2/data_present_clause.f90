#ifndef T1
!T1:data present clause,V:2.7-2.3
      LOGICAL FUNCTION test1()
        USE OPENACC
        IMPLICIT NONE
        INCLUDE "acc_testsuite.Fh"

        INTEGER :: errors = 0
	      REAL(8),DIMENSION(LOOPCOUNT, 10):: a, b, c
	      INTEGER,DIMENSION(LOOPCOUNT, 2):: devtest
	      INTEGER:: x, y, temp
	      REAL(8):: pivot
                                
       	devtest = 1
       	IF (acc_is_present(devtest)) THEN
           	 acc_update_device(devtest, sizeof(devtest(1,1)))
       	ELSE
           	acc_create(devtest, sizeof(devtest(1,1)))
       	END IF

        !$acc enter data copyin(devtest(1:LOOPCOUNT, 1:2))
       	DO x = 1, LOOPCOUNT
           	pivot = 0
           	DO y = 1, 10
               	a(x, y) = a(x, y) + pivot
               	b(x, y) = b(x, y) + pivot
               	pivot = pivot + 1
           	END DO
           	c(x, 1) = 0
       	END DO
        !$acc data copyout(c(1:LOOPCOUNT, 1:1))) present(a(1:LOOPCOUNT,1:10), b(1:LOOPCOUNT, 1:10))
          !$acc parallel
            !$acc loop
            DO x = 1, LOOPCOUNT
              temp = 0
              DO y = 1, 10
                temp = temp + a(x, y) + b(x, y)
              END DO
              c(x, 1) = temp / 20
            END DO
          !$acc end parallel
        !$acc end data
        DO x = 1, LOOPCOUNT
          DO y = 1, 10
            IF (abs(c(x, 1) - (a(x, y) + b(x, y)) / 2) .gt. PRECISION) THEN
              errors = errors + 1
          END DO
        END DO

        acc_delete(devtest, sizeof(devtest(1, 1)))

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