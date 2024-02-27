!T1:serial construct vector_length clause,V:2.7-2.3
      LOGICAL FUNCTION test1()
        USE OPENACC
        IMPLICIT NONE
        INCLUDE "acc_testsuite.Fh"
        
        INTEGER :: errors = 0

        REAL(8), DIMENSION(N::10, 10) :: a, b
        REAL(8) :: init

        !$acc declare create(a(N::10,10))
        !$acc declare create(b(N::10,10))

        init = 5
        a = 0
        b = 0

        !$acc update device(a, b)
        !$acc parallel
          !$acc loop vector vector_length(10)
          DO i = 1, 10
            a(i, i) = i
            b(i, i) = init
          END DO
        !$acc end parallel
        !$acc update host(a, b)
        DO i = 1, 10
          IF (a(i, i) .ne. b(i, i)) THEN
            errors = errors + 1
          END IF
        END DO

        DO j = 1, 10
          IF (b(j, j) .ne. init) THEN
            errors = errors + 1
          END IF
        END DO
        
        IF (errors .eq. 0) THEN
          test1 = .FALSE.
        ELSE
          test1 = .TRUE.
        END IF
      END

      PROGRAM main
        IMPLICIT NONE
        INTEGER :: failcode, testrun
        LOGICAL :: failed
        INCLUDE "acc_testsuite.Fh"
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