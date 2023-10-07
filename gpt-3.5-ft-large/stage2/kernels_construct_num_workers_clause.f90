#ifndef T1
!T1:kernels construct num_workers clause,V:2.7-2.3
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

      FUNCTION getNumWorkers ( istream, size )
        INTEGER, INTENT(IN) :: istream(size)
        INTEGER, INTENT(IN) :: size
        INTEGER :: ifile
        INTEGER :: fileSize
        INTEGER :: ctr
        INTEGER :: current, past1, past2
        INTEGER :: total = 0

        ifile = 1
        OPEN(10, FILE = "kernels_num_workers.3.data.txt", STATUS = "UNKNOWN")
        DO WHILE (ifile .gt. -1)
          READ(10, *, IOSTAT = ifile) fileSize
          IF (ifile .gt. -1) THEN
            ctr = ctr + 1
            istream(ctr) = fileSize
          END IF
        END DO
        CLOSE(10)

        DO ctr = 1, size
          CALL acc_attach(ADDRESS(istream(ctr)), SIZEOF(fileSize))
        END DO

        current = 0
        past1 = 0
        past2 = 0
        ctr = 0
        DO
          past2 = past1
          past1 = current
          CALL rand_num(current)
          current = (current * 10) + 1
          IF (past1 .eq. 1 .AND. past2 .eq. 0) THEN
            EXIT DO
          END IF
          ctr = ctr + 1
        END DO
        total = istream(ctr + 1)

        getNumWorkers = total
      END FUNCTION

#ifndef T1
!T1:kernels construct num_workers clause,V:2.7-2.3
      LOGICAL FUNCTION test1()
        USE OPENACC
        IMPLICIT NONE
        INCLUDE "acc_testsuite.Fh"

        INTEGER :: errors = 0

        INTEGER :: independent_loop
        INTEGER :: num_workers_clause
        INTEGER, DIMENSION(1) :: num_iterations = (/10000/)
        INTEGER, DIMENSION(1) :: iterations_device
        INTEGER :: multiplier
        REAL(8), DIMENSION(1) :: a
        REAL(8), DIMENSION(1) :: b
        REAL(8) :: deviation = 0

        iterations_device(1) = getNumWorkers(num_iterations, 1)

        IF (iterations_device(1) EQU 0) THEN
          iterations_device(1) = 1
        END IF

        SEEDDEV(SEED)

        !$acc data copyout(a(1:iterations_host(1)))
          !$acc kernels
            !$acc loop num_workers(multiplier)
            DO independent_loop = 1, iterations_device(1)
              IF (iterations_device(1) .MOD. independent_loop .eq. 0) THEN
                !$acc loop independent
                DO multiplier = 1, iterations_host(1)
                  a(multiplier) = a(multiplier) + b(multiplier)
                END DO
              END IF
            END DO
          !$acc end kernels
        !$acc end data

        DO independent_loop = 1, iterations_device(1)
          IF (iterations_device(1) .MOD. independent_loop .eq. 0) THEN
            DO multiplier = 1, iterations_host(1)
              deviation = max(deviation, (a(multiplier) - (independent_loop + 1)) * (a(multiplier) - (independent_loop + 1))))
            END DO
          END IF
        END DO


        IF (deviation .gt. ((2 + iterations_device(1)) * (2 + iterations_device(1)) * .5)) THEN
           has passed. num_workers on device appears to function properly.
        END IF


        IF (errors .eq. 0) THEN
          test1 = .FALSE.
        ELSE
          test1 = .TRUE.
        END IF
      END
#endif