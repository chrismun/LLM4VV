#ifndef T1
!T1:acc delete,V:2.7-2.3
      LOGICAL FUNCTION test1()
        USE OPENACC
        IMPLICIT NONE
        INCLUDE "acc_testsuite.Fh"

        INTEGER :: errors = 0

        ! Test deleting object constructed on device

        TYPE(DEVICE_LIST) :: a
        TYPE(DEVICE_LIST), POINTER :: devtest
        INTEGER :: b, n = 100000
        INTEGER, DEVICE :: c(1)
        REAL(8), DEVICE :: randomdata(n), hostcopy(n)
        INTEGER :: x

        ! Data initialization
        SEEDDIM(1) = 1
#       SEED
        CALL RANDOM_SEED(PUT=SEED)
        CALL RANDOM_NUMBER(randomdata)
        hostcopy = 1

        devtest => NULL

        !$acc enter data copyin(a(1:DEV_ALLOC/sizeof(DEVICE_LIST))))
        DO WHILE (devtest .eqv. NULL)
          !$acc serial present(a(1:DEV_ALLOC/sizeof(DEVICE_LIST))))
          !$acc loop
          DO x = 1, 400
            devtest = a(x)
            IF (ISDEVPRESENT(devtest)) THEN
              a(x) = devtest
            ELSE
              a(x) = devtest
            END IF
          END DO
          !$acc serial present(a(1:DEV_ALLOC/sizeof(DEVICE_LIST)))) vector_length(16)
          !$acc loop vector_length(16)
          DO x = 1, 400
            a(x) = a(x)
          END DO
          !$acc end serial
        END DO

        DO x = 1, n
          IF (randomdata(x) .lt. .5) THEN
            randomdata(x) = 2
            hostcopy(x) = 2
          END IF
        END DO

        !$acc enter data copyin(randomdata(1:n))
        !$acc enter data copyin(c(1))
        !$acc parallel
          !$acc loop
          DO x = 1, n
            c(1) = 1
          END DO
        !$acc end parallel
        !$acc enter data copyin(c(1:1))
        !$acc parallel
          !$acc loop
          DO x = 1, n
            c(1) = c(1) + 1
          END DO
          !$acc loop
          DO x = 1, n
            randomdata(x) = randomdata(x) + c(1)
          END DO
        !$acc end parallel
        !$acc exit data copyout(randomdata(1:n))

        DO x = 1, n
          IF (abs(randomdata(x) - (1 + hostcopy(x))) .gt. PRECISION) THEN
            errors = errors + 1
          END IF
        END DO
        !$acc data copyin(a(1:DEV_ALLOC/sizeof(DEVICE_LIST)))) delete(a(1:DEV_ALLOC/sizeof(DEVICE_LIST))))

        !$acc data copy(a(1)) copyout(b) present(a(1), b)
          b = 0
          !$acc parallel
            b = b + a(1)%obj
          !$acc end parallel
          IF (b .ne. 1848) THEN
            errors = errors + 1
          END IF
        !$acc end data

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