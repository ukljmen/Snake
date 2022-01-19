#include <iostream>
#include <cstring>
#include "SnakeView.h"
#include <sstream>

SnakeView::SnakeView(SnakeBoard &p) : brd(p) {
    update_snake();

    if (!font.loadFromFile("arial.ttf")) {
        std::cerr << strerror(errno) << std::endl;
        abort();
    }
    txt.setFont(font);
    txt.setPosition(300, 5);

    background.setPointCount(4);
    background.setPoint(0, sf::Vector2f(50.f, 50.f));
    background.setPoint(1, sf::Vector2f(700.f, 50.f));
    background.setPoint(2, sf::Vector2f(700.f, 450.f));
    background.setPoint(3, sf::Vector2f(50.f, 450.f));
    background.setFillColor(sf::Color::Blue);

    greensq.setPointCount(4);
    greensq.setPoint(0, sf::Vector2f(0.f, 0.f));
    greensq.setPoint(1, sf::Vector2f(50.f, 0.f));
    greensq.setPoint(2, sf::Vector2f(50.f, 50.f));
    greensq.setPoint(3, sf::Vector2f(0.f, 50.f));
    greensq.setFillColor(sf::Color::Green);

    Fruit.setPointCount(8);
    Fruit.setPoint(0, sf::Vector2f(20.f, 10.f));
    Fruit.setPoint(1, sf::Vector2f(30.f, 10.f));
    Fruit.setPoint(2, sf::Vector2f(40.f, 20.f));
    Fruit.setPoint(3, sf::Vector2f(40.f, 30.f));
    Fruit.setPoint(4, sf::Vector2f(30.f, 40.f));
    Fruit.setPoint(5, sf::Vector2f(20.f, 40.f));
    Fruit.setPoint(6, sf::Vector2f(10.f, 30.f));
    Fruit.setPoint(7, sf::Vector2f(10.f, 20.f));
    Fruit.setFillColor(sf::Color::Red);

}

void SnakeView::draw(sf::RenderTarget &target, sf::RenderStates states) const {
    target.draw(greensq, states);

}

void SnakeView::drawwholesnake(sf::RenderWindow &win) {
    win.draw(background);
    for (auto &i : vec) {
        win.draw(greensq);
        greensq.setPosition((i.xP * 50) + 50, (i.yP * 50) + 50);
    }
    update_score();
    win.draw(txt);

}

void SnakeView::update_snake() {
    vec = brd.getSnakeParts();
    fField = brd.getFruitPosition();

}

void SnakeView::drawFruit(sf::RenderWindow &win) {
    win.draw(Fruit);
    Fruit.setPosition(fField.first * 50 + 50, fField.second * 50 + 50);

}

void SnakeView::update_score() {
    std::stringstream ss;
    ss << brd.getScore();
    std::string s = ss.str();
    txt.setString("score: " + s);
}

