
#include <iostream>
#include<cstdlib>
#include<ctime>
#include <fstream>
#include "SnakeBoard.h"

SnakeBoard::SnakeBoard() {
    score = 0;
    snak.push_back({3, 4, left});
    this->board[3][4].hasSnake = true;
    snak.push_back({4, 4, left});
    this->board[4][4].hasSnake = true;

    snak.push_back({5, 4, left});
    this->board[5][4].hasSnake = true;

    snak.push_back({6, 4, right});
    this->board[6][4].hasSnake = true;

    difficulty = NOTSTARTED;

    placeFruit();
}

bool SnakeBoard::hasFruit(int x, int y) {
    return board[x][y].hasFruit;
}

bool SnakeBoard::hasSnake(int x, int y) {
    return board[x][y].hasSnake;
}

bool SnakeBoard::isInBoard(int x, int y) const {
    if (x >= 0 && x < width && y >= 0 && y < height) {
        return true;
    } else return false;
}

std::vector<SnakePart> SnakeBoard::getSnakeParts() {
    return snak;
}

GameState SnakeBoard::getGameState() {
    return this->state;
}

GameDifficulty SnakeBoard::getGameDifficulty() {
    return difficulty;
};

void SnakeBoard::turnLeft() {
    int newx, newy;
    Direction newdir;
    if (snak[snak.size() - 1].dir == up) {
        newx = snak[snak.size() - 1].xP - 1;
        newy = snak[snak.size() - 1].yP;
        newdir = left;
    }
    if (snak[snak.size() - 1].dir == down) {
        newx = snak[snak.size() - 1].xP + 1;
        newy = snak[snak.size() - 1].yP;
        newdir = right;
    }
    if (snak[snak.size() - 1].dir == left) {
        newx = snak[snak.size() - 1].xP;
        newy = snak[snak.size() - 1].yP + 1;
        newdir = down;
    }
    if (snak[snak.size() - 1].dir == right) {
        newx = snak[snak.size() - 1].xP;
        newy = snak[snak.size() - 1].yP - 1;
        newdir = up;
    }
    checkCollision(newx, newy);
    if (state == RUNNING) {
        this->snak.push_back({newx, newy, newdir});
        board[newx][newy].hasSnake = true;
        if (hasFruit(newx, newy) == true) {
            board[newx][newy].hasFruit = false;
            placeFruit();
            score++;
        } else {
            shortenSnake();
        }
    }

}

void SnakeBoard::turnRight() {
    int newx, newy;
    Direction newdir;
    if (snak[snak.size() - 1].dir == up) {
        newx = snak[snak.size() - 1].xP + 1;
        newy = snak[snak.size() - 1].yP;
        newdir = right;
    }
    if (snak[snak.size() - 1].dir == down) {
        newx = snak[snak.size() - 1].xP - 1;
        newy = snak[snak.size() - 1].yP;
        newdir = left;
    }
    if (snak[snak.size() - 1].dir == left) {
        newx = snak[snak.size() - 1].xP;
        newy = snak[snak.size() - 1].yP - 1;
        newdir = up;
    }
    if (snak[snak.size() - 1].dir == right) {
        newx = snak[snak.size() - 1].xP;
        newy = snak[snak.size() - 1].yP + 1;
        newdir = down;
    }

    checkCollision(newx, newy);
    if (state == RUNNING) {
        this->snak.push_back({newx, newy, newdir});
        board[newx][newy].hasSnake = true;
        if (hasFruit(newx, newy) == true) {
            board[newx][newy].hasFruit = false;
            placeFruit();
            score++;
        } else {
            shortenSnake();
        }
    }

}

void SnakeBoard::moveForward() {
    int newx, newy;
    Direction newdir = this->snak[snak.size() - 1].dir;
    if (snak[snak.size() - 1].dir == up) {
        newx = snak[snak.size() - 1].xP;
        newy = snak[snak.size() - 1].yP - 1;
    }
    if (snak[snak.size() - 1].dir == down) {
        newx = snak[snak.size() - 1].xP;
        newy = snak[snak.size() - 1].yP + 1;
    }
    if (snak[snak.size() - 1].dir == left) {
        newx = snak[snak.size() - 1].xP - 1;
        newy = snak[snak.size() - 1].yP;
    }
    if (snak[snak.size() - 1].dir == right) {
        newx = snak[snak.size() - 1].xP + 1;
        newy = snak[snak.size() - 1].yP;
    }
    if (state == RUNNING) { checkCollision(newx, newy); }
    if (state == RUNNING) {
        this->snak.push_back({newx, newy, newdir});
        board[newx][newy].hasSnake = true;
        if (hasFruit(newx, newy) == true) {
            board[newx][newy].hasFruit = false;
            placeFruit();
            score++;
        } else {
            shortenSnake();
        }
    }
}

void SnakeBoard::shortenSnake() {
    board[snak[0].xP][snak[0].yP].hasSnake = false;
    snak.erase(snak.begin());

}

void SnakeBoard::placeFruit() {
    srand(time(NULL));
    int i = 0, x, y;
    while (i < 1) {
        x = rand() % 13;
        y = rand() % 8;

        if (board[x][y].hasSnake == false) {
            i++;
        }
    }
    board[x][y].hasFruit = true;
    fruitField.first = x;
    fruitField.second = y;


}

std::pair<int, int> SnakeBoard::getFruitPosition() {
    return fruitField;
}

void SnakeBoard::checkCollision(int x, int y) {
    if (hasSnake(x, y) == true || isInBoard(x, y) == false) {
        state = FINISHED;
        std::fstream file;
        file.open("scores.txt", std::ios::out | std::ios::app);
        file << score << std::endl;
        file.close();
    }

}

int SnakeBoard::getScore() const {
    return score;
}

void SnakeBoard::setGameDifficulty(int a) {
    if (a == 1) difficulty = EASY;
    if (a == 2) difficulty = MEDIUM;
    if (a == 3) difficulty = HARD;

}






