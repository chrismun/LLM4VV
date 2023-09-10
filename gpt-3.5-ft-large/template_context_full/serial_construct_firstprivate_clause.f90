#ifndef T1
!T1:serial construct firstprivate clause,V:2.7-2.3
      LOGICAL FUNCTION test1()
        USE OPENACC
        IMPLICIT NONE
        INCLUDE "acc_testsuite.Fh"
        INTEGER :: errors = 0


       !array data
        INTEGER, DIMENSION(10):: a
        INTEGER, DIMENSION(10):: a_copy
       !variables
        INTEGER:: i, temp = 0, temp_copy = 31


       !init
        a = 0

        a(1) = 10

        a_copy = 0

        IF (acc_on_device(acc_get_device_num(acc_get_device_type()))) THEN
          #pragma acc enter data create(a(1:10))
      END IF

      !$acc serial firstprivate(a_copy(1))) copy(a(1:10))
      !$acc loop
        DO i = 2, 10
          a(i) = a(i-1) + 1
        END DO
        DO i = 1, 10
          a_copy(i) = a(i)
        END DO
      END DO


      IF (acc_on_device(acc_get_device_num(acc_get_device_type()))) THEN
          #pragma acc exit data copyout(a(1:10))
        END IF

        temp = 0
      !$acc update host(a_copy(1:10)))
        DO i = 1, 10
          temp = temp + a_copy(i)
        END DO

        IF (temp .eq. temp_copy) THEN
          a(0) = 1
        ELSE
          errors = 1
      END IF

      IF (errors .eq. 0) THEN
          test1 = .FALSE.
      ELSE
          test1 = .TRUE.
        END IF
      END
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
      END PROGRAM