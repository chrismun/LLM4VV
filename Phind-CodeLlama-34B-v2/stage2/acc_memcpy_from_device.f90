#ifndef T1
!T1:acc memcpy from device,V:2.7-2.3
      LOGICAL FUNCTION test1()
        USE OPENACC
        IMPLICIT NONE
        INCLUDE "acc_testsuite.Fh"
        
        INTEGER :: errors = 0
        INTEGER, PARAMETER :: N = 1024
        REAL(8), DIMENSION(N) :: a, b
        REAL(8), DIMENSION(:), POINTER :: d_a, d_b
        TYPE(C_PTR) :: cptr_a, cptr_b

        ! Allocate memory on the device
        cptr_a = acc_malloc(N * 8)
        cptr_b = acc_malloc(N * 8)

        ! Associate device memory with host arrays
        CALL C_F_POINTER(cptr_a, d_a, [N])
        CALL C_F_POINTER(cptr_b, d_b, [N])

        ! Initialize host arrays
        a = 1.0
        b = 2.0

        ! Copy data from host to device
        CALL acc_copyin(a, d_a)
        CALL acc_copyin(b, d_b)

        ! Launch kernel to perform vector addition
        !$acc parallel
        !$acc loop
        DO i = 1, N
          d_a(i) = d_a(i) + d_b(i)
        END DO
        !$acc end parallel

        ! Copy data back from device to host
        CALL acc_copyout(d_a, a)

        ! Check if the kernel executed correctly
        DO i = 1, N
          IF (a(i) .ne. 3.0) THEN
            errors = errors + 1
          END IF
        END DO

        ! Free device memory
        CALL acc_free(cptr_a)
        CALL acc_free(cptr_b)

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