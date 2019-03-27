#include "boomerang.h"
#include "main.h"
#include <stdlib.h>


Boomerang::Boomerang(float x, float y) {
    this->position = glm::vec3(x, y, 0);
    this->rotation = 0;
    this->speed_x = -0.046;
    this->speed_y = 0.04;
    this->gravity_x = 0.001;

    static GLfloat vertex_buffer_data_triangles[]={
    -0.05,0.0,0.0,
    0.05,0.0,0.0,
    0.3,0.2,0.0,
    -0.05,0.0,0.0,
    0.05,0.0,0.0,
    0.3,-0.2,0.0
  };
    this->triangle = create3DObject(GL_TRIANGLES,6, vertex_buffer_data_triangles, COLOR_BROWN, GL_FILL);

}

void Boomerang::draw(glm::mat4 VP) {
    Matrices.model = glm::mat4(1.0f);
    glm::mat4 translate = glm::translate (this->position);    // glTranslatef
    glm::mat4 rotate    = glm::rotate((float) (this->rotation * M_PI / 180.0f), glm::vec3(0, 0, 1));
    // rotate          = rotate * glm::translate(glm::vec3(0, -0.6, 0));
    Matrices.model *= (translate * rotate);
    glm::mat4 MVP = VP * Matrices.model;
    glUniformMatrix4fv(Matrices.MatrixID, 1, GL_FALSE, &MVP[0][0]);
    draw3DObject(this->triangle);
}

void Boomerang::set_position(float x, float y) {
    this->position = glm::vec3(x, y, 0);
}
//
void Boomerang::tick() {
    this->rotation += 20;

    this->speed_x+=this->gravity_x;
    this->position.x+=this->speed_x;
    this->position.y-=this->speed_y;

}
bounding_box_t Boomerang::return_box(){
  bounding_box_t coin_bb;
  coin_bb.x = this->position.x;
  coin_bb.y = this->position.y;
  coin_bb.width = 0.3f;
  coin_bb.height = 0.2f;
  return coin_bb;
}
