#ifndef T1
!T1:data construct no_create clause,V:2.7-2.3
      LOGICAL FUNCTION test1()
        USE OPENACC
        IMPLICIT NONE
        INCLUDE "acc_testsuite.Fh"
        
        INTEGER :: errors = 0
        INTEGER, PARAMETER :: N = 100
        INTEGER :: i
        INTEGER, DIMENSION(:), ALLOCATABLE :: a, a_host

        ALLOCATE(a(N), a_host(N))

        ! Initialize host array
        DO i = 1, N
          a_host(i) = i
        END DO

        !$acc data copyin(a_host) copyout(a)
        !$acc parallel loop
        DO i = 1, N
          a(i) = a_host(i)
        END DO
        !$acc end data

        !$acc data no_create(a_host)
        !$acc parallel loop
        DO i = 1, N
          a_host(i) = a(i)
        END DO
        !$acc end data

        ! Check results
        DO i = 1, N
          IF (a_host(i) .ne. i) THEN
            errors = errors + 1
          END IF
        END DO

        DEALLOCATE(a, a_host)

        IF (errors .eq. 0) THEN
          test1 = .FALSE.
        ELSE
          test1 = .TRUE.
        END IF
      END
#endif