find_package(ament_cmake_gtest REQUIRED)
find_package(rmw REQUIRED)
find_package(std_msgs REQUIRED)
find_package(std_srvs REQUIRED)
find_package(rosidl_typesupport_introspection_cpp REQUIRED)
find_package(rosidl_typesupport_introspection_c REQUIRED)

set(TEST_TARGETS
  test_logging
  test_get_native_entities
  test_serialization_format
  test_rmw_implementation
)

foreach(test_target ${TEST_TARGETS})
  ament_add_gtest(${test_target} ${test_target}.cpp APPEND_LIBRARY_DIRS "/opt/gsd/x86_64/ecal/lib")
  if(TARGET ${test_target})
    target_link_libraries(${test_target} 
      ${PROJECT_NAME} 
      rmw::rmw
      std_msgs::std_msgs__rosidl_typesupport_introspection_cpp
      std_msgs::std_msgs__rosidl_typesupport_introspection_c
      std_srvs::std_srvs__rosidl_typesupport_introspection_cpp
      std_srvs::std_srvs__rosidl_typesupport_introspection_c
    )
  endif()
endforeach()
