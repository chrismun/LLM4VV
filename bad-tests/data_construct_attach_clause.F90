#ifndef T1
!T1:data construct attach clause,V:2.7-2.3
      LOGICAL FUNCTION test1()
        USE OPENACC
        IMPLICIT NONE
        INCLUDE "acc_testsuite.Fh"
        
        INTEGER :: errors = 0
        INTEGER, ALLOCATABLE, DEVICE :: d_arr(:)
        INTEGER, POINTER :: h_ptr
        INTEGER, DIMENSION(:), ALLOCATABLE :: h_arr
        INTEGER :: arr_size = 100
        INTEGER :: i

        ALLOCATE(h_arr(arr_size))
        ALLOCATE(d_arr(arr_size))

        ! Initialize host array
        DO i = 1, arr_size
          h_arr(i) = i
        END DO

        h_ptr => h_arr

        !$ACC ENTER DATA CREATE (d_arr)
        !$ACC ATTACH d_arr= h_ptr

        ! Copy host array to device 
        !$ACC UPDATE DEVICE(d_arr)
        
        !$ACC PARALLEL LOOP
        DO i = 1, arr_size
          IF (d_arr(i) /= h_arr(i)) THEN
            errors = errors + 1
          END IF
        END DO

        !$ACC DETACH d_arr
        !$ACC EXIT DATA DELETE(d_arr)

        IF (errors .eq. 0) THEN
          test1 = .FALSE.
        ELSE
          test1 = .TRUE.
        END IF
      END FUNCTION test1
#endif

      PROGRAM main
        IMPLICIT NONE
        INTEGER :: failcode, testrun
        LOGICAL :: failed
        INCLUDE "acc_testsuite.Fh"
        
#ifndef T1
        LOGICAL :: test1
#endif
        failcode = 0
        failed = .FALSE.
        
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
      END PROGRAM main