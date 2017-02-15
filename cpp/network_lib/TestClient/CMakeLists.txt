project(TestClient)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11")
set(SOURCE_FILES Client.cpp ../Socket.cpp ../Socket.h)
add_executable(TestClient ${SOURCE_FILES})
target_link_libraries(TestClient ws2_32)