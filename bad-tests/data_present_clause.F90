#ifndef T1
!T1:data present clause,V:2.7-2.3
      LOGICAL FUNCTION test1()
        USE OPENACC
        IMPLICIT NONE
        INTEGER, DIMENSION(:), ALLOCATABLE :: array
        INTEGER :: datasize = 1024
        INTEGER :: errors = 0
        INTEGER :: i 

        ALLOCATE (array(datasize))

        DO i=1, datasize
            array(i) = i
        END DO

        !$ACC ENTER DATA COPYIN(array)

        !$ACC PARALLEL PRESENT(array)
        DO i=1, datasize
            array(i) = array(i) + 1
        END DO
        !$ACC END PARALLEL

        !$ACC EXIT DATA COPYOUT(array)

        DO i=1, datasize
            IF (array(i) /= i + 1) THEN
                errors = errors + 1
            END IF
        END DO

        DEALLOCATE (array)

        IF (errors .eq. 0) THEN
          test1 = .FALSE.
        ELSE
          test1 = .TRUE.
        END IF
      END FUNCTION test1
#endif