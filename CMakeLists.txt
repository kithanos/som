cmake_minimum_required(VERSION 3.5.1)
project( som )
find_package( OpenCV REQUIRED )
add_executable( som som.cpp MatNumDeArquivo.cpp )
target_link_libraries( som ${OpenCV_LIBS} )
