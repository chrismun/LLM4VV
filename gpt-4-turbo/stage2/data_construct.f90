! Example code in Fortran to test the OpenACC data construct.
! This code verifies that the data is correctly copied to the device, modified, and copied back.
!TEST_DATA_CONSTRUCT:data construct,V:2.7-2.3
      LOGICAL FUNCTION test_data_construct()
        USE OPENACC
        IMPLICIT NONE

        INTEGER, DIMENSION(10) :: host_array
        INTEGER :: i, errors

        errors = 0

        ! Initialize host_array on the host
        DO i = 1, 10
          host_array(i) = i
        END DO

        ! Use OpenACC data region with copy to operate on host_array
        !$acc data copy(host_array)
          !$acc parallel loop
          DO i = 1, 10
            host_array(i) = host_array(i) ** 2
          END DO
        !$acc end data

        ! Check the results
        DO i = 1, 10
          IF (host_array(i) /= i**2) THEN
            errors = errors + 1
          END IF
        END DO

        IF (errors == 0) THEN
          test_data_construct = .FALSE.
        ELSE
          test_data_construct = .TRUE.
        END IF
      END FUNCTION test_data_construct

      PROGRAM main
        IMPLICIT NONE
        INTEGER :: failcode, testrun
        LOGICAL :: failed

        LOGICAL :: test_data_construct

        failed = .FALSE.
        failcode = 0
        failed = test_data_construct()
        IF (failed) THEN
          failcode = failcode + 2 ** 0
        END IF
        print *, "Test Completed - Failcode:", failcode
        CALL EXIT(failcode)
      END PROGRAM main