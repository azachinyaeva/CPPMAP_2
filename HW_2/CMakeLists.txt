cmake_minimum_required(VERSION 3.2)
project(HW2.cpp)
add_executable(HW2 HW2.cpp consoleParameter.h ProgressBar.cpp ProgressBar.h)
target_compile_features (HW2 PRIVATE cxx_std_17)