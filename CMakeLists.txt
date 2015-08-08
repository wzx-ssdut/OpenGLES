cmake_minimum_required(VERSION 3.3)
project(GLES)


set(GLES_ROOT ${CMAKE_SOURCE_DIR})


if(WIN32)
	set(WINDOWS_BIT win32)
else()
	set(WINDOWS_BIT win64)
endif()


set(BINARY_GLES3 ${GLES_ROOT}/external/PVRVFrame/lib/${WINDOWS_BIT}/libGLESv2.dll)
set(BINARY_EGL   ${GLES_ROOT}/external/PVRVFrame/lib/${WINDOWS_BIT}/libEGL.dll)


include_directories(
	external/PVRVFrame/include
	external/glm-0.9.6.3
)
link_directories(
	external/PVRVFrame/lib/${WINDOWS_BIT}
)


set(LIBRARY_GLES3 libGLESv2)
set(LIBRARY_EGL   libEGL)


# framework library
set(FRAMEWORK_LIBRARY framework)
add_subdirectory(framework)


# samples
add_subdirectory(00_BlankWindow)
add_subdirectory(01_RedTriangle)

