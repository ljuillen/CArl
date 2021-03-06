project( Ext_Solver_CArl )

# --- Check the CMake version
cmake_minimum_required(VERSION 2.8.8)
if("${CMAKE_MAJOR_VERSION}.${CMAKE_MINOR_VERSION}" VERSION_GREATER 2.8)
  if("${CMAKE_MAJOR_VERSION}.${CMAKE_MINOR_VERSION}.${CMAKE_PATCH_VERSION}" VERSION_GREATER 2.8.8)
    cmake_policy(VERSION 2.8.8)
  endif()
endif()

set( CMAKE_ALLOW_LOOSE_LOOP_CONSTRUCTS true )

if ( COMMAND cmake_policy )
   cmake_policy( SET CMP0003 NEW )
endif()

# --- CGAL
# CGAL uses CMake -> find it!
find_package( CGAL COMPONENTS Core )

if ( NOT CGAL_FOUND )
   message(STATUS "This project requires the CGAL library, and will not be compiled.")
   return()
endif()

include( ${CGAL_USE_FILE} )
message(STATUS "CGAL version    : ${CGAL_VERSION}")
message(STATUS "CGAL dir        : ${CGAL_DIR}")

# --- Boost
# Boost uses CMake -> find it!
find_package( Boost REQUIRED )

if ( NOT Boost_FOUND )
   message(STATUS "This project requires the Boost library, and will not be compiled.")
   return()
endif()

# --- libMesh commands
# Have to do the search by hand ...
# Check if there is a env. variable for the libMesh
set(LIBMESH_DIR $ENV{LIBMESH_DIR})

# If not, use the default path
if ( "${LIBMESH_DIR}" STREQUAL "" )
   set (LIBMESH_DIR "/usr/local" )
endif()

# Set the path to the libmesh-config binary
set(LIBMESH_CONFIG "${LIBMESH_DIR}/bin/libmesh-config")

# Get the libMesh's flags, includes, libs ...
execute_process(COMMAND ${LIBMESH_CONFIG} --cppflags OUTPUT_VARIABLE LIBMESH_CPPFLAGS OUTPUT_STRIP_TRAILING_WHITESPACE)
execute_process(COMMAND ${LIBMESH_CONFIG} --cxxflags OUTPUT_VARIABLE LIBMESH_CXXFLAGS OUTPUT_STRIP_TRAILING_WHITESPACE)
execute_process(COMMAND ${LIBMESH_CONFIG} --include OUTPUT_VARIABLE LIBMESH_INCLUDE OUTPUT_STRIP_TRAILING_WHITESPACE)
execute_process(COMMAND ${LIBMESH_CONFIG} --libs OUTPUT_VARIABLE LIBMESH_LIBS OUTPUT_STRIP_TRAILING_WHITESPACE)

execute_process(COMMAND ${LIBMESH_CONFIG} --version OUTPUT_VARIABLE LIBMESH_VERSION OUTPUT_STRIP_TRAILING_WHITESPACE)

# Append them to the CMake flags and linkers
set( CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} ${LIBMESH_CPPFLAGS} ${LIBMESH_CXXFLAGS} ${LIBMESH_INCLUDE}" )
set( CMAKE_EXE_LINKER_FLAGS "${CMAKE_EXE_LINKER_FLAGS} ${LIBMESH_LIBS}" ) 

message(STATUS "libMesh version : ${LIBMESH_VERSION}")
message(STATUS "libMesh dir     : ${LIBMESH_DIR}")

# --- Set CArl directories and files

# Directories
set ( SOURCE_DIR src )

set ( EXEC_SRC_DIR                      ${SOURCE_DIR}/execs )
set ( COMMON_SRC_DIR                    ${SOURCE_DIR}/common )
set ( INCLUDE_SRC_DIR                   ${SOURCE_DIR}/include )

set ( INTERSECTION_PARALLEL_DIR         ${COMMON_SRC_DIR}/intersections_parallel )
set ( FETI_DIR                          ${COMMON_SRC_DIR}/FETI )
set ( CARL_PARSERS_DIR                  ${COMMON_SRC_DIR}/parsers )
set ( COUPLING_MATRIX_DIR               ${COMMON_SRC_DIR}/coupling_matrix )
set ( PETSC_MATRIX_OPERATIONS_DIR       ${COMMON_SRC_DIR}/PETSC_matrix_operations )
set ( MISC_DIR                          ${COMMON_SRC_DIR}/misc )

