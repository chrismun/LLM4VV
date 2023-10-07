!T1:declare directive device_resident clause,V:2.7-2.3
     LOGICAL FUNCTION test1()
       USE OPENACC
       IMPLICIT NONE
       INCLUDE "acc_testsuite.Fh"
       
       INTEGER :: n = 1000
       REAL :: a(n), b(n)
       REAL :: expect_sum
       REAL :: error = 0.0
       INTEGER :: errors = 0
       INTEGER :: i

       DO i = 1, n
         a(i) = float(i)
         b(i) = float(i)
       END DO

       !$ACC DECLARE copy(b) device_resident(a)

       !$ACC PARALLEL LOOP PRIVATE(a) REDUCTION(+:error)
       DO i = 1, n
         b(i) = a(i) + b(i)
         error = error + abs(b(i) - (2*float(i)))
       END DO

       expect_sum = 0.0
       DO i = 1, n
         expect_sum = expect_sum + abs(2*float(i))
       END DO

       IF (error / expect_sum > 1.e-7) THEN
         errors = errors + 1
       END IF

       !$ACC UPDATE SELF(error)

       IF (errors .eq. 0) THEN
         test1 = .FALSE.
       ELSE
         test1 = .TRUE.
       END IF
     END