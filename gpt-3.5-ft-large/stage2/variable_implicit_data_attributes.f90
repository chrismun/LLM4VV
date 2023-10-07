#ifndef T1
!T1:variable implicit data attributes,V:2.7-2.3
      LOGICAL FUNCTION test1()
        USE OPENACC
        IMPLICIT NONE
        INCLUDE "acc_testsuite.Fh"
        
        INTEGER :: errors = 0


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

c     The conditions described in the spec are tested over here. In a data region,
c     there is a copy without a data statement on a variable. Elsewhere in a compute
c     region, there is another copy clause.
#ifndef T1
      test1 = 0
      called_cnt = 0
      !$acc data copy(present_p[0:1])
        present_p_tmp = present_p
        !$acc parallel copyin(present_p[0:1])
          present_p[0] = 1
        !$acc end parallel
        IF (present_p .NEQV. present_p_tmp) THEN
          test1 = test1 + 1
        END IF
      !$acc end data
      IF (called_cnt .eq. 2) THEN
        test1 = test1 + 1
      END IF
#endif