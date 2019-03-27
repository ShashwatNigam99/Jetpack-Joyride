#include "main.h"

#ifndef COIN_H
#define COIN_H


class Coin {
public:
    Coin() {}
    Coin(float x, float y, color_t color,int special);
    glm::vec3 position;
    float rotation;
    int special;
    void draw(glm::mat4 VP);
    void set_position(float x, float y);

    void tick();
    bounding_box_t return_box();

private:
    VAO *object;
};

#endif // COIN_H
