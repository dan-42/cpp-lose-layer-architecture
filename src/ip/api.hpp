//
// Created by dan on 01.02.16.
//

#ifndef LOSE_LAYER_ARCHITECTURE_IP_API_HPP
#define LOSE_LAYER_ARCHITECTURE_IP_API_HPP

#include <vector>
#include <cstdint>
#include <string>
#include <functional>

namespace ip { namespace api {

    typedef std::vector<uint8_t > binary_data;

    struct not_fragmented {
      int meta_information{0};
    };

    struct fragmented {
      double meta_information{0.0};
    };

    struct last_fragmented {
      std::string  meta_information;
    };

    /**
     * not needed directly here, but good to see the calling arguments
     */
    typedef std::function<void(not_fragmented, binary_data)>  not_fragmented_received_callback;
    typedef std::function<void(fragmented, binary_data)>      fragmented_received_callback;
    typedef std::function<void(last_fragmented)>              last_fragmented_callback;
}}

#endif //LOSE_LAYER_ARCHITECTURE_IP_API_HPP
