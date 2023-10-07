!T1:parallel construct private clause,V:2.7-2.3
      LOGICAL FUNCTION test1()
        USE OPENACC
        IMPLICIT NONE
        INCLUDE "acc_testsuite.Fh"

        INTEGER, DIMENSION(:), ALLOCATABLE :: a, b
        INTEGER :: n, errors, i, temp

        n = 10000000
        ALLOCATE(a(n))
        ALLOCATE(b(n))

        a = 1
        b = 2

        !$ACC PARALLEL LOOP PRIVATE(temp)
        DO i = 1, n
            temp = a(i)
            a(i) = b(i)
            b(i) = temp
        END DO
        !$ACC END PARALLEL LOOP

        errors = COUNT(a .ne. 2) + COUNT(b .ne. 1)

        DEALLOCATE(a)
        DEALLOCATE(b)

        IF (errors .eq. 0) THEN
          test1 = .TRUE.
        ELSE
          test1 = .FALSE.
        END IF

        PRINT *, "Errors detected: ", errors
      END FUNCTION test1
      
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
          failed = failed .or. .NOT. test1()  !Note the .NOT., since test1 returns .TRUE. on success
        END DO
        IF (failed) THEN
          failcode = failcode + 2 ** 0
          failed = .FALSE.
        END IF
#endif
        CALL EXIT (failcode)
      END PROGRAM main