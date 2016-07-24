#ifndef STATEMACHINE_H
#define STATEMACHINE_H

#include <stdexcept>
#include <tuple>

template <typename CRTP, typename... States>
class StateMachine
{
public:

  template <typename Event> void process_event(Event&& event = {})
  {
    auto& index = std::get<Index>(states);
    find_type_by_index(index.value, states, [&](auto&& s1) {
      Accessor::invoke_state(*this->crtp(), s1, std::forward<Event>(event));
    });
  }

  template <typename Event, typename... Ts> void process_event(Ts... args)
  {
    process_event(Event{std::forward<Ts>(args)...});
  }

  struct invoke_helper {
    template <typename F, typename... Ts>

    static auto invoke_if(F&& f, Ts&&... args) ->
      typename std::enable_if<true, decltype( f(std::forward<Ts>(args)...))>::type
    {
      return f(std::forward<Ts>(args)...);
    }

    static auto invoke_if(...) -> void
    {
    }
  };

  template <typename F>
  void apply(F&& callback)
  {
    find_type_by_index(std::get<Index>(states).value, states, [&](auto&& s) {
      invoke_helper::invoke_if(std::forward<F>(callback),s);
    });
  }

protected:

  template <typename State> void set_state() noexcept
  {
    auto& index = std::get<Index>(states);
    find_type_by_index(index.value, states, [&](auto&& s1) {
      Accessor::invoke_transition(*this->crtp(), s1, std::get<State>(states));
    });
    index.value = index_of<State, States...>::value;
  }

  class Accessor
  {
  private:
    friend class StateMachine;

    template <typename... Args>
    static auto invoke_state(CRTP& self, Args&&... args) ->
      decltype( self.state(std::forward<Args>(args)...) )
    {
      return self.state(std::forward<Args>(args)...);
    }

    static void invoke_state(...) noexcept
    {
    }

    template <typename... Args>
    static auto invoke_transition(CRTP& self, Args&&... args) ->
      decltype( self.transition(std::forward<Args>(args)...) )
    {
      return self.transition(std::forward<Args>(args)...);
    }

    static void invoke_transition(...)
    {
      throw std::logic_error("Invalid state transition");
    }
  };

private:

  template <typename ...> struct index_of;

  template <typename T, typename... Ts>
  struct index_of<T, T, Ts...>
  {
    static constexpr const std::size_t value = 0;
  };

  template <typename T, typename T1, typename... Ts>
  struct index_of<T, T1, Ts...> : index_of<T, Ts...> {
    static constexpr const std::size_t value = index_of<T, Ts...>::value + 1;
  };

  template <std::size_t I, std::size_t N>
  struct find_type_by_index_helper
  {
    template <typename Tuple, typename F>
    static void invoke(std::size_t index, Tuple&& values, F&& callback)
    {
      if (index == I) callback(std::get<I>(std::forward<Tuple>(values)));
      else find_type_by_index_helper<I+1, N>::invoke(index, std::forward<Tuple>(values), std::forward<F>(callback));
    }
  };

  template <std::size_t N>
  struct find_type_by_index_helper<N, N>
  {
    template <typename Tuple, typename F>
    static void invoke(std::size_t, Tuple&&, F)
    {
    }
  };

  template <typename Tuple, typename Fn>
  void find_type_by_index(std::size_t index, Tuple&& values, Fn&& callback)
  {
    using helper = find_type_by_index_helper<0, std::tuple_size<typename std::decay<Tuple>::type>::value>;
    helper::invoke(index, std::forward<Tuple>(values), std::forward<Fn>(callback));
  }

  struct Index {
    std::size_t value = 0;
  };

  std::tuple<States..., Index> states;

  CRTP* crtp() noexcept { return static_cast<CRTP*>(this); }

};

#endif
