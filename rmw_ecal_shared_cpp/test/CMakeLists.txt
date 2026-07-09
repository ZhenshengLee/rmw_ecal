find_package(ament_cmake_gtest REQUIRED)
find_package(rmw REQUIRED)

set(TEST_TARGETS
  test_names
  test_qos_profile_check_compatible
  test_rmw_init_options
  test_logging
  test_guid_utils
  test_security_logging
  test_buffer_backend_user_data
  test_ecal_qos_to_rmw_qos
  test_rmw_qos_to_ecal_qos
  test_rmw_features
  test_rmw_network_flow_endpoints
  test_serialization_common
)

foreach(test_target ${TEST_TARGETS})
  ament_add_gtest(${test_target} ${test_target}.cpp APPEND_LIBRARY_DIRS "/opt/gsd/x86_64/ecal/lib")
  if(TARGET ${test_target})
    target_link_libraries(${test_target} ${PROJECT_NAME} rmw::rmw)
  endif()
endforeach()
