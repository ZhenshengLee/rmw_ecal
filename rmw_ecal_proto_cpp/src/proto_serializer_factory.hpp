// Copyright 2020 Continental AG
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

#pragma once

#include <rmw_ecal_shared_cpp/serializer_factory.hpp>

#include "serialization/proto_serializer.hpp"
#include "serialization/proto_deserializer.hpp"

#include "common.hpp"

#include "../../rmw_ecal_dynamic_cpp/src/custom_serializer_factory.hpp"

namespace eCAL
{
  namespace rmw
  {
    class ProtoSerializerFactory : public SerializerFactory
    {
      Serializer *CreateSerializer(const rosidl_message_type_support_t *type_support) const override
      {
        auto *proto_ts = GetTypeSupport(type_support);
        if (proto_ts != nullptr)
        {
          return new ProtoSerializer{proto_ts};
        }
        return CustomSerializerFactory{}.CreateSerializer(type_support);
      }

      Deserializer *CreateDeserializer(const rosidl_message_type_support_t *type_support) const override
      {
        auto *proto_ts = GetTypeSupport(type_support);
        if (proto_ts != nullptr)
        {
          return new ProtoDeserializer{proto_ts};
        }
        return CustomSerializerFactory{}.CreateDeserializer(type_support);
      }
    };
  } // namespace rmw
} // namespace eCAL