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

#include <gtest/gtest.h>
#include <string>

#include "internal/qos.hpp"

TEST(NamespaceTest, topic_mangling)
{
  EXPECT_EQ(eCAL::rmw::DemangleTopicName("rt/chatter"), "/chatter");
  EXPECT_EQ(eCAL::rmw::DemangleTopicName("chatter"), "chatter");
  EXPECT_EQ(eCAL::rmw::MangleTopicName("/chatter"), "rt/chatter");
  EXPECT_EQ(eCAL::rmw::MangleTopicName("chatter"), "rtchatter");
}

TEST(NamespaceTest, service_mangling)
{
  EXPECT_EQ(eCAL::rmw::DemangleServiceName("rs/add_two_ints"), "/add_two_ints");
  EXPECT_EQ(eCAL::rmw::DemangleServiceName("add_two_ints"), "add_two_ints");
}

TEST(NamespaceTest, prefix_constants)
{
  EXPECT_EQ(eCAL::rmw::pub_name_prefix, "rt");
  EXPECT_EQ(eCAL::rmw::service_name_prefix, "rs");
  EXPECT_EQ(eCAL::rmw::parameter_name_prefix, "rp");
  EXPECT_EQ(eCAL::rmw::action_name_prefix, "ra");
  EXPECT_EQ(eCAL::rmw::private_symbol_prefix, "_");
}

TEST(NamespaceTest, build_query)
{
  EXPECT_EQ(
    eCAL::rmw::BuildQueryServiceName("/", "my_node"),
    "rs/_node/my_node");
  EXPECT_EQ(
    eCAL::rmw::BuildQueryServiceName("/ns", "my_node"),
    "rs/_node/ns/my_node");
  EXPECT_EQ(
    eCAL::rmw::BuildQueryServiceName("/ns/sub", "my_node"),
    "rs/_node/ns/sub/my_node");
}
