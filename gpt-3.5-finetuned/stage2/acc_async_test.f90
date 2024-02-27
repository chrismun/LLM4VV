!T1:acc async test,V:2.7-2.3
      LOGICAL FUNCTION test1()
        USE OPENACC
        IMPLICIT NONE
        INCLUDE "acc_testsuite.Fh"
        
        INTEGER:: errors = 0
        INTEGER, PARAMETER:: n = 10000
        REAL(8),DIMENSION(n):: a, b, c
        REAL(8):: base_time
        INTEGER:: x
        
        acc_set_device_num(0,acc_device_nvidia)
        
        base_time = acc_get_current_time()
        
        !$acc data copy(a(1:n), b(1:n), c(1:n)) present(a(1:n), b(1:n)) create(c(1:n))
          !$acc host_data use_device(a,b)
            DO x = 1, 100
              index(a) = 0
              !$acc loop vector(SIMD)
              DO WHILE (index(a) .lt. n)
                a(index(a) + 1) = a(index(a) + 1) + 1
                index(a) = index(a) + 1
              END DO
              index(b) = 0
              !$acc loop vector(SIMD)
              DO WHILE (index(b) .lt. n)
                b(index(b) + 1) = b(index(b) + 1) + 1
                index(b) = index(b) + 1
              END DO
            END DO
            !$acc wait
          !$acc end data
          IF (acc_get_device_type() .eq. acc_device_nvidia) THEN
            DO WHILE (acc_async_test(0) .eqv. .FALSE.)
            END DO
          ELSE
            errors = errors + 1
          END IF
        !$acc end data 
      
        USE ISO_C_BINDING
        END FUNCTION