#ifndef T1
!T1:loop construct gang clause,V:2.7-2.3
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

  LOGICAL FUNCTION test1()
        USE OPENACC
        IMPLICIT NONE
        INTEGER :: errors = 0
        
        
 
        !This test checks whether the clause functions correctly with the parallel directive but not the kernels directive 
        INTEGER :: test(9), loopcounter, index, totalarray, gangcounter !Data values
        REAL(8),DIMENSION(9):: a !Value array
        REAL(8) :: temp
        totalarray = 0
        
        !Initilization
        
        test1 = 0
        for loopcounter = 1 to 3
            for index = 1 to 3
            test(loopcounter*3 - index) = index
          END DO
          DO index = 1 to 9
            totalarray = totalarray + test(index)
          END DO
          acc data copy(a)
            a(1) = 0
            !$acc end data
          acc data copyin(test(1:9)) copyout(a(1:9))
            !$acc parallel loop gang
            for loopcounter = 1 to 3
              temp = 0
              !$acc loop vector reduction(+:temp)
              for gangcounter = 1 to 3
                temp = temp + test(loopcounter*3 + gangcounter - 4)
              !$acc end loop
              a(loopcounter*3 - gangcounter + 1) = temp
            !$acc end loop
            !$acc end data
          DO loopcounter = 1 to 3
            IF (a(loopcounter*3 - 2) .ne. (test(loopcounter*3 - 2) + test(loopcounter*3 - 1) + test(loopcounter*3))) THEN
              errors = errors + 1
            END IF
          END DO
        END DO
        
        !This test checks whether a performance optimization occurs
        a = 1
        acc data copyin(a(0:8))
          !$acc parallel loop gang
          for loopcounter = 0 to 8
            a(loopcounter) = a(loopcounter) + 1
          !$acc end loop
        !$acc end data
        DO loopcounter = 0 to 8
          IF (a(loopcounter) .eq. 2) THEN
            EXIT
          END IF
          errors = 1
        END DO
        


      END