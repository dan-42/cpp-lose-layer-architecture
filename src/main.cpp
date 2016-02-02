



#include <ip/controller.hpp>
#include <udp/controller.hpp>

int main() {


  ip::controller ip_controller{};
  udp::controller<decltype(ip_controller)> udp_controller{ip_controller};

  udp_controller.init();

  udp_controller.async_receive([](udp::api::udp_message ){ std::cout << "main udp_message received in callback" << std::endl;});

  std::vector<uint8_t> data_to_send;
  udp_controller.send(data_to_send);


  ip_controller.simulate_reveiced_data();

  return 0;
}