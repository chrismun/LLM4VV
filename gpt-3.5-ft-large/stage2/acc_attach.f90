#ifndef T1
!T1:acc attach,V:2.7-2.3
      LOGICAL FUNCTION test1()
        USE OPENACC
        IMPLICIT NONE
        INCLUDE "acc_testsuite.Fh"
        
        INTEGER :: errors = 0

        IF (acc_get_device_type() .eq. acc_device_host) THEN
          ! host-only code
          TYPE(REAL),DIMENSION(10,10,10) :: f, f_copy 
          INTEGER :: x, y, z

          CALL RANDOM_NUMBER(f)
          f_copy = f

          !$acc enter data create(f(1:10,1:10,1:9))

          CALL acc_attach(f)

          !$acc parallel
            !$acc loop
            DO x = 1, 10
              DO y = 1, 10
                DO z = 1, 9
                  f(x, y, z) = f(x, y, z) + 1
                END DO
              END DO
            END DO
          !$acc end parallel

          CALL acc_detach(f)
          !$acc exit data copyout(f(1:10,1:10,1:9))

          DO x = 1, 10
            DO y = 1, 10
              DO z = 1, 9
                IF (abs(f(x, y, z) - (1 + f_copy(x, y, z)))) .gt. PRECISION THEN
                  errors = errors + 1
                END IF
              END DO
            END DO
          END DO
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