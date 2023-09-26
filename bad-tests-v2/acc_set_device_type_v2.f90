#ifndef T1
!T1:acc set device type,V:2.7-2.3
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
      CONTAINS
	COMPUTE_TEST:SUBROUTINE compute_test()
	  IMPLICIT NONE
	  REAL(8),DIMENSION(10, 10) :: a, b, c
	  INTEGER :: errors = 0

	  CALL RANDOM_NUMBER(a)
	  CALL RANDOM_NUMBER(b)
	  c = 0

	  !$acc data copyin(a(1:10, 1:10), b(1:10, 1:10)) copy(c(1:10, 1:10))
    	  !$acc parallel
	  !$acc loop
	  DO i = 1, 10
	    !$acc loop
	    DO j = 1, 10
	      c(i, j) = a(i, j) + b(i, j)
	    END DO
	  END DO
	  !$acc end parallel
	  !$acc end data

	  DO i = 1, 10
	    DO j = 1, 10
	      IF (abs(c(i, j) - (a(i, j) + b(i, j))) .gt. PRECISION) THEN
		error = error + 1
	      END IF
	    END DO
	  END DO
	 END

#ifndef HOST_DATA_OPENMP
        COMPILE_OPENMP_HOST_DATA:SUBROUTINE compile_openmp_host_data()
	  INTEGER :: errors = 0
	  USE LIBOMP
        END SUBROUTINE
       
#ifndef HOST_DATA_MIC_OPENMP
	 COMPILE_MIC_OPENMP_HOST_DATA:SUBROUTINE compile_mic_openmp_host_data()
	  INTEGER :: errors = 0
          USE LIBMIC
	 END SUBROUTINE
#endif
#endif
      END SUBROUTINE
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