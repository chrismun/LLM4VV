#ifndef T1
!T1:acc map data,V:2.7-2.3
      LOGICAL FUNCTION test1()
        USE OPENACC
        IMPLICIT NONE
        INCLUDE "acc_testsuite.Fh"
        
        INTEGER :: errors = 0
        TYPE(c_ptr) :: data_dev
        TYPE(c_ptr) :: data_arg
        INTEGER(c_size_t) :: bytes
        
        ! Allocate device memory for the data
        data_dev = acc_malloc(bytes)
        
        ! Map the device memory to the host memory
        CALL acc_map_data(data_arg, data_dev, bytes)
        
        ! Check that the data is mapped correctly
        IF (data_arg .ne. data_dev) THEN
          errors = errors + 1
        END IF
        
        ! Free the device memory
        CALL acc_free(data_dev)
        
        IF (errors .eq. 0) THEN
          test1 = .FALSE.
        ELSE
          test1 = .TRUE.
        END IF
      END
#endif