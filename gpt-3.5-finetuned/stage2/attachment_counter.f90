!T1:attachment counter,V:2.7-2.3
      LOGICAL FUNCTION test1()
        USE OPENACC
        IMPLICIT NONE
        INCLUDE "acc_testsuite.Fh"
        
        INTEGER :: errors = 0

        IMPLICIT NONE
        INCLUDE "acc_testsuite.Fh"

        INTEGER, PARAMETER :: size = 1000
        REAL(8),DIMENSION(size):: a
        REAL(8),DIMENSION(size):: b
        REAL(8),DIMENSION(size):: c
        REAL(8),DIMENSION(size):: d

c      ! a = 1, b = 2, c = 3
        a = 1
        b = 2
        c = 3
        d = 0

        !$acc data copyin(a(1:size), b(1:size), c(1:size)) create(d(1:size))
          !$acc parallel present(a(1:size), b(1:size), c(1:size), d(1:size))
            !$acc loop
            do i = 1, size
              d(i) = a(i) + b(i) + c(i)
            enddo
          !$acc end parallel
        !$acc end data

        !$acc data copyout(d(1:size)) copyin(a(1:size), b(1:size), c(1:size))
          !$acc parallel present(a(1:size), b(1:size), c(1:size), d(1:size))
            !$acc loop
            do i = 1, size
              d(i) = d(i) + a(i) + b(i) + c(i) ! updates the parameter by adding to the current value
            enddo
          !$acc end parallel
        !$acc end data

        do i = 1, size
          if (floor(d(i) + 0.5)) .NE. floor((double(1 + 2 + 3 + 1 + 2 + 3)) + 0.5) then
            errors = errors + 1
          end if
        enddo

        !$acc exit data delete(a(1:size), b(1:size), c(1:size))

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