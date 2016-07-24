#include "statemachine.h"

#define CATCH_CONFIG_MAIN
#include "catch.hpp"

struct Idle {};
struct Running {};
// struct Start { int value = 0; }; // VS2015 missing NSDMIs for aggregates
struct Start { int value; Start(int value = 0) : value(value) {} };
struct Stop {};
struct Pause {};
struct Resume {};

class TestMachine : public StateMachine<TestMachine, Idle, Running>
{
  int value = 0;

public:

  bool operator==(int other) const { return value == other; }

private:

  friend class Accessor;

  void transition(Idle, Running) {}

  void transition(Running, Idle) {}

  void state(Idle, Start e)
  {
    if (e.value > 0) value = e.value;
    else ++value;
    set_state<Running>();
  }

  void state(Running, Stop)
  {
    set_state<Idle>();
  }

};


TEST_CASE( "Basic tests" ) {

  TestMachine m;
  REQUIRE(m == 0);
  m.process_event<Start>();
  REQUIRE(m == 1);
  m.process_event<Stop>();
  REQUIRE(m == 1);
  m.process_event<Start>();
  REQUIRE(m == 2);
  m.process_event<Stop>();
  REQUIRE(m == 2);

  m.process_event<Start>(10);
  REQUIRE(m == 10);
  m.process_event<Stop>();
  REQUIRE(m == 10);

  REQUIRE_THROWS( m.apply([](Idle) { throw 42; }) );
  REQUIRE_THROWS( m.apply([](auto) { throw 42; }) );
  REQUIRE_THROWS( m.apply([](auto&) { throw 42; }) );
  REQUIRE_THROWS( m.apply([](auto&&) { throw 42; }) );
  REQUIRE_THROWS( m.apply([](const auto&) { throw 42; }) );
  REQUIRE_NOTHROW( m.apply([](Running) { throw 42; }) );

}
