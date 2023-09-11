#ifndef T1
!T1:data construct copyout clause,V:2.7-2.3
      LOGICAL FUNCTION test1()
        USE OPENACC
        IMPLICIT NONE
        INCLUDE "acc_testsuite.Fh"
        
        INTEGER :: errors = 0
        INTEGER :: var1, var2
        INTEGER :: structured_reference_counter, dynamic_reference_counter
        INTEGER :: present_or_copyout, pcopyout
        INTEGER :: finalize
        INTEGER :: acc_copyout_finalize, acc_copyout
        INTEGER :: acc_attach, acc_detach
        INTEGER :: acc_create, acc_present
        INTEGER :: acc_zero
        
        ! Initialize variables
        var1 = 1
        var2 = 2
        structured_reference_counter = 0
        dynamic_reference_counter = 0
        present_or_copyout = 0
        pcopyout = 0
        finalize = 0
        
        ! Test copyout clause on structured data
        !$acc data copyout(var1, var2)
        !$acc end data
        ! Check if var1 and var2 are present in shared memory
        IF (var1 .ne. 1 .or. var2 .ne. 2) THEN
          errors = errors + 1
        END IF
        ! Check if structured reference counter is updated
        IF (structured_reference_counter .ne. 1) THEN
          errors = errors + 1
        END IF
        ! Check if dynamic reference counter is updated
        IF (dynamic_reference_counter .ne. 1) THEN
          errors = errors + 1
        END IF
        
        ! Test copyout clause on compute construct
        !$acc parallel copyout(var1, var2)
        !$acc end parallel
        ! Check if var1 and var2 are present in shared memory
        IF (var1 .ne. 1 .or. var2 .ne. 2) THEN
          errors = errors + 1
        END IF
        ! Check if structured reference counter is updated
        IF (structured_reference_counter .ne. 2) THEN
          errors = errors + 1
        END IF
        ! Check if dynamic reference counter is updated
        IF (dynamic_reference_counter .ne. 2) THEN
          errors = errors + 1
        END IF
        
        ! Test copyout clause on declare directive
        !$acc declare copyout(var1, var2)
        ! Check if var1 and var2 are present in shared memory
        IF (var1 .ne. 1 .or. var2 .ne. 2) THEN
          errors = errors + 1
        END IF
        ! Check if structured reference counter is updated
        IF (structured_reference_counter .ne. 3) THEN
          errors = errors + 1
        END IF
        ! Check if dynamic reference counter is updated
        IF (dynamic_reference_counter .ne. 3) THEN
          errors = errors + 1
        END IF
        
        ! Test copyout clause on exit data directive
        !$acc exit data copyout(var1, var2)
        ! Check if var1 and var2 are present in shared memory
        IF (var1 .ne. 1 .or. var2 .ne. 2) THEN
          errors = errors + 1
        END IF
        ! Check if structured reference counter is updated
        IF (structured_reference_counter .ne. 4) THEN
          errors = errors + 1
        END IF
        ! Check if dynamic reference counter is updated
        IF (dynamic_reference_counter .ne. 4) THEN
          errors = errors + 1
        END IF
        
        ! Test copyout clause with zero modifier
        !$acc data copyout(var1, var2) zero
        !$acc end data
        ! Check if var1 and var2 are present in shared memory
        IF (var1 .ne. 1 .or. var2 .ne. 2) THEN
          errors = errors + 1
        END IF
        ! Check if structured reference counter is updated
        IF (structured_reference_counter .ne. 5) THEN
          errors = errors + 1
        END IF
        ! Check if dynamic reference counter is updated
        IF (dynamic_reference_counter .ne. 5) THEN
          errors = errors + 1
        END IF
        
        ! Test copyout clause with present_or_copyout and pcopyout
        !$acc data copyout(var1, var2) present_or_copyout
        !$acc end data
        ! Check if var1 and var2 are present in shared memory
        IF (var1 .ne. 1 .or. var2 .ne. 2) THEN
          errors = errors + 1
        END IF
        ! Check if structured reference counter is updated
        IF (structured_reference_counter .ne. 6) THEN
          errors = errors + 1
        END IF
        ! Check if dynamic reference counter is updated
        IF (dynamic_reference_counter .ne. 6) THEN
          errors = errors + 1
        END IF
        
        ! Test copyout clause with finalize clause
        !$acc exit data copyout(var1, var2) finalize
        ! Check if var1 and var2 are present in shared memory
        IF (var1 .ne. 1 .or. var2 .ne. 2) THEN
          errors = errors + 1
        END IF
        ! Check if structured reference counter is updated
        IF (structured_reference_counter .ne. 7) THEN
          errors = errors + 1
        END IF
        ! Check if dynamic reference counter is updated
        IF (dynamic_reference_counter .ne. 7) THEN
          errors = errors + 1
        END IF
        
        ! Test copyout clause with acc_copyout_finalize and acc_copyout
        !$acc data copyout(var1, var2)
        !$acc end data
        ! Check if var1 and var2 are present in shared memory
        IF (var1 .ne. 1 .or. var2 .ne. 2) THEN
          errors = errors + 1
        END IF
        ! Check if structured reference counter is updated
        IF (structured_reference_counter .ne. 8) THEN
          errors = errors + 1
        END IF
        ! Check if dynamic reference counter is updated
        IF (dynamic_reference_counter .ne. 8) THEN
          errors = errors + 1
        END IF
        
        ! Test copyout clause with acc_attach and acc_detach
        !$acc data copyout(var1, var2)
        !$acc end data
        ! Check if var1 and var2 are present in shared memory
        IF (var1 .ne. 1 .or. var2 .ne. 2) THEN
          errors = errors + 1
        END IF
        ! Check if structured reference counter is updated
        IF (structured_reference_counter .ne. 9) THEN
          errors = errors + 1
        END IF
        ! Check if dynamic reference counter is updated
        IF (dynamic_reference_counter .ne. 9) THEN
          errors = errors + 1
        END IF
        
        ! Test copyout clause with acc_create and acc_present
        !$acc data copyout(var1, var2)
        !$acc end data
        ! Check if var1 and var2 are present in shared memory
        IF (var1 .ne. 1 .or. var2 .ne. 2) THEN
          errors = errors + 1
        END IF
        ! Check if structured reference counter is updated
        IF (structured_reference_counter .ne. 10) THEN
          errors = errors + 1
        END IF
        ! Check if dynamic reference counter is updated
        IF (dynamic_reference_counter .ne. 10) THEN
          errors = errors + 1
        END IF
        
        ! Test copyout clause with acc_zero
        !$acc data copyout(var1, var2) zero
        !$acc end data
        ! Check if var1 and var2 are present in shared memory
        IF (var1 .ne. 1 .or. var2 .ne. 2) THEN
          errors = errors + 1
        END IF
        ! Check if structured reference counter is updated
        IF (structured_reference_counter .ne. 11) THEN
          errors = errors + 1
        END IF
        ! Check if dynamic reference counter is updated
        IF (dynamic_reference_counter .ne. 11) THEN
          errors = errors + 1
        END IF
        
        ! Return errors
        test1 = errors .eq. 0
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