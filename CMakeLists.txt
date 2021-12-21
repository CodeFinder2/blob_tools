cmake_minimum_required(VERSION 3.1)
project(blob_tools)

find_package(catkin REQUIRED message_generation roscpp std_msgs)
find_package(Boost REQUIRED COMPONENTS system)
find_package(BZip2)

# Exclude cpp from message generators
list(REMOVE_ITEM CATKIN_MESSAGE_GENERATORS gencpp)

add_message_files(FILES Blob.msg)
generate_messages(DEPENDENCIES std_msgs)
catkin_package(
  INCLUDE_DIRS include
  LIBRARIES ${PROJECT_NAME}
  CATKIN_DEPENDS message_runtime roscpp
)

add_library(${PROJECT_NAME} src/compression.cpp src/shape_shifter.cpp)
target_include_directories(${PROJECT_NAME} SYSTEM PRIVATE ${catkin_INCLUDE_DIRS})
target_include_directories(${PROJECT_NAME} PRIVATE include)
target_compile_features(${PROJECT_NAME} PUBLIC cxx_std_11)
if(BZIP2_FOUND)
  target_include_directories(${PROJECT_NAME} SYSTEM PRIVATE ${BZIP2_INCLUDE_DIR})
  target_compile_definitions(${PROJECT_NAME} PRIVATE HAVE_BZIP2 ${BZIP2_DEFINITIONS})
  target_link_libraries(${PROJECT_NAME} ${BZIP2_LIBRARIES})
endif()

install(TARGETS ${PROJECT_NAME}
  ARCHIVE DESTINATION ${CATKIN_PACKAGE_LIB_DESTINATION}
  LIBRARY DESTINATION ${CATKIN_PACKAGE_LIB_DESTINATION}
  RUNTIME DESTINATION ${CATKIN_PACKAGE_BIN_DESTINATION}
)

install(DIRECTORY include/${PROJECT_NAME}/
  DESTINATION ${CATKIN_PACKAGE_INCLUDE_DESTINATION}
  FILES_MATCHING PATTERN "*.h"
  PATTERN ".git" EXCLUDE
)

add_subdirectory(example)
