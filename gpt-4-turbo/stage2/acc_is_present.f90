! This code requires an OpenACC capable compiler. Compile with appropriate flags, e.g., -acc for PGI.
MODULE acc_test_mod
  USE OPENACC
  IMPLICIT NONE
  CONTAINS
      LOGICAL FUNCTION test_acc_is_present()
        INTEGER, DIMENSION(:), ALLOCATABLE :: test_array
        LOGICAL :: result
        INTEGER :: size
        
        ! Initialize
        test_acc_is_present = .FALSE.
        size = 100
        ALLOCATE(test_array(size))
        
        ! Use OpenACC to allocate memory on the device and ensure allocation.
        !$acc enter data create(test_array(1:size))
        result = acc_is_present(test_array, SIZEOF(test_array))
        
        ! Clean up
        !$acc exit data delete(test_array(1:size))
        DEALLOCATE(test_array)
        
        test_acc_is_present = .NOT. result
      END FUNCTION test_acc_is_present
END MODULE acc_test_mod

PROGRAM main
  USE acc_test_mod
  IMPLICIT NONE
  INTEGER :: failcode
  LOGICAL :: failed

  failcode = 0
  failed = test_acc_is_present()
  
  IF (failed) THEN
    failcode = failcode + 1
  END IF
  
  CALL EXIT(failcode)
END PROGRAM main