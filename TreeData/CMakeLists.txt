cmake_minimum_required(VERSION 3.10)

enable_testing()
project(TreeData VERSION 1.0.0 LANGUAGES C CXX)
set(CMAKE_C_STANDARD 99)
set(CMAKE_CXX_STANDARD 17)

add_library(${PROJECT_NAME} STATIC 
	include/TreeData.hpp
	src/TreeData.cpp
)
add_library(${PROJECT_NAME}::${PROJECT_NAME} ALIAS ${PROJECT_NAME})

target_include_directories(${PROJECT_NAME}
	PUBLIC
		$<INSTALL_INTERFACE:include>
    		$<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/include>
	PRIVATE
		${CMAKE_CURRENT_SOURCE_DIR}/src
)

add_subdirectory(tests)

##############################################
# Installation instructions

install(FILES ${CMAKE_CURRENT_SOURCE_DIR}/include/TreeData.hpp DESTINATION include)

install(TARGETS ${PROJECT_NAME} EXPORT ${PROJECT_NAME}Targets
    LIBRARY DESTINATION lib
    ARCHIVE DESTINATION lib
    RUNTIME DESTINATION bin
    INCLUDES DESTINATION include
)

install(EXPORT ${PROJECT_NAME}Targets
    FILE ${PROJECT_NAME}Targets.cmake
    NAMESPACE ${PROJECT_NAME}::
    DESTINATION lib/cmake/${PROJECT_NAME}
)

file(WRITE "${PROJECT_BINARY_DIR}/${PROJECT_NAME}Config.cmake" "
include(CMakeFindDependencyMacro)
#find_dependency(record)  # list dependencies here
include(\"\${CMAKE_CURRENT_LIST_DIR}/${PROJECT_NAME}Targets.cmake\")
")

include(CMakePackageConfigHelpers)
write_basic_package_version_file("${PROJECT_BINARY_DIR}/${PROJECT_NAME}Config-version.cmake"
    VERSION 1.0
    COMPATIBILITY AnyNewerVersion
)

install(FILES          # only if there are dependencies
    ${PROJECT_BINARY_DIR}/${PROJECT_NAME}Config.cmake
    ${PROJECT_BINARY_DIR}/${PROJECT_NAME}Config-version.cmake
    DESTINATION "lib/cmake/${PROJECT_NAME}" 
)
