#ifndef T1
!T1:parallel construct wait clause,V:2.7-2.3
      LOGICAL FUNCTION test1()
        USE OPENACC
        IMPLICIT NONE
        INCLUDE "acc_testsuite.Fh"
        
        INTEGER :: errors = 0
        INTEGER, DIMENSION(10) :: a, b, c
        INTEGER :: i

        DO i = 1, 10
          a(i) = i
          b(i) = i * 2
        END DO

        !$acc parallel copy(a(1:10), b(1:10)) async(1)
          !$acc loop
          DO i = 1, 10
            a(i) = a(i) + b(i)
          END DO
        !$acc end parallel

        !$acc parallel copy(a(1:10)) async(2)
          !$acc loop
          DO i = 1, 10
            a(i) = a(i) * 2
          END DO
        !$acc end parallel

        !$acc parallel wait(1) async(3)
          !$acc loop
          DO i = 1, 10
            a(i) = a(i) - 1
          END DO
        !$acc end parallel

        !$acc parallel wait(2, 3) async(4)
          !$acc loop
          DO i = 1, 10
            a(i) = a(i) * 3
          END DO
        !$acc end parallel

        !$acc parallel wait(4) async(5)
          !$acc loop
          DO i = 1, 10
            a(i) = a(i) + 1
          END DO
        !$acc end parallel

        !$acc parallel wait(5) async(6)
          !$acc loop
          DO i = 1, 10
            a(i) = a(i) - 2
          END DO
        !$acc end parallel

        !$acc parallel wait(6) async(7)
          !$acc loop
          DO i = 1, 10
            a(i) = a(i) * 4
          END DO
        !$acc end parallel

        !$acc parallel wait(7) async(8)
          !$acc loop
          DO i = 1, 10
            a(i) = a(i) + 3
          END DO
        !$acc end parallel

        !$acc parallel wait(8) async(9)
          !$acc loop
          DO i = 1, 10
            a(i) = a(i) - 4
          END DO
        !$acc end parallel

        !$acc parallel wait(9) async(10)
          !$acc loop
          DO i = 1, 10
            a(i) = a(i) * 5
          END DO
        !$acc end parallel

        DO i = 1, 10
          IF (a(i) .ne. ((i + i * 2 - 1 + 3) * 5)) THEN
            errors = errors + 1
          END IF
        END DO

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