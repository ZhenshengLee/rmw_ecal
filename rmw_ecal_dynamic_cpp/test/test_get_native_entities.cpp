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

#include "gtest/gtest.h"

#include "rcutils/allocator.h"
#include "rcutils/strdup.h"
#include "rmw/error_handling.h"
#include "rmw/rmw.h"

#include "rosidl_typesupport_introspection_cpp/message_type_support_decl.hpp"
#include "rosidl_typesupport_introspection_cpp/service_type_support_decl.hpp"

#include "std_msgs/msg/string.hpp"
#include "std_srvs/srv/empty.hpp"

class TestNativeEntitiesDynamicCpp : public ::testing::Test
{
protected:
  void SetUp() override
  {
    rcutils_allocator_t allocator = rcutils_get_default_allocator();
    rmw_init_options_t options = rmw_get_zero_initialized_init_options();
    ASSERT_EQ(RMW_RET_OK, rmw_init_options_init(&options, allocator));
    options.enclave = rcutils_strdup("/", allocator);
    
    ASSERT_EQ(RMW_RET_OK, rmw_init(&options, &context));
    ASSERT_EQ(RMW_RET_OK, rmw_init_options_fini(&options));

    node = rmw_create_node(&context, "my_node", "/my_ns");
    ASSERT_NE(nullptr, node) << rmw_get_error_string().str;
  }

  void TearDown() override
  {
    ASSERT_EQ(RMW_RET_OK, rmw_destroy_node(node));
    ASSERT_EQ(RMW_RET_OK, rmw_shutdown(&context));
    ASSERT_EQ(RMW_RET_OK, rmw_context_fini(&context));
  }

  rmw_context_t context{rmw_get_zero_initialized_context()};
  rmw_node_t * node{nullptr};
};

TEST_F(TestNativeEntitiesDynamicCpp, get_domain_participant)
{
  EXPECT_STREQ("rmw_ecal_dynamic_cpp", node->implementation_identifier);
  
  const char * original_identifier = node->implementation_identifier;
  node->implementation_identifier = "not-matching-rmw-identifier";
  EXPECT_STRNE("rmw_ecal_dynamic_cpp", node->implementation_identifier);
  node->implementation_identifier = original_identifier;
}

TEST_F(TestNativeEntitiesDynamicCpp, get_datawriter)
{
  const rosidl_message_type_support_t * ts =
    rosidl_typesupport_introspection_cpp::get_message_type_support_handle<std_msgs::msg::String>();
  
  rmw_qos_profile_t qos_profile = rmw_qos_profile_default;
  rmw_publisher_options_t options = rmw_get_default_publisher_options();
  
  rmw_publisher_t * pub = rmw_create_publisher(node, ts, "/test_topic", &qos_profile, &options);
  ASSERT_NE(nullptr, pub) << rmw_get_error_string().str;
  EXPECT_STREQ("rmw_ecal_dynamic_cpp", pub->implementation_identifier);

  EXPECT_EQ(RMW_RET_OK, rmw_destroy_publisher(node, pub));
}

TEST_F(TestNativeEntitiesDynamicCpp, get_datareader)
{
  const rosidl_message_type_support_t * ts =
    rosidl_typesupport_introspection_cpp::get_message_type_support_handle<std_msgs::msg::String>();
  
  rmw_qos_profile_t qos_profile = rmw_qos_profile_default;
  rmw_subscription_options_t options = rmw_get_default_subscription_options();
  
  rmw_subscription_t * sub = rmw_create_subscription(node, ts, "/test_topic", &qos_profile, &options);
  ASSERT_NE(nullptr, sub) << rmw_get_error_string().str;
  EXPECT_STREQ("rmw_ecal_dynamic_cpp", sub->implementation_identifier);

  EXPECT_EQ(RMW_RET_OK, rmw_destroy_subscription(node, sub));
}

TEST_F(TestNativeEntitiesDynamicCpp, get_service)
{
  const rosidl_service_type_support_t * ts =
    rosidl_typesupport_introspection_cpp::get_service_type_support_handle<std_srvs::srv::Empty>();
  
  rmw_qos_profile_t qos_profile = rmw_qos_profile_default;
  rmw_service_t * srv = rmw_create_service(node, ts, "/test_service", &qos_profile);
  ASSERT_NE(nullptr, srv) << rmw_get_error_string().str;
  EXPECT_STREQ("rmw_ecal_dynamic_cpp", srv->implementation_identifier);

  EXPECT_EQ(RMW_RET_OK, rmw_destroy_service(node, srv));
}

TEST_F(TestNativeEntitiesDynamicCpp, get_client)
{
  const rosidl_service_type_support_t * ts =
    rosidl_typesupport_introspection_cpp::get_service_type_support_handle<std_srvs::srv::Empty>();
  
  rmw_qos_profile_t qos_profile = rmw_qos_profile_default;
  rmw_client_t * client = rmw_create_client(node, ts, "/test_service", &qos_profile);
  ASSERT_NE(nullptr, client) << rmw_get_error_string().str;
  EXPECT_STREQ("rmw_ecal_dynamic_cpp", client->implementation_identifier);

  EXPECT_EQ(RMW_RET_OK, rmw_destroy_client(node, client));
}
