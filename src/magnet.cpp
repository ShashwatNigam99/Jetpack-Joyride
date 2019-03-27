#include "magnet.h"
#include "main.h"

Magnet::Magnet(float x, float y) {
    this->position = glm::vec3(x, y, 0);
    this->rotation = 0;


    // Our vertices. Three consecutive floats give a 3D vertex; Three consecutive vertices give a triangle.
    // A cube has 6 faces with 2 triangles each, so this makes 6*2=12 triangles, and 12*3 vertices
    static const GLfloat vertex_buffer_data_left[] = {
    -0.4f,0.0f,0.0f,
    0.0f,0.2f,0.0f,
    0.0f,-0.2f,0.0f,//
    };
    static const GLfloat vertex_buffer_data_right[] = {
    0.4f,0.0f,0.0f,
    0.0f,0.2f,0.0f,
    0.0f,-0.2f,0.0f,//
    };

    this->left = create3DObject(GL_TRIANGLES, 3, vertex_buffer_data_left, COLOR_WHITE, GL_FILL);
    this->right = create3DObject(GL_TRIANGLES, 3, vertex_buffer_data_right, COLOR_RED, GL_FILL);

}

void Magnet::draw(glm::mat4 VP) {
    Matrices.model = glm::mat4(1.0f);
    glm::mat4 translate = glm::translate (this->position);    // glTranslatef
    glm::mat4 rotate    = glm::rotate((float) (this->rotation * M_PI / 180.0f), glm::vec3(0, 1, 0));
    // No need as coords centered at 0, 0, 0 of cube arouund which we waant to rotate
    // rotate          = rotate * glm::translate(glm::vec3(0, -0.6, 0));
    Matrices.model *= (translate * rotate);
    glm::mat4 MVP = VP * Matrices.model;
    glUniformMatrix4fv(Matrices.MatrixID, 1, GL_FALSE, &MVP[0][0]);
    draw3DObject(this->left);
    draw3DObject(this->right);
}

void Magnet::set_position(float x, float y) {
    this->position = glm::vec3(x, y, 0);
}

void Magnet::tick() {
  // this->rotation += 1;
   // std::cout<<"coin :"<<this->position.x<<","<<this->position.y<<"\n";
}

bounding_box_t Magnet::return_box(){
  bounding_box_t coin_bb;
  coin_bb.x = this->position.x;
  coin_bb.y = this->position.y;
  coin_bb.width = 0.4f;
  coin_bb.height = 0.4f;
  return coin_bb;
}
