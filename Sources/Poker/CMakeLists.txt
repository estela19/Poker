# Target name
set(target Poker)

# Sources
file(GLOB_RECURSE sources ${CMAKE_CURRENT_SOURCE_DIR}/*.cc)

add_library(${target} STATIC ${sources})

target_compile_options(${target}
    PRIVATE

    PUBLIC
    ${DEFAULT_COMPILE_OPTIONS}

    INTERFACE
)

set_target_properties(${target}
	PROPERTIES
	${DEFAULT_PROJECT_OPTIONS}
)

target_link_libraries(${target}
	PRIVATE

    PUBLIC
    ${DEFAULT_LINKER_OPTIONS}

	INTERFACE
)