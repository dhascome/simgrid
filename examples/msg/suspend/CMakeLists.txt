cmake_minimum_required(VERSION 2.6)

set(EXECUTABLE_OUTPUT_PATH "${CMAKE_CURRENT_BINARY_DIR}")

add_executable(suspend suspend.c)

### Add definitions for compile
target_link_libraries(suspend simgrid )

set(tesh_files
  ${tesh_files}
  ${CMAKE_CURRENT_SOURCE_DIR}/suspend.tesh
  PARENT_SCOPE
  )
set(xml_files
  ${xml_files}
  ${CMAKE_CURRENT_SOURCE_DIR}/deployment_suspend.xml
  PARENT_SCOPE
  )
set(examples_src
  ${examples_src}
  ${CMAKE_CURRENT_SOURCE_DIR}/suspend.c
  PARENT_SCOPE
  )
set(bin_files
  ${bin_files}
  PARENT_SCOPE
  )
set(txt_files
  ${txt_files}
  PARENT_SCOPE
  )
