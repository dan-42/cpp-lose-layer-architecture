//
// Created by dan on 01.02.16.
//

#ifndef LOSE_LAYER_ARCHITECTURE_CONTROLLER_HPP
#define LOSE_LAYER_ARCHITECTURE_CONTROLLER_HPP


#include <util/util.hpp>
#include <ip/api.hpp>
#include <udp/api.hpp>

namespace udp {


  namespace detail {
    using namespace udp::api;
    typedef boost::fusion::map<
        boost::fusion::pair<udp_message,      udp_message_received_callback>
    > callback_map_type;
  }



 template<typename LowerLayer>
  class controller {
  public:
    controller(LowerLayer& lower_layer) : lower_layer_(lower_layer) {
    }

    virtual ~controller(){}

    template<typename... Callbacks>
    void async_receive(Callbacks... callbacks) {
      callback_manager.set_callbacks(callbacks...);
    }

    void init() {
      lower_layer_.async_receive(
          [this](ip::api::fragmented meta_information,     ip::api::binary_data payload) {
            std::cout << "udp::controller received fragmented message"     << std::endl;
            api::udp_message msg{};
            this->callback_manager.invoke_callback(msg);
          },
          [](ip::api::not_fragmented meta_information, ip::api::binary_data payload) { std::cout << "udp::controller received not_fragmented message" << std::endl; }
      );
    }

    void send(std::vector<uint8_t> data) {
      uint8_t udp_port_information = 23;
      data.push_back(udp_port_information);
      lower_layer_.send(data);
    }
  private:
    LowerLayer& lower_layer_;
    util::callback_manager<detail::callback_map_type> callback_manager;
  };
}

#endif //LOSE_LAYER_ARCHITECTURE_CONTROLLER_HPP
