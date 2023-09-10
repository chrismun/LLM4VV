#ifndef T1
!T1:exit data directive,V:2.7-2.3
      LOGICAL FUNCTION test1()
        USE OPENACC
        IMPLICIT NONE
        INCLUDE "acc_testsuite.Fh"
        
        INTEGER :: errors = 0


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

c1      ATOMIC
c2      ATOMIC
      CONTAINS
      SUBROUTINE init_matrices1
        REAL, DIMENSION(LOOPCOUNT, LOOPCOUNT) :: a, b, c
        INTEGER :: x, y

        !$acc enter data create(a(1:LOOPCOUNT, 1:LOOPCOUNT), b(1:LOOPCOUNT, 1:LOOPCOUNT), c(1:LOOPCOUNT, 1:LOOPCOUNT))
        
        SEEDDIM(1) = 1
#       ifdef SEED
        SEEDDIM(1) = SEED
#       endif
        CALL RANDOM_SEED(PUT=SEEDDIM)

        CALL RANDOM_NUMBER(a)
        CALL RANDOM_NUMBER(b)
        CALL RANDOM_NUMBER(c)

        !$acc update device(a(1:LOOPCOUNT, 1:LOOPCOUNT), b(1:LOOPCOUNT,1:LOOPCOUNT), c(1:LOOPCOUNT,1:LOOPCOUNT))
      END SUBROUTINE init_matrices1

c1test  SEQUENTIAL
      INTEGER FUNCTION test1_c1
        USE OPENACC
        IMPLICIT NONE
        INCLUDE "acc_testsuite.Fh"
        INTEGER :: x, y, errors = 0
        REAL(8), DIMENSION(LOOPCOUNT, LOOPCOUNT) :: a, b, c
        INTEGER :: c1, test1_c1

        !$acc data copyin(a(1:LOOPCOUNT, 1:LOOPCOUNT), b(1:LOOPCOUNT, 1:LOOPCOUNT)) copy(c(1:LOOPCOUNT, 1:LOOPCOUNT))
          DO WHILE (test1_c1 .ne. 0)
            test1_c1 = 0
            !$acc parallel loop reduction(+:c1)
            DO x = 1, LOOPCOUNT
              DO y = 1, LOOPCOUNT
                c(x, y) = c(x, y) + a(x, y) + b(x, y)
              END DO
            END DO
            !$acc parallel
            DO x = 1, LOOPCOUNT
              DO y = 1, LOOPCOUNT
                IF (c(x, y) .lt. a(x, y) .or. c(x, y) .lt. b(x, y)) THEN
                  test1_c1 = 1
                END IF
              END DO
            END DO
          END DO
        !$acc enter data copyout(c(1:LOOPCOUNT, 1:LOOPCOUNT)) reference(a(1:LOOPCOUNT,1:LOOPCOUNT), b(1:LOOPCOUNT, 1:LOOPCOUNT))
        !$acc exit data copyout(c(1:LOOPCOUNT, 1:LOOPCOUNT)) delete(a(1:LOOPCOUNT,1:LOOPCOUNT),b(1:LOOPCOUNT,1:LOOPCOUNT))
        DO x = 1, LOOPCOUNT
          DO y = 1, LOOPCOUNT
            IF (abs(c(x, y)) .gt. PRECISION) THEN
              errors = errors + 1
            END IF
          END DO
        END DO
        test1_c1 = errors
      END

