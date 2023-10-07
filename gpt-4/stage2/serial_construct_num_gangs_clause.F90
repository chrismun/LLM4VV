! Filename : serial_num_gangs_test.f90
#ifndef T1
!T1:serial construct num_gangs clause,V:2.7-2.3
      LOGICAL FUNCTION test1()
        USE OPENACC
        INTEGER :: errors = 0
        INTEGER, DIMENSION(:), ALLOCATABLE :: a
        INTEGER, DIMENSION(:), ALLOCATABLE :: b
        INTEGER :: i
        INTEGER :: gang_size = 1024
        INTEGER :: num_gangs = 1024
        
        ALLOCATE(a(gang_size*num_gangs), b(gang_size*num_gangs))
        a = 1
        b = 0

        !$ACC SERIAL NUM_GANGS(num_gangs)
        DO i = 1, gang_size * num_gangs
          b(i) = a(i)
        END DO
        !$ACC END SERIAL
        
        IF (ALL(b .eq. a)) THEN
          errors = errors + 1
        END IF

        DEALLOCATE(a, b)
        
        IF (errors .eq. 0) THEN
          test1 = .TRUE.
        ELSE
          test1 = .FALSE.
        END IF
      END FUNCTION test1
#endif

      PROGRAM main
        IMPLICIT NONE
        INTEGER :: failcode
        LOGICAL :: failed
#ifndef T1
        LOGICAL :: test1
#endif
        failed = .FALSE.
        failcode = 0
#ifndef T1
        failed = failed .or. (NOT test1())
        IF (failed) THEN
          failcode = failcode + 1
        END IF
#endif
        PRINT*, "Test result : ", failcode
      END PROGRAM main