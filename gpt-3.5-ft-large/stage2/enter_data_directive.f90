PROGRAM main
      IMPLICIT NONE
      INTEGER :: failcode, testrun
      LOGICAL :: failed
      INCLUDE "acc_testsuite.Fh"
      REAL(8),DIMENSION(10) :: a, b, c
      failed = .FALSE.
      failcode = 0
#ifndef T1
      LOGICAL :: test1
#endif
      INTEGER :: dev_present

      dev_present = 1
      !$acc enter data copyin(a(1:10), b(1:10), c(1:10))
      !$acc parallel present(a(1:10), b(1:10), c(1:10))
        !$acc loop
        DO testrun = 0, 9
          a(testrun + 1) = 2.0
        END DO
        !$acc loop
        DO testrun = 0, 9
          b(testrun + 1) = 2.0
        END DO
        !$acc loop
        DO testrun = 0, 9
          c(testrun + 1) = 2.0
        END DO
      !$acc end parallel

      DO testrun = 0, 9
        IF (abs(a(testrun + 1) - 2.0) .gt. PRECISION) THEN
          dev_present = 0
        END IF
        IF (abs(b(testrun + 1) - 2.0) .gt. PRECISION) THEN
          dev_present = 0
        END IF
        IF (abs(c(testrun + 1) - 2.0) .gt. PRECISION) THEN
          dev_present = 0
        END IF
      END DO

      IF (dev_present .eq. 0) THEN
        failcode = failcode + 2**1
      END IF
#ifndef T1
      DO testrun = 1, NUM_TEST_CALLS
        failed = failed .or. test1
      END DO
#endif
      EXIT (failcode)
      END PROGRAM


      LOGICAL FUNCTION test1()
        IMPLICIT NONE
        INTEGER :: errors
        INCLUDE "acc_testsuite.Fh"
        INTEGER :: testrun, dev_present
        REAL(8),DIMENSION(10) :: a, b, c
        dev_present = 1
        errors = 0

        DO testrun = 0, 9
          a(testrun + 1) = 1
          b(testrun + 1) = 1
          c(testrun + 1) = 1
        END DO

        $OMP_TARGET_ENTER_DATA MAPTO(a(0:9),b(0:9),c(0:9))
        $OMP_TARGET
        $OMP_PARALLEL
          $OMP_PARALLEL FOR
          DO testrun = 0, 9
            a(testrun + 1) = 2
          END DO
          $OMP_PARALLEL FOR
          DO testrun = 0, 9
            b(testrun + 1) = 2
          END DO
          $OMP_PARALLEL FOR
          DO testrun = 0, 9
            c(testrun + 1) = 2
          END DO
        $OMP_END PARALLEL
        $OMP_TARGET_EXIT_DATA copyout(a(0:9),b(0:9),c(0:9))

        DO testrun = 0, 9
          IF (abs(a(testrun + 1) - 1) .gt. PRECISION) THEN
            errors = errors + 1
          END IF
          IF (abs(b(testrun + 1) - 1) .gt. PRECISION) THEN
            errors = errors + 1
          END IF
          IF (abs(c(testrun + 1) - 1) .gt. PRECISION) THEN
            errors = errors + 1
          END IF
        END DO

        IF (errors .eq. 0) THEN
          test1 = .FALSE.
        ELSE
          test1 = .TRUE.
        END IF
      END