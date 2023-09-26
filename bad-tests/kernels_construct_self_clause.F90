! This tests the OpenACC Kernels Construct Self Clause

#ifndef T1
!T1:kernels construct self clause,V:2.7-2.3
    LOGICAL FUNCTION test1()
      USE OPENACC
      IMPLICIT NONE
      INCLUDE "acc_testsuite.Fh"
      
      INTEGER :: errors = 0
      REAL, DIMENSION(:), ALLOCATABLE :: a
      INTEGER :: i, N = 10000
      ALLOCATE (a(N))

      !Initialize a with zeros
      a = 0

      !Execute kernels on local device if self condition is true
      !$ACC KERNELS IF(.false.) SELF(.true.)
      DO i = 1, N
        a(i) = i
      END DO
      !$ACC END KERNELS
      
      !Check for errors
      DO i = 1, N
      IF (ABS(a(i) - i) > 0.0001) THEN
          errors = errors + 1
      END IF
      END DO

      DEALLOCATE(a)

      IF (errors .eq. 0) THEN
        test1 = .FALSE.
      ELSE
        test1 = .TRUE.
      END IF

    END FUNCTION test1
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
END PROGRAM main