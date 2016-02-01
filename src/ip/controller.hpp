//
// Created by dan on 01.02.16.
//

#ifndef LOSE_LAYER_ARCHITECTURE_IP_CONTROLLER_HPP
#define LOSE_LAYER_ARCHITECTURE_IP_CONTROLLER_HPP

#include <util/util.hpp>

#include <ip/api.hpp>

namespace ip {


  namespace detail {
    using namespace ip::api;
    typedef boost::fusion::map<
        boost::fusion::pair<fragmented,      fragmented_received_callback>,
        boost::fusion::pair<not_fragmented,  not_fragmented_received_callback>,
        boost::fusion::pair<last_fragmented, last_fragmented_callback>
    > callback_map_type;
  }

  class controller {
  public:
    controller(){};
    virtual ~controller(){}


    void init() {

    }

    template<typename... Callbacks>
    void async_receive(Callbacks... callbacks) {
      callback_manager.set_callbacks(callbacks...);
    }

    void simulate_reveiced_data() {
      api::fragmented fragmented;
      api::binary_data payload;

      callback_manager.invoke_callback(fragmented, payload);
    }

  private:
    util::callback_manager<detail::callback_map_type> callback_manager;
  };
}

#endif //LOSE_LAYER_ARCHITECTURE_CONTROLLER_HPP
