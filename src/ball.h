#include "main.h"

#ifndef BALL_H
#define BALL_H


class Ball {
public:
    Ball() {}
    Ball(float x, float y, color_t color);
    glm::vec3 position;
    float rotation;
    void draw(glm::mat4 VP);
    void set_position(float x, float y);

    void tick();
    void up();
    void right();
    void left();
    void down();
    void gravity_fall();

    double default_speed_x;
    double speed_x;
    double speed_up_y;
    double speed_down_y;
    double speed_y;
    double gravity;

private:
    VAO *object;
};

class Viserion {
public:
  Viserion() {}
  Viserion(float x, float y);
    glm::vec3 position;
    float rotation;
    void draw(glm::mat4 VP);
    void set_position(float x, float y);
    void tick();


private:
    VAO *p1;
    VAO *p2;
};
class Semicircle {
public:
  Semicircle() {}
  Semicircle(float x, float y);
    glm::vec3 position;
    float rotation;
    void draw(glm::mat4 VP);
    void set_position(float x, float y);
    void tick();


private:
    VAO *p1;
    VAO *p2;
};
#endif // BALL_H
