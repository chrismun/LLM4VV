! Fortran program starts here
#ifndef T1
!T1:exit data directive,V:2.7-2.3
      LOGICAL FUNCTION test1()
        ! Using OpenACC library
        USE OPENACC
        IMPLICIT NONE
        INCLUDE "acc_testsuite.Fh"
        
        INTEGER :: errors = 0
        INTEGER, DIMENSION(:), ALLOCATABLE :: a
        INTEGER :: i
        
        ALLOCATE (a (10))
        
        ! Create device copy of the array "a"
        !$ACC ENTER DATA COPYIN(a)
        
        ! Modify the array "a" on the device
        !$ACC KERNELS
          DO i = 1, 10
             a(i) = i
          END DO
        !$ACC END KERNELS
        
        ! Exit data from the device to host
        !$ACC EXIT DATA COPYOUT(a)
        
        ! Testing for data correctness
        DO i = 1, 10
            IF(a(i) .NE. i) THEN
                errors = errors + 1
            END IF
        END DO

        ! If errors exist, return true, else return false
        IF (errors .eq. 0) THEN
          test1 = .FALSE.
        ELSE
          test1 = .TRUE.
        END IF
      END FUNCTION test1
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
      END PROGRAM main
      
! Fortran program ends here