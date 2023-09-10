#ifndef T1
!T1:serial,construct-independent,V:2.7-2.3
      LOGICAL FUNCTION test1()
        USE OPENACC
        IMPLICIT NONE
        INCLUDE "acc_testsuite.Fh"

        INTEGER :: errors = 0
        INTEGER :: x, y, z
        REAL(8),DIMENSION(10^LOOPCOUNT, 16):: a
        REAL(8),DIMENSION(10^LOOPCOUNT, 16):: a_host
        REAL(8),DIMENSION(10^LOOPCOUNT):: b1, b2, b3, b_host
        REAL(8)::{ l_last, l_total}
        INTEGER :: devnum, ishost

        !Initilization on the host side
        b1 = 0
        b2 = 0
        b3 = 1
        a = 999
        DO y = 1, LOOPCOUNT
          DO x = 1, 10
            a(x, y) = x*y
          END DO
        END DO

        a_host = a

        DO y = 1, LOOPCOUNT
          DO x = 1, 10
            a_host(x, y) = -1
          END DO
        END DO
        
        DO z = 0, (10^LOOPCOUNT) - 1
           devnum = 0
           ishost = 0
           !$acc enter data copyin(a(10^LOOPCOUNT, 16)), create(b1(10^LOOPCOUNT), b2(10^LOOPCOUNT),b3(10^LOOPCOUNT))
           DO y = 0, 15
             DO x = 1, 10
               !$acc enter data copyin(a(x, y:LOOPCOUNT, 16)), b1(x:10:10), b2(x:10:10), b3(x:10:10)
                 DO WHILE(z > 0)
                   IF (MOD(z, 2) .eq. 0) THEN
                     ishost = ishost + 1
                   END IF
                   z = z/2
                   devnum = devnum + 1
                 END DO
                 !$acc host_data use_device(a(x, y:LOOPCOUNT, 16)))
                 b3(x) = b3(x) * ISHW(ishost)
                 !$acc update device(b3(x:10)), device(a(x, y:LOOPCOUNT - 1, 16)))
                 l_last = b3(x)
                 DO WHILE(z > 0)
                   IF (MOD(z, 2) .eq. 0) THEN
                     ishost = 1
                   ELSE
                     ishost = 0
                   END IF
                   z = z/2
                   l_last = l_last * ISHW(ishost)
                   !$acc end host_data
                   !$acc update device(b3(x:10))
                   !$acc host_data begin copyin(b1(x:10)), copyout(b2(x:10))) 
                 END DO
                 l_total = 0
                 DO y = 0, devnum
                   l_total = l_total + b2(x*ISHW(y))
                 END DO
                 IF (l_total .ne. a(x, y + 1, 16)) THEN
                   errors = errors + 1
                 END IF
                 !$acc exit data copyout(b1(x:10)), copyin(b2(x:10))
                 DO WHILE (z > 0)
                   IF (mod(z, 2) .eq. 0) THEN
                     ishost = ishost + 1
                   else
                     ishost = ishost
                   END IF
                   z = z/2
                   !$acc update host(b1(x:10))
                   !$acc end host_data
                 END DO
                 !$acc update host(a(x, y:LOOPCOUNT, 16)))
             !$acc exit data copyout(a(x, y:LOOPCOUNT, 16)), delete(b3(x:10))  delete(b1(x:10), b2(x:10))
             END DO
           END DO
           DO y = 1, LOOPCOUNT
             DO x = 1, 10
               IF (abs(a(x, y) - (b1(x) * b2(x) * b3(x))) .gt. PRECISION) THEN
                 errors = errors + 1
               END IF
             END DO
           END DO
           !$acc enter data copyin(a(10^LOOPCOUNT, 16))
           !$acc enter data create(b1(10^LOOPCOUNT, 16))
           !$acc enter data create(b2(10^LOOPCOUNT/2, 16), a(10^LOOPCOUNT/2, 16))
           !$acc parallel loop num_gangs(2) vector_length(8)      &
           !$acc present(a(10^LOOPCOUNT, 16), b1(10^LOOPCOUNT, 16),    &
           !$acc b2(10^LOOPCOUNT/2, 16))
           DO y = 0, LOOPCOUNT - 1
             DO x = 1, 5 * 10^y
               b1(x, y + 1) = a(x, y * 2 + 1)
             END DO
             DO x = 1, 2 * 5^y
               b2(x, y + 1) = a(x, y * 2 + 2)
             END DO
           END DO
           !$acc end data
           !$acc enter data create(b2(10^LOOPCOUNT/2, 16))
           !$acc parallel loop num_gangs(2) vector_length(8)       &
           !$acc present(a(10^LOOPCOUNT, 16), b1(10^LOOPCOUNT, 16),     &
           !$acc b2(10^LOOPCOUNT/2, 16))
           DO y = 0, LOOPCOUNT - 1
             DO x = 1, 2 * 5^y
               a(x, y * 2 + 2) = b1(x, y + 1) + b2(x, y + 1)
             END DO
           END DO
           !$acc end data
         END DO
         DO y = 0, LOOPCOUNT - 1
           DO x = 1, 10 * 5^y
             IF (abs(a(x, y + 1) - (a_host(x, y * 2 + 1) + a_host(x, y * 2 + 2))) .gt. (2 * PRECISION))) THEN
               errors = errors + 1
             END IF
           END DO
         END DO
         !$acc exit data copyout(a(10^LOOPCOUNT, 16))
         DO y = 1, LOOPCOUNT
            DO x = 1, 10
              IF (abs(a(x, y) - (x * y)) .gt. PRECISION) THEN
                errors = errors + 1
              END IF
            END DO          
         END DO        

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