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

#include "rmw_ecal_shared_cpp/rmw/event.hpp"

#include "internal/common.hpp"
#include "internal/publisher.hpp"
#include "internal/subscriber.hpp"

namespace eCAL
{
  namespace rmw
  {

    rmw_ret_t rmw_publisher_event_init(const char *implementation_identifier,
                                       rmw_event_t *rmw_event,
                                       const rmw_publisher_t *publisher,
                                       rmw_event_type_t event_type)
    {
      RMW_CHECK_ARGUMENT_FOR_NULL(rmw_event, RMW_RET_INVALID_ARGUMENT);
      RMW_CHECK_ARGUMENT_FOR_NULL(publisher, RMW_RET_INVALID_ARGUMENT);
      CHECK_RMW_IMPLEMENTATION(implementation_identifier, publisher);

      auto *impl = GetImplementation(publisher);
      Event *event_listener = nullptr;
      switch (event_type)
      {
      case rmw_event_type_t::RMW_EVENT_OFFERED_DEADLINE_MISSED:
        event_listener = &impl->GetDataDroppedEventListener();
        break;
      case rmw_event_type_t::RMW_EVENT_OFFERED_QOS_INCOMPATIBLE:
        event_listener = &impl->GetQosIncompatibleEventListener();
        break;
      case rmw_event_type_t::RMW_EVENT_PUBLISHER_INCOMPATIBLE_TYPE:
        event_listener = &impl->GetIncompatibleTypeEventListener();
        break;
      case rmw_event_type_t::RMW_EVENT_PUBLICATION_MATCHED:
        event_listener = &impl->GetMatchedEventListener();
        break;
      case rmw_event_type_t::RMW_EVENT_LIVELINESS_LOST:
        event_listener = &impl->GetLivelinessLostEventListener();
        break;
      default:
        return RMW_RET_UNSUPPORTED;
      }

      rmw_event->event_type = event_type;
      rmw_event->implementation_identifier = implementation_identifier;
      rmw_event->data = event_listener;

      return RMW_RET_OK;
    }

    rmw_ret_t rmw_subscription_event_init(const char *implementation_identifier,
                                          rmw_event_t *rmw_event,
                                          const rmw_subscription_t *subscription,
                                          rmw_event_type_t event_type)
    {
      RMW_CHECK_ARGUMENT_FOR_NULL(rmw_event, RMW_RET_INVALID_ARGUMENT);
      RMW_CHECK_ARGUMENT_FOR_NULL(subscription, RMW_RET_INVALID_ARGUMENT);
      CHECK_RMW_IMPLEMENTATION(implementation_identifier, subscription);

      auto *impl = GetImplementation(subscription);
      Event *event_listener = nullptr;
      switch (event_type)
      {
      case rmw_event_type_t::RMW_EVENT_REQUESTED_DEADLINE_MISSED:
        event_listener = &impl->GetDataDroppedEventListener();
        break;
      case rmw_event_type_t::RMW_EVENT_REQUESTED_QOS_INCOMPATIBLE:
        event_listener = &impl->GetQosIncompatibleEventListener();
        break;
      case rmw_event_type_t::RMW_EVENT_SUBSCRIPTION_INCOMPATIBLE_TYPE:
        event_listener = &impl->GetIncompatibleTypeEventListener();
        break;
      case rmw_event_type_t::RMW_EVENT_SUBSCRIPTION_MATCHED:
        event_listener = &impl->GetMatchedEventListener();
        break;
      case rmw_event_type_t::RMW_EVENT_LIVELINESS_CHANGED:
        event_listener = &impl->GetLivelinessChangedEventListener();
        break;
      case rmw_event_type_t::RMW_EVENT_MESSAGE_LOST:
        event_listener = &impl->GetMessageLostEventListener();
        break;
      default:
        return RMW_RET_UNSUPPORTED;
      }

      rmw_event->event_type = event_type;
      rmw_event->implementation_identifier = implementation_identifier;
      rmw_event->data = event_listener;

      return RMW_RET_OK;
    }

    rmw_ret_t rmw_take_event(const char *implementation_identifier,
                             const rmw_event_t *event_handle,
                             void * /* event_info */,
                             bool *taken)
    {
      RMW_CHECK_ARGUMENT_FOR_NULL(event_handle, RMW_RET_INVALID_ARGUMENT);
      RMW_CHECK_ARGUMENT_FOR_NULL(taken, RMW_RET_INVALID_ARGUMENT);
      CHECK_RMW_IMPLEMENTATION(implementation_identifier, event_handle);

      auto ecal_event = GetImplementation(event_handle);
      *taken = ecal_event->TakeTriggered();

      return RMW_RET_OK;
    }

    rmw_ret_t rmw_event_fini(const char *implementation_identifier, rmw_event_t *event)
    {
      RMW_CHECK_ARGUMENT_FOR_NULL(event, RMW_RET_INVALID_ARGUMENT);
      CHECK_RMW_IMPLEMENTATION(implementation_identifier, event);

      event->event_type = rmw_event_type_t::RMW_EVENT_INVALID;
      event->implementation_identifier = nullptr;
      delete GetImplementation(event);

      return RMW_RET_OK;
    }

  } // namespace rmw
} // namespace eCAL
