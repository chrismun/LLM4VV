!T1:kernels construct if clause,V:2.7-2.3
      PROGRAM main
        USE openacc
        IMPLICIT NONE
        INTEGER :: errors = 0
        INTEGER, DIMENSION(1024) :: A
        LOGICAL :: offload_enabled

        offload_enabled = .TRUE.
        CALL test_kernels_if_clause(A, offload_enabled, errors)

        offload_enabled = .FALSE.
        CALL test_kernels_if_clause(A, offload_enabled, errors)

        IF (errors .eq. 0) THEN
          PRINT *, "Test Passed"
        ELSE
          PRINT *, "Test Failed"
        END IF

        CALL EXIT(errors)
      END PROGRAM main

      SUBROUTINE test_kernels_if_clause(A, offload, errors)
        USE openacc
        IMPLICIT NONE
        INTEGER, DIMENSION(:), INTENT(OUT) :: A
        INTEGER, INTENT(INOUT) :: errors
        LOGICAL, INTENT(IN) :: offload
        INTEGER :: i

        !$acc kernels if(offload)
        DO i = 1, SIZE(A)
          A(i) = i
        END DO
        !$acc end kernels

        ! Verify that A has been modified.
        DO i = 1, SIZE(A)
          IF (A(i) /= i) THEN
            errors = errors + 1
          END IF
        END DO
      END SUBROUTINE test_kernels_if_clause
