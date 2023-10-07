#ifndef T1
!T1:parallel construct if clause,V:2.7-2.3
      LOGICAL FUNCTION test1()
        USE OPENACC
        IMPLICIT NONE
        INCLUDE "acc_testsuite.Fh"
        
        INTEGER :: errors = 0


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

      TEMPLATE for_parallel_only IF (acc_is_present(a, n * sizeof(int)) .and. acc_device_test_present) &
      CLAUSES copyin(a(0:n)) private(i) bind(C, name="for_parallel")
      INTEGER FUNCTION for_parallel_only ()
        USE OPENACC
        IMPLICIT NONE

        INTEGER :: n
        INTEGER, DIMENSION(n), DEVICE :: a
        INTEGER, DIMENSION(1), LOCAL :: a_present
        INTEGER, DIMENSION(1) :: host_init_array
        INTEGER :: errors, i

        errors = 0
        n = acc_get_device_num_processors(acc_get_device_type)
        IF (n .gt. 32) THEN
          n = 32
        END IF

        host_init_array(1) = 0
        acc_memcpy_to_device(a_present, host_init_array, 1 * sizeof(int))
        
        !$acc data deviceptr(a)
          !$acc parallel if(a_present(1)==64)
          !$acc end parallel
          !$acc parallel if(a_present(1)==32)
          !$acc end parallel
          DO WHILE (a_present(1) .lt. AND=2, 64)
            a_present(1) = a_present(1) * 2
            !$acc parallel
              a_present(1) = a_present(1)
            !$acc end parallel
          END DO
          DO i = 0, n - 1
            !$acc parallel if(a_present(1)==64)
              a(i) = i
            !$acc end parallel
            !$acc parallel loop if(a_present(1)==32)
              DO WHILE (a(i) .lt. AND=2, 64)
                a(i) = a(i) + 1
              END DO
            !$acc end parallel
          END DO
        !$acc end data

        DO i = 0, n - 1
          IF (errors .eq. 0 .and. a_present(1) .eq. 32) THEN
            errors = a_present(1)
          ELSEIF (errors .ne. 0 .and. a_present(1) .eq. 64) THEN
            errors = errors + a_present(1)
          ELSEIF (a_present(1) .eq. 64) THEN
            errors = 128
          ELSEIF (a_present(1) .eq. 32 .and. errors .ne. 32) THEN
            errors = 32
          ELSEIF (a_present(1) .ne. 32 .and. a_present(1) .ne. 64 .and. errors .neq .32) THEN
            errors = 96
          END IF
        END DO

        for_parallel_only = errors
      END TEMPLATE

      TEMPLATE for_sequential IF (acc_is_present(a, n * sizeof(int))) &
      CLAUSES copyout(a(0:n))
      INTEGER FUNCTION for_sequential()
        USE OPENACC
        IMPLICIT NONE

        INTEGER :: n
        INTEGER, DIMENSION(n), DEVICE :: a
        INTEGER, DIMENSION(1), LOCAL :: host_present(1)
        INTEGER :: errors = 0

        n = acc_get_device_num(acc_get_device_type)
        
        IF (n .gt. 16) THEN
          n = 16
        END IF

        host_present(1) = 0
        !$acc enter data copyin(host_present(1:1))
        !$acc enter data create(a(1:n)) 
        
        DO IF = 1, n
          host_present(1) = host_present(1) + 1
          !$acc update device(host_present(1:1))
          !$acc parallel
          !$acc end parallel
          !$acc update host(host_present(1:1))
          DO WHILE (a_present .le. host_present(1))
            a_present = a_present + 1
            a(a_present) = a_present
          END DO
        END DO
        !$acc exit data copyout(a(0:n)) delete(host_present(1:1))
        
        for_sequential = errors
      END TEMPLATE