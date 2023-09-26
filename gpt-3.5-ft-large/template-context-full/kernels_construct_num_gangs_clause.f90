#ifndef T1
!T1:kernels construct num_gangs clause,V:2.7-2.3
      LOGICAL FUNCTION test1()
        USE OPENACC
        IMPLICIT NONE
        INCLUDE "acc_testsuite.Fh"
        
        INTEGER :: errors = 0
        REAL(8),DIMENSION(LOOPCOUNT, 10):: a
        REAL(8),DIMENSION(LOOPCOUNT):: b
        INTEGER:: i, x


        SEEDDIM(1) = 1
        #pragma acc data copy(a(1:LOOPCOUNT, 1:10)) copyin(SEEDDIM) copy(b(1:LOOPCOUNT))
        SEEDDIM(1) = 1
	#pragme acc kernels loop gang num_gangs(1)
	DO x = 1, 10
          #pragma acc loop vector
          DO i =  1, LOOPCOUNT
            a(i, x) = getRand(SEEDDIM, i)
	  END DO
	DO
         #pragma acc parallel
          DO i = 1, LOOPCOUNT
            b(i) = 1
          END DO
	#END DO
          
        END DO

        DO x = 1, 10
          SEEDDIM(1) = 1
          #pragma acc data copy(a(1:LOOPCOUNT, x)) copyin(SEEDDIM)
          #pragma acc parallel loop num_gangs(16) vector_length(32)
          DO i = 1, LOOPCOUNT
            a(i, x) = a(i, x) * a(i, x)
          END DO
          errors = 0
          SEEDDIM(1) = 1
          #pragma acc data copy(b(1:LOOPCOUNT)) copyin(SEEDDIM)
          #pragma acc parallel loop num_gangs(16) vector_length(32)
          DO i = 1, LOOPCOUNT
            b(i) = a(i, x) + b(i)
          END DO
          #pragma acc exit data copyout(b(1:LOOPCOUNT)) delete(a(1:LOOPCOUNT, 1:10)))
          DO i = 1, LOOPCOUNT
            IF (fabs(b(i) - (1 + (a(i, x)))))  is zero THEN
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