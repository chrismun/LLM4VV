! Test for atomic construct, OpenACC
! Author: AI Engineer

#ifndef T1
!T1:atomic construct,V:2.7-2.3
      LOGICAL FUNCTION test1()
      USE OPENACC
      IMPLICIT NONE
      INCLUDE "acc_testsuite.Fh"

      INTEGER :: errors = 0
      INTEGER, DIMENSION(1024) :: A, B
      INTEGER :: i, temp

      A = (/ (i, i=1, 1024) /)
      B = 0
      errors = 0

      !$acc data copyin(A) copy(B)
      !$acc parallel num_gangs(1024)
      !$acc loop gang
      DO i=1, 1024
        !$acc atomic
        B = B + A(i)
      END DO
      !$acc end parallel
      !$acc end data

      temp = SUM(A)

      IF (B .ne. temp) THEN
         errors = errors + 1
      END IF

      IF (errors .eq. 0) THEN
         test1 = .TRUE.
      ELSE
         test1 = .FALSE.
      END IF

      END FUNCTION test1
#endif

PROGRAM main
  IMPLICIT NONE
  INCLUDE "acc_testsuite.Fh"

  INTEGER :: failcode
  LOGICAL :: failed

  failcode = 0
  failed = .FALSE.

#ifndef T1
  DO testrun = 1, NUM_TEST_CALLS
    failed = failed .or. test1()
  END DO
  IF (failed) THEN
    failcode = failcode + 1
  END IF
#endif

  CALL EXIT (failcode)
END PROGRAM main