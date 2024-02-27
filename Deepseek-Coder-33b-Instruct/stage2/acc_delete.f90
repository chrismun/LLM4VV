!T1:acc delete,V:2.7-2.3
      LOGICAL FUNCTION test1()
        USE OPENACC
        IMPLICIT NONE
        INCLUDE "acc_testsuite.Fh"
        
        INTEGER :: errors = 0
        INTEGER, PARAMETER :: N = 100
        REAL, DIMENSION(:), ALLOCATABLE :: a, b
        INTEGER :: i

        ALLOCATE(a(N), b(N))

        !$acc enter data create(a(1:N), b(1:N))

        !$acc parallel loop
        DO i = 1, N
          a(i) = i * 1.0
        END DO

        !$acc parallel loop
        DO i = 1, N
          b(i) = i * 2.0
        END DO

        !$acc update host(a(1:N), b(1:N))

        !$acc delete(a(1:N), b(1:N))

        !$acc exit data delete(a(1:N), b(1:N))

        ! Check if the arrays are deleted
        IF (ALLOCATED(a) .OR. ALLOCATED(b)) THEN
          errors = errors + 1
        END IF

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