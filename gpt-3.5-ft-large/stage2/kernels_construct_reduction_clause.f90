#ifndef T1
!T1:kernels construct reduction clause,V:2.7-2.3
!#REduction:,kernels construct,part(256:383)
      LOGICAL FUNCTION test1()
        USE OPENACC
        IMPLICIT NONE
        INCLUDE "acc_testsuite.Fh"
        
        INTEGER :: errors = 0
        REAL(8), DIMENSION(10, 128), PUBLIC :: a, b, c, d
        REAL(8) :: avg
        INTEGER :: x, y
        INTEGER :: temp
        INTEGER, PUBLIC :: a_host(10*128), b_host(10*128), c_host(10*128), temp_H(10) = 0, per_H(10), final_H(10), check(128)

        a = 0.0
        b = 0.0
        c = 0.0
        d = 0.0
        SEEDDIM(1)
        CALL RANDOM_SEED 
        CALL RANDOM_NUMBER(a)
        CALL RANDOM_NUMBER(b)
        CALL RANDOM_NUMBER(c)
        avg = 0
        !$acc data copy(a(1:10, 1:128), b(1:10, 1:128), c(1:10, 1:128), d(1:10, 1:128)) copyout(d(1:10, 1:128))
          !$acc kernels reduction(+:avg)
          DO y = 1, 10
            avg = 0
            !$acc loop independent reduction(+:avg)
            DO x = 1, 128
              avg = avg + ((a(y, x) + b(y, x) + c(y, x)) / 3 )
            END DO
            avg = avg / 128
            !$acc loop independent
            DO x = 1, 128
              d(y, x) = a(y, x) + b(y, x) + c(y, x) - avg
            END DO
          END DO
        !$acc end data
        DO y = 1, 10
          DO x = 1, 128
            temp_H(y) = temp_H(y) + a_host((y - 1) * 128 + x) + b_host((y - 1) * 128 + x) + c_host((y - 1) * 128 + x)
          END DO
          temp_H(y) = temp_H(y) / 128
          DO x = 1, 128
            final_H((y - 1) * 128 + x) = a_host((y - 1) * 128 + x) + b_host((y - 1) * 128 + x) + c_host((y - 1) * 128 + x) - temp_H(y)
          END DO
        END DO
        DO y = 1, 10
          DO x = 1, 128
            IF (abs(final_H((y - 1) * 128 + x) - d(y, x)) .GT. PRECISION) THEN
              errors = errors + 1
              EXIT
            END IF
          END DO
        END DO

        !Test 2 predefined reduction operator test (logical exclusive or)
        !$acc data copyin(a(1:10, 1:128), b(1:10, 1:128), c(1:10, 1:128)) copyout(b(1:10, 1:128))
        DO y = 1, 10
          !$acc kernels reduction( .:temp_H(0:128) )
          DO x = 1, 128
            b(y, x) = a(y, x)
            temp_H(x) = input(y, x) .xor. sum
          END DO
        END DO
          !$acc end kernels
        END DO
  
        !$acc end data
        

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