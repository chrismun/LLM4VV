#ifndef T1
        !T1:wait clause,V:2.7-2.3
      LOGICAL FUNCTION test1()
        USE OPENACC
        IMPLICIT NONE
        INCLUDE "acc_testsuite.Fh"
        
        INTEGER :: errors = 0


        
         !Setup Loop
       
        !$acc  data  copy (a(0:n))
        DO CONSTRUCTION_LOOP_COUNTER = 1, LOOP_COUNT
        	!Initialization
        	DO INIT_LOOP_COUNTER = 0, LOOP_COUNT - 1
          	a(INIT_LOOP_COUNTER * n ) = INIT_LOOP_COUNTER
        	END DO
        	
        	!Reference
        	DO TRANSFER_LOOP_COUNTER = 1, TRANSFER_COUNT
        		tmp = a((TRANSFER_LOOP_COUNTER -1) *n + (LOOP_COUNT - n ))   
        		DO REF_LOOP_COUNTER = (TRANSFER_LOOP_COUNTER - 1) * n + TRANSFER_LOOP_COUNTER + (INIT_LOOP_COUNTER * n), n, (LOOP_COUNT * n )
        			a(REF_LOOP_COUNTER) = 0 
        		END DO
        		a((TRANSFER_LOOP_COUNTER -1) * n + (LOOP_COUNT - n)) = tmp
        	END DO
        	
          	 !$acc begin update device(a(0:((n - 1) *  n)))) async
         	 !$acc wait
      
        	!Compute
        	DO VECTOR_LOOP_COUNTER = 0, (LOOP_COUNT - 1)
			DO COMPUTE_LOOP_COUNTER = VECTOR_LOOP_COUNTER, LOOP_COUNT * n, LOOP_COUNT
        		 !$acc compute  present_or_copyin(a(0:n))  wait(a(n * LOOP_COUNT)) 
			 DO ACC_LOOP_COUNTER = 0, n
         		        a( (VECTOR_LOOP_COUNTER * n) + n + ACC_LOOP_COUNTER * LOOP_COUNT) = a(LOOP_COUNT * n + (VECTOR_LOOP_COUNTER * n) + ACC_LOOP_COUNTER)
                          a( LOOP_COUNT * n + (VECTOR_LOOP_COUNTER * n) + ACC_LOOP_COUNTER) = a( (VECTOR_LOOP_COUNTER * n) + n + ACC_LOOP_COUNTER * LOOP_COUNT)
			END DO

       		END DO
        
        
             
       
         !$acc  end  data
      	END DO
        
        
        DO VERIFICATION_LOOP_COUNTER = 0, n * LOOP_COUNT - 1
          IF (ABS(a(VERIFICATION_LOOP_COUNTER) - VERIFICATION_LOOP_COUNTER) .gt. PRECISION) THEN
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