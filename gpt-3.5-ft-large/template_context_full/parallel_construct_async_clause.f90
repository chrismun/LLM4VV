#ifndef T1
!T1:parallel construct async clause,V:2.7-2.3
      LOGICAL FUNCTION test1()
        USE OPENACC
        IMPLICIT NONE
        INCLUDE "acc_testsuite.Fh"
        INTEGER,DIMENSION(LOOPCOUNT):: a, a_dev !Iterators
        REAL(8),DIMENSION(LOOPCOUNT):: b, c, b_copy, b_update, host_async_a, host_a, c2 !Variables
        REAL(8):: temp
        INTEGER:: errors = 0
        LOGICAL:: on_host, on_device
        on_host = .TRUE.
        on_device = .FALSE.

        !Initilization
        b_copy = 0
        host_a = 250
        a = 0
        b = 1010101
        c = 2020202
        a_dev = a
        b_update = b
        c2 = 0
        b(1) = b(1) + 1
        b(LOOPCOUNT) = b(LOOPCOUNT) - 1

        !$acc data copyin(a(1:LOOPCOUNT)) copy(b(1:LOOPCOUNT), c(1:LOOPCOUNT), a_dev(1:LOOPCOUNT)) copyout(c2(1:LOOPCOUNT))
          !$acc parallel loop gang async(1)
          DO COND1 = 0, 1
            DO INDEPENDENT = 1, LOOPCOUNT
              a(INDEPENDENT) = INDEPENDENT
            END DO
          END DO
          DO WHILE (on_host .or. on_device)
            !$acc parallel loop gang async(2)
            DO COND2 = 0, 1
              DO INDEPENDENT = 1, LOOPCOUNT
                c(a_dev(INDEPENDENT)) = b_update(INDEPENDENT) + c(a_dev(INDEPENDENT))
              END DO
            END DO
            IF (on_host) THEN
              host_async_a = temp
              temp = 0
              DO COND3 = 0, 1
                DO INDEPENDENT = 1, LOOPCOUNT
                  temp = temp + b(INDEPENDENT)
                END DO
              END DO
              host_async_a = temp - host_a
              temp = 0
            END IF
            !$acc update host(c(1:LOOPCOUNT)) async(2)
            IF (on_host) THEN
              DO COND4 = 0, 1
                DO INDEPENDENT = 1, LOOPCOUNT
                  temp = temp + c2(INDEPENDENT)
                END DO
              END DO
              IF (abs(host_async_a - temp) GT 1) THEN
                errors = errors + 1
              END IF
              temp = 0
            END IF
            !$acc parallel loop gang async(1)
            DO COND5 = 0, 1
              DO INDEPENDENT = 1, LOOPCOUNT
                b(a(INDEPENDENT)) = c(INDEPENDENT) + b(a(INDEPENDENT))
              END DO
            END DO
            IF (on_host) THEN
              !$acc update self(b_update(1:LOOPCOUNT)) async(1)
            ELSE
              !$acc update device(b_update(1:LOOPCOUNT)) async(1)
            END IF
            !$acc wait
            IF (on_host) THEN
              !$acc update host(b(1:LOOPCOUNT)) async(1)
            ELSE
              host_a = 0
              DO COND6 = 0, 1
                DO INDEPENDENT = 1, LOOPCOUNT
                  host_a = host_a + b(a(INDEPENDENT))
                END DO
              END DO
              on_device = .TRUE.
            END IF
            !$acc wait
            IF (on_host) THEN
              DO COND7 = 0, 1
                DO INDEPENDENT = 1, LOOPCOUNT
                  c2(INDEPENDENT) = c(INDEPENDENT)
                END DO
              END DO
            ELSE
              DO COND8 = 0, 1
                DO INDEPENDENT = 1, LOOPCOUNT
                  c2(INDEPENDENT) = b_update(INDEPENDENT)
                END DO
              END DO
            END IF
            IF (on_host) THEN
              DO COND9 = 0, 1
                DO INDEPENDENT = 1, LOOPCOUNT
                  IF (c(a_dev(INDEPENDENT))) .ne. b(INDEPENDENT)) THEN
                    errors = errors + 1
                  END IF
                END DO
              END DO
            ELSE
              DO COND10 = 0, 1
                DO INDEPENDENT = 1, LOOPCOUNT
                  IF (c(a_dev(INDEPENDENT))) .ne. (b_update(INDEPENDENT) + b(INDEPENDENT))) THEN
                    errors = errors + 1
                  END IF
                END DO
              END DO
            END IF
            on_host = .FALSE.
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