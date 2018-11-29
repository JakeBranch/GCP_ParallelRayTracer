cmake_minimum_required(VERSION 2.6)
project(RAYTRACER)

include_directories(
    src
    contrib
)

if(MSVC)
    include_directories(
        contrib/SDL2/include
    )

    link_directories(
        ${CMAKE_SOURCE_DIR}/contrib/SDL2/lib/x86
    )

endif()

if(MSVC)
	add_definitions(-DSDL_MAIN_HANDLED)
endif()

add_executable(RayTracer
    src/main.cpp
    src/Camera.h
    src/Camera.cpp
    src/Ray.h
    src/Ray.cpp
    src/Window.h
    src/Window.cpp
    src/Geometry.h
    src/Geometry.cpp
    src/Sphere.h
    src/Sphere.cpp
    src/RayTracer.h
    src/RayTracer.cpp
)

if(MSVC)
    target_link_libraries(RayTracer
        SDL2
    )
else()
    target_link_libraries(RayTracer)
endif()

if(MSVC)
	add_custom_command(TARGET RayTracer POST_BUILD
		COMMAND ${CMAKE_COMMAND} -E copy_if_different
		"${CMAKE_SOURCE_DIR}/contrib/SDL2/lib/x86/SDL2.dll"
		"$<TARGET_FILE_DIR:RayTracer>"
	)
endif()
