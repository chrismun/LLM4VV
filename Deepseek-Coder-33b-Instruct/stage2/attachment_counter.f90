#ifndef T1
!T1:attachment counter,V:2.7-2.3
      LOGICAL FUNCTION test1()
        USE OPENACC
        IMPLICIT NONE
        INCLUDE "acc_testsuite.Fh"
        
        INTEGER :: errors = 0
        INTEGER, TARGET :: a
        INTEGER, POINTER :: ptr
        INTEGER :: counter

        ! Initialize the pointer
        ptr => a

        ! Attach the pointer to a target
        !$acc data copyin(ptr)
        !$acc update device(ptr)

        ! Check the attachment counter
        !$acc get deviceptr(ptr)
        counter = acc_get_attachment_counter(ptr)
        IF (counter .ne. 1) THEN
          errors = errors + 1
        END IF

        ! Detach the pointer
        !$acc update host(ptr)

        ! Check the attachment counter
        counter = acc_get_attachment_counter(ptr)
        IF (counter .ne. 0) THEN
          errors = errors + 1
        END IF

        !$acc end data

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