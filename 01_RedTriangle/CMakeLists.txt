set(APP_NAME 01_RedTriangle)


include_directories(
	${GLES_ROOT}/framework
)


add_executable(${APP_NAME}
	Scene.hpp
	Scene.cpp
)
target_link_libraries(${APP_NAME}
	${FRAMEWORK_LIBRARY}
)

add_custom_command(TARGET ${APP_NAME}
	PRE_BUILD
	COMMAND ${CMAKE_COMMAND} -E copy ${BINARY_GLES3} ${CMAKE_CURRENT_BINARY_DIR}/${CMAKE_BUILD_TYPE}
	COMMAND ${CMAKE_COMMAND} -E copy ${BINARY_EGL}   ${CMAKE_CURRENT_BINARY_DIR}/${CMAKE_BUILD_TYPE}
)