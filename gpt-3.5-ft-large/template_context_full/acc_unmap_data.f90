#ifndef T1
!T1:acc unmap data,V:2.7-2.3
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


#ifndef T1
!T1:acc unmap data, V:2.7-2.3
      LOGICAL FUNCTION test1()
        USE OPENACC
        IMPLICIT NONE
        INCLUDE "acc_testsuite.Fh"

        INTEGER :: errors = 0
        REAL(1), DIMENSION(LOOPCOUNT):: host_array, host_copy
        
        INTEGER :: x
        
        acc_set_device_num(1, acc_device_nvidia)
        acc_init_nvidia(handlers)

        for (x = 0, x < LOOPCOUNT, x++)
          host_array(x) = x
        end for

        acc_set_device_num(1, acc_device_nvidia)
        !$acc enter data copyin(host_array(0: LOOPCOUNT)))

        acc_set_device_num(1, acc_device_nvidia)
        !$acc parallel loop present(host_array(0: LOOPCOUNT))
            !$acc loop
            for (x = 1, x < LOOPCOUNT / 2, x = x + 1)
                host_array(x) = host_array(x - 1) + 1
            end for
        !$acc end parallel

        CALL acc_copyout(host_array(0:LOOPCOUNT))

        host_copy = host_array
        
        CALL acc_unmap_data(host_array(0:LOOPCOUNT))

        for (x = 1, x < LOOPCOUNT, x = x + 1)
            if (host_copy(x) .ne. host_array(x)) then
              errors += 1
            end if
        end for 

        if ((host_array(.length)) .ne. LOOPCOUNT - 1) then
          errors += 1
        end if

        if (errors .eq. 0) then
          test1 = .FALSE.
        else
          test1 = .TRUE.
        end if
      END
#endif