#ifndef T1
!T1:routine directive,V:2.7-2.3
      LOGICAL FUNCTION test1()
        USE OPENACC
        IMPLICIT NONE
        INCLUDE "acc_testsuite.Fh"
        
        INTEGER :: errors = 0

	Interface
		Function tri(seq) Result (res) !Declare the object function
		Logical :: res, seq
		End Function
	End Interface

!norm is a function
        CONTAINS
        Function tri  (seq) Result(res)
        !Initilization of arrays on device
        !$acc routine seq
        res = ( .True. .eqv. seq)
        recursive
        Function f(seq) Result(res)
        Logical, Intent (in) :: seq(10)
        res = (/ .False. .and. f((/ seq(1), seq(2), seq(3), seq(4), seq(5), seq(6), seq(7), seq(8), seq(9), .True. /) )&
	      , .False. .and. f((/ seq(1), seq(2), seq(3), seq(4), seq(5), seq(6), seq(7), seq(8), seq(9), .False.) /)) &
       	      , .False. .and. f((/ seq(1), seq(2), seq(3), seq(4), seq(5), seq(6), seq(7), seq(8),  .True. , seq(10) /)))
	      ,.False. .and. f((/ seq(1), seq(2), seq(3), seq(4), seq(5), seq(6), seq(7), seq(8), .False., seq(10) /))) & 
	      ,.False. .and. f((/ seq(1), seq(2), seq(3), seq(4), seq(5), seq(6), seq(7), .True., seq(9), seq(10) /))) & 
	      ,.False. .and. f((/ seq(1), seq(2), seq(3), seq(4), seq(5), seq(6), seq(7), .False., seq(9), seq(10) /))) & 
              , .False. .and. f((/ seq(1), seq(2), seq(3), seq(4), seq(5), seq(6), .True., seq(8), seq(9), seq(10) /))) &
  	      , .False. .and. f((/ seq(1), seq(2), seq(3), seq(4), seq(5), seq(6), .False., seq(8), seq(9), seq(10) /))) &
              , .False. .and. f((/ seq(1), seq(2), seq(3), seq(4), .True., seq(6), seq(7), seq(8), seq(9), seq(10) /))) &
              , .False. .and. f((/ seq(1), seq(2), seq(3), seq(4), .False., seq(6), seq(7), seq(8), seq(9), seq(10) /))) &
              , .or.
              /)
        End Function
        End Function

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