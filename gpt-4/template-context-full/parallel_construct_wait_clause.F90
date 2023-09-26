#ifndef T1
    !T1:parallel construct wait clause,V:2.7-2.3
          LOGICAL FUNCTION test1()
            USE OPENACC
            IMPLICIT NONE
            INTEGER :: i, n = 1000
            INTEGER, DIMENSION(1000) :: a, b
            INCLUDE "acc_testsuite.Fh"

            INTEGER :: errors = 0
            errors = acc_get_num_devices( acc_device_all );

            IF (errors .eq. 0) THEN
               test1 = .FALSE.
            ELSE
               !$ACC PARALLEL LOOP COPYOUT(a) ASYNC
               DO i = 1, n
                  a(i) = i
               END DO

               !$ACC PARALLEL LOOP COPYOUT(b) ASYNC
               DO i = 1, n
                  b(i) = i
               END DO

               !$ACC WAIT 

               DO i = 1, n
                  IF (a(i) /= i .OR. b(i) /= i) THEN
                     errors = errors + 1
                  END IF
               END DO

               IF (errors .eq. 0) THEN
                  test1 = .TRUE.
               ELSE
                  test1 = .FALSE.
               END IF
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