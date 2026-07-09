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

#include "rcutils/logging.h"
#include "rmw/error_handling.h"

TEST(TestLogging, rmw_logging)
{
  EXPECT_EQ(rcutils_logging_initialize(), RCUTILS_RET_OK);
  EXPECT_EQ(rcutils_logging_set_logger_level("rmw_ecal_shared_cpp", RCUTILS_LOG_SEVERITY_DEBUG), RCUTILS_RET_OK);
  EXPECT_EQ(rcutils_logging_set_logger_level("rmw_ecal_shared_cpp", RCUTILS_LOG_SEVERITY_INFO), RCUTILS_RET_OK);
  EXPECT_EQ(rcutils_logging_set_logger_level("rmw_ecal_shared_cpp", RCUTILS_LOG_SEVERITY_WARN), RCUTILS_RET_OK);
  EXPECT_EQ(rcutils_logging_set_logger_level("rmw_ecal_shared_cpp", RCUTILS_LOG_SEVERITY_ERROR), RCUTILS_RET_OK);
  EXPECT_EQ(rcutils_logging_set_logger_level("rmw_ecal_shared_cpp", RCUTILS_LOG_SEVERITY_FATAL), RCUTILS_RET_OK);
  EXPECT_EQ(rcutils_logging_shutdown(), RCUTILS_RET_OK);
}

TEST(TestLogging, rmw_logging_bad_verbosity)
{
  EXPECT_EQ(rcutils_logging_initialize(), RCUTILS_RET_OK);
  rcutils_ret_t ret = rcutils_logging_set_logger_level(
    "rmw_ecal_shared_cpp", static_cast<int>(RCUTILS_LOG_SEVERITY_FATAL + 1));
  EXPECT_EQ(ret, RCUTILS_RET_INVALID_ARGUMENT);
  EXPECT_EQ(rcutils_logging_shutdown(), RCUTILS_RET_OK);
}


