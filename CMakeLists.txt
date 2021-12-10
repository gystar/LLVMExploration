cmake_minimum_required(VERSION 3.10) 

# set the project name 
project(testpass) 

# add the executable 
file(GLOB_RECURSE CFG_SRC_CPPS cfg/*.cpp)
add_executable(cfgbuilder main.cpp ${CFG_SRC_CPPS})

# llvm surport
set(LLVM_DIR "/opt/llvm-10/lib/cmake/llvm")
find_package(LLVM CONFIG REQUIRED)
include_directories("." ${LLVM_INCLUDE_DIRS})
add_definitions(${LLVM_DEFINITIONS_LIST})
llvm_map_components_to_libnames(llvm_libs support core irreader passes)

#llvm编译时的使用使用的是-fno-rtti，此工程也应该使用相同的flag，否则会出现"undefined reference to `typeinfo "错误
set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -fno-rtti")
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -fno-rtti")

target_link_libraries (cfgbuilder ${llvm_libs})

# target:make run
add_custom_target(run
    COMMAND cfgbuilder
    DEPENDS cfgbuilder
    WORKING_DIRECTORY ${CMAKE_PROJECT_DIR}
)


