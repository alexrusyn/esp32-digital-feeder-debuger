FILE(GLOB_RECURSE app_sources ${CMAKE_SOURCE_DIR}/src/*.*)

idf_component_register(SRCS ${app_sources})

set(REACT_DIR "${CMAKE_SOURCE_DIR}/client")
set(REACT_BUILD_DIR "${REACT_DIR}/build")

add_custom_target(build_react ALL
    COMMAND npm ci
    COMMAND npm run build
    WORKING_DIRECTORY ${REACT_DIR}
    COMMENT "Building React app..."
)

spiffs_create_partition_image(spiffs ${REACT_BUILD_DIR} FLASH_IN_PROJECT)

add_dependencies(${COMPONENT_TARGET} build_react)
