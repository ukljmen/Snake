
#ifndef SNAKE_SNAKEVIEW_H
#define SNAKE_SNAKEVIEW_H

#include "SFML/Graphics.hpp"
#include "SnakeBoard.h"

class SnakeView : public sf::Drawable {
private:
    sf::Text txt;
    sf::Font font;
    SnakeBoard &brd;
    std::vector<SnakePart> vec;
    std::pair<int, int> fField;
    sf::ConvexShape greensq, background;
    sf::ConvexShape Fruit;
public:
    explicit SnakeView(SnakeBoard &p);

    void draw(sf::RenderTarget &target, sf::RenderStates states) const;

    void update_snake();

    void drawwholesnake(sf::RenderWindow &win);

    void drawFruit(sf::RenderWindow &win);

    void update_score();


};


#endif //SNAKE_SNAKEVIEW_H
