
#ifndef SNEJK_SNAKEPART_H
#define SNEJK_SNAKEPART_H

enum Direction {
    up, down, left, right
};

struct SnakePart {
    int xP;
    int yP;
    Direction dir;
};


#endif //SNEJK_SNAKEPART_H