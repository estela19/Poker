# Target name
set(target Server)

# Sources
file(GLOB_RECURSE sources ${CMAKE_CURRENT_SOURCE_DIR}/Sources/*.cc)

add_executable(${target} ${sources})

target_include_directories(${target}
	PRIVATE
	${CMAKE_CURRENT_SOURCE_DIR}/Includes
)

set_target_properties(${target}
	PROPERTIES
	${DEFAULT_PROJECT_OPTIONS}
)

target_compile_options(${target}
	PRIVATE
	${DEFAULT_COMPILER_OPTIONS}
)

target_link_libraries(${target}
	PRIVATE
	${DEFAULT_LINKER_OPTIONS}
	Poker
)