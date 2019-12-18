cmake_minimum_required(VERSION 3.13)
project(MTF_Transpose_Performance_Evaluation)

set(CMAKE_CXX_STANDARD 14)

add_executable(MTF_Transpose_Performance_Evaluation statistics.cpp dlist.h dlist.cpp.h mtflist.h mtflist.cpp.h transposelist.h transposelist.cpp.h)