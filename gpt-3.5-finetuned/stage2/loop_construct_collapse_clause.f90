!T1:loop construct collapse clause,V:2.7-2.3
      LOGICAL FUNCTION test1()
        USE OPENACC
        IMPLICIT NONE
        INCLUDE "acc_testsuite.Fh"

        INTEGER, PARAMETER :: LOOP_COUNT = 2
        INTEGER, PARAMETER :: N = 10
        REAL(8) :: a(LOOP_COUNT, LOOP_COUNT, N)
        REAL(8) :: b(LOOP_COUNT, LOOP_COUNT, N)
        REAL(8) :: c(LOOP_COUNT, LOOP_COUNT)

        INTEGER :: x, y, z
        INTEGER :: errors = 0

        SEEDDIM(1) = 1
        SEEDDIM(1) = SEED
        CALL RANDOM_SEED(PUT=SEEDDIM)

        DO x = 1, LOOP_COUNT
          DO y = 1, LOOP_COUNT
            CALL RANDOM_NUMBER(a(x, y, :))
            b(x, y, :) = 0
          END DO
        END DO

        !$acc data copyin(a(1:LOOP_COUNT,1:LOOP_COUNT,1:N)) copyout(c(1:LOOP_COUNT,1:LOOP_COUNT), b(1:LOOP_COUNT,1:LOOP_COUNT,1:N))
          !$acc parallel
            !$acc loop collapse(LOOP_COUNT)
            DO x = 1, LOOP_COUNT
              !$acc loop collapse(LOOP_COUNT)
              DO y = 1, LOOP_COUNT
                !$acc loop
                DO z = 1, N
                  b(x, y, z) = a(x, y, z)
                END DO
                c(x, y) = 0
                !$acc loop.REDUCTION(+:c)
                DO z = 1, N
                  c(x, y) = c(x, y) + b(x, y, z)
                END DO
              END DO
            END DO
          !$acc end parallel
        !$acc end data

        DO x = 1, LOOP_COUNT
          DO y = 1, LOOP_COUNT
            DO z = 1, N
              IF (b(x, y, z) .ne. a(x, y, z)) THEN
                errors = errors + 1
              END IF
            END DO

            IF (c(x, y) .ne. SUM(b(x, y, 1:N))) THEN
              errors = errors + 1
            END IF
          END DO
        END DO

        IF (errors .eq. 0) THEN
          test1 = .FALSE.
        ELSE
          test1 = .TRUE.
        END IF
      END

      PROGRAM main
        IMPLICIT NONE
        INCLUDE "acc_testsuite.Fh"

        INTEGER :: failcode, testrun
        LOGICAL :: failed
        LOGICAL :: test1
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
      END PROGRAM