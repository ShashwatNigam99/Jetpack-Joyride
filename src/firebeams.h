#include "main.h"

#ifndef FIREBEAMS_H
#define FIREBEAMS_H


class FireBeams {
public:
    FireBeams() {}
    FireBeams(float x, float y,float angle);
    glm::vec3 position;
    float rotation;
    float angle;

    void draw(glm::mat4 VP);
    void set_position(float x, float y);

    void tick();
    bounding_box_t return_box();


private:
    VAO *balls;
    VAO *line;
};

#endif // FIREBEAM_H
