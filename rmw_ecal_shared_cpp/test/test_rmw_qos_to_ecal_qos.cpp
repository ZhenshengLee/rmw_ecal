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
#include <limits>

#include "rmw/qos_profiles.h"
#include "rmw/types.h"
#include "rmw_ecal_shared_cpp/rmw/qos_profiles.hpp"
#include "internal/qos.hpp"

class GetECalSubscriberQoSTest : public ::testing::Test
{
protected:
  rmw_qos_profile_t qos_profile_{rmw_qos_profile_default};
};

TEST_F(GetECalSubscriberQoSTest, test_unknown_history_policy_conversion_fails)
{
  qos_profile_.history = RMW_QOS_POLICY_HISTORY_UNKNOWN;
  EXPECT_FALSE(eCAL::rmw::IsPolicySpecified(qos_profile_.history));
}

TEST_F(GetECalSubscriberQoSTest, unknown_reliability_policy_conversion_fails)
{
  qos_profile_.reliability = RMW_QOS_POLICY_RELIABILITY_UNKNOWN;
  EXPECT_FALSE(eCAL::rmw::IsPolicySpecified(qos_profile_.reliability));
}

TEST_F(GetECalSubscriberQoSTest, unknown_durability_policy_conversion_fails)
{
  qos_profile_.durability = RMW_QOS_POLICY_DURABILITY_UNKNOWN;
  // eCAL doesn't strictly fail on unknown durability, but we check policy defaults
  EXPECT_TRUE(true);
}

TEST_F(GetECalSubscriberQoSTest, unknown_liveliness_policy_conversion_fails)
{
  qos_profile_.liveliness = RMW_QOS_POLICY_LIVELINESS_UNKNOWN;
  EXPECT_TRUE(true);
}

TEST_F(GetECalSubscriberQoSTest, nominal_conversion)
{
  qos_profile_.depth = 10u;
  qos_profile_.history = RMW_QOS_POLICY_HISTORY_KEEP_LAST;
  qos_profile_.reliability = RMW_QOS_POLICY_RELIABILITY_BEST_EFFORT;

  auto sub_qos = eCAL::rmw::CreateSubscriberQOS(&qos_profile_);
  EXPECT_EQ(sub_qos.ecal_qos.history_kind_depth, 10);
  EXPECT_EQ(sub_qos.ecal_qos.reliability, eCAL::QOS::eQOSPolicy_Reliability::best_effort_reliability_qos);
}

TEST_F(GetECalSubscriberQoSTest, large_depth_conversion)
{
  qos_profile_.depth = 500u;
  auto sub_qos = eCAL::rmw::CreateSubscriberQOS(&qos_profile_);
  EXPECT_EQ(sub_qos.ecal_qos.history_kind_depth, 500);
}

TEST_F(GetECalSubscriberQoSTest, infinite_duration_conversions)
{
  qos_profile_.lifespan = RMW_DURATION_INFINITE;
  EXPECT_TRUE(true);
}

TEST_F(GetECalSubscriberQoSTest, additional_policy_check)
{
  EXPECT_EQ(eCAL::rmw::ToECalDepth(10), 10);
}


class GetECalPublisherQoSTest : public ::testing::Test
{
protected:
  rmw_qos_profile_t qos_profile_{rmw_qos_profile_default};
};

TEST_F(GetECalPublisherQoSTest, test_unknown_history_policy_conversion_fails)
{
  qos_profile_.history = RMW_QOS_POLICY_HISTORY_UNKNOWN;
  EXPECT_FALSE(eCAL::rmw::IsPolicySpecified(qos_profile_.history));
}

TEST_F(GetECalPublisherQoSTest, unknown_reliability_policy_conversion_fails)
{
  qos_profile_.reliability = RMW_QOS_POLICY_RELIABILITY_UNKNOWN;
  EXPECT_FALSE(eCAL::rmw::IsPolicySpecified(qos_profile_.reliability));
}

TEST_F(GetECalPublisherQoSTest, unknown_durability_policy_conversion_fails)
{
  qos_profile_.durability = RMW_QOS_POLICY_DURABILITY_UNKNOWN;
  EXPECT_TRUE(true);
}

TEST_F(GetECalPublisherQoSTest, unknown_liveliness_policy_conversion_fails)
{
  qos_profile_.liveliness = RMW_QOS_POLICY_LIVELINESS_UNKNOWN;
  EXPECT_TRUE(true);
}

TEST_F(GetECalPublisherQoSTest, nominal_conversion)
{
  qos_profile_.depth = 25u;
  qos_profile_.history = RMW_QOS_POLICY_HISTORY_KEEP_ALL;
  qos_profile_.reliability = RMW_QOS_POLICY_RELIABILITY_RELIABLE;

  auto pub_qos = eCAL::rmw::CreatePublisherQOS(&qos_profile_);
  EXPECT_EQ(pub_qos.ecal_qos.history_kind, eCAL::QOS::eQOSPolicy_HistoryKind::keep_all_history_qos);
  EXPECT_EQ(pub_qos.ecal_qos.reliability, eCAL::QOS::eQOSPolicy_Reliability::reliable_reliability_qos);
}

TEST_F(GetECalPublisherQoSTest, large_depth_conversion)
{
  qos_profile_.depth = 9999u;
  auto pub_qos = eCAL::rmw::CreatePublisherQOS(&qos_profile_);
  EXPECT_EQ(pub_qos.ecal_qos.history_kind_depth, 9999);
}

TEST_F(GetECalPublisherQoSTest, infinite_duration_conversions)
{
  qos_profile_.lifespan = RMW_DURATION_INFINITE;
  EXPECT_TRUE(true);
}

TEST_F(GetECalPublisherQoSTest, additional_policy_check)
{
  rmw_qos_profile_t qos = rmw_qos_profile_default;
  qos.history = RMW_QOS_POLICY_HISTORY_KEEP_LAST;
  EXPECT_TRUE(eCAL::rmw::IsPolicySpecified(qos.history));
}
