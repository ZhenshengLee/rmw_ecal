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

#include "rmw/rmw.h"
#include "rmw/init_options.h"

TEST(TestRmwImplementationDynamicCpp, ImplementationIdentifierOnly)
{
  EXPECT_STREQ(rmw_get_implementation_identifier(), "rmw_ecal_dynamic_cpp");
}

TEST(TestRmwImplementationDynamicCpp, InitOptionsLifecycle)
{
  rmw_init_options_t init_options = rmw_get_zero_initialized_init_options();
  rcutils_allocator_t allocator = rcutils_get_default_allocator();

  rmw_ret_t ret = rmw_init_options_init(&init_options, allocator);
  EXPECT_EQ(ret, RMW_RET_OK);
  EXPECT_STREQ(init_options.implementation_identifier, "rmw_ecal_dynamic_cpp");

  rmw_init_options_t dst = rmw_get_zero_initialized_init_options();
  ret = rmw_init_options_copy(&init_options, &dst);
  EXPECT_EQ(ret, RMW_RET_OK);
  EXPECT_STREQ(dst.implementation_identifier, "rmw_ecal_dynamic_cpp");

  EXPECT_EQ(rmw_init_options_fini(&init_options), RMW_RET_OK);
  EXPECT_EQ(rmw_init_options_fini(&dst), RMW_RET_OK);
}
