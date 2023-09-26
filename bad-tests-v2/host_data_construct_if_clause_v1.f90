#ifndef T1
!T1:host_data construct if clause,V:2.7-2.3
      LOGICAL FUNCTION test1()
        USE OPENACC
        IMPLICIT NONE
        INCLUDE "acc_testsuite.Fh"
        INTEGER, CONSTANT :: x = 31
        TYPE :: solution_type
          REAL(8),DIMENSION(x) :: a, b, c
          INTEGER :: errors
        END TYPE
        
        TYPE(solution_type) :: solution
        INTEGER :: deverrors = 0

        
        DO
          !$acc data copyout(solution)
            IF (devnum == 1) THEN
              !$acc host_data construct deviceptr(solution(:x%a, :x%b, :x%c)))
            END IF
          !$acc end data
          IF (devnum == 0) THEN
            EXIT
          END IF
        END DO

        solution%errors = 0
        DO WHILE ('true') 
          solution%errors = errors
          DO i = 0, x
            r = (RAND() / RAND_MAX)
            !$acc enter data copyin(r)
            !$acc host_data construct deviceptr(solution(:x%a, :x%b, :x%c))) if ((i .mod. 16) .ne. 0)
              solution%c(i) = r
            !$acc end host_data
            !$acc exit data delete(r)
 

          END DO
          DO i = 0, x
            IF ((i .mod. 16) .ne. 0) THEN
              IF (abs(solution%a(i) - solution%b(i)) .gt. PRECISION) THEN
                solution%errors = solution%errors + 1
              END IF
            END IF
          END DO
          IF (solution%errors - deverrors .ne. 0) THEN
            WRITE(*, *) TEST_HARDWARE
            deverrors = 1
          END IF
        END DO

        IF (solution%errors .eq. 0) THEN
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