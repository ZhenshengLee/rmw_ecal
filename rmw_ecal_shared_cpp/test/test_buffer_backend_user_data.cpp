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
#include <vector>
#include <cstring>

#include "rmw/rmw.h"
#include "rmw/serialized_message.h"

TEST(test_buffer_backend_user_data, SerializedMessageBufferCheck)
{
  rcutils_allocator_t allocator = rcutils_get_default_allocator();
  rmw_serialized_message_t serialized_msg = rmw_get_zero_initialized_serialized_message();
  ASSERT_EQ(rmw_serialized_message_init(&serialized_msg, 64, &allocator), RMW_RET_OK);

  const char * test_data = "ecal_buffer_test_payload";
  size_t len = std::strlen(test_data);
  std::memcpy(serialized_msg.buffer, test_data, len + 1);
  serialized_msg.buffer_length = len;

  EXPECT_EQ(serialized_msg.buffer_length, len);
  EXPECT_STREQ(reinterpret_cast<char *>(serialized_msg.buffer), test_data);

  EXPECT_EQ(rmw_serialized_message_fini(&serialized_msg), RMW_RET_OK);
}

TEST(test_buffer_backend_user_data, SerializedMessageResizeCheck)
{
  rcutils_allocator_t allocator = rcutils_get_default_allocator();
  rmw_serialized_message_t serialized_msg = rmw_get_zero_initialized_serialized_message();
  ASSERT_EQ(rmw_serialized_message_init(&serialized_msg, 16, &allocator), RMW_RET_OK);

  EXPECT_EQ(rmw_serialized_message_resize(&serialized_msg, 128), RMW_RET_OK);
  EXPECT_GE(serialized_msg.buffer_capacity, 128u);

  EXPECT_EQ(rmw_serialized_message_fini(&serialized_msg), RMW_RET_OK);
}

TEST(test_buffer_backend_user_data, SerializedMessageCopyCheck)
{
  rcutils_allocator_t allocator = rcutils_get_default_allocator();
  rmw_serialized_message_t src = rmw_get_zero_initialized_serialized_message();
  rmw_serialized_message_t dst = rmw_get_zero_initialized_serialized_message();

  ASSERT_EQ(rmw_serialized_message_init(&src, 32, &allocator), RMW_RET_OK);
  ASSERT_EQ(rmw_serialized_message_init(&dst, 32, &allocator), RMW_RET_OK);

  const char * val = "copy_test";
  std::memcpy(src.buffer, val, std::strlen(val) + 1);
  src.buffer_length = std::strlen(val);

  // In rosidl / rmw, we can copy payload data via copy functions or manual buffer copy.
  // We check that direct buffer copies are safe with eCAL.
  std::memcpy(dst.buffer, src.buffer, src.buffer_length + 1);
  dst.buffer_length = src.buffer_length;

  EXPECT_STREQ(reinterpret_cast<char *>(dst.buffer), val);

  EXPECT_EQ(rmw_serialized_message_fini(&src), RMW_RET_OK);
  EXPECT_EQ(rmw_serialized_message_fini(&dst), RMW_RET_OK);
}

TEST(test_buffer_backend_user_data, ZeroInitializedMessageFiniSafe)
{
  rmw_serialized_message_t msg = rmw_get_zero_initialized_serialized_message();
  // Finalizing a zero-initialized serialized message returns INVALID_ARGUMENT since allocator is invalid
  EXPECT_EQ(rmw_serialized_message_fini(&msg), RMW_RET_INVALID_ARGUMENT);
}

TEST(test_buffer_backend_user_data, SerializedMessageReallocateCheck)
{
  rcutils_allocator_t allocator = rcutils_get_default_allocator();
  rmw_serialized_message_t msg = rmw_get_zero_initialized_serialized_message();
  ASSERT_EQ(rmw_serialized_message_init(&msg, 10, &allocator), RMW_RET_OK);

  EXPECT_EQ(rmw_serialized_message_resize(&msg, 20), RMW_RET_OK);
  EXPECT_EQ(rmw_serialized_message_fini(&msg), RMW_RET_OK);
}
