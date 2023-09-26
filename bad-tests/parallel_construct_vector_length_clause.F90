! Test OpenACC vector_length clause on parallel construct
MODULE openacc_test
  USE OPENACC
  IMPLICIT NONE
  INTEGER, PARAMETER :: N = 1024, VECTOR_LENGTH = 128
  REAL, DIMENSION(:), ALLOCATABLE :: A, B, C
  INTEGER :: i, errors 

CONTAINS 

  LOGICAL FUNCTION test_vector_length()
    INTEGER :: myVectorLength, expected 
    REAL :: temp

    ALLOCATE(A(N), B(N), C(N))
    FORALL(i = 1:N) A(i) = i
    FORALL(i = 1:N) B(i) = N - i

    ! test_vector_length should return .false. when the OpenACC vector_length clause works correctly
    errors = 0
    ! restrict vector_length to certain logical threads.
    !$ACC parallel loop vector_length(VECTOR_LENGTH)
    DO i = 1, N 
      C(i) = A(i) + B(i)
    END DO
    !$ACC end parallel loop

    myVectorLength = acc_get_device_num(acc_device_nvidia)
    expected = min(VECTOR_LENGTH, acc_get_property(myVectorLength,acc_device_nvidia,acc_property_vectorSize))
    IF (myVectorLength /= expected) THEN
      errors = errors + 1
    END IF

    DEALLOCATE(A, B, C)

    IF (errors == 0) THEN
      test_vector_length = .FALSE.
    ELSE
      test_vector_length = .TRUE.
    END IF
  END FUNCTION test_vector_length

End Module openacc_test

PROGRAM main
  USE openacc_test
  IMPLICIT NONE
  LOGICAL :: testPassed
  INTEGER :: failcode
  failcode = 0
  testPassed = test_vector_length()
  IF (.NOT. testPassed) THEN
    failcode = 1
  END IF
  CALL EXIT(failcode)
END PROGRAM main