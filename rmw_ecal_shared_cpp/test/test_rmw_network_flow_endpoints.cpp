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

#include "rmw/get_network_flow_endpoints.h"
#include "rmw_ecal_shared_cpp/rmw/get_network_flow_endpoints.hpp"

TEST(TestRmwNetworkFlowEndpoints, NetworkFlowEndpointsCheck)
{
  rcutils_allocator_t allocator = rcutils_get_default_allocator();
  rmw_network_flow_endpoint_array_t network_flow_endpoint_array =
    rmw_get_zero_initialized_network_flow_endpoint_array();

  rmw_ret_t ret = eCAL::rmw::rmw_publisher_get_network_flow_endpoints(
    nullptr, &allocator, &network_flow_endpoint_array);
  EXPECT_EQ(ret, RMW_RET_UNSUPPORTED);

  ret = eCAL::rmw::rmw_subscription_get_network_flow_endpoints(
    nullptr, &allocator, &network_flow_endpoint_array);
  EXPECT_EQ(ret, RMW_RET_UNSUPPORTED);
}
