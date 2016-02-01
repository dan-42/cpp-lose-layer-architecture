//
// Created by dan on 01.02.16.
//

#ifndef LOSE_LAYER_ARCHITECTURE_CONTROLLER_HPP
#define LOSE_LAYER_ARCHITECTURE_CONTROLLER_HPP


#include <util/util.hpp>

#include <ip/api.hpp>

namespace udp {

 template<typename LowerLayer>
  class controller {
  public:
    controller(LowerLayer& lower_layer) : lower_layer_(lower_layer) {
    }


    virtual ~controller(){}
    void init() {

      lower_layer_.async_receive(
          [](ip::api::fragmented meta_information,     ip::api::binary_data payload) { std::cout << "udp::controller received fragmented message"     << std::endl; },
          [](ip::api::not_fragmented meta_information, ip::api::binary_data payload) { std::cout << "udp::controller received not_fragmented message" << std::endl; }
      );

    }

  private:

    LowerLayer& lower_layer_;
  };
}

#endif //LOSE_LAYER_ARCHITECTURE_CONTROLLER_HPP
