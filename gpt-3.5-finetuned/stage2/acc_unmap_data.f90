!T1:acc unmap data,V:2.7-2.3
      LOGICAL FUNCTION test1()
      USE OPENACC
      IMPLICIT NONE
      INCLUDE "acc_testsuite.Fh"
      INTEGER :: errors = 0
      REAL(8),DIMENSION(LOOPCOUNT) :: a, b, c
      INTEGER :: i
      INTEGER :: a_dev_ptr, b_dev_ptr, c_dev_ptr

      !Init
      SEEDDIM(1) = 1
      CALL RANDOM_SEED(PUT=SEEDDIM)

      CALL RANDOM_NUMBER(a)
      CALL RANDOM_NUMBER(b)
      c = 0

      !$acc enter data create(c(1:LOOPCOUNT))
      !$acc update device(c(1:LOOPCOUNT))
      !$acc data copyin(a(1:LOOPCOUNT), b(1:LOOPCOUNT)) create(a(1:LOOPCOUNT),b(1:LOOPCOUNT))
        !$acc host_data use_device(a,b)
          DO i = 1, LOOPCOUNT
            a(i) = a(i) * a(i)
            b(i) = b(i) * b(i)
          END DO
        !$acc end host_data
        CALL acc_map_data(c(1:LOOPCOUNT), c_dev_ptr)
        !$acc enter data copyin(a(1:LOOPCOUNT), b(1:LOOPCOUNT))
          !$acc parallel
            !$acc loop
              DO i = 1, LOOPCOUNT
                c(i) = a(i) + b(i)
            END DO
          !$acc end parallel
        !$acc exit data delete(a(1:LOOPCOUNT), b(1:LOOPCOUNT))
      !$acc end data
      CALL acc_unmap_data(c(1:LOOPCOUNT))
      DO i = 1, LOOPCOUNT
        IF (abs(c(i) - (a(i) + b(i))) .gt. TOLERANCE) THEN
          errors = errors + 1
          EXIT
        END IF
      END DO
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