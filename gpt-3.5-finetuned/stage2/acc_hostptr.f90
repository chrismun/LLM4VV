!T1:acc hostptr,V:2.7-2.3
      LOGICAL FUNCTION test1()
        USE OPENACC
        IMPLICIT NONE
        INCLUDE "acc_testsuite.Fh"
        
        INTEGER :: errors = 0

        ! Use the acc_hostptr function to get the host pointer associated with a device pointer
        REAL(8), ALLOCATABLE, TARGET :: a(:)
        INTEGER :: device_array
        TYPE(C_PTR) :: h_a

        ALLOCATE(a(N))
        h_a = c_f_pointer(c_loc(a), (/height/)) ! Getting the device pointer to use with acc_hostptr
        device_array = a  ! Get device address
        a = 5 ! Initialize host memory
        !$acc update device(a(1:height))
        !$acc parallel present(h_a)
          !$acc loop
          DO i = 1, height
            a(i) = a(i) * 2
          END DO
        !$acc end parallel
        PRINT*, acc_hostptr(device_array, 1d0, 1.0)
        IF (allocated(a)) THEN
          errors = errors + 1
          PRINT*, "acc_hostptr unchanged"
        END IF
        !$acc exit data delete(a)
        IF (allocated(a)) THEN
          PRINT*, "alloc has data"
          errors = errors + 1
        END IF
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