set(CPP_SOURCES ${CMAKE_CURRENT_LIST_DIR}/mylib.cpp)
set(SWIG_WRAPPER ${CMAKE_CURRENT_LIST_DIR}/mylib.i)

# Direct swig to process and generate wrappers in c++ mode
SET_PROPERTY(SOURCE ${SWIG_WRAPPER} PROPERTY CPLUSPLUS ON)

include_directories(${CMAKE_CURRENT_LIST_DIR})
