//
// Created by dan on 01.02.16.
//

#ifndef LOSE_LAYER_ARCHITECTURE_UDP_API_HPP_HPP
#define LOSE_LAYER_ARCHITECTURE_UDP_API_HPP_HPP


#include <vector>
#include <cstdint>
#include <string>
#include <functional>

namespace udp { namespace api {

    struct udp_message {
      int meta_information{0};
    };

    /**
     * not needed directly here, but good to see the calling arguments
     */
    typedef std::function<void(udp_message)>  udp_message_received_callback;

}}



#endif //LOSE_LAYER_ARCHITECTURE_UDP_API_HPP_HPP
