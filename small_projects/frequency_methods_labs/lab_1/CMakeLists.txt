cmake_minimum_required(VERSION 3.10)  # Specify CMake version  
project(MatplotExample)  # Name your project  

# Define the C++ standard  
 # Specify C++14 standard; you can change to 17 or 20 if needed  

# Add the Matplot++ include directory  
include_directories(matplotplusplus) 
add_subdirectory(matplotplusplus)


file(GLOB SOURCES src/*.cpp)

include_directories(include)


# Create an executable from main.cpp  
#add_executable(MatplotExample main.cpp)  
add_executable(MatplotExample ${SOURCES})  

# Link Matplot++ to your executable  
target_link_libraries(MatplotExample PUBLIC  matplot)