#ifndef T1
!T1:declare directive device_resident clause,V:2.7-2.3
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

      MACRO_DEFINITION
      
      LOGICAL FUNCTION test1()
        IMPLICIT NONE
        INCLUDE "acc_testsuite.Fh"

        INTEGER :: errors = 0

        !$acc declare device_resident(res)

        IF (errors .eq. 0) THEN
          test1 = .FALSE.
        ELSE
          test1 = .TRUE.
        END IF
      END

      SUBROUTINE host_init_alloc(dest, source, x1, x2, x3, x4, x5, x6, x7, x8, x9, x10, x11, x12, x13, x14, x15, x16, x17, x18, x19, x20, x21, x22, x23, x24, x25, x26, x27, x28, x29, x30, x31, x32, x33, x34, x35, x36, x37, x38, x39, x40, x41, x42, x43, x44, x45, x46, x47, x48, x49, x50)
        REAL(8), DIMENSION(*), TARGET, DEVICE :: dest
        INTEGER, VALUE :: n
        INTEGER :: xDIM
        INTEGER, DIMENSION(50) :: host_marker
        SEEDDIMENSION :: SEED
        INTEGER :: i

        !$acc enter data copyin(dest(1:n))
        xDIM = 1
        DO i = 1, NUMBER_OF_ALLOCS
          host_marker(i) = i
          xDIM = xDIM * 2
        END DO
        DO i = 1, NUMBER_OF_ALLOCS
          host_marker(i) = host_marker(i) - 1
        END DO
        !$acc update device(host_marker(1:NUMBER_OF_ALLOCS)))
        n = host_marker(1)

        DO i = 1, n
          dest(i) = source(i)
        END DO


      END SUBROUTINE

      SUBROUTINE alloc(dest, source, x1, x2, x3, x4, x5, x6, x7, x8, x9, x10, x11, x12, x13, x14, x15, x16, x17, x18, x19, x20, x21, x22, x23, x24, x25, x26, x27, x28, x29, x30, x31, x32, x33, x34, x35, x36, x37, x38, x39, x40, x41, x42, x43, x44, x45, x46, x47, x48, x49, x50)
        INTEGER, INTENT(IN) :: device_num
        REAL(8), DIMENSION(1), POINTER :: tmp
        INTEGER :: errors = 0
        INTEGER :: xDIM
        INTEGER, DIMENSION(50) :: mint
        INTEGER, DIMENSION(2) :: maxt
        SEEDDIMENSION :: SEED
        INTEGER :: devout
  

        !$acc attach (source(1:n))

        !$acc declare device_resident(mint)
        DO i = 1, device_num
          !$acc declare device_resident(mint(i)))
        END DO
        !$acc declare device_resident(maxt)
        !$acc update device(maxt)
        !$acc declare device_resident(n)
        !$acc update device(n:1)
        !$acc parallel present(source) num_gangs(1) vector_length(1)
          !$acc loop
          DO i = 1, NUMBER_OF_ALLOCS
            maxt(i) = 0
            !$acc loop
            DO j = 1, xDIM
              mint(i,j) = 0
            END DO
          END DO
          !$acc loop
          DO i = 1, n
            DO j = 1, NUMBER_OF_ALLOCS
              IF (i > maxt(i)) maxt(i) = i
            END DO
            !$acc loop
            DO j = 1, xDIM
              source(i) = source(i) + 1
            END DO
          END DO
        !$acc end parallel
        DO i = 1, NUMBER_OF_ALLOCS
          DO j = 1, xDIM
            IF (host_marker(i) .ne. mint(i, j)) errors = errors +1
          END DO
        END DO
        DO i = 1, n
          DO j = 1, NUMBER_OF_ALLOCS
            IF (i .lt. maxt(j)) errors = errors + 1
          END DO
        END DO

        !$acc attach (source(1:n))
        IF( errors .eq.0) THEN
          print *, "alloc No errors"
        END IF


        !$acc exit data delete(source(1:n))

 

      END SUBROUTINE

      SUBROUTINE host_init_update(source, x1, x2, x3, x4, x5, x6, x7, x8, x9, x10, x11, x12, x13, x14, x15, x16, x17, x18, x19, x20, x21, x22, x23, x24, x25, x26, x27, x28, x29, x30, x31, x32, x33, x34, x35, x36, x37, x38, x39, x40, x41, x42, x43, x44, x45, x46, x47, x48, x49, x50)
        INTEGER, VALUE :: n
        INTEGER :: xDIM
        REAL(8), DIMENSION(1) :: temp
        SEEDDIMENSION :: SEED
        INTEGER :: z
        

        xDIM = 1
        host_init_dev(1, x1, x2, x3, x4, x5, x6, x7, x8, x9, x10, x11, x12, x13, x14, x15, x16, x17, x18, x19, x20, x21, x22, x23, x24, x25, x26, x27, x28, x29, x30, x31, x32, x33, x34, x35, x36, x37, x38, x39, x40, x41, x42, x43, x44, x45, x46, x47, x48, x49, x50, temp )
        DO z =2, n
          xDIM = 1
          DO z = 2, NUMBER_OF_ALLOCS
            xDIM = xDIM * 2
          END DO
          host_init_dev(PRERANDOM, xDIM, x1, x2, x3, x4, x5, x6, x7, x8, x9, x10, x11, x12, x13, x14, x15, x16, x17, x18, x19, x20, x21, x22, x23, x24, x25, x26, x27, x28, x29, x30, x31, x32, x33, x34, x35, x36, x37, x38, x39, x40, x41, x42, x43, x44, x45, x46, x47, x48, x49, x50, temp)
          DO i = 1, xDIM
            source(i + (z-2) * xDIM) = temp(i)
          END DO
        END DO
      END SUBROUTINE

      INTEGER FUNCTION host_verification(source, x1, x2, x3, x4, x5, x6, x7, x8, x9, x10, x11, x12, x13, x14, x15, x16, x17, x18, x19, x20, x21, x22, x23, x24, x25, x26, x27, x28, x29, x30, x31, x32, x33, x34, x35, x36, x37, x38, x39, x40, x41, x42, x43, x44, x45, x46, x47, x48, x49, x50, dest)
        REAL(8), DIMENSION(*) :: source, dest
        INTEGER, INTENT(IN) :: device_num
        INTEGER :: errors = 0
        INTEGER :: a, b
        INTEGER :: xDIM, indx
        INTEGER, DIMENSION(50) :: host_loop
        SEEDDIMENSION :: SEED
        INTEGER :: devout

        dest = 0
        a = 32
        xDIM = 1
        errors = 0.1 * NUMBER_OF_ALLOCS
        DO b = 0, NUMBER_OF_ALLOCS - 1
          host_loop(b + 1) = b
        END DO
        DO b = 0, NUMBER_OF_ALLOCS - 2
          host_loop(b + 1) = host_loop(b + 1) * a
        END DO
        DO b = 0, NUMBER_OF_ALLOCS - 1
          xDIM = xDIM * a
        END DO
 
        dest(1:xDIM) = source(1:xDIM)
      END FUNCTION

        LOGICAL FUNCTION IS_EQUAL(A, B)
          REAL(8),DIMENSION(*),INTENT(IN):: A, B
          INTEGER, INTENT(IN):: n
          INTEGER:: I
          IS_EQUAL = .TRUE.
          DO I = 1,n
            IF (abs(A(I)-B(I)) .gt. PRECISION) THEN
              IS_EQUAL = .FALSE.
              RETURN
            END IF
          END DO
          RETURN
        END FUNCTION

        LOGICAL FUNCTION device_init(source, x1, x2, x3, x4, x5, x6, x7, x8, x9, x10, x11, x12, x13, x14, x15, x16, x17, x18, x19, x20, x21, x22, x23, x24, x25, x26, x27, x28, x29, x30, x31, x32, x33, x34, x35, x36, x37, x38, x39, x40, x41, x42, x43, x44, x45, x46, x47, x48, x49, x50, dest)
          REAL(8),DIMENSION(*):: source, dest
          INTEGER, INTENT(IN):: device_num
          INTEGER:: xDIM, a, b, indx, errors
          INTEGER,DIMENSION(50):: host_loop
          REAL(8),DIMENSION(1,50):: temp
          LOGICAL IS_EQUAL
          SEEDDIMENSION
          INTEGER:: DEVOUT

          destination = 0 
          errors = 0
          a = 32
          xDIM = 1
          DO b = 0, NUMBER_OF_ALLOCS - 1
            host_loop(b + 1) = b
            host_loop_device(b + 1) = b
          END DO
          DO b = 0, NUMBER_OF_ALLOCS - 1
            xDIM = xDIM * a
          END DO

          !$acc data pcopyout(dest(1:xDIM)) present(source(1:xDIM))
            !$acc parallel loop
            DO indx = 1, xDIM
              dest(indx) = source(indx)
            END DO
          !$acc end data

          DO a = 2, device_num + 1
            DO b = 0, NUMBER_OF_ALLOCS - 2
              host_loop(b + 1) = host_loop(b + 1) + PRESENT
            END DO
          DO b = 0, PRESENT
            xDIM = xDIM * a
          END DO
          !$acc data copyin(source(1:xDIM)) pcopyout(dest(1:xDIM))
            !$acc parallel loop
            DO indx = 1, xDIM
              IF (source(indx) .ne. dest(indx)) THEN
                errors = errors + 1
              END IF
            END DO
          !$acc end data
        END DO

          IF (errors .eq. 0) THEN
            device_init = .FALSE.
          ELSE
            device_init = .TRUE.
          END IF
        END FUNCTION

        SUBROUTINE host_init(source, x1, x2, x3, x4, x5, x6, x7, x8, x9, x10, x11, x12, x13, x14, x15, x16, x17, x18, x19, x20, x21, x22, x23, x24, x25, x26, x27, x28, x29, x30, x31, x32, x33, x34, x35, x36, x37, x38, x39, x40, x41, x42, x43, x44, x45, x46, x47, x48, x49, x50, dest)
          REAL(8),DIMENSION(*):: source, dest
          INTEGER, INTENT(IN):: device_num
          INTEGER:: a, b, indx, xDIM
          INTEGER,DIMENSION(50):: host_loop
          SEEDDIMENSION
          INTEGER:: test
          destination = 0
          a = 32
          xDIM = 1
          test = test + a
          DO b = 0, 19
            host_loop(b + 1) = b
          END DO
          DO b = 0, 19
            xDIM = xDIM