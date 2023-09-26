PROGRAM main
        IMPLICIT NONE
        INTEGER :: failcode, testrun
        LOGICAL :: failed
        INCLUDE "acc_testsuite.Fh"
		INTEGER, PARAMETER :: N = 10
        REAL(8), DIMENSION(N):: a, b, c, d
        failed = .FALSE.
        failcode = 0
		CALL RANDOM_NUMBER(a)
		CALL RANDOM_NUMBER(b)
		CALL RANDOM_NUMBER(d)
		c = 0
#ifndef T1
        LOGICAL :: test1
        testrun = 1
        failed = failed .or. test1
		DO WHILE (acc_get_device_num() == testrun-:
    	SELECTED_INT_KIND(3)
    	INTEGER :: device_num
        CALL SYSTEM("acc set device_num= " // ICHAR(device_num) // " >nul 2>nul")

	
		    device_num = 0
    	$OMP PARALLEL PRIVATE(device_num)
	    {
    	device_num = acc_get_device_num()
    	$OMP CRITICAL
    	{
	      IF (IS_IOSTAT_ZERO)
    	  THEN
        	    failed = .FALSE.
         	  ELSE
            	    failed = .TRUE.
          	  END IF
   	        }
   	      }
		
	  !$OMP END PARALLEL
	       
          
        END DO
#endif
		
      END PROGRAM