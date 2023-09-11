fortran
#ifndef T1
!T1:data construct copy clause,V:2.7-2.3
      LOGICAL FUNCTION test1()
        USE OPENACC
        IMPLICIT NONE
        INCLUDE "acc_testsuite.Fh"
        
        INTEGER :: errors = 0
        INTEGER :: var1, var2
        INTEGER :: copy_in, copy_out
        INTEGER :: attach, detach
        INTEGER :: present_or_copy, pc_copy
        INTEGER :: null_pointer
        
        ! Initialize variables
        var1 = 1
        var2 = 2
        copy_in = 0
        copy_out = 0
        attach = 0
        detach = 0
        present_or_copy = 0
        pc_copy = 0
        null_pointer = 0
        
        ! Test copy clause on structured data
        !$acc data copy(var1, var2)
        !$acc end data
        
        ! Test copy clause on compute constructs
        !$acc parallel copy(var1, var2)
        !$acc end parallel
        
        ! Test copy clause on declare directives
        !$acc declare copy(var1, var2)
        
        ! Test copyin action
        !$acc data copyin(var1, var2)
        !$acc end data
        
        ! Test present increment action
        !$acc data present(var1, var2)
        !$acc end data
        
        ! Test attach action
        !$acc data attach(var1, var2)
        !$acc end data
        
        ! Test detach action
        !$acc data detach(var1, var2)
        !$acc end data
        
        ! Test present decrement action
        !$acc data present(var1, var2)
        !$acc end data
        
        ! Test copyout action
        !$acc data copyout(var1, var2)
        !$acc end data
        
        ! Test errors
        !$acc data copy(var1, var2)
        !$acc end data
        
        !$acc parallel copy(var1, var2)
        !$acc end parallel
        
        !$acc declare copy(var1, var2)
        
        !$acc data copyin(var1, var2)
        !$acc end data
        
        !$acc data present(var1, var2)
        !$acc end data
        
        !$acc data attach(var1, var2)
        !$acc end data
        
        !$acc data detach(var1, var2)
        !$acc end data
        
        !$acc data present(var1, var2)
        !$acc end data
        
        !$acc data copyout(var1, var2)
        !$acc end data
        
        ! Check results
        IF (copy_in .ne. 1 .or. copy_out .ne. 1 .or. attach .ne. 1 .or. detach .ne. 1 .or. present_or_copy .ne. 1 .or. pc_copy .ne. 1 .or. null_pointer .ne. 0) THEN
          errors = errors + 1
        END IF
        
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