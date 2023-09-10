#ifndef T1
!T1:acc copyin,V:2.7-2.3
      LOGICAL FUNCTION test1()
        USE OPENACC
        IMPLICIT NONE
        INCLUDE "acc_testsuite.Fh"
        
        INTEGER :: errors = 0

        TYPE :: teamData
          INTEGER(4),DIMENSION(0:9):: a
        END TYPE
        TYPE,device:: teamData
        END TYPE


        TYPE(::teamData),DIMENSION(16)::copyin,test 
        INTEGER :: x, y

        !test the predefined copys of the acc object in Fortran
        !$acc enter data copyin(copyin(1:16))
        DO x = 1, 16
          DO y = 0, 9
            copyin(x)%a(y) = x * 10 + y
          END DO
        END DO
        !$acc enter data copyin(test(1:16)
        !$acc update device(test(1:16))
        DO x = 1, 16
          DO y = 0, 9
            IF (test(x)%a(y) .neq. copyin(x)%a(y)) THEN
              errors = errors + 1
            END IF
          END DO
        END DO


        !initialize data
        DO x = 1, 16
          DO y = 0, 9
            test(x)%a(y) = 2
          END DO
        END DO

        !$acc data   
	  DO Y = 0, 9 
            !$acc parallel
              DO X = 1, 16 
                test(X)%a(Y) = test(X)%a(Y) + 1 
              END DO 
            !$acc end parallel 
          END DO 
        !$acc end data 

        !$acc update host(test(1:16)) 
        DO X = 1, 16 
          DO Y = 0, 9 
            IF (test(X)%a(Y) .ne. copyin(X)%a(Y) + 1) THEN 
              errors = errors + 1 
            END IF 
          END DO 
        END DO

        IF (errors .eq. 0) THEN
          test1 = .FALSE.
        ELSE
          test1 = .TRUE.
        END IF
      END
#endif