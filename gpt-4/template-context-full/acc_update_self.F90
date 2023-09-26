!T1:acc update self,V:2.7-2.3
      LOGICAL FUNCTION test1()
        USE OPENACC
        IMPLICIT NONE
        INCLUDE "acc_testsuite.Fh"
        
        INTEGER :: errors = 0
        INTEGER, DIMENSION(:), ALLOCATABLE :: a
        INTEGER, DIMENSION(:), ALLOCATABLE :: b
        INTEGER :: length, i

        length = 1000

        ALLOCATE(a(length))
        ALLOCATE(b(length))

        DO i = 1, length
            a(i) = i
        END DO    

        !$ACC PARALLEL LOOP COPY(a)
        DO i = 1, length
            a(i) = a(i) * 2
        END DO  

        CALL acc_update_self(a, length * 4)  !updates 'a' on host

        DO i = 1, length
            IF (a(i) /= i*2) THEN
                errors = errors + 1   !check if update is correct
            END IF
        END DO 

        DEALLOCATE(a)
        DEALLOCATE(b)

        IF (errors .eq. 0) THEN
            test1 = .FALSE.
        ELSE
            test1 = .TRUE.
        END IF
      END FUNCTION test1

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
        DO testrun = 1, NUM_TEST_CALLS
            failed = failed .or. test1()
        END DO
        IF (failed) THEN
            failcode = failcode + 2 ** 0
            failed = .FALSE.
        END IF
        CALL EXIT (failcode)
      END PROGRAM main