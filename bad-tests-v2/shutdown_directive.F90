module test_openacc_shutdown
    use openacc
    implicit none
    real, dimension(100) :: vec1, vec2, vec_res
    end module test_openacc_shutdown

    program check_compiler
    use test_openacc_shutdown

    integer :: device_type
    logical :: condition

    vec1 = 19.0
    vec2 = 23.0
    device_type = 1  ! considering 1 as the device type for GPU
    condition = .true.

    !$acc init device_type(device_type)
    !$acc enter data copyin(vec1, vec2) create(vec_res)

    !$acc parallel loop copy(vec1, vec2) create(vec_res)
    do i=1, 100
      vec_res(i) = vec1(i) + vec2(i)
    end do

    !$acc update host(vec_res)
    !$acc exit data delete(vec1, vec2) copyout(vec_res)

    print *, "Result vector: ", vec_res

    !$acc shutdown device_type(device_type) if(condition)

    end program check_compiler