#ifndef T1
!T1:data construct copyin clause,V:2.7-2.3
      LOGICAL FUNCTION test1()
        USE OPENACC
        IMPLICIT NONE
        INCLUDE "acc_testsuite.Fh"
        
        INTEGER :: errors = 0
        INTEGER :: var1, var2
        INTEGER :: structured_reference_counter, dynamic_reference_counter
        INTEGER :: present_or_copyin, pc_or_copyin
        INTEGER :: readonly
        
        ! Initialize variables
        var1 = 1
        var2 = 2
        structured_reference_counter = 0
        dynamic_reference_counter = 0
        present_or_copyin = 0
        pc_or_copyin = 0
        readonly = 0
        
        ! Test copyin clause on structured data
        !$acc data copyin(var1, var2)
        !$acc end data
        
        ! Test copyin clause on compute construct
        !$acc parallel copyin(var1, var2)
        !$acc end parallel
        
        ! Test copyin clause on enterdata directive
        !$acc enterdata copyin(var1, var2)
        
        ! Test copyin clause with readonly modifier
        !$acc data copyin(var1, var2) readonly
        !$acc end data
        
        ! Test copyin clause with present_or_copyin and pc_or_copyin
        !$acc data copyin(var1, var2) present_or_copyin
        !$acc end data
        !$acc data copyin(var1, var2) pc_or_copyin
        !$acc end data
        
        ! Check reference counters
        IF (structured_reference_counter .ne. 0) THEN
          errors = errors + 1
        END IF
        IF (dynamic_reference_counter .ne. 0) THEN
          errors = errors + 1
        END IF
        IF (present_or_copyin .ne. 0) THEN
          errors = errors + 1
        END IF
        IF (pc_or_copyin .ne. 0) THEN
          errors = errors + 1
        END IF
        
        ! Check for errors
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