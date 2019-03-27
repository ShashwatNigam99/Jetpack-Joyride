#include "main.h"

#ifndef SCORE_H
#define SCORE_H

class Rectangle {
public:
    Rectangle() {}
    Rectangle(float x, float y, float l,float b, float rot);
    glm::vec3 position;
    float rotation;
    float length;
    float breadth;
    void draw(glm::mat4 VP);
    void set_position(float x, float y);
private:
    VAO *rectangle;
};


class Number {
public:
    Number() {}
    Number(float x, float y, int n);
    glm::vec3 position;
    Rectangle seg1;
    Rectangle seg2;
    Rectangle seg3;
    Rectangle seg4;
    Rectangle seg5;
    Rectangle seg6;
    Rectangle seg7;
    int number;
    void draw(glm::mat4 VP);
    void set_position(float x, float y);
    void tick(float x,float y,int number);
};


class Score {
public:
    Score() {}
    Score(float x, float y,long long int score);
    glm::vec3 position;
    long long int score;  
    Number d1;
    Number d2;
    Number d3;
    Number d4;
    Number d5;
    Number d6;
    void draw(glm::mat4 VP);
    void set_position(float x, float y);
    void tick(float x,float y, long long int score);
};

#endif // SCORE_H
