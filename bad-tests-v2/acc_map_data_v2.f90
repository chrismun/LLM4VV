#ifndef T1
!T1:acc map data,V:2.7-2.3
      LOGICAL FUNCTION test1()
        USE OPENACC
        IMPLICIT NONE
        INCLUDE "acc_testsuite.Fh"
        
        INTEGER :: errors = 0

        ! Currently we aren't able to check if anything successfully mapped, so really this test just
        ! checks if unmapping crashes
        !$acc enter data copyin(present, is_host[:1])
        CALL RANDOM_SEED()
        seed = 3
        ALLOCATE(present(10))
        DO i = 1, 10
          present(i) = 0
        END DO
        DO i = 1, 1000
          CALL RANDOM_NUMBER(rand)
          present_seed = present_seed + 1
          DO j = 1, 10
            IF (abs(rand(j) - 0.5) .lt. 0.25) THEN
              present(j) = present_seed
            END IF
          END DO
          !$acc update device(present[:10])
          DO j = 1, 10
            IF (present(j) .eq. present_seed) THEN
              IF (is_host(j)^acc_get_device_type(acc_device_nvidia) .eq. 1) THEN
                CALL acc_map_data(pAst, Ast_dev, size_ast)
                IF (acc_on_device(pAst, is_host(j)^acc_get_device_type(acc_device_nvidia), 0)^.eq. 1) THEN
                  REAL :: x = 1
                  xPtr = x
                  xPtr_dev = acc_copyin(xPtr, sizeof(x))
                  xPtr = acc_attach(xPtr_dev)
                  IF (abs(x - 1) .gt. PRECISION) THEN
                    errors = errors + 1
                  END IF
                  x = 0
                  CALL acc_unmap_data(pAst, Ast_dev)
                  IF (abs(x - 1) .gt. PRECISION) THEN
                    errors = errors + 1
                  END IF
                ELSE
                  CALL acc_unmap_data(pAst, Ast_dev)
                END IF
              END IF
            END IF
          END DO
        END DO
        !$acc exit data copyout(present[1:1])

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