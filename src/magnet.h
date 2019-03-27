#include "main.h"

#ifndef MAGNET_H
#define MAGNET_H


class Magnet {
public:
    Magnet() {}
    Magnet(float x, float y);
    glm::vec3 position;
    float rotation;
    void draw(glm::mat4 VP);
    void set_position(float x, float y);

    void tick();
    bounding_box_t return_box();

private:
    VAO *left;
    VAO *right;
};

#endif // MAGNET_H
