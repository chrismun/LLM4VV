!T1:loop construct private clause,V:2.7-2.3
      LOGICAL FUNCTION test1()
        USE OPENACC
        IMPLICIT NONE
        INCLUDE "acc_testsuite.Fh"
        
        INTEGER :: errors = 0
        INTEGER, PARAMETER :: N = 100
        REAL(KIND=8), DIMENSION(N) :: a, b, c
        INTEGER :: i, j, k, div
        REAL(KIND=8) :: tmp

        ! Initialize arrays
        a = 0.0
        b = 1.0
        c = 2.0
        div = 3

        !$acc data copyin(a, b, c, div) copyout(a)
        !$acc parallel loop gang
        do k = 1, N
          !$acc loop worker private(tmp)
          do j = 1, N
            tmp = b(j) + c(j)
            !$acc loop vector
            do i = 1, N
              a(i) = a(i) + tmp/div
            enddo
          enddo
        enddo
        !$acc end data

        ! Check the results
        do i = 1, N
          if (a(i) .ne. b(i) + c(i) / div) then
            errors = errors + 1
          endif
        enddo

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