#ifndef T1
!T1:kernels construct, wait clause,V:2.7-2.3
      LOGICAL FUNCTION test1()
        USE OPENACC
        IMPLICIT NONE
        INCLUDE "acc_testsuite.Fh"

        INTEGER :: errors = 0

        INTEGER,DIMENSION(10*LOOPCOUNT,OMPTHREADS),DEVICE :: a
        INTEGER,DIMENSION(LOOPCOUNT),HOST :: b
        INTEGER,DIMENSION(10,OMPTHREADS),DEVICE :: c,g
        REAL(8),DIMENSION(LOOPCOUNT,OMPTHREADS),DEVICE :: d
        INTEGER,DIMENSION(10,OMPTHREADS),DEVICE :: c_copy,g_copy
        REAL(8),DIMENSION(LOOPCOUNT,OMPTHREADS),DEVICE :: d_copy
        REAL(8),DIMENSION(10*LOOPCOUNT),HOST,DIMENSION(:,:),TARGET :: HOST_c, HOST_g, HOST_d
        real(8) :: temp
        INTEGER :: x, y, q

        !Initilization on the host
        HOST_c = 923
        HOST_g = 213
        HOST_d = 1

        DO x = 0, 10*LOOPCOUNT - 1
          a(x,:) = x
          DO y = 1, OMPTHREADS
            c(x + 1,y) = 1
            c_copy(x + 1,y) = 0
          END DO
          b(mod(x, LOOPCOUNT) + 1) = x
        END DO
        DO x = 1, LOOPCOUNT
          b(x) = -1 * b(x)
        END DO
        DO x = 1, LOOPCOUNT
          DO y = 1, OMPTHREADS
            d(x,y) = 1
            d_copy(x,y) = 0
          END DO
        END DO
        !$acc enter data copyin(c(1:10*LOOPCOUNT,1:OMPTHREADS), d(1:LOOPCOUNT,1:OMPTHREADS)) 
        !$acc enter data copyin(c_copy(1:10*LOOPCOUNT,1:OMPTHREADS), g_copy(1:10*LOOPCOUNT,1:OMPTHREADS), d_copy(1:LOOPCOUNT,1:OMPTHREADS))

        !$acc kernels loop independent private(errors) present(c(1:10*LOOPCOUNT,1:OMPTHREADS), d(1:LOOPCOUNT,1:OMPTHREADS), c_copy(1:10*LOOPCOUNT,1:OMPTHREADS), g_copy(1:10*LOOPCOUNT,1:OMPTHREADS), d_copy(1:LOOPCOUNT,1:OMPTHREADS))
          DO x = 0, 9
            !$acc loop independent
            DO y = 1, OMPTHREADS
              !$acc loop independent seq
              DO q = 1, LOOPCOUNT
                c_copy(x*LOOPCOUNT + q,y) = c(x*LOOPCOUNT + q,y)
              END DO
            END DO
            !$acc loop independent
            DO y = 1, OMPTHREADS
              !$acc loop independent seq
              DO q = 1, LOOPCOUNT
                d_copy(x*LOOPCOUNT + q,y) = d(x*LOOPCOUNT + q,y)
              END DO
            END DO
            !$acc loop independent
            DO y = 1, OMPTHREADS
              !$acc loop independent seq
              DO q = 1, LOOPCOUNT
              g_copy(x*LOOPCOUNT + q,y) = g(x*LOOPCOUNT + q,y)
              END DO
            END DO
            !$acc loop seq
            DO y = 1, OMPTHREADS
              c(x*LOOPCOUNT + 1,y) = c_copy(x*LOOPCOUNT + 1,y) + HOST_c(y)
            END DO
            !$acc loop
            DO y = 1, OMPTHREADS
              d(x*LOOPCOUNT + 1,y) = d_copy(x*LOOPCOUNT + 1,y) + HOST_d(mod(x*LOOPCOUNT + 1, 10*LOOPCOUNT))
            END DO
            !$acc loop gang
            DO z = 1, OMPTHREADS
              !$acc loop vector
              DO y = 2, LOOPCOUNT
                d(x*LOOPCOUNT + y,z) = d(x*LOOPCOUNT + y - 1,z) + c(x*LOOPCOUNT + y - 1,z)
              END DO
            END DO
            !$acc loop independent
            DO y = 1, OMPTHREADS
              g(x*LOOPCOUNT + 1,y) = 0
            END DO
            !$acc loop gang
            DO y = 1, OMPTHREADS
              !$acc loop vector
              DO z = 2, LOOPCOUNT
                g(x*LOOPCOUNT + z,y) = g(x*LOOPCOUNT + z - 1,y) + d(x*LOOPCOUNT + z - 1,y)
              END DO
            END DO
            !$acc loop independent
            DO y = 1, OMPTHREADS
              IF (g(x*LOOPCOUNT + LOOPCOUNT,y) .ne. a(a(x*LOOPCOUNT + LOOPCOUNT,y), y) + HOST_g(x*LOOPCOUNT + LOOPCOUNT,y)) THEN
                errors = errors + 1
              END IF
            END DO
            !$acc loop gang
            DO y = 1, OMPTHREADS
              !$acc loop vector
              DO z = 1, LOOPCOUNT
                IF (g(x*LOOPCOUNT + z,y) .ne. a(x*LOOPCOUNT + z,y) + HOST_g(x*LOOPCOUNT + z,y)) THEN
                  errors = errors + 1
                END IF
              END DO
            END DO
          END DO
        !$acc end kernels
        !$acc exit data copyout(c(1:10*LOOPCOUNT, 1:OMPTHREADS), d(1:LOOPCOUNT, 1:OMPTHREADS))
        !$acc exit data copyout(c_copy(1:10*LOOPCOUNT, 1:OMPTHREADS), g_copy(1:10*LOOPCOUNT, 1:OMPTHREADS), d_copy(1:LOOPCOUNT, 1:OMPTHREADS))

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
        !Condition1
#ifndef T1
        LOGICAL :: test1
        INTEGER :: testrun
#endif
        failed = .FALSE.
        failcode = 0
        !Condition1
#ifndef T1
        DO testrun = 1, NUM_TEST_CALLS
          failed = failed .or. test1()
        END DO
        IF (failed .eqv. .TRUE.) THEN
          failcode = failcode + 2 ** 0
        END IF
#endif
        CALL EXIT (failcode)
      END PROGRAM