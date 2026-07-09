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
#include <string>

#include "internal/common.hpp"

TEST(GUIDUtilsTest, bad_arguments)
{
  // Test extracting sequence number from short payload
  std::string short_payload = "short";
  // The function expects sequence number at the end, if the payload is shorter than sequence_number_t size (8 bytes),
  // doing math inside GetSequenceDataSize might underflow.
  // We can test behavior with payload of exact minimum size.
  std::string min_payload(sizeof(eCAL::rmw::sequence_number_t), 'x');
  EXPECT_EQ(eCAL::rmw::GetSequenceDataSize(min_payload), 0u);
}

TEST(GUIDUtilsTest, sequence_data_size_and_extract)
{
  std::string payload = "HelloECAL";
  eCAL::rmw::sequence_number_t seq = 12345;
  payload.append(reinterpret_cast<const char *>(&seq), sizeof(seq));

  EXPECT_EQ(eCAL::rmw::GetSequenceDataSize(payload), 9u);
  EXPECT_EQ(eCAL::rmw::GetSequenceNumber(payload), 12345);
}

TEST(GUIDUtilsTest, sequence_number_generation)
{
  auto seq1 = eCAL::rmw::GenerateSequenceNumber();
  auto seq2 = eCAL::rmw::GenerateSequenceNumber();
  EXPECT_LT(seq1, seq2);
  EXPECT_EQ(seq2, seq1 + 1);
}
