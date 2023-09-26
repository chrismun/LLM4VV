MODULE OpenACC_Test_Mod
        USE OPENACC
        IMPLICIT NONE
        INTEGER, PARAMETER :: n = 100 
        INTEGER :: num_workers, iArr(n)
      END MODULE OpenACC_Test_Mod
      
      SUBROUTINE test_num_workers()
        USE OpenACC_Test_Mod
        INTEGER :: i

        !$ACC PARALLEL NUM_WORKERS(num_workers) 
        !$ACC LOOP
        DO i = 1, n
            iArr(i) = i * 2
        END DO
        !$ACC END PARALLEL
      END SUBROUTINE test_num_workers

      LOGICAL FUNCTION test1()
        USE OpenACC_Test_Mod
        INTEGER :: errors = 0
        COMPLEX :: c

        CALL test_num_workers()

        DO i = 1, n
            IF(iArr(i) /= i*2) THEN
              errors = errors + 1
            END IF
        END DO
        IF (errors .eq. 0) THEN
          test1 = .FALSE.
        ELSE
          test1 = .TRUE.
        END IF
      END FUNCTION test1

      PROGRAM main
        USE OpenACC_Test_Mod
        IMPLICIT NONE
        INTEGER :: failcode, testrun
        LOGICAL :: failed
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
      END PROGRAM main