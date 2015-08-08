
set(COMMON_SOURCE
	Util.hpp
	Util.cpp
	Application.hpp
	Application.cpp
	PlatformWindows.hpp
	PlatformWindows.cpp
	
	gl/Program.hpp
	gl/Program.cpp
	gl/Shader.hpp
	gl/Shader.cpp
)


add_library(${FRAMEWORK_LIBRARY}
	${COMMON_SOURCE}
)
target_link_libraries(${FRAMEWORK_LIBRARY}
	${LIBRARY_GLES3}
	${LIBRARY_EGL}
)
