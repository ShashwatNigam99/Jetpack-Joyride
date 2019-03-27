#include "main.h"

#ifndef FIRELINES_H
#define FIRELINES_H


class Firelines {
public:
    Firelines() {}
    Firelines(float x, float y,double up_max,double down_max,double speed);
    glm::vec3 position;
    float rotation;

    // double length;
    double up_max;
    double down_max;
    double speed;

    void draw(glm::mat4 VP);
    void set_position(float x, float y);

    void tick();
    bounding_box_t return_box();
    

private:
    VAO *balls;
    VAO *line;
};

#endif // FIRELINES_H
