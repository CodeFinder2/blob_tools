add_executable(blob_tools_example_publisher publisher.cpp)
add_executable(blob_tools_example_subscriber subscriber.cpp)
target_include_directories(blob_tools_example_publisher PRIVATE ../include ${catkin_INCLUDE_DIRS})
target_include_directories(blob_tools_example_subscriber PRIVATE ../include ${catkin_INCLUDE_DIRS})
target_link_libraries(blob_tools_example_publisher ${catkin_LIBRARIES} ${PROJECT_NAME})
target_link_libraries(blob_tools_example_subscriber ${catkin_LIBRARIES} ${PROJECT_NAME})

