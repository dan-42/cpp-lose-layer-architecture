

#include <iostream>

#include <vector>
#include <functional>

#include <boost/fusion/container.hpp>
#include <boost/fusion/sequence.hpp>
#include <boost/fusion/algorithm.hpp>



namespace util {

  template<typename F>
  struct function_traits : public function_traits<decltype(&F::operator())> {
  };

  template<typename ClassType, typename ReturnType, typename... Args>
  struct function_traits<ReturnType(ClassType::*)(Args...) const> {
    enum {
      arity = sizeof...(Args)
    };

    using result_type = ReturnType;

    using function_type = std::function<ReturnType(Args...)>;

  private:
    template<size_t i>
    struct arg_ {
      typedef typename std::tuple_element<i, std::tuple<Args...>>::type type;
    };

  public:
    template<size_t i>
    using arg = typename arg_<i>::type;
  };

  template<typename F, typename... Ts>
  F for_each_args(F f, Ts&&... a) {
    return std::initializer_list<int>{(std::ref(f)(std::forward<Ts>(a)),0)...}, f;
  }



  template<typename CallbackFusionMap>
  struct callback_manager {

    template<typename... Callbacks>
    void set_callbacks(Callbacks... callbacks) {
      util::for_each_args([this](auto callback ) {
        typedef util::function_traits<decltype(callback)> callback_traits;
        typedef typename callback_traits::template arg<0> arg_0_t;
        boost::fusion::at_key<arg_0_t>(callback_map) = callback;
      }, callbacks...);
    }

    template<typename Service, typename... Args>
    void invoke_callback(const Service &service, Args... args) {
      if(!boost::fusion::at_key<Service>(callback_map)) {
        std::cerr << " no callback set: " << typeid(Service).name() << std::endl;
        return;
      }
      boost::fusion::at_key<Service>(callback_map)(service, args...);
    }

  private:
    CallbackFusionMap callback_map;
  };


} /*namespace util*/


typedef std::vector<uint8_t > binary_data;




namespace layer_1 {
  namespace api {
    struct who_is {   };
    struct i_am {  };
    struct unused { };

    typedef std::function<void(who_is, binary_data)> who_is_received_callback;
    typedef std::function<void(i_am, binary_data)> i_am_received_callback;
    typedef std::function<void(unused)> unused_callback;
  }

  namespace detail {

    using namespace layer_1::api;

    typedef boost::fusion::map<
      boost::fusion::pair<who_is, who_is_received_callback>,
      boost::fusion::pair<i_am,   i_am_received_callback>,
      boost::fusion::pair<unused, unused_callback>
    > callback_map_type;

  }
}

int main() {

  util::callback_manager<layer_1::detail::callback_map_type> cm{};

  auto handle_who_is = [](layer_1::api::who_is wi, binary_data ) { std::cout << "got a who_is " << std::endl; };
  auto handle_i_am   = [](layer_1::api::i_am ia,   binary_data ) { std::cout << "got a i_am " << std::endl; };

  cm.set_callbacks(handle_who_is, handle_i_am);

  layer_1::api::who_is wi{};
  cm.invoke_callback(wi, binary_data{});

  layer_1::api::i_am ia{};
  cm.invoke_callback(ia, binary_data{});

  layer_1::api::unused unused{};
  cm.invoke_callback(unused);

  std::cout << "Hello, World!" << std::endl;
  return 0;
}