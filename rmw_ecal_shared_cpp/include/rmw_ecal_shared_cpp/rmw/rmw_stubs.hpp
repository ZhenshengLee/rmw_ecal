// Copyright 2026 Continental AG
//
// Licensed under the Apache License, Version 2.0 (the "License");
// you may not use this file except in compliance with the License.
// You may obtain a copy of the License at
//
//     http://www.apache.org/licenses/LICENSE-2.0
//
// Unless required by applicable law or agreed to in writing, software
// distributed under the License is distributed on an "AS IS" BASIS,
// WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
// See the License for the specific language governing permissions and
// limitations under the License.

#pragma once

#if ROS_DISTRO >= HUMBLE

#include <rmw/rmw.h>
#include <rmw/event.h>
#include <rmw/get_service_endpoint_info.h>
#include <rmw/service_endpoint_info_array.h>
#include <rmw/dynamic_message_type_support.h>
#include <rosidl_dynamic_typesupport/api/serialization_support.h>

#ifdef __cplusplus
extern "C" {
#endif

bool rmw_event_type_is_supported(rmw_event_type_t event_type)
{
  switch (event_type) {
    case RMW_EVENT_LIVELINESS_CHANGED:
    case RMW_EVENT_REQUESTED_DEADLINE_MISSED:
    case RMW_EVENT_LIVELINESS_LOST:
    case RMW_EVENT_OFFERED_DEADLINE_MISSED:
    case RMW_EVENT_MESSAGE_LOST:
    case RMW_EVENT_OFFERED_QOS_INCOMPATIBLE:
    case RMW_EVENT_REQUESTED_QOS_INCOMPATIBLE:
    case RMW_EVENT_SUBSCRIPTION_INCOMPATIBLE_TYPE:
    case RMW_EVENT_PUBLISHER_INCOMPATIBLE_TYPE:
    case RMW_EVENT_SUBSCRIPTION_MATCHED:
    case RMW_EVENT_PUBLICATION_MATCHED:
      return true;
    default:
      return false;
  }
}

rmw_ret_t rmw_count_clients(
  const rmw_node_t * node,
  const char * service_name,
  size_t * count)
{
  (void)node;
  (void)service_name;
  if (count) {
    *count = 0;
  }
  return RMW_RET_OK;
}

rmw_ret_t rmw_count_services(
  const rmw_node_t * node,
  const char * service_name,
  size_t * count)
{
  (void)node;
  (void)service_name;
  if (count) {
    *count = 0;
  }
  return RMW_RET_OK;
}

rmw_ret_t rmw_get_gid_for_client(
  const rmw_client_t * client,
  rmw_gid_t * gid)
{
  (void)client;
  (void)gid;
  return RMW_RET_UNSUPPORTED;
}

rmw_ret_t rmw_get_clients_info_by_service(
  const rmw_node_t * node,
  rcutils_allocator_t * allocator,
  const char * service_name,
  bool no_mangle,
  rmw_service_endpoint_info_array_t * clients_info)
{
  (void)node;
  (void)allocator;
  (void)service_name;
  (void)no_mangle;
  (void)clients_info;
  return RMW_RET_UNSUPPORTED;
}

rmw_ret_t rmw_get_servers_info_by_service(
  const rmw_node_t * node,
  rcutils_allocator_t * allocator,
  const char * service_name,
  bool no_mangle,
  rmw_service_endpoint_info_array_t * servers_info)
{
  (void)node;
  (void)allocator;
  (void)service_name;
  (void)no_mangle;
  (void)servers_info;
  return RMW_RET_UNSUPPORTED;
}

rmw_ret_t rmw_take_dynamic_message(
  const rmw_subscription_t * subscription,
  rosidl_dynamic_typesupport_dynamic_data_t * dynamic_data,
  bool * taken,
  rmw_subscription_allocation_t * allocation)
{
  (void)subscription;
  (void)dynamic_data;
  (void)allocation;
  if (taken) {
    *taken = false;
  }
  return RMW_RET_UNSUPPORTED;
}

rmw_ret_t rmw_take_dynamic_message_with_info(
  const rmw_subscription_t * subscription,
  rosidl_dynamic_typesupport_dynamic_data_t * dynamic_data,
  bool * taken,
  rmw_message_info_t * message_info,
  rmw_subscription_allocation_t * allocation)
{
  (void)subscription;
  (void)dynamic_data;
  (void)message_info;
  (void)allocation;
  if (taken) {
    *taken = false;
  }
  return RMW_RET_UNSUPPORTED;
}

rmw_ret_t rmw_serialization_support_init(
  const char * serialization_lib_name,
  rcutils_allocator_t * allocator,
  rosidl_dynamic_typesupport_serialization_support_t * serialization_support)
{
  (void)serialization_lib_name;
  (void)allocator;
  (void)serialization_support;
  return RMW_RET_UNSUPPORTED;
}

#ifdef __cplusplus
}
#endif

#endif
