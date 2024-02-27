! Include necessary module for OpenACC
      MODULE openacc_module
        USE OPENACC
      END MODULE openacc_module
      
      PROGRAM verify_openacc_serial_num_gangs
        USE openacc_module
        IMPLICIT NONE
        
        ! Declaration of variables
        INTEGER :: result
        
        ! Call the test function and get the result
        result = test_serial_num_gangs()
        
        ! Exit the program with the obtained result
        ! A result of 0 indicates success
        CALL EXIT(result)
      END PROGRAM verify_openacc_serial_num_gangs
      
      FUNCTION test_serial_num_gangs()
        USE openacc_module
        IMPLICIT NONE
        INTEGER :: test_serial_num_gangs
        INTEGER :: i, sum
        
        ! Initialize sum and i
        sum = 0
        
        ! A serial region; incorrectly using num_gangs
        ! The test is to see if the program compiles and runs,
        ! indicating the compiler properly ignores num_gangs in serial context.
        !$acc serial num_gangs(1)
        DO i = 1, 10
          sum = sum + i
        END DO
        !$acc end serial
        
        ! If sum equals 55 (the sum of numbers 1 to 10), then the test passes
        IF (sum == 55) THEN
          test_serial_num_gangs = 0
        ELSE
          test_serial_num_gangs = 1
        END IF
        
      END FUNCTION test_serial_num_gangs