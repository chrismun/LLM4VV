!T1:kernels_construct_reduction,V:2.7-2.3
LOGICAL FUNCTION test1()
  USE OPENACC
  IMPLICIT NONE
  INCLUDE "acc_testsuite.Fh"

  INTEGER :: errors = 0

  REAL(8), DIMENSION(LOOPCOUNT):: a, b, d
  REAL(8) :: x1, y1, z1, w1
  INTEGER :: x, y, z, w
  REAL(8) :: result
  REAL(8) :: temp_scalar = 0
  REAL(8) :: temp_loop = 0
        
  SEEDDIM(1) = 1
    SEEDDIM(1) = _RANDSEED
  CALL RANDOM_SEED(PUT=SEEDDIM)
  CALL RANDOM_NUMBER(a)
  CALL RANDOM_NUMBER(b)
  d = 0
  result = 0

  !$acc data copyin(a(1:LOOPCOUNT), b(1:LOOPCOUNT)) copyout(d(1:LOOPCOUNT)) copy(result)
    !$acc kernels loop reduction(+:result)
    DO x = 1, LOOPCOUNT
      result = result + a(x) * b(x)
    END DO

    !$acc loop worker independent
    DO x = 1, LOOPCOUNT
      d(x) = d(x) + result
    END DO
  !$acc end data

  DO x = 1, LOOPCOUNT
    IF (abs(d(x) - result) .gt. PRECISION) THEN
      errors = errors + 1
    END IF
  END DO

  !$acc data copyin(a(1:LOOPCOUNT), b(1:LOOPCOUNT)) copyout(d(1:LOOPCOUNT)) copy(result)
    !$acc kernels loop reduction(+:result) 
    DO x = 1, LOOPCOUNT
      DO y = 1, LOOPCOUNT
        result = result + a(x) * b(y) 
      END DO
    END DO

    !$acc loop worker independent
    DO x = 1, LOOPCOUNT
      d(x) = result
    END DO
  !$acc end data

  temp_scalar = 0
  DO w = 1, LOOPCOUNT
    temp_scalar = temp_scalar + a(w) * b(w)
  END DO
  temp_loop = temp_scalar
  temp_scalar = 0

  DO z = 1, LOOPCOUNT
    DO y = 1, LOOPCOUNT
      temp_scalar = temp_scalar + a(z) * b(y)
    END DO
  END DO

  DO w = 1, LOOPCOUNT
    DO z  = 1, LOOPCOUNT
      temp_scalar = temp_scalar + a(w) * b(w)    
    END DO
  END DO

  IF (ABS(d(1) - (temp_loop + even_more_loops) * LOOPCOUNT) .gt. PRECISION) THEN
    errors = errors + 1
  END IF

  !$acc data copyin(a(1:LOOPCOUNT), b(1:LOOPCOUNT)) copyout(d(1:LOOPCOUNT)) 
    !$acc kernels loop independent
    DO w = 1, LOOPCOUNT
      temp = 0
      !$acc loop reduction(+:temp)
      DO z = 1, LOOPCOUNT
        temp = temp + a(z) * b(z)
      END DO
      DO z = 1, LOOPCOUNT
        result = result + a(z) * b(z)
      END DO
      d(w) = temp
    END DO
  !$acc end data

  temp_scalar = 0
  DO z = 1, LOOPCOUNT
    temp_scalar = temp_scalar + (a(z) * b(z))
  END DO

  DO w = 1, LOOPCOUNT
    IF (abs(d(w) - temp_scalar) .gt. PRECISION) THEN
      errors = errors + 1
    END IF
  END DO

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