set ( EXT_LIBMESH_SOLVER_DIR            ${EXEC_SRC_DIR}/ext_solver_libmesh )
set ( COMMON_EXT_LIBMESH_SOLVER_DIR     ${EXT_LIBMESH_SOLVER_DIR}/ext_solver_libmesh_common )
set ( EXT_LIBMESH_SOLVER_INCLUDE_DIR    ${COMMON_EXT_LIBMESH_SOLVER_DIR}/include )

# Source files - CArl libs
file ( GLOB COMMON_SOURCES                  "${COMMON_SRC_DIR}/common*.cpp" )
file ( GLOB FETI_SOURCES                    "${FETI_DIR}/*.cpp" )
file ( GLOB CARL_PARSERS_SOURCES            "${CARL_PARSERS_DIR}/*.cpp" )
file ( GLOB INCLUDE_SOURCES                 "${INCLUDE_SRC_DIR}/*.h" )
file ( GLOB INTERSECTION_PARALLEL_SOURCES   "${INTERSECTION_PARALLEL_DIR}/*.cpp" )
file ( GLOB COUPLING_MATRIX_SOURCES         "${COUPLING_MATRIX_DIR}/*.cpp" )
file ( GLOB PETSC_MATRIX_OPERATIONS_SOURCES "${PETSC_MATRIX_OPERATIONS_DIR}/*.cpp" )
file ( GLOB MISC_SOURCES                    "${MISC_DIR}/*.cpp" )

# Source files - CArl execs.
set  ( CARL_INTER_EXEC        ${EXEC_SRC_DIR}/CArl_build_intersections/CArl_build_intersections.cpp )
file ( GLOB CARL_TOOLS_EXECS  "${EXEC_SRC_DIR}/CArl_tools/*.cpp" )
file ( GLOB CARL_FETI_EXECS   "${EXEC_SRC_DIR}/CArl_FETI/*.cpp" )

# Source files - external solvers (libMesh)
file ( GLOB LIBMESH_EXT_EXECS "${EXT_LIBMESH_SOLVER_DIR}/*.cpp" )
file ( GLOB LIBMESH_EXT_COMMON "${COMMON_EXT_LIBMESH_SOLVER_DIR}/*.cpp" )

include_directories( ${INCLUDE_SRC_DIR} ${INCLUDE_SRC_DIR}/parsers ${EXT_LIBMESH_SOLVER_INCLUDE_DIR} )

# --- Set CArl libraries
add_library( MISC_OBJS OBJECT                           ${MISC_SOURCES} )
add_library( COMMON_OBJS OBJECT                         ${COMMON_SOURCES} )
add_library( FETI_OBJS OBJECT                           ${FETI_SOURCES} )
add_library( CARL_PARSERS_OBJS OBJECT                   ${CARL_PARSERS_SOURCES} )
add_library( INTERSECTION_PARALLEL_OBJS OBJECT          ${INTERSECTION_PARALLEL_SOURCES} )
add_library( COUPLING_MATRIX_OBJS OBJECT                ${COUPLING_MATRIX_SOURCES} )
add_library( PETSC_MATRIX_OPERATIONS_OBJS OBJECT        ${PETSC_MATRIX_OPERATIONS_SOURCES} )
add_library( COMMON_EXT_LIBMESH_SOLVER_OBJS OBJECT      ${LIBMESH_EXT_COMMON})

# --- Set CArl executables
add_executable( CArl_build_intersections  ${CARL_INTER_EXEC}
                $<TARGET_OBJECTS:CARL_PARSERS_OBJS> $<TARGET_OBJECTS:COMMON_OBJS>
                $<TARGET_OBJECTS:INTERSECTION_PARALLEL_OBJS>)

add_to_cached_list( CGAL_EXECUTABLE_TARGETS CArl_build_intersections )
target_link_libraries(CArl_build_intersections ${CGAL_LIBRARIES} ${BOOST_LIBRARIES} ${CGAL_3RD_PARTY_LIBRARIES} )

