//
// Created by dan on 01.02.16.
//

#ifndef LOSE_LAYER_ARCHITECTURE_UTIL_HPP
#define LOSE_LAYER_ARCHITECTURE_UTIL_HPP


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





#endif //LOSE_LAYER_ARCHITECTURE_UTIL_HPP
