#ifndef TEST1
!TEST1:enter data directive,V:2.7-2.3
      LOGICAL FUNCTION enter_data_test()
        USE OPENACC
        IMPLICIT NONE
        INTEGER :: errors = 0
        INTEGER, DIMENSION(:), ALLOCATABLE :: arr
        INTEGER :: sum

        ALLOCATE(arr(10))
        arr = (/ (I, I=1, 10) /)
        sum = 0

        !$ACC ENTER DATA COPYIN(arr)

        !$ACC PARALLEL LOOP REDUCTION(+:sum)
        DO I=1, 10
            sum = sum + arr(I)
        END DO

        !$ACC EXIT DATA DELETE(arr)

        IF (sum /= 55) THEN
          errors = errors + 1
        END IF

        IF (errors .eq. 0) THEN
          enter_data_test = .FALSE.
        ELSE
          enter_data_test = .TRUE.
        END IF
      END FUNCTION enter_data_test
#endif

      PROGRAM main
        IMPLICIT NONE
        INTEGER :: failcode, testrun
        LOGICAL :: failed
#ifndef TEST1
        LOGICAL :: enter_data_test
#endif
        failed = .FALSE.
        failcode = 0
#ifndef TEST1
        DO testrun = 1, NUM_TEST_CALLS
          failed = failed .or. enter_data_test()
        END DO
        IF (failed) THEN
          failcode = failcode + 2 ** 0
        END IF
#endif
        CALL EXIT (failcode)
      END PROGRAM main