foreach( CArl_FETI_source_file ${CARL_FETI_EXECS} )
    string ( REPLACE ".cpp" "" full_CArl_FETI_exec_name ${CArl_FETI_source_file} )
    string ( REPLACE "${CMAKE_CURRENT_LIST_DIR}/${EXEC_SRC_DIR}/CArl_FETI/" "" CArl_FETI_exec_name ${full_CArl_FETI_exec_name} )
    add_executable (    ${CArl_FETI_exec_name} ${CArl_FETI_source_file} 
                        $<TARGET_OBJECTS:CARL_PARSERS_OBJS> $<TARGET_OBJECTS:COMMON_OBJS>
                        $<TARGET_OBJECTS:FETI_OBJS> $<TARGET_OBJECTS:MISC_OBJS> 
                        $<TARGET_OBJECTS:COUPLING_MATRIX_OBJS> $<TARGET_OBJECTS:PETSC_MATRIX_OPERATIONS_OBJS> )
    add_to_cached_list( CGAL_EXECUTABLE_TARGETS ${CArl_FETI_exec_name} )
    target_link_libraries( ${CArl_FETI_exec_name} ${CGAL_LIBRARIES} ${BOOST_LIBRARIES} ${CGAL_3RD_PARTY_LIBRARIES} )
endforeach( CArl_FETI_source_file ${CARL_FETI_EXECS} )

foreach( CArl_tools_source_file ${CARL_TOOLS_EXECS} )
    string ( REPLACE ".cpp" "" full_CArl_tools_exec_name ${CArl_tools_source_file} )
    string ( REPLACE "${CMAKE_CURRENT_LIST_DIR}/${EXEC_SRC_DIR}/CArl_tools/" "" CArl_tools_exec_name ${full_CArl_tools_exec_name} )
    add_executable ( ${CArl_tools_exec_name} ${CArl_tools_source_file} 
                     $<TARGET_OBJECTS:CARL_PARSERS_OBJS> $<TARGET_OBJECTS:COMMON_OBJS> 
                     $<TARGET_OBJECTS:MISC_OBJS> $<TARGET_OBJECTS:COUPLING_MATRIX_OBJS>
                     $<TARGET_OBJECTS:PETSC_MATRIX_OPERATIONS_OBJS>)
    add_to_cached_list( CGAL_EXECUTABLE_TARGETS ${CArl_tools_exec_name} )
    target_link_libraries( ${CArl_tools_exec_name} ${CGAL_LIBRARIES} ${BOOST_LIBRARIES} ${CGAL_3RD_PARTY_LIBRARIES} )
endforeach( CArl_tools_source_file ${CARL_TOOLS_EXECS} )

foreach( libmesh_ext_source_file ${LIBMESH_EXT_EXECS} )
    string ( REPLACE ".cpp" "" full_libmesh_ext_exec_name ${libmesh_ext_source_file} )
    string ( REPLACE "${CMAKE_CURRENT_LIST_DIR}/${EXEC_SRC_DIR}/ext_solver_libmesh/" "" libmesh_ext_exec_name ${full_libmesh_ext_exec_name} )
    add_executable ( ${libmesh_ext_exec_name} ${libmesh_ext_source_file}
                     $<TARGET_OBJECTS:MISC_OBJS> $<TARGET_OBJECTS:COMMON_EXT_LIBMESH_SOLVER_OBJS>
                     $<TARGET_OBJECTS:PETSC_MATRIX_OPERATIONS_OBJS> $<TARGET_OBJECTS:COMMON_OBJS> $<TARGET_OBJECTS:CARL_PARSERS_OBJS> )
    add_to_cached_list( CGAL_EXECUTABLE_TARGETS ${libmesh_ext_exec_name} )
    target_link_libraries( ${libmesh_ext_exec_name} ${CGAL_LIBRARIES} ${BOOST_LIBRARIES} ${CGAL_3RD_PARTY_LIBRARIES} )
endforeach( libmesh_ext_source_file ${LIBMESH_EXT_EXECS} )
