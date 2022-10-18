add_executable(shell-app main.cpp img_set.cpp image.cpp)
include_directories(
    ${CMAKE_SOURCE_DIR}/include
)
target_link_libraries(shell-app ${OpenCV_LIBS} )
