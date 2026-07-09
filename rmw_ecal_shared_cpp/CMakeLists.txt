# ========================= RMW eCAL LICENSE =================================
#
# Copyright (C) 2019 - 2020 Continental Corporation
#
# Licensed under the Apache License, Version 2.0 (the "License");
# you may not use this file except in compliance with the License.
# You may obtain a copy of the License at
#
#      http://www.apache.org/licenses/LICENSE-2.0
#
# Unless required by applicable law or agreed to in writing, software
# distributed under the License is distributed on an "AS IS" BASIS,
# WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
# See the License for the specific language governing permissions and
# limitations under the License.
#
# ========================= RMW eCAL LICENSE =================================

cmake_minimum_required(VERSION 3.12)

project(rmw_ecal_shared_cpp)

if(NOT CMAKE_CXX_STANDARD)
  set(CMAKE_CXX_STANDARD 14)
endif()

if(CMAKE_COMPILER_IS_GNUCXX OR CMAKE_CXX_COMPILER_ID MATCHES "Clang")
  add_compile_options(-Wall -Wextra -Wpedantic)
endif()

if (CMAKE_CXX_COMPILER_ID MATCHES "MSVC")
  add_compile_options(/W4)
  add_compile_definitions(_CRT_SECURE_NO_WARNINGS)
  # CMake >= 3.15 will erroneously define PROTOBUF_USE_DLLS otherwise
  set (Protobuf_USE_STATIC_LIBS TRUE)
endif()

include("cmake/discover-ros-distro-extras.cmake")

find_package(ament_cmake REQUIRED)

find_package(rmw REQUIRED)
find_package(rosidl_generator_c REQUIRED)
find_package(rosidl_typesupport_introspection_c REQUIRED)
find_package(rosidl_typesupport_introspection_cpp REQUIRED)

find_package(eCAL REQUIRED)
find_package(Protobuf REQUIRED)

create_targets_protobuf()

include_directories(
  ${PROJECT_SOURCE_DIR}/include
  ${PROJECT_SOURCE_DIR}/include/rmw_ecal_shared_cpp/serialization
  ${PROJECT_SOURCE_DIR}/src
)

add_library(${PROJECT_NAME} SHARED
  src/event.cpp
  src/get_network_flow_endpoints.cpp
  src/get_node_info_and_types.cpp
  src/get_service_names_and_types.cpp
  src/get_topic_names_and_types.cpp
  src/get_topic_endpoint_info.cpp
  src/init_options.cpp
  src/init.cpp
  src/qos_profiles.cpp
  src/rmw.cpp
  src/features.cpp
  src/serialization/serializer_cpp.cpp
  src/serialization/serializer_c.cpp
  src/serialization/deserializer_cpp.cpp
  src/serialization/deserializer_c.cpp
)

set(proto_files
  ${CMAKE_CURRENT_SOURCE_DIR}/protobuf/subscriber.proto
  ${CMAKE_CURRENT_SOURCE_DIR}/protobuf/publisher.proto
  ${CMAKE_CURRENT_SOURCE_DIR}/protobuf/client.proto
  ${CMAKE_CURRENT_SOURCE_DIR}/protobuf/service.proto
  ${CMAKE_CURRENT_SOURCE_DIR}/protobuf/ecal/service.proto
  ${CMAKE_CURRENT_SOURCE_DIR}/protobuf/ecal/host.proto
  ${CMAKE_CURRENT_SOURCE_DIR}/protobuf/ecal/process.proto
  ${CMAKE_CURRENT_SOURCE_DIR}/protobuf/ecal/topic.proto
  ${CMAKE_CURRENT_SOURCE_DIR}/protobuf/ecal/monitoring.proto
)

PROTOBUF_TARGET_CPP(${PROJECT_NAME} ${CMAKE_CURRENT_SOURCE_DIR}/protobuf ${proto_files})

target_compile_definitions(${PROJECT_NAME} PRIVATE "RMW_PROTOBUF_SHARED_CPP_BUILDING_LIBRARY")

target_include_directories(${PROJECT_NAME} PUBLIC
  "$<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/include>"
  "$<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/include/rmw_ecal_shared_cpp>"
  "$<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/include/rmw_ecal_shared_cpp/serialization>"
  "$<INSTALL_INTERFACE:include>"
  "$<INSTALL_INTERFACE:include/rmw_ecal_shared_cpp>"
  "$<INSTALL_INTERFACE:include/rmw_ecal_shared_cpp/serialization>"
  ${rosidl_generator_c_INCLUDE_DIRS}
  ${rosidl_typesupport_introspection_c_INCLUDE_DIRS}
  ${rosidl_typesupport_introspection_cpp_INCLUDE_DIRS}
  ${rmw_INCLUDE_DIRS}
)

target_link_libraries(${PROJECT_NAME} PUBLIC
  eCAL::core
  rmw::rmw
  ${rosidl_generator_c_LIBRARIES}
  ${rosidl_generator_c_TARGETS}
  ${rosidl_typesupport_introspection_c_LIBRARIES}
  ${rosidl_typesupport_introspection_cpp_LIBRARIES}
)

ament_export_include_directories(include include/rmw_ecal_shared_cpp include/rmw_ecal_shared_cpp/serialization)
ament_export_libraries(${PROJECT_NAME})
ament_export_targets(${PROJECT_NAME})
ament_export_dependencies(rmw)
ament_export_dependencies(rosidl_typesupport_introspection_c)
ament_export_dependencies(rosidl_typesupport_introspection_cpp)

install(
  DIRECTORY include/
  DESTINATION include
)

install(
  TARGETS ${PROJECT_NAME}
  EXPORT ${PROJECT_NAME}
  ARCHIVE DESTINATION lib
  LIBRARY DESTINATION lib
  RUNTIME DESTINATION bin
)

if(BUILD_TESTING)
  add_subdirectory(test)
endif()

ament_package(CONFIG_EXTRAS "cmake/discover-ros-distro-extras.cmake")

