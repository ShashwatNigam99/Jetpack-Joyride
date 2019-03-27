#include "main.h"

#ifndef BOOMERANG_H
#define BOOMERANG_H


class Boomerang {
public:
    Boomerang() {}
    Boomerang(float x, float y);
    glm::vec3 position;
    float rotation;
    float speed_x;
    float speed_y;
    float gravity_x;

    void draw(glm::mat4 VP);
    void set_position(float x, float y);

    void tick();
    bounding_box_t return_box();


private:
    VAO *triangle;
};

#endif // FIREBEAM_H
