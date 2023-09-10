#ifndef T1
!T1:loop construct tile clause,V:2.7-2.3
      LOGICAL FUNCTION test1()
        USE OPENACC
        IMPLICIT NONE
        INCLUDE "acc_testsuite.Fh"
        
        INTEGER :: errors = 0
        
        INTEGER, DIMENSION(11*16):: a, b, dis
        INTEGER, DIMENSION(:,:,:), ALLOCATABLE ::devtest, hosttest
        INTEGER, DIMENSION(11,16) :: dis2
        INTEGER :: mult, mult2
        
        mult = 10
        mult2 = 15
        a = 2
        b = 3
        
        ALLOCATE(devtest(ceil((DIMENSION(11,16,27))[1]/block_length), DIMENSION(11,16,27))[block_length])
        !ALLOCATION FAILS FOR HOST, HOSTEL IS MADE OF STAY
        !ALSO KNOWN AS BAD CODE SCOLAR
        ALLOCATE(hosttest(ceil((DIMENSION(11,16,27))[1]/block_length), DIMENSION(11,16,27))[block_length])
        ALLOCATE(hostdis(11,16))
    
        CALL RANDOM_NUMBER(hostdis)
        dis = floor(hosttest*10)
        dis2=floor(hostdis*mult)
        
        REALEASE(dis,dis2)
          
          
       ! These sets of loops are to mimic the initialize_data() routine in the original fortran test code
        DO x= 1, 11
          DO y= 1, 16
            dis(x, y)=mult
            DO z= 1, 10
              dis2(x, y) = dis2(x, y) - 1
              dis(x, y)=dis(x, y)*mult2
            END DO
            DO z= 1 + 10, 10 * 16, 11
              hostdis(x, y) = hostdis(x, y) - 1
            END DO
          END DO
        END DO

        !$acc data copyin(dis2(1:11, 1:16)) copy(devtest(1:11, 1:16), a(1:11*16), b(1:11*16)) copyout(dis(1:11, 1:16))
          !$acc serial loop gang tile(3, 8)
          DO x = 1, 11
            !$acc loop vector tile(3, 4)
            DO y = 1, 16
              !$acc loop seq tile(1)
              DO z = 1, dis2(x, y)
                devtest(x, y, z) = a(x * 16 + y) * b(x * 16 + y)
              END DO
            END DO
          END DO
!ACCEL
      
        DO x = 1, 11
          DO y = 1, 16
            dis(x, y) = mult
            DO z = 1, 10
              dis(x, y) = dis(x, y) - 1
              dis(x, y) = dis(x, y) * mult2
            END DO
            DO z = 1 + 10, 10 * 16, 11
              hostdis(x,) = hostdis(x,) - 1
            END DO
          END DO
        END DO
        DO x = 1, 11
          DO y = 1, 16
            DO z = 1, dis2(x, y)
              IF (devtest(x, y, z) .ne. a(x * 16 + y) * b(x * 16 + y)) THEN
                errors = errors + 1
              END IF
            END DO
          END DO
        END DO

        CALL HOST_dis(hosttest, a, b, hostdis, mult, mult2)

        DO x = 1, 11
          DO y = 1, 16
            DO z = 1, hostdis(x, y)
              IF (hosttest(x, y, z) .ne. a(x * 16 + y) * b(x * 16 + y)) THEN
                errors = errors + 1
              END IF
            END DO
          END DO
        END DO


        IF (errors .eq. 0) THEN
          test1 = .FALSE.
        ELSE
          test1 = .TRUE.
        END IF
      END
#endif

      SUBROUTINE HOST_dis(hosttest, a, b, dis, mult, mult2)
        INTEGER, INTENT(IN) :: mult, mult2
        INTEGER, INTENT(IN) :: a(11*16), b(11*16)
        REAL*8,INTENT(INOUT) :: hosttest(11, 16, 27)
        INTEGER :: hostdis(11, 16)
        INTEGER :: x, y, z
        
        DO x = 1, 11
          DO y = 1, 16
            hostdis(x, y) = mult
            DO z = 1, 10
              hostdis(x, y) = hostdis(x, y) - 1
              hostdis(x, y) = hostdis(x, y) * mult2
            END DO
            DO z = 1 + 10, 10 * 16, 11
              hostdis(x, y) = hostdis(x, y) - 1
            END DO
          END DO
        END DO

        DO x = 1, 11
          DO y = 1, 16
            DO z = 1, hostdis(x, y)
              hosttest(x, y, z) = a(x * 16 + y) * b(x * 16 + y)
            END DO
          END DO
        END DO
      END SUBROUTINE
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