#ifndef T1
!T1:acc memcpy d2d,V:2.7-2.3
      LOGICAL FUNCTION test1()
        USE OPENACC
        IMPLICIT NONE
        INCLUDE "acc_testsuite.Fh"
        
        INTEGER :: errors = 0
        INTEGER, PARAMETER :: N = 100
        REAL(KIND=4), DIMENSION(N) :: a, a_dev1, a_dev2
        INTEGER :: i, dev_num_src, dev_num_dest

        ! Initialize data on host
        DO i = 1, N
          a(i) = REAL(i)
        END DO

        ! Copy data to device 1
        !$ACC DATA COPYIN(a) CREATE(a_dev1)
        !$ACC KERNELS
        DO i = 1, N
          a_dev1(i) = a(i)
        END DO
        !$ACC END KERNELS
        !$ACC END DATA

        ! Get device numbers
        dev_num_src = acc_get_device_num(acc_device_nvidia)
        dev_num_dest = acc_get_device_num(acc_device_radeon)

        ! Copy data from device 1 to device 2
        CALL acc_memcpy_d2d(a_dev2, a_dev1, N*4, dev_num_dest, dev_num_src)

        ! Check results
        !$ACC DATA COPYIN(a_dev2)
        !$ACC KERNELS
        DO i = 1, N
          IF (a_dev2(i) .NE. REAL(i)) THEN
            errors = errors + 1
          END IF
        END DO
        !$ACC END KERNELS
        !$ACC END DATA

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