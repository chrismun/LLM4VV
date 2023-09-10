#ifndef T1
!T1:data deviceptr clause, V:2.7-2.3
    FUNCTION test1() 
        USE OPENACC
        IMPLICIT NONE
        INCLUDE "acc_testsuite.Fh"
    
        INTEGER, DEVICE :: errors = 0
        INTEGER, DEVICE :: a
        INTEGER, pointer, DEVICE :: p
    
        a = 10
        p = a /* Store the value of 'a' into a device pointer 'p' */

        !$ACC data deviceptr(p)
            !$ACC parallel num_gangs(1) vector_length(1)
                IF (p .NE. 10) THEN /*If p does not equal 10, increment the error counter*/
                    errors = errors + 1
                END IF
            !$ACC end parallel
        !$ACC end data 
    
        test1 = errors /*Return the number of errors that were encountered*/
    END FUNCTION test1
#endif

    PROGRAM main
        IMPLICIT NONE
        INTEGER :: failcode, testrun
        LOGICAL :: failed
        INCLUDE "acc_testsuite.Fh"
#ifndef T1
        INTEGER :: test1
#endif
        failed = .FALSE.
        failcode = 0
#ifndef T1
        DO testrun = 1, NUM_TEST_CALLS
          failed = failed .or. (test1().NE. 0) /*Run test1 and check if there were any errors*/
        END DO
        IF (failed) THEN
          failcode = failcode + 2 ** 0
          failed = .FALSE.
        END IF
#endif
        CALL EXIT (failcode)
    END PROGRAM main