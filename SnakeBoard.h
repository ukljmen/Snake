
#ifndef SNEJK_SNAKEBOARD_H
#define SNEJK_SNAKEBOARD_H

#include<vector>
#include "Field.h"
#include "SnakePart.h"

enum GameState {
    RUNNING, FINISHED
};
enum GameDifficulty {
    NOTSTARTED, HARD, MEDIUM, EASY
};

class SnakeBoard {

public:
    SnakeBoard();

    bool hasFruit(int x, int y);

    bool hasSnake(int x, int y);

    bool isInBoard(int x, int y) const;

    std::vector<SnakePart> getSnakeParts();

    GameState getGameState();

    GameDifficulty getGameDifficulty();

    void turnLeft();

    void turnRight();

    void moveForward();

    void shortenSnake();

    void placeFruit();

    std::pair<int, int> getFruitPosition();

    void checkCollision(int x, int y);

    int getScore() const;

    void setGameDifficulty(int a);


private:
    Field board[13][8];
    int width = 13;
    int height = 8;
    int score;
    GameState state = RUNNING;
    GameDifficulty difficulty;
    std::vector<SnakePart> snak;
    std::pair<int, int> fruitField;

};

#endif //SNEJK_SNAKEBOARD_H