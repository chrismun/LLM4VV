fortran
#ifndef T1
!T1:kernels construct num_gangs clause,V:2.7-2.3
      LOGICAL FUNCTION test1()
        USE OPENACC
        IMPLICIT NONE
        INCLUDE "acc_testsuite.Fh"
        
        INTEGER :: errors = 0
        INTEGER :: num_gangs
        INTEGER :: num_workers
        INTEGER :: num_vectors
        INTEGER :: i
        
        !$acc kernels num_gangs(2, 3, 4)
        !$acc parallel num_gangs(2, 3, 4)
        !$acc loop gang
        DO i = 1, 10
          !$acc loop worker
          DO j = 1, 10
            !$acc loop vector
            DO k = 1, 10
              !$acc loop
              CALL acc_attach(i, j, k)
            END DO
          END DO
        END DO
        !$acc end parallel
        !$acc end kernels
        
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