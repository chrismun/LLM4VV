!T1:data construct copy clause,V:2.7-2.3
      LOGICAL FUNCTION test1()
        USE OPENACC
        IMPLICIT NONE
        INCLUDE "acc_testsuite.Fh"
        
        INTEGER :: errors = 0
        INTEGER :: N = 10
        INTEGER, DIMENSION(:), ALLOCATABLE :: a, a_copy
        INTEGER :: i

        ALLOCATE(a(N), a_copy(N))

        ! Initialize a and a_copy
        DO i = 1, N
          a(i) = i
          a_copy(i) = 0
        END DO

        !$acc data copy(a)
        !$acc parallel loop
        DO i = 1, N
          a(i) = a(i) * 2
        END DO
        !$acc end parallel loop
        !$acc end data

        ! Copy data back to host
        a_copy = a

        ! Check if the copy was successful
        DO i = 1, N
          IF (a_copy(i) .ne. i * 2) THEN
            errors = errors + 1
          END IF
        END DO

        DEALLOCATE(a, a_copy)

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