#include <iostream>
#include "doctest.h"
#include "sources/player.hpp"
#include "sources/game.hpp"
#include "sources/card.hpp"
#include <stdexcept>

using namespace std;
using namespace ariel;

TEST_CASE("Test1 - newGame"){
    Player p1("Avraham");
    Player p2 ("Balestin");

    Game game(p1, p2);

    CHECK(p1.stacksize() == 26);
    CHECK(p2.stacksize() == 26);
}

TEST_CASE("Test2 - endGame"){
    Player p1("Avraham");
    Player p2("Balestin");

    Game game(p1, p2);

    game.playAll();

    CHECK(p1.stacksize() == 0);
    CHECK(p2.stacksize() == 0);
}

TEST_CASE("Test3 - endGame"){
    Player p1("Avraham");
    Player p2("Balestin");

    Game game(p1, p2);

    game.playAll();

    CHECK(p1.cardesTaken() + p2.cardesTaken() == 52);
}

TEST_CASE("Test4 - notThrows"){
    Player p1("Avraham");
    Player p2("Balestin");

    Game game(p1, p2);

    game.playTurn();
    CHECK_NOTHROW(game.printLastTurn());
}

TEST_CASE("Test5 - notThrows"){
    Player p1("Avraham");
    Player p2("Balestin");

    Game game(p1, p2);

    game.playTurn();
    game.playTurn();
    CHECK_NOTHROW(game.printLog());
}

TEST_CASE("Test6 - notThrows"){
    Player p1("Avraham");
    Player p2("Balestin");

    Game game(p1, p2);

    game.playTurn();
    game.playTurn();
    CHECK_NOTHROW(game.printStats());
}

TEST_CASE("Test7 - notThrows"){
    Player p1("Avraham");
    Player p2("Balestin");
    Game game(p1, p2);
    game.playAll();
    CHECK_NOTHROW(game.printWiner());
}

TEST_CASE("Test8 - newGame"){
    Player p1("Avraham");
    Player p2 ("Balestin");

    Game game(p1, p2);
    CHECK(p1.cardesTaken() == 0);
    CHECK(p2.cardesTaken() == 0);
}

TEST_CASE("Test9 - newGame"){
    Player p1("Avraham");
    Player p2 ("Balestin");

    Game game(p1, p2);

    CHECK(p1.cardesTaken() == 0);
    CHECK(p2.cardesTaken() == 0);
    game.playTurn();
    CHECK(p1.stacksize()<52);
    CHECK(p2.stacksize()<52);
}

TEST_CASE("Test10 - isVoid"){
    Player p1("Avraham");
    Player p2 ("Balestin");

    Game game(p1, p2);

    CHECK(std::is_void<decltype(game.playAll())>::value);
    CHECK(std::is_void<decltype(game.playTurn())>::value);
    CHECK(std::is_void<decltype(game.printLastTurn())>::value);
    CHECK(std::is_void<decltype(game.printLog())>::value);
    CHECK(std::is_void<decltype(game.printStats())>::value);
    CHECK(std::is_void<decltype(game.printWiner())>::value);
}
