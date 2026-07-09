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

#include "rmw/qos_profiles.h"
#include "rmw/types.h"
#include "rmw_ecal_shared_cpp/rmw/qos_profiles.hpp"

TEST(TestQoSProfileCheckCompatible, compatible)
{
  rmw_qos_profile_t qos_profile = rmw_qos_profile_default;
  rmw_qos_compatibility_type_t compatibility = RMW_QOS_COMPATIBILITY_ERROR;
  char reason[1024] = {0};

  rmw_ret_t ret = eCAL::rmw::rmw_qos_profile_check_compatible(
    qos_profile, qos_profile, &compatibility, reason, sizeof(reason));

  EXPECT_EQ(ret, RMW_RET_OK);
  EXPECT_EQ(compatibility, RMW_QOS_COMPATIBILITY_OK);
}

TEST(TestQoSProfileCheckCompatible, incompatible)
{
  rmw_qos_profile_t pub_profile = rmw_qos_profile_default;
  pub_profile.avoid_ros_namespace_conventions = false;

  rmw_qos_profile_t sub_profile = rmw_qos_profile_default;
  sub_profile.avoid_ros_namespace_conventions = true;

  rmw_qos_compatibility_type_t compatibility = RMW_QOS_COMPATIBILITY_OK;
  char reason[1024] = {0};

  rmw_ret_t ret = eCAL::rmw::rmw_qos_profile_check_compatible(
    pub_profile, sub_profile, &compatibility, reason, sizeof(reason));

  EXPECT_EQ(ret, RMW_RET_OK);
  // eCAL compatibility check returns error if avoid_ros_namespace_conventions mismatch
  EXPECT_EQ(compatibility, RMW_QOS_COMPATIBILITY_ERROR);
}

TEST(TestQoSProfileCheckCompatible, warn_compatible)
{
  rmw_qos_profile_t pub_profile = rmw_qos_profile_default;
  rmw_qos_profile_t sub_profile = rmw_qos_profile_default;
  // eCAL doesn't check reliability mismatch for warnings, it defaults to OK.
  // We customize this test to check eCAL's specific behavior.
  sub_profile.reliability = RMW_QOS_POLICY_RELIABILITY_UNKNOWN;

  rmw_qos_compatibility_type_t compatibility = RMW_QOS_COMPATIBILITY_ERROR;
  char reason[1024] = {0};

  rmw_ret_t ret = eCAL::rmw::rmw_qos_profile_check_compatible(
    pub_profile, sub_profile, &compatibility, reason, sizeof(reason));

  EXPECT_EQ(ret, RMW_RET_OK);
  EXPECT_EQ(compatibility, RMW_QOS_COMPATIBILITY_OK);
}

TEST(TestQoSProfileCheckCompatible, invalid_arguments)
{
  rmw_qos_profile_t qos_profile = rmw_qos_profile_default;
  char reason[1024] = {0};

  rmw_ret_t ret = eCAL::rmw::rmw_qos_profile_check_compatible(
    qos_profile, qos_profile, nullptr, reason, sizeof(reason));
  EXPECT_EQ(ret, RMW_RET_INVALID_ARGUMENT);
}
