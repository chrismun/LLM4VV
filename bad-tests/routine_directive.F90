!T1:routine directive,V:2.7-2.3
MODULE OPENACC_ROUTINE_TEST
  USE OPENACC
  IMPLICIT NONE
  
  REAL, DIMENSION(:), ALLOCATABLE :: a

  !$acc routine seq
  PURE FUNCTION area_triangle(base, height)
    REAL, INTENT(IN) :: base, height
    REAL :: area_triangle
    
    area_triangle = 0.5 * base * height
  END FUNCTION area_triangle
END MODULE OPENACC_ROUTINE_TEST

PROGRAM TEST_ROUTINE
  USE OPENACC_ROUTINE_TEST
  IMPLICIT NONE
  
  INTEGER :: n, i, errors
  REAL :: base, height, area
  INTEGER, PARAMETER :: npts = 10000
  REAL, DIMENSION(npts) :: bases, heights, areas
  
  base = 5.0
  height = 12.0
  errors = 0

  DO i = 1, npts
    bases(i) = base
    heights(i) = height
  END DO

  !$acc data copyin(bases(1:npts), heights(1:npts)), copyout(areas(1:npts))
     !$acc kernels
       DO i = 1, npts
         areas(i) = area_triangle(bases(i), heights(i))
       END DO
     !$acc end kernels
  !$acc end data

  DO i = 1, npts
    IF (ABS(areas(i) - 0.5 * bases(i) * heights(i)) > 1e-6) THEN
      errors = errors + 1
    END IF
  END DO

  IF (errors == 0) THEN
    PRINT *, "OpenACC routine directive test passed."
  ELSE
    PRINT *, "OpenACC routine directive test failed!"
    PRINT *, "Found", errors, "errors."
  END IF
END PROGRAM TEST_ROUTINE