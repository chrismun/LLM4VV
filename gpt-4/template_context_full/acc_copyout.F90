!T1:acc copyout,V:2.7-2.3
  LOGICAL FUNCTION test1()
    USE OPENACC
    IMPLICIT NONE
    INTEGER :: i
    INTEGER, DIMENSION(:), ALLOCATABLE :: h_data, d_data
    INTEGER :: errors = 0
    INTEGER :: nelements = 100

    ALLOCATE(h_data(nelements))
    ALLOCATE(d_data(nelements))

    DO i = 1, nelements
      h_data(i) = i
    END DO

    !$acc enter data copyin(h_data(1:nelements))
    !$acc kernels present(d_data) copy(d_data(1:nelements)=h_data(1:nelements))
    !$acc end kernels

    DEALLOCATE(d_data)
    CALL acc_copyout(d_data, nelements * size_of(h_data))

    IF (ALL(h_data == d_data)) THEN
      errors = errors + 1
    END IF

    !$acc exit data delete(h_data(1:nelements))

    IF (errors .eq. 0) THEN
      test1 = .FALSE.
    ELSE
      test1 = .TRUE.
    END IF
  END FUNCTION test1

  PROGRAM main
    IMPLICIT NONE
    INTEGER :: failcode, testrun
    LOGICAL :: failed
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
  END PROGRAM main