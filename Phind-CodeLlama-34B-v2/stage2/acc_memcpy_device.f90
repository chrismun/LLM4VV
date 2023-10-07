#ifndef T1
!T1:acc memcpy device,V:2.7-2.3
      LOGICAL FUNCTION test1()
        USE OPENACC
        IMPLICIT NONE
        INCLUDE "acc_testsuite.Fh"
        
        INTEGER :: errors = 0
        INTEGER(KIND=8), PARAMETER :: N = 1024
        REAL(KIND=8), DIMENSION(N) :: a, b, c
        TYPE(C_PTR) :: a_dev, b_dev

        a = 1.0
        b = 2.0

        ! Allocate device memory
        a_dev = acc_malloc(N * 8)
        b_dev = acc_malloc(N * 8)

        ! Copy data to device
        CALL acc_memcpy_device(a_dev, C_LOC(a), N * 8)
        CALL acc_memcpy_device(b_dev, C_LOC(b), N * 8)

        ! Perform element-wise addition on device
        CALL acc_map_data(c_dev, N * 8)
        CALL acc_map_data(a_dev, N * 8)
        CALL acc_map_data(b_dev, N * 8)
        !$acc parallel loop
        DO i = 1, N
          c(i) = a(i) + b(i)
        END DO
        !$acc end parallel loop
        CALL acc_unmap_data(c_dev)
        CALL acc_unmap_data(a_dev)
        CALL acc_unmap_data(b_dev)

        ! Copy result back to host
        CALL acc_memcpy_device(C_LOC(c), c_dev, N * 8)

        ! Check result
        DO i = 1, N
          IF (c(i) .ne. 3.0) THEN
            errors = errors + 1
          END IF
        END DO

        ! Free device memory
        CALL acc_free(a_dev)
        CALL acc_free(b_dev)

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