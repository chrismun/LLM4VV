! Add this snippet within the test1() function.

       INTEGER, PARAMETER :: N = 1000
       REAL, DIMENSION(N) :: A, B, C
       INTEGER :: I

       A = 1.0
       B = 2.0
       C = 0.0

       !$ACC PARALLEL LOOP
       DO I = 1, N
          C(I) = A(I) + B(I)
       END DO

       !$ACC END PARALLEL

       DO I = 1, N
         IF (C(I) /= 3.0) THEN
            errors = errors + 1
         END IF
       END DO