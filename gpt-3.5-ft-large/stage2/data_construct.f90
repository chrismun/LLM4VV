#ifndef T1
!T1:data construct,V:2.7-2.3
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

#endif
#ifndef T1
!T1:data construct,V:2.7-2.3
      LOGICAL FUNCTION test1()
        USE OPENACC
        IMPLICIT NONE
        INCLUDE "acc_testsuite.Fh"
        
        INTEGER :: errors = 0
        INTEGER,DIMENSION(10) :: a,b,c

        a = (/ (i-1, i=1, 10) /)
        b = (/ (2*(i-1), i=1, 10) /)
        c = 0

        CALL acc_attach(a,10)
        CALL acc_attach(b,10)
        CALL acc_attach(c,10)

        IF (acc_get_property(acc_device_test,c,10*4) .eq. acc_device_not_present) THEN
          !$acc data copyin(a(1:10), b(1:10)) copyout(c(1:10))
            !$acc parallel
              !$acc loop
              DO i = 1, 10
                c(i) = a(i) + b(i)
              END DO
            !$acc end parallel
          !$acc end data
        END IF

        DO i = 1, 10
          IF (c(i) .ne. (a(i) + b(i))) THEN
            errors = errors + 1
          END IF
        END DO

        CALL acc_detach(a(1))
        CALL acc_detach(b(1))
        CALL acc_detach(c(1))

        IF (errors .eq. 0) THEN
          test1 = .FALSE.
        ELSE
          test1 = .TRUE.
        END IF
      END
#endif