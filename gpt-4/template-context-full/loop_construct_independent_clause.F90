#ifndef T1
!T1:loop construct independent clause,V:2.7-2.3
    LOGICAL FUNCTION test1()
        USE OPENACC
        IMPLICIT NONE
        REAL, DIMENSION(1024, 1024) :: a, b, c
        INTEGER :: i, j, k, errors = 0
        real :: diff, expected

        a = 1.0
        b = 2.0
        c = 0.0
        expected = 2048.0

        ! Use independent clause to allow iterations to execute in parallel
        !$ACC PARALLEL LOOP INDEPENDENT
        DO j = 1, 1024
            !$ACC LOOP INDEPENDENT
            DO i = 1, 1024
                DO k = 1, 1024
                    c(i,j) = c(i,j) + a(i,k) * b(k,j)
                END DO
            END DO
        END DO

        ! Verify results
        DO j = 1, 1024
            DO i = 1, 1024
                diff = ABS(expected - c(i,j))
                IF (diff > 0.001) THEN
                    errors = errors + 1
                END IF
            END DO
        END DO

        IF (errors .eq. 0) THEN
            test1 = .TRUE.
        ELSE
            test1 = .FALSE.
        END IF
    END FUNCTION test1
#endif