!T1:serial construct vector_length clause,V:2.7-2.3
      LOGICAL FUNCTION test1()
        USE OPENACC
        IMPLICIT NONE
        INCLUDE "acc_testsuite.Fh"
        
        INTEGER :: errors = 0
        INTEGER, DIMENSION(:), ALLOCATABLE :: a, b
        INTEGER :: n, i
        INTEGER :: vector_length

        n = 1024
        vector_length = 64

        ALLOCATE(a(n), b(n))

        ! initialize arrays
        a = 1
        b = 2

        ! Test vector_length clause
        !$ACC SERIAL VECTOR_LENGTH(vector_length)
        DO i = 1, n
            a(i) = a(i) + b(i)
        END DO
        !$ACC END SERIAL

        ! Test result
        DO i = 1, n
            IF (a(i) /= 3) THEN
                errors = errors + 1
            END IF
        END DO

        DEALLOCATE(a, b)

        IF (errors .eq. 0) THEN
          test1 = .FALSE.
        ELSE
          test1 = .TRUE.
        END IF
      END FUNCTION test1