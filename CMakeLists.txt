cmake_minimum_required(VERSION 3.10)
project(SYMPYLER)

SET(CMAKE_CXX_STANDARD 11)

find_package(OpenMP REQUIRED)
set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} ${OpenMP_C_FLAGS}")
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} ${OpenMP_CXX_FLAGS}")

find_package(PythonInterp 3)

if (PYTHONINTERP_FOUND)
    if (UNIX AND NOT APPLE)
        if (PYTHON_VERSION_MAJOR EQUAL 3)
            find_package(Boost COMPONENTS python${PYTHON_VERSION_SUFFIX})
            find_package(PythonInterp 3)
            find_package(PythonLibs 3 REQUIRED)
        else()
            find_package(Boost COMPONENTS python)
            find_package(PythonInterp)
            find_package(PythonLibs REQUIRED)
        endif()
    else()
        if (PYTHON_VERSION_MAJOR EQUAL 3)
            find_package(Boost COMPONENTS python${PYTHON_VERSION_MAJOR}${PYTHON_VERSION_MINOR} numpy)
            find_package(PythonInterp 3)
            find_package(PythonLibs 3 REQUIRED)
        else()
            find_package(Boost COMPONENTS python${PYTHON_VERSION_MAJOR}${PYTHON_VERSION_MINOR})
            find_package(PythonInterp)
            find_package(PythonLibs REQUIRED)
        endif()
    endif()
else()
    message("Python not found")
endif()

message(STATUS "PYTHON_LIBRARIES = ${PYTHON_LIBRARIES}")
message(STATUS "PYTHON_EXECUTABLE = ${PYTHON_EXECUTABLE}")
message(STATUS "PYTHON_INCLUDE_DIRS = ${PYTHON_INCLUDE_DIRS}")
message(STATUS "Boost_LIBRARIES = ${Boost_LIBRARIES}")
message(STATUS "OpenMP_CXX_INCLUDE_DIRS = ${OpenMP_CXX_INCLUDE_DIRS}")
message(STATUS "OpenMP_CXX_LIBRARIES = ${OpenMP_CXX_LIBRARIES}")
message(STATUS "METIS_INCLUDES = ${METIS_INCLUDES}")
message(STATUS "METIS_LIBRARIES = ${METIS_LIBRARIES}")
message(STATUS "CMAKE_MODULE_PATH = ${CMAKE_MODULE_PATH}")

set(PYLBC_INCLUDE_DIRS ${CMAKE_CURRENT_LIST_DIR})
set(LBC_INCLUDE_DIRS
        ${CMAKE_CURRENT_LIST_DIR}/lbc/lbc/includes
        ${CMAKE_CURRENT_LIST_DIR}/lbc/utils/includes
        ${CMAKE_CURRENT_LIST_DIR}/lbc/utils/external/includes
        ${CMAKE_CURRENT_LIST_DIR}/lbc/example)

set(LBC_SOURCE_FILES
        ${CMAKE_CURRENT_LIST_DIR}/lbc/example/sptrsv.cpp
        ${CMAKE_CURRENT_LIST_DIR}/lbc/utils/metis_interface.cpp
        ${CMAKE_CURRENT_LIST_DIR}/lbc/utils/sparse_inspector.cpp)

add_subdirectory(lbc)

include_directories(
        ${Boost_INCLUDE_DIRS}
        ${PYTHON_INCLUDE_DIRS}
        ${OpenMP_CXX_INCLUDE_DIRS}
        ${PYLBC_INCLUDE_DIRS}
        ${LBC_INCLUDE_DIRS}
        ${METIS_INCLUDES})

link_libraries(lbc
        ${OpenMP_CXX_LIBRARIES}
        ${METIS_LIBRARIES}
        ${Boost_LIBRARIES}
        ${PYTHON_LIBRARIES})

add_subdirectory(pylbc)