



#include <ip/controller.hpp>
#include <udp/controller.hpp>

int main() {


  ip::controller ip_controller{};
  udp::controller<decltype(ip_controller)> udp_controller{ip_controller};

  udp_controller.init();




  ip_controller.simulate_reveiced_data();

  return 0;
}