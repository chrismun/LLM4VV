#ifndef T1
!T1:acc unmap data,V:2.7-2.3
      LOGICAL FUNCTION test1()
        USE OPENACC
        IMPLICIT NONE
        INCLUDE "acc_testsuite.Fh"
        
        INTEGER :: errors = 0
        REAL(KIND=4), DIMENSION(:), ALLOCATABLE :: a
        REAL(KIND=4), DIMENSION(:), POINTER :: a_d
        INTEGER :: i, n

        n = 100
        ALLOCATE(a(1:n))
        ALLOCATE(a_d(1:n))

        ! Initialize host data
        DO i = 1, n
          a(i) = REAL(i)
        END DO

        ! Map data to device
        a_d => a
        CALL acc_map_data(a_d, n)

        ! Unmap data from device
        CALL acc_unmap_data(a_d)

        ! Check if unmap was successful
        IF (ASSOCIATED(a_d)) THEN
          errors = errors + 1
        END IF

        DEALLOCATE(a)
        DEALLOCATE(a_d)

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