c2test  SEQUENTIAL
      INTEGER FUNCTION test1_c2
        USE OPENACC
        IMPLICIT NONE
        INCLUDE "acc_testsuite.Fh"
        INTEGER :: x, y, errors = 0
        REAL(8), DIMENSION(LOOPCOUNT, LOOPCOUNT) :: a, b, c
        INTEGER :: c1, test1_c2

        !$acc data copyin(a(1:LOOPCOUNT, 1:LOOPCOUNT), b(1:LOOPCOUNT, 1:LOOPCOUNT)) copy(c(1:LOOPCOUNT, 1:LOOPCOUNT))
          DO WHILE (test1_c2 .ne. 0)
            test1_c2 = 0
            !$acc parallel loop reduction(+:c2)
            DO x = 1, LOOPCOUNT
              DO y = 1, LOOPCOUNT
                c(x, y) = c(x, y) + a(x, y) + b(x, y)
              END DO
            END DO
            !$acc parallel
            DO x = 1, LOOPCOUNT
              DO y = 1, LOOPCOUNT
                IF (c(x, y) .lt. a(x, y) - PRECISION OR c(x, y) .lt. b(x, y) - PRECISION) THEN
                  test1_c2 = 1
                END IF
              END DO
            END DO
          END DO
        !$acc enter data copyout(c(1:LOOPCOUNT, 1:LOOPCOUNT)) reference(a(1:LOOPCOUNT, 1:LOOPCOUNT), b(1:LOOPCOUNT, 1:LOOPCOUNT))
        !$acc exit data copyout(c(1:LOOPCOUNT, 1:LOOPCOUNT)) delete(a(1:LOOPCOUNT,1:LOOPCOUNT),b(1:LOOPCOUNT,1:LOOPCOUNT))
        DO x = 1, LOOPCOUNT
          DO y = 1, LOOPCOUNT
            IF (abs(c(x, y) - (a(x, y) + b(x, y))) .gt. PRECISION) THEN
              errors = errors + 1
            END IF
          END DO
        END DO
        test1_c2 = errors
      END

        SUBROUTINE init_matrices1
          REAL(8), DIMENSION(LOOPCOUNT, LOOPCOUNT) :: a, b, c
          INTEGER :: x, y
          INTEGER :: c1, c2

          !$acc enter data create(a(1:LOOPCOUNT, 1:LOOPCOUNT), b(1:LOOPCOUNT, 1:LOOPCOUNT), c(1:LOOPCOUNT, 1:LOOPCOUNT))
          
          SEEDDIM(1) = 1
#         ifdef SEED
          SEEDDIM(1) = SEED
#         endif
          CALL RANDOM_SEED(PUT=SEEDDIM)

          CALL RANDOM_NUMBER(a)
          CALL RANDOM_NUMBER(b)
          CALL RANDOM_NUMBER(c)

          !$acc update device(a(1:LOOPCOUNT, 1:LOOPCOUNT), b(1:LOOPCOUNT,1:LOOPCOUNT), c(1:LOOPCOUNT,1:LOOPCOUNT))

          c1 = 0
          c2 = 0

          !$acc data exit copyout(c(1:LOOPCOUNT, 1:LOOPCOUNT)) delete(a(1:LOOPCOUNT, 1:LOOPCOUNT), b(1:LOOPCOUNT, 1:LOOPCOUNT))

          DO x = 1, LOOPCOUNT
            DO y = 1, LOOPCOUNT
              c1 = c1 + a(x, y) + b(x, y)
              c2 = c2 + c(x, y)
            END DO
          END DO

          IF (c1 .NE. c2) THEN
            WRITE(*, *) c1
            WRITE(*, *) c2
            CALL EXIT(1)
          END IF
        END SUBROUTINE init_matrices1

        SUBROUTINE init_matrices2
          REAL(8), DIMENSION(LOOPCOUNT, LOOPCOUNT) :: a, b, c
          INTEGER :: x, y

          SEEDDIM(1) = 1
#         ifdef SEED
          SEEDDIM(1) = SEED
#         endif
          CALL RANDOM_SEED(PUT=SEEDDIM)

          CALL RANDOM_NUMBER(a)
          CALL RANDOM_NUMBER(b)
          CALL RANDOM_NUMBER(c)

          !$acc enter data create(c(1:LOOPCOUNT, 1:LOOPCOUNT))
          !$acc enter data create(a(1:LOOPCOUNT, 1:LOOPCOUNT), b(1:LOOPCOUNT, 1:LOOPCOUNT))
          
          !$acc update device(a(1:LOOPCOUNT, 1:LOOPCOUNT), b(1:LOOPCOUNT, 1:LOOPCOUNT), c(1:LOOPCOUNT, 1:LOOPCOUNT))

          !$acc exit data delete(a(1:LOOPCOUNT, 1:LOOPCOUNT), b(1:LOOPCOUNT, 1:LOOPCOUNT)) copyout(c(1:LOOPCOUNT, 1:LOOPCOUNT))
          
        END SUBROUTINE init_matrices2

        INTEGER FUNCTION test1()
          USE OPENACC
          IMPLICIT NONE
          INCLUDE "acc_testsuite.Fh"
          INTEGER :: test1_c1, test1_c2
          INTEGER :: failed
          failed = 0

          !$acc data
          CALL init_matrices1

          IF (test1_c1() .NE. 0) THEN
            failed = 1
          END IF
          IF (test1_c2() .NE. 0) THEN
            failed = 1
          END IF

          !$acc end data

          CALL init_matrices2
          
          CALL EXIT (failed)
        END 

      END PROGRAM