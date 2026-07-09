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

#include "rosidl_typesupport_introspection_c/message_introspection.h"
#include "rosidl_typesupport_introspection_cpp/message_introspection.hpp"
#include "rosidl_runtime_c/message_type_support_struct.h"
#include "rmw_ecal_shared_cpp/serialization/common.hpp"

TEST(TestSerializationCommon, GetMembersCAndCpp)
{
  rosidl_typesupport_introspection_c__MessageMembers c_members{};
  c_members.message_name_ = "TestMsgC";
  c_members.message_namespace_ = "test_msgs";

  rosidl_message_type_support_t c_ts{};
  c_ts.data = &c_members;

  auto * fetched_c = GetCMembers(&c_ts);
  ASSERT_NE(fetched_c, nullptr);
  EXPECT_STREQ(fetched_c->message_name_, "TestMsgC");

  rosidl_typesupport_introspection_cpp::MessageMembers cpp_members{};
  cpp_members.message_name_ = "TestMsgCpp";
  cpp_members.message_namespace_ = "test_msgs";

  rosidl_message_type_support_t cpp_ts{};
  cpp_ts.data = &cpp_members;

  auto * fetched_cpp = GetCppMembers(&cpp_ts);
  ASSERT_NE(fetched_cpp, nullptr);
  EXPECT_STREQ(fetched_cpp->message_name_, "TestMsgCpp");
}
