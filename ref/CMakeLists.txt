cmake_minimum_required(VERSION 3.10)
project(miniAMR DESCRIPTION "Adaptive Mesh Refinement Mini-App")
find_package(MPI REQUIRED)
message(STATUS "Run: ${MPIEXEC} ${MPIEXEC_NUMPROC_FLAG} ${MPIEXEC_MAX_NUMPROCS} ${MPI_C_COMPILER_INCLUDE_DIRS}")

add_executable(miniAMR.out block.c check_sum.c comm_block.c comm.c comm_parent.c comm_refine.c comm_util.c driver.c init.c main.c move.c pack.c plot.c profile.c rcb.c refine.c sfc.c stencil.c util.c monitor.c
)
set(CMAKE_C_FLAGS_RELEASE "-O3 -Wall")
set(CMAKE_C_FLAGS_DEBUG "-g -DDEBUG -O3 -Wall")
target_include_directories(miniAMR.out PRIVATE ${MPI_C_INCLUDE_PATH})
target_compile_options(miniAMR.out PRIVATE ${MPI_C_COMPILE_FLAGS} ${MY_COMPILE_FLAGS})
target_link_libraries(miniAMR.out PRIVATE ${MPI_C_LIBRARIES} ${MPI_CXX_LINK_FLAGS})
target_link_libraries(miniAMR.out PRIVATE m)
