! This is a Fortran program to test OpenACC parallel construct with default clause
! The program aims to test default private and firstprivate behavior

#ifndef T1
!T1:parallel construct default clause,V:2.7-2.3
      MODULE m1
        INTEGER, DIMENSION(10) :: a, b
      END MODULE m1

      LOGICAL FUNCTION test1()
        USE OPENACC
        USE m1
        IMPLICIT NONE
        INCLUDE "acc_testsuite.Fh"
        
        INTEGER :: i 
        INTEGER, DIMENSION(10) :: c = 0
        INTEGER :: errors = 0
        

       b = (/ (i, i=1,10) /)  ! Here, b array initialized with values 1 to 10

       !$ACC PARALLEL LOOP DEFAULT(PRIVATE) COPYOUT(c) COPYIN(b)
       DO i = 1, 10
         c(i) = b(i) + 1
       END DO

       IF( ALL( c == b + 1 ) ) THEN
          errors = errors + 1
       END IF

       ! Reset array c
       c = 0

       a = b

       !$ACC PARALLEL LOOP DEFAULT(FIRSTPRIVATE) COPYOUT(c) COPYIN(a)
       DO i = 1, 10
         c(i) = a(i) + 1
       END DO

       IF( ALL( c == a + 1 ) ) THEN
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