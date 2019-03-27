#include "score.h"
#include "main.h"
#include <stdlib.h>

Rectangle::Rectangle(float x, float y,float l,float b,float rot) {
    this->position = glm::vec3(x, y, 0);
    this->rotation = rot;
    this->length= l;
    this->breadth = b;


    static GLfloat vertex_buffer_data_rectangle[]={
    -l/2,-b/2,0.0,
    l/2,-b/2,0.0,
    -l/2,b/2,0.0,

    l/2,b/2,0.0,
    l/2,-b/2,0.0,
    -l/2,b/2,0.0
  };
    this->rectangle = create3DObject(GL_TRIANGLES,6, vertex_buffer_data_rectangle, COLOR_BROWN, GL_FILL);

}

void Rectangle::draw(glm::mat4 VP) {
    Matrices.model = glm::mat4(1.0f);
    glm::mat4 translate = glm::translate (this->position);    // glTranslatef
    glm::mat4 rotate    = glm::rotate((float) (this->rotation * M_PI / 180.0f), glm::vec3(0, 0, 1));
    // rotate          = rotate * glm::translate(glm::vec3(0, -0.6, 0));
    Matrices.model *= (translate * rotate);
    glm::mat4 MVP = VP * Matrices.model;
    glUniformMatrix4fv(Matrices.MatrixID, 1, GL_FALSE, &MVP[0][0]);
    draw3DObject(this->rectangle);
}

void Rectangle::set_position(float x, float y) {
    this->position = glm::vec3(x, y, 0);
}
/////////////////////////////////////////////////////////////
Number::Number(float x, float y,int number) {
    this->position = glm::vec3(x, y, 0);
    this->number = number;
    this->seg1 = Rectangle(x-3.5,3.8,0.2,0.02,0);
    this->seg5 = Rectangle(x-3.6,3.5,0.2,0.02,-90);
    this->seg6 = Rectangle(x-3.4,3.5,0.2,0.02,-90);
    this->seg7 = Rectangle(x-3.5,3.4,0.2,0.02,0);
    this->seg3 = Rectangle(x-3.4,3.7,0.2,0.02,-90);
    this->seg4 = Rectangle(x-3.5,3.6,0.2,0.02,0);
    this->seg2 = Rectangle(x-3.6,3.7,0.2,0.02,-90);
}

void Number::draw(glm::mat4 VP) {

       if(this->number==0){
            this->seg1.draw(VP);
            this->seg2.draw(VP);
            this->seg3.draw(VP);
            this->seg5.draw(VP);
            this->seg6.draw(VP);
            this->seg7.draw(VP);
          }
      else if(this->number==1){
            this->seg3.draw(VP);
            this->seg6.draw(VP);
          }
      else if(this->number==2){
            this->seg1.draw(VP);
            this->seg3.draw(VP);
            this->seg4.draw(VP);
            this->seg5.draw(VP);
            this->seg7.draw(VP);
          }
      else if(this->number==3){
            this->seg1.draw(VP);
            this->seg3.draw(VP);
            this->seg4.draw(VP);
            this->seg6.draw(VP);
            this->seg7.draw(VP);
          }
      else if(this->number==4){
            this->seg2.draw(VP);
            this->seg3.draw(VP);
            this->seg4.draw(VP);
            this->seg6.draw(VP);
         }
      else if(this->number==5){
            this->seg1.draw(VP);
            this->seg2.draw(VP);
            this->seg4.draw(VP);
            this->seg6.draw(VP);
            this->seg7.draw(VP);
      }
      else if(this->number==6){
            this->seg1.draw(VP);
            this->seg2.draw(VP);
            this->seg4.draw(VP);
            this->seg5.draw(VP);
            this->seg6.draw(VP);
            this->seg7.draw(VP);
      }
      else if(this->number==7){
            this->seg1.draw(VP);
            this->seg3.draw(VP);
            this->seg6.draw(VP);
      }
      else if(this->number==8){
            this->seg1.draw(VP);
            this->seg2.draw(VP);
            this->seg3.draw(VP);
            this->seg4.draw(VP);
            this->seg5.draw(VP);
            this->seg6.draw(VP);
            this->seg7.draw(VP);
      }
      else if(this->number==9){
            this->seg1.draw(VP);
            this->seg2.draw(VP);
            this->seg3.draw(VP);
            this->seg4.draw(VP);
            this->seg6.draw(VP);
            this->seg7.draw(VP);
    }
}

void Number::set_position(float x, float y) {
    this->position = glm::vec3(x, y, 0);
    this->seg1.set_position(x-3.5,3.8);
    this->seg5.set_position(x-3.6,3.5);
    this->seg6.set_position(x-3.4,3.5);
    this->seg7.set_position(x-3.5,3.4);
    this->seg3.set_position(x-3.4,3.7);
    this->seg4.set_position(x-3.5,3.6);
    this->seg2.set_position(x-3.6,3.7);
}

void Number::tick(float x,float y, int number) {
   this->set_position(x,3.0);
   this->number = number;
}
/////////////////////////////////////////////////////////////
Score::Score(float x, float y,long long int score) {
    this->position = glm::vec3(x, y, 0);
    this->score = score;

    this->d1 = Number(x+2.0,4.0,score%10);
    this->d2 = Number(x+1.7,4.0,(score/10)%10);
    this->d3 = Number(x+1.4,4.0,(score/100)%10);
    this->d4 = Number(x+1.1,4.0,(score/1000)%10);
    this->d5 = Number(x+0.8,4.0,(score/10000)%10);
    this->d6 = Number(x+0.5,4.0,(score/100000)%10);
}

void Score::draw(glm::mat4 VP) {
  this->d1.draw(VP);
  this->d2.draw(VP);
  this->d3.draw(VP);
  this->d4.draw(VP);
  this->d5.draw(VP);
  this->d6.draw(VP);
}

void Score::set_position(float x, float y) {
    this->position = glm::vec3(x, y, 0);
}

void Score::tick(float x,float y,long long int score) {

      this->score = score;
      this->d1.tick(x+2.0,4.0,score%10);
      this->d2.tick(x+1.7,4.0,(score/10)%10);
      this->d3.tick(x+1.4,4.0,(score/100)%10);
      this->d4.tick(x+1.1,4.0,(score/1000)%10);
      this->d5.tick(x+0.8,4.0,(score/10000)%10);
      this->d6.tick(x+0.5,4.0,(score/100000)%10);
}
