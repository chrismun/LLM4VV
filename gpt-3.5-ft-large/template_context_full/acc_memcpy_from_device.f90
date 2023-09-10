#ifndef T1
!T1:acc memcpy from device,V:2.7-2.3
      LOGICAL FUNCTION test1()
        USE OPENACC
        IMPLICIT NONE
        INCLUDE "acc_testsuite.Fh"
        
        INTEGER :: errors = 0
        REAL(8),DIMENSION(LOOPCOUNT):: a, b
        INTEGER ,DIMENSION(1) :: devtest
        INTEGER :: multi
        multi = 0


        devtest(1) = 1
        #        ifdef _OPENACC
!$acc enter data copyin(devtest(1:1))
#        endif



        SEEDDIM(1) = 1
#        ifdef _OPENACC
!$acc data copyout(a(1:LOOPCOUNT), b(1:LOOPCOUNT))
#        Endif
        CALL RANDOM_SEED()
        CALL RANDOM_NUMBER(a)
        b = 0
        IF (acc_is_present(a(1:LOOPCOUNT)) .eqv. 1) THEN
          a = 1.0
        END IF
        IF (acc_is_present(a(1:LOOPCOUNT)) .eqv. 0) THEN
          a = 2.0
        END IF
        #        ifdef _OPENACC
!$acc exit data copyout(a(1:LOOPCOUNT))
#        Endif
        

        CALL acc_memcpy_from_device(b(1), a(1), LOOPCOUNT*4)

        DO WHILE (MULTI < 10)
          CALL acc_memcpy_from_device(b(1), a(1), LOOPCOUNT * 4)
          DO i = 1, LOOPCOUNT
            IF (abs(b(i) - a(i)) .gt. PRECISION) THEN
              errors = errors + 1
            END IF
          END DO
          multi = multi + 1
        END DO



        DELETEDEVCOLL
        IF ((FOR_TESTING_HOSTNEEDEDMODES .eq. 1) .or. (acc_get_device_type() .eq. acc_device_altera))
          THEN
          IF (errors .eq. 0) THEN
            test1 = .FALSE.
          ELSE
            test1 = .TRUE.
          END IF
        ELSE
          test1 = .FALSE.
        END IF
      END
#endif

        DO WHILE (MULTI < 10)
          CALL acc_memcpy_from_device(b(1), a(1), LOOPCOUNT * 4)
          DO i = 1, LOOPCOUNT
            IF (abs(b(i) - a(i)) .gt. PRECISION) THEN
              errors = errors + 1
            END IF
          END DO
          multi = multi + 1
        END DO



        DELETEDEVCOLL
        IF ((FOR_TESTING_HOSTNEEDEDMODES .eq. 1) .or. (acc_get_device_type() .eq. acc_device_altera))
          THEN
          IF (errors .eq. 0) THEN
            test1 = .FALSE.
          ELSE
            test1 = .TRUE.
          END IF
        ELSE
          test1 = .FALSE.
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