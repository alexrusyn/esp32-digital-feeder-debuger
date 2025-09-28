FILE(GLOB_RECURSE app_sources ${CMAKE_SOURCE_DIR}/src/*.*)

idf_component_register(SRCS ${app_sources})

set(REACT_DIR "${CMAKE_SOURCE_DIR}/client")
set(REACT_BUILD_DIR "${REACT_DIR}/build")

spiffs_create_partition_image(spiffs ${REACT_BUILD_DIR} FLASH_IN_PROJECT)

