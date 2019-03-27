#include "main.h"

#ifndef POWERUPS_H
#define POWERUPS_H


class Coin_double {
public:
    Coin_double() {}
    Coin_double(float x, float y);
    glm::vec3 position;
    float rotation;
    float speed;
    float speed_x;

    void draw(glm::mat4 VP);
    void set_position(float x, float y);

    void tick();
    bounding_box_t return_box();

private:
    VAO *circle;
    VAO *cross;
};

class Strength {
public:
    Strength() {}
    Strength(float x, float y);
    glm::vec3 position;
    float rotation;
    float speed;
    float speed_x;


    void draw(glm::mat4 VP);
    void set_position(float x, float y);

    void tick();
    bounding_box_t return_box();

private:
    VAO *circle;
    VAO *plus;
};

class Waterball {
public:
    Waterball() {}
    Waterball(float x, float y);
    glm::vec3 position;
    float rotation;
    float speed_x;
    float speed_y;
    float gravity;

    void draw(glm::mat4 VP);
    void set_position(float x, float y);

    void tick();
    bounding_box_t return_box();

private:
    VAO *circle;
};

class Propulsion {
public:
    Propulsion() {}
    Propulsion(float x, float y);
    glm::vec3 position;
    float rotation;

    float speed_y;
    float gravity;

    void draw(glm::mat4 VP);
    void set_position(float x, float y);

    void tick();

private:
    VAO *circle;
};
class Iceball {
public:
    Iceball() {}
    Iceball(float x, float y);
    glm::vec3 position;
    float rotation;
    float speed_x;


    void draw(glm::mat4 VP);
    void set_position(float x, float y);

    void tick();
    bounding_box_t return_box();

private:
    VAO *circle;
};
#endif
