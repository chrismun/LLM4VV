!This tests the OpenACC kernels construct private clause.
!Test file is to test fortran
#ifndef _PRIVATE_H
  #define _PRIVATE_H

!T1:kernels construct private clause, V:2.7-2.3
      #include "acc_testsuite.Fh"
      LOGICAL FUNCTION test1()
        USE OPENACC
        IMPLICIT NONE
        
        INTEGER :: errors = 0
        INTEGER, DIMENSION(:), ALLOCATABLE :: arr
        INTEGER, DIMENSION(:), ALLOCATABLE :: result
        INTEGER :: i, len, temp
        
        len = 1000
        ALLOCATE(arr(len))
        ALLOCATE(result(len))
        
        arr = 1
        result = 0
        
        !$ACC Kernels Private(temp)
        DO i = 1, len
          temp = arr(i)
          result(i) = temp
        END DO
        !$ACC End Kernels
        
        DO i = 1, len
          IF (arr(i) .NE. result(i)) THEN
            errors = errors + 1
          END IF
        END DO

        DEALLOCATE(arr, result)
        
        IF (errors .eq. 0) THEN
          test1 = .TRUE.
        ELSE
          test1 = .FALSE.
        END IF
      END FUNCTION test1


    PROGRAM main
        USE OpenACC
        IMPLICIT NONE
        INTEGER :: failcode
        LOGICAL :: failed
        INTEGER, EXTERNAL :: test1
        INTEGER :: testrun, NUM_TEST_CALLS

        NUM_TEST_CALLS = 100
        failcode = 0
        failed = .FALSE.
        
        
        DO testrun = 1, NUM_TEST_CALLS
          IF (test1() .EQV. .FALSE.) THEN
            failed = .TRUE.
          END IF
        END DO

        IF(failed) THEN
          failcode = 1
        END IF

        CALL EXIT(failcode)

    END PROGRAM main

#endif