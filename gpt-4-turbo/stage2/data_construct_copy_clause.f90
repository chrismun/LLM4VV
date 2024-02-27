! Example code to test OpenACC data construct copy clause in Fortran.
!T1:data construct copy clause,V:2.7-2.3
      MODULE test_module
        USE OPENACC
        IMPLICIT NONE
      CONTAINS
        LOGICAL FUNCTION test1()
        INTEGER, DIMENSION(10) :: hostArray
        INTEGER :: i, errors

        hostArray = 0
        errors = 0

        ! Using the copy clause
        !$acc enter data copy(hostArray)

        ! Performing some computation on the device
        !$acc parallel loop
        DO i = 1, 10
          hostArray(i) = i
        END DO
        
        !$acc exit data copyout(hostArray)

        ! Checking if the modifications are reflected on the host
        DO i = 1, 10
          IF (hostArray(i) /= i) THEN
            errors = errors + 1
          END IF
        END DO

        IF (errors .eq. 0) THEN
          test1 = .TRUE.
        ELSE
          test1 = .FALSE.
        END IF
      END FUNCTION test1
      END MODULE test_module

      PROGRAM main
        USE test_module
        IMPLICIT NONE
        INTEGER :: failcode, testrun
        LOGICAL :: failed
        failed = .FALSE.
        failcode = 0

        LOGICAL :: test1

        DO testrun = 1, 1 ! Only one test call, since this is a simple test
          failed = failed .OR. test1()
        END DO
        IF (failed) THEN
          failcode = failcode + 2 ** 0
        END IF

        CALL EXIT (failcode)
      END PROGRAM main