
#include <SFML/Graphics.hpp>
#include "SnakeBoard.h"
#include "SnakeView.h"
#include "Welcome.h"

int main() {

    sf::RenderWindow win(sf::VideoMode(750, 500), "Snake Game");

    SnakeBoard snake;
    SnakeView sv(snake);
    Welcome wlc(snake);

    sf::Event event;
    sf::Clock clk;
    int eventcontainer;

    while (win.isOpen()) {


        while (win.pollEvent(event)) {
            if (event.type == sf::Event::Closed) { win.close(); }


            if (snake.getGameState() == FINISHED) {
                goto finished;
            }

            if (snake.getGameDifficulty() == NOTSTARTED) {
                win.clear(sf::Color(80, 0, 80));
                wlc.display_setup(win);
                if (event.type == sf::Event::MouseButtonPressed) {
                    if (event.mouseButton.x > 100 && event.mouseButton.x < 250 && event.mouseButton.y > 250 &&
                        event.mouseButton.y < 350) {
                        snake.setGameDifficulty(1);
                    }
                    if (event.mouseButton.x > 300 && event.mouseButton.x < 450 && event.mouseButton.y > 250 &&
                        event.mouseButton.y < 350) {
                        snake.setGameDifficulty(2);
                    }
                    if (event.mouseButton.x > 500 && event.mouseButton.x < 650 && event.mouseButton.y > 250 &&
                        event.mouseButton.y < 350) {
                        snake.setGameDifficulty(3);
                    }
                }

                goto exit2;
            }

            if (event.type == sf::Event::KeyReleased) {

                if (event.key.code == 71) {
                    eventcontainer = 71;
                }
                if (event.key.code == 72) {
                    eventcontainer = 72;
                }
            }
        }
        if (snake.getGameDifficulty() == NOTSTARTED) {
            goto exit;
        }

        if (clk.getElapsedTime().asSeconds() > 0.5 * snake.getGameDifficulty()) {
            switch (eventcontainer) {

                case 71:
                    snake.turnLeft();
                    eventcontainer = 0;
                    sv.update_snake();
                    clk.restart();
                    break;

                case 72:
                    snake.turnRight();
                    eventcontainer = 0;
                    sv.update_snake();
                    clk.restart();
                    break;

                default:
                    snake.moveForward();
                    eventcontainer = 1;
                    sv.update_snake();
                    clk.restart();
                    break;
            }

        }
        win.clear(sf::Color(80, 0, 80));

        sv.drawwholesnake(win);
        sv.drawFruit(win);

        finished:
        if (snake.getGameState() == FINISHED) {
            wlc.display_gameover(win);
        }

        exit:
        exit2:

        win.display();
    }

    return 0;
}
