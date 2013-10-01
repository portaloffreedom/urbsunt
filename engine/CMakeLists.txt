

set(engine_SRCS shaders/shader.cpp math/frustum.cpp geometrytransform.cpp matrixstack.cpp renderengine.cpp camera.cpp math/math.cpp ${engine_SRCS})

add_subdirectory(math)

add_library(SmEngine_static STATIC ${engine_SRCS})
add_library(SmEngine_dynamic SHARED ${engine_SRCS})
add_subdirectory(shaders)