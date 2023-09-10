#ifndef T1
!T1:acc hostptr,V:2.7-2.3
      LOGICAL FUNCTION test1()
        USE OPENACC
        IMPLICIT NONE
        INCLUDE "acc_testsuite.Fh"
        
        INTEGER :: errors = 0          
        INTEGER, ALLOCATABLE, TARGET, DIMENSION(:) :: a, dev_a
        TYPE(C_PTR) :: h_ptr, d_ptr
        INTEGER :: device_data, i, N = 100

        ALLOCATE( a(N) )
        a = 1

        ! Start compute construct, move array a to GPU
        !$acc enter data copyin(a)

        ! Get the device address of the array a
        d_ptr = acc_deviceptr(a)

        ! acc_hostptr should return the host pointer to the array a
        h_ptr = acc_hostptr(d_ptr)

        IF(h_ptr /= C_LOC(a)) THEN
            WRITE(*,*) "acc_hostptr did not return correct host address"
            errors = errors + 1
        END IF

        !$acc exit data delete(a)

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