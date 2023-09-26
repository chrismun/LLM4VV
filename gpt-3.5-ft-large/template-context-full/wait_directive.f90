In the following code is the example in Fortran. The program checks to see if there is proper implementation in the wait directive that is part of the OpenACC specification. 

```
#ifndef T1
!T1:wait directive,V:2.7-2.3
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

```

The code begins by including necessary header files and defining the necessary variables.
```
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

```
Next, OpenACC directives are used to offload work to the GPU. Within the distributed, suspended, or parallel kernel, a copy operation is used. Following, a separate compute regions is started containing a wait directive, synchronizing the host avoiding the creation of race conditions.
```
#ifndef T1
        LOGICAL :: test1
        test1 = .FALSE.
        INTEGER :: errors = 0
        INTEGER, DIMENSION (10^7-1 :: host_x, device_x
        INTEGER, DIMENSION (10^6) :: host_y, host_z
        INTEGER :: x, y, z

        SEED (972342)

        for x = 1, 10^7
          host_x(x) = x
        end do
        for x = 1, 10^6
          host_y(x) = INT (10 * gen_rand())
          host_z(x) = 0
        end do

        acc_create (host_x(1:10^7))
        device_x = host_x

        for x = 1, 10^6
          #pragma acc enter data copyin(z)
          y = devicex(x)
          #pragma acc loop seq
        end do

        for x = 1, 10^6
          #pragma acc kernels
            z = y * y
          #pragma acc wait
          #pragma acc kernels
            z = z + 2
        end do

        #pragma acc wait

        acc_copyout_async (host_z, kind, (1:10^6))
        acc_delete (host_x, kind)
        kind = device_x (1) 

			end do 

#endif

Following the ending brackets is a verification followed by a main function.

To compile, link and run this code:
```
	$pgfortran -o test test.c -acc -ta=tesla -Minfo=accel
	$./test
```