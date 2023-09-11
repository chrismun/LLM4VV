#ifndef T1
!T1:parallel construct num_gangs clause,V:2.7-2.3
      LOGICAL FUNCTION test1()
        USE OPENACC
        IMPLICIT NONE
        INCLUDE "acc_testsuite.Fh"
        
        INTEGER :: errors = 0
        INTEGER, DIMENSION(3) :: num_gangs
        INTEGER :: num_gangs_default
        REAL(8), DIMENSION(:), ALLOCATABLE :: a, b, c
        INTEGER :: i

        num_gangs = (/ 1, 2, 3 /)
        num_gangs_default = 1

        ALLOCATE(a(1000), b(1000), c(1000))

        !$acc parallel num_gangs(num_gangs(1), num_gangs(2), num_gangs(3))
        DO i = 1, 1000
          a(i) = 1.0
          b(i) = 2.0
        END DO
        !$acc end parallel

        !$acc parallel num_gangs(num_gangs_default)
        DO i = 1, 1000
          c(i) = a(i) + b(i)
        END DO
        !$acc end parallel

        DO i = 1, 1000
          IF (c(i) .ne. 3.0) THEN
            errors = errors + 1
          END IF
        END DO

        DEALLOCATE(a, b, c)

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