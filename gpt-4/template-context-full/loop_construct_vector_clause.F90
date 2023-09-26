!acc_testsuite.Fh: OpenACC TestSuite Header File
!**********************************************
      INTEGER, PARAMETER :: TEST_PASSES=10
      INTEGER, PARAMETER :: NUM_TEST_CALLS=100
      INTEGER, PARAMETER :: NUM_THREADS=4
      INTEGER, PARAMETER :: VEC_LEN=32
!**********************************************
#ifndef T1
!T1:loop construct vector clause,V:2.7-2.3
      logical function test1()
        use openacc
        implicit none
        INCLUDE "acc_testsuite.Fh"
        
        INTEGER :: errors = 0
        INTEGER :: i, n=100
        INTEGER, DIMENSION(n) :: out, in
        INTEGER :: vector_length

        in = (/ (i,i=1,n) /)
        out = 0

        !$acc parallel vector_length(VEC_LEN)
        !$acc loop vector
        DO i = 1, n
          out(i) = in(i)
        END DO
        !$acc end parallel

        vector_length = acc_get_property(acc_device_not_host, acc_device_num( acc_async_sync ), acc_property_vector_length)
        
        IF (vector_length .ne. VEC_LEN) THEN
          errors = errors + 1   
        END IF

        DO i = 1, n
          IF (out(i) .ne. in(i)) THEN
            errors = errors + 1
          END IF
        END DO

        IF (errors .eq. 0) THEN
          test1 = .FALSE.
        ELSE
          test1 = .TRUE.
        END IF
      END
#endif

      PROGRAM main
        implicit none
        INTEGER :: failcode, testrun
        LOGICAL :: failed
        INCLUDE "acc_testsuite.Fh"
#ifndef T1
        logical :: test1
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