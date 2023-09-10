LOOP_CONSTRUCT REDUCTION(* : VAR)

      RECURSIVE FUNCTION RUN_LOOP(VAR, PREVRET, LOOPCOUNT) RESULT(OUT)
        IMPLICIT NONE
        INCLUDE "acc_testsuite.Fh"
        INTEGER :: VAR
        INTEGER :: PREVRET
        INTEGER :: LOOPCOUNT
        INTEGER :: OUT
        INTEGER :: x, y !Iterators
        INTEGER,DIMENSION(1) :: devtest
        INTEGER :: mult
        INTEGER :: temp
        INTEGER :: errors = 0

        IF (LOOPCHILD .eq. 0) THEN
          mult = LOOPCOUNT
        ELSE
          mult = 1
        END IF

        !$acc data copy(devtest(1:1))
          !$acc parallel
            !$acc loop
            DO x = 1, 1
              devtest(x) = x
              !$acc loop    
              DO y = 1, LOOPCOUNT
                IF (LOOPCHILD .eq. 0) THEN
                  devtest(1) = devtest(1) * (LOOPCOUNT - y + 1)
                ELSE
                  devtest(1) = devtest(1) + devtest(1) * (LOOPCOUNT - y + 1)
                END IF
              END DO
            END DO
          !$acc end parallel
        !$acc end data

        IF (abs(devtest(1) - out) .gt. (LOOPCOUNT / 2)) THEN
          errors = 5
        END IF

        IF (LOOPCHILD .eq. 0) THEN
          OUT = devtest(1)
        ELSE
          OUT = PREVRET + devtest(1)
        END IF
      END FUNCTION RUN_LOOP

#ifndef T1
!T1: loop construct reduction clause
      LOGICAL FUNCTION test1()
      USE OPENACC
      IMPLICIT NONE
      INTEGER :: xIter, yIter, zIter
      INTEGER :: errors, temp
      INTEGER :: mult
      INCLUDE "acc_testsuite.Fh"
      errors = 0
      mult = 1

      !$acc data
        !$acc parallel
          !$acc loop
            DO zIter = 0, loopNum - 1
                !$acc loop vector reduction(+:x[0:9]) private(temp)
                DO xIter = 0, 9
                  temp = 0
                  DO yIter = 0, 9
                    x[xIter*10 + yIter] = (mult + xIter) * 2
                    temp = temp + (mult + xIter)
                  END DO
                  x[xIter*10 + yIter] = temp
                END DO
          mult = mult + 1
        END DO
          !$acc end parallel
      !$acc end data

      IF (errors .eq. 0) THEN
        test1 = .FALSE.
      ELSE
        test1 = .TRUE.
      END IF
      END
#endif

 0 STANDARD_LOOPED_CODE

      PROGRAM main
        IMPLICIT NONE
        INTEGER :: failcode, testrun
        LOGICAL :: failed
        INCLUDE "acc_testsuite.Fh"
        failed = .FALSE.
        failcode = 0
        INTEGER :: xIter, yIter
        INTEGER :: temp
        INTEGER :: mult

        !Data initilization
        INTEGER,DIMENSION(10*LOOPCOUNT):: a
        INTEGER,DIMENSION(10) :: a_host
        INTEGER :: independent_result
        INTEGER :: initial_reduction
        INTEGER :: temp

        a = 0
        a_host = 0

        initial_reduction = 0
        temp = 0

        !$omp parallel
        !$omp for
        for xIter = 0 to 9
          !$omp for reduction(+: temp)
          for yIter = 0 to LOOPCOUNT
            a[(10*xIter) + yIter] = yIter
            temp = temp + yIter
          end
          a[(10*xIter) + yIter] = temp
          initial_reduction = initial_reduction + temp
        end
        !$omp end parallel
        temp = 0

        !$acc data
          !$acc parallel
            !$acc loop independent reduction(+: temp)
            for xIter = 0 to 9
              temp = 0
              !$acc loop independent
              for yIter = 0 to LOOPCOUNT
                temp = temp + a[(10*xIter) + yIter]
              end
              !$acc loop independent
              for yIter = 0 to LOOPCOUNT
                a[(10*xIter) + yIter] = (a[(10*xIter) + yIter]/temp) * initial_reduction
              end
            end
            !$acc loop
            for xIter = 0 to 9
              temp = 0
              for yIter = 0 to LOOPCOUNT
                temp = temp + a[(10*xIter) + yIter]
              end
              a_host(xIter + 1) = temp
            end
          !$acc end parallel
        !$acc end data

        independent_result = 0
        DO xIter = 0, 9
          independent_result = independent_result + a_host(xIter + 1)
        END DO
        IF (abs(independent_result - temp) .gt. 10 * LOOPCOUNT) THEN
          temp = 1
          CALL TEST_OUTPUT(a, temp)
          failcode = failcode + 2 ** 0
        END IF

#ifndef T1
        DO testrun = 1, NUM_TEST_CALLS
          CALL test1
        END DO
#endif
        CALL EXIT (failcode)
      END PROGRAM