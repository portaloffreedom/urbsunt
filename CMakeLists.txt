cmake_minimum_required(VERSION 2.6)

project(demo-sdl)
find_package(OpenGL)
find_package(GLEW REQUIRED)

if(CMAKE_COMPILER_IS_GNUCXX)
   SET(ENABLE_CXX11 "-std=c++11")

   EXECUTE_PROCESS(COMMAND "${CMAKE_CXX_COMPILER} -dumpversion" OUTPUT_VARIABLE GCC_VERSION)
   if (GCC_VERSION VERSION_LESS 4.7)
      SET(ENABLE_CXX11 "-std=c++0x")
   endif()

   SET(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} ${ENABLE_CXX11}")
endif()


add_subdirectory(engine)

add_executable(demo-sdl main.cpp)

target_link_libraries(demo-sdl SmEngine_dynamic ${GLEW_LIBRARIES} ${OPENGL_gl_LIBRARY} SDL2)

install(TARGETS demo-sdl RUNTIME DESTINATION bin)

