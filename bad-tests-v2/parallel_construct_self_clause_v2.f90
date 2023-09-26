#ifndef T1
!T1:parallel construct self clause,V:2.7-2.3
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

c const unsigned int threshold = 16*1024*1024;
c unsigned int received_data[threshold];
      template<int arg>
      void host_manipulation_function(int length, unsigned int * a){
        for (int x = 0; x < length; ++x){
          a[x] = a[x] + 1;
        }
      }

      inline unsigned int initialize(unsigned int * a, int length){
        for (int x = 0; x < length; ++x){
          a[x] = x;
        }
        return a[length-1];
      }


#ifndef T1
      LOGICAL FUNCTION test1()
        IMPLICIT NONE
        INCLUDE "acc_testsuite.Fh"
        INTEGER :: errors = 0
        INTEGER :: length = 1000
        INTEGER :: initialization_host = 0
        INTEGER :: initialization_device = 0
        INTEGER :: reduction_host = 0
        INTEGER :: reduction_device = 0
        INTEGER :: temp
        INTEGER :: x
        INTEGER, DIMENSION(1, length - 1) :: a
        INTEGER :: devdata

        !Initialization
        DO x = 1, length
          initialization_host = initialization_host + x
        END DO

        !$acc data copy(initialization_device:initialization_device)
          !$acc parallel loop reduction(+:initialization_device)
          DO x = 0, length - 1
            initialization_device = initialization_device + x
          END DO
        !$acc end data

        IF (initialization_host .ne. initialization_device) THEN
          errors = errors + 1
        END IF

        devdata = initialize(length - 1, a(1, :))

        !$acc data copyin(a(1:length - 1, 1)) copyout(received_data(0:length - 1))
          !$acc parallel loop device_type(host) gang vector private(reduction_host, temp)
          DO x = 0, devdata
            reduction_host = 0;
            temp = 0;
            DO reduction(reduction_host:temp)
              IF (received_data(temp) == initialization_device + temp) THEN
                IF (temp .ne. reduction_host) THEN
                  reduction_host = temp;
                END IF
              END IF
            END DO
            DO temp = 0, reduction_host
              received_data(temp) = a(temp * a)
            END DO
          END DO
          !$acc parallel loop device_type(host) gang vector private(temp)
          DO x = 0, devdata
            host_manipulation_function(a(0), temp)
            a(temp) = temp
          END DO
        !$acc end data
        DO x = 0, devdata
          reduction_device = reduction_device + x
        END DO
        !$acc exit data copyout(received_data(0:devdata))
        IF (reduction_host .ne. reduction_device) THEN
          errors = errors + 1
        END IF

        DO x = 0, devdata
          IF (abs(initialization_device + x - received_data(x)) .gt. PRECISION) THEN
            errors = errors + 4
          END IF
        END DO

        test1 = errors
      END FUNCTION
#endif