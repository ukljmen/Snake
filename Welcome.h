
#include<SFML/Graphics.hpp>
#include "SnakeBoard.h"

#ifndef SNAKE_WELCOME_H
#define SNAKE_WELCOME_H


class Welcome {

private:
    SnakeBoard &wbrd;
    sf::Text title, choose, d1, d2, d3, finalScore;
    sf::Font fontey;
    sf::ConvexShape tile;
public:
    explicit Welcome(SnakeBoard &o);

    void display_setup(sf::RenderWindow &win);

    void display_gameover(sf::RenderWindow &win);

};


#endif //SNAKE_WELCOME_H
