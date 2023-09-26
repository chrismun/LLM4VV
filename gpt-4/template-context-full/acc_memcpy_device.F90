#ifndef T1
!T1:acc memcpy device,V:2.7-2.3
  LOGICAL FUNCTION test1()
    USE OPENACC
    USE, INTRINSIC :: ISO_C_BINDING
    IMPLICIT NONE
    INCLUDE "acc_testsuite.Fh"
    
    INTEGER :: errors=0
    INTEGER(C_SIZE_T) :: bytes=100
    TYPE(C_PTR) :: data_dev_dest, data_dev_src
    REAL, DIMENSION(:), ALLOCATABLE :: src, dest
    INTEGER :: i

    ALLOCATE(src(bytes))
    ALLOCATE(dest(bytes))
    
    FORALL(i = 1:bytes) src(i) = i*1.0
    dest = 0.0

    data_dev_src = acc_malloc(bytes*C_SIZEOF(REAL))
    data_dev_dest = acc_malloc(bytes*C_SIZEOF(REAL))

    CALL acc_memcpy_to_device(data_dev_src,C_LOC(src(1)),bytes*C_SIZEOF(REAL))
    CALL acc_memcpy_device(data_dev_dest,data_dev_src,bytes*C_SIZEOF(REAL))
    CALL acc_memcpy_from_device(C_LOC(dest(1)),data_dev_dest,bytes*C_SIZEOF(REAL))

    FORALL(i = 1:bytes) errors = errors + (dest(i) .NE. src(i)) 

    CALL acc_free(data_dev_src)
    CALL acc_free(data_dev_dest)

    DEALLOCATE(src)
    DEALLOCATE(dest)

    IF (errors .eq. 0) THEN
      test1 = .FALSE.
    ELSE
      test1 = .TRUE.
    END IF
  END FUNCTION test1
#endif