#include "powerups.h"
#include "main.h"

Coin_double::Coin_double(float x, float y) {
    this->position = glm::vec3(x, y, 0);
    this->rotation = 0;
    this->speed = 0.02;
    this->speed_x = 0.03;


    // Our vertices. Three consecutive floats give a 3D vertex; Three consecutive vertices give a triangle.
    // A cube has 6 faces with 2 triangles each, so this makes 6*2=12 triangles, and 12*3 vertices
    static GLfloat vertex_buffer_data_circle[900] ;
    for (int i=0;i<100;++i){
      vertex_buffer_data_circle[9*i]=(0.3*cos(i*2*3.14159/100));
      vertex_buffer_data_circle[9*i+1]=(0.3*sin(i*2*3.14159/100));
      vertex_buffer_data_circle[9*i+2]=0.0;

      vertex_buffer_data_circle[9*i+3]=(0.3*cos((i+1)*2*3.14159/100));
      vertex_buffer_data_circle[9*i+4]=(0.3*sin((i+1)*2*3.14159/100));
      vertex_buffer_data_circle[9*i+5]=0.0;

      vertex_buffer_data_circle[9*i+6]=0.0;
      vertex_buffer_data_circle[9*i+7]=0.0;
      vertex_buffer_data_circle[9*i+8]=0.0;
    }
    this->circle = create3DObject(GL_TRIANGLES, 300, vertex_buffer_data_circle, COLOR_GREEN, GL_FILL);
    static GLfloat vertex_buffer_data_cross[] ={
      0.3*cos(0.1666*2*3.14159),0.3*sin(0.1666*2*3.14159),0.0f,
      0.3*cos(0.1666*2*3.14159)-0.05,0.3*sin(0.1666*2*3.14159),0.0f,
      -0.3*cos(0.1666*2*3.14159),-0.3*sin(0.1666*2*3.14159),0.0f,

      -0.3*cos(0.1666*2*3.14159),-0.3*sin(0.1666*2*3.14159),0.0f,
      -0.3*cos(0.1666*2*3.14159)+0.05,-0.3*sin(0.1666*2*3.14159),0.0f,
      0.3*cos(0.1666*2*3.14159),0.3*sin(0.1666*2*3.14159),0.0f,

      -0.3*cos(0.1666*2*3.14159),0.3*sin(0.1666*2*3.14159),0.0f,
      -0.3*cos(0.1666*2*3.14159)+0.05,0.3*sin(0.1666*2*3.14159),0.0f,
      0.3*cos(0.1666*2*3.14159),-0.3*sin(0.1666*2*3.14159),0.0f,

      0.3*cos(0.1666*2*3.14159),-0.3*sin(0.1666*2*3.14159),0.0f,
      0.3*cos(0.1666*2*3.14159)-0.05,-0.3*sin(0.1666*2*3.14159),0.0f,
      -0.3*cos(0.1666*2*3.14159),0.3*sin(0.1666*2*3.14159),0.0f
    };
    this->cross= create3DObject(GL_TRIANGLES, 12 , vertex_buffer_data_cross, COLOR_BLUE , GL_FILL);
}

void Coin_double::draw(glm::mat4 VP) {
    Matrices.model = glm::mat4(1.0f);
    glm::mat4 translate = glm::translate (this->position);    // glTranslatef
    glm::mat4 rotate    = glm::rotate((float) (this->rotation * M_PI / 180.0f), glm::vec3(0, 1, 0));
    // No need as coords centered at 0, 0, 0 of cube arouund which we waant to rotate
    // rotate          = rotate * glm::translate(glm::vec3(0, -0.6, 0));
    Matrices.model *= (translate * rotate);
    glm::mat4 MVP = VP * Matrices.model;
    glUniformMatrix4fv(Matrices.MatrixID, 1, GL_FALSE, &MVP[0][0]);
    draw3DObject(this->circle);
    draw3DObject(this->cross);
}

void Coin_double::set_position(float x, float y) {
    this->position = glm::vec3(x, y, 0);
}

void Coin_double::tick() {
  if(this->position.y+this->speed>4 && this->speed>0 || this->position.y+this->speed<-3 && this->speed<0)
     this->speed*=-1;
  this->position.x-=(this->speed_x);
  this->position.y+=this->speed;
  // this->rotation += 2;
  //  std::cout<<"coin :"<<this->position.x<<","<<this->position.y<<"\n";
}

bounding_box_t Coin_double::return_box(){
  bounding_box_t coin_bb;
  coin_bb.x = this->position.x;
  coin_bb.y = this->position.y;
  coin_bb.width = 0.3f;
  coin_bb.height = 0.3f;
  return coin_bb;
}
/////////////////////////////////////////////////////////////////////////////////////
Strength::Strength(float x, float y) {
    this->position = glm::vec3(x, y, 0);
    this->rotation = 0;
    this->speed = 0.02;
    this->speed_x = 0.03;



    // Our vertices. Three consecutive floats give a 3D vertex; Three consecutive vertices give a triangle.
    // A cube has 6 faces with 2 triangles each, so this makes 6*2=12 triangles, and 12*3 vertices
    static GLfloat vertex_buffer_data_circle[900] ;
    for (int i=0;i<100;++i){
      vertex_buffer_data_circle[9*i]=(0.3*cos(i*2*3.14159/100));
      vertex_buffer_data_circle[9*i+1]=(0.3*sin(i*2*3.14159/100));
      vertex_buffer_data_circle[9*i+2]=0.0;

      vertex_buffer_data_circle[9*i+3]=(0.3*cos((i+1)*2*3.14159/100));
      vertex_buffer_data_circle[9*i+4]=(0.3*sin((i+1)*2*3.14159/100));
      vertex_buffer_data_circle[9*i+5]=0.0;

      vertex_buffer_data_circle[9*i+6]=0.0;
      vertex_buffer_data_circle[9*i+7]=0.0;
      vertex_buffer_data_circle[9*i+8]=0.0;
    }
    this->circle= create3DObject(GL_TRIANGLES, 300, vertex_buffer_data_circle, COLOR_BLUE, GL_FILL);

    static GLfloat vertex_buffer_data_plus[] ={
      0.3*cos(0.2361*2*3.14159),0.3*sin(0.2361*2*3.14159),0.0f,
      -0.3*cos(0.2361*2*3.14159),0.3*sin(0.2361*2*3.14159),0.0f,
      0.3*cos(0.2361*2*3.14159),-0.3*sin(0.2361*2*3.14159),0.0f,

      0.3*cos(0.2361*2*3.14159),-0.3*sin(0.2361*2*3.14159),0.0f,
      -0.3*cos(0.2361*2*3.14159),-0.3*sin(0.2361*2*3.14159),0.0f,
      -0.3*cos(0.2361*2*3.14159),0.3*sin(0.2361*2*3.14159),0.0f,

      0.3*sin(0.2361*2*3.14159),0.3*cos(0.2361*2*3.14159),0.0f,
      -0.3*sin(0.2361*2*3.14159),0.3*cos(0.2361*2*3.14159),0.0f,
      0.3*sin(0.2361*2*3.14159),-0.3*cos(0.2361*2*3.14159),0.0f,

      0.3*sin(0.2361*2*3.14159),-0.3*cos(0.2361*2*3.14159),0.0f,
      -0.3*sin(0.2361*2*3.14159),-0.3*cos(0.2361*2*3.14159),0.0f,
      -0.3*sin(0.2361*2*3.14159),0.3*cos(0.2361*2*3.14159),0.0f
    };
    this->plus= create3DObject(GL_TRIANGLES, 12 , vertex_buffer_data_plus, COLOR_RED, GL_FILL);

}

void Strength::draw(glm::mat4 VP) {
    Matrices.model = glm::mat4(1.0f);
    glm::mat4 translate = glm::translate (this->position);    // glTranslatef
    glm::mat4 rotate    = glm::rotate((float) (this->rotation * M_PI / 180.0f), glm::vec3(0, 1, 0));
    // No need as coords centered at 0, 0, 0 of cube arouund which we waant to rotate
    // rotate          = rotate * glm::translate(glm::vec3(0, -0.6, 0));
    Matrices.model *= (translate * rotate);
    glm::mat4 MVP = VP * Matrices.model;
    glUniformMatrix4fv(Matrices.MatrixID, 1, GL_FALSE, &MVP[0][0]);
    draw3DObject(this->circle);
    draw3DObject(this->plus);
}

void Strength::set_position(float x, float y) {
    this->position = glm::vec3(x, y, 0);
}

void Strength::tick() {
  if(this->position.y+this->speed>4 && this->speed>0 || this->position.y+this->speed<-3 && this->speed<0)
     this->speed*=-1;
  this->position.x-=(this->speed_x);
  this->position.y+=this->speed;
}

bounding_box_t Strength::return_box(){
  bounding_box_t coin_bb;
  coin_bb.x = this->position.x;
  coin_bb.y = this->position.y;
  coin_bb.width = 0.3f;
  coin_bb.height = 0.3f;
  return coin_bb;
}
/////////////////////////////////////////////////////////////////////////////////////
Waterball::Waterball(float x, float y) {
    this->position = glm::vec3(x, y, 0);
    this->rotation = 0;
    this->speed_x = 0.05;
    this->speed_y = 0;
    this->gravity = 0.02;

    // Our vertices. Three consecutive floats give a 3D vertex; Three consecutive vertices give a triangle.
    // A cube has 6 faces with 2 triangles each, so this makes 6*2=12 triangles, and 12*3 vertices
    static GLfloat vertex_buffer_data_circle[900] ;
    for (int i=0;i<100;++i){
      vertex_buffer_data_circle[9*i]=(0.1*cos(i*2*3.14159/100));
      vertex_buffer_data_circle[9*i+1]=(0.1*sin(i*2*3.14159/100));
      vertex_buffer_data_circle[9*i+2]=0.0;

      vertex_buffer_data_circle[9*i+3]=(0.1*cos((i+1)*2*3.14159/100));
      vertex_buffer_data_circle[9*i+4]=(0.1*sin((i+1)*2*3.14159/100));
      vertex_buffer_data_circle[9*i+5]=0.0;

      vertex_buffer_data_circle[9*i+6]=0.0;
      vertex_buffer_data_circle[9*i+7]=0.0;
      vertex_buffer_data_circle[9*i+8]=0.0;
    }
    this->circle= create3DObject(GL_TRIANGLES, 300, vertex_buffer_data_circle, COLOR_BLUE, GL_FILL);
}

void Waterball::draw(glm::mat4 VP) {
    Matrices.model = glm::mat4(1.0f);
    glm::mat4 translate = glm::translate (this->position);    // glTranslatef
    glm::mat4 rotate    = glm::rotate((float) (this->rotation * M_PI / 180.0f), glm::vec3(0, 1, 0));
    // No need as coords centered at 0, 0, 0 of cube arouund which we waant to rotate
    // rotate          = rotate * glm::translate(glm::vec3(0, -0.6, 0));
    Matrices.model *= (translate * rotate);
    glm::mat4 MVP = VP * Matrices.model;
    glUniformMatrix4fv(Matrices.MatrixID, 1, GL_FALSE, &MVP[0][0]);
    draw3DObject(this->circle);
}

void Waterball::set_position(float x, float y) {
    this->position = glm::vec3(x, y, 0);
}

void Waterball::tick() {
   if(this->position.y>-3){
     this->speed_y+=this->gravity;
     this->position.y-=this->speed_y;
     this->position.x+=this->speed_x;
   }
}

bounding_box_t Waterball::return_box(){
  bounding_box_t coin_bb;
  coin_bb.x = this->position.x;
  coin_bb.y = this->position.y;
  coin_bb.width = 0.3f;
  coin_bb.height = 0.3f;
  return coin_bb;
}
///////////////////////////////////////////////////////////////////////////////////////////
Propulsion::Propulsion(float x, float y) {
    this->position = glm::vec3(x, y, 0);
    this->rotation = 0;

    this->speed_y = 0;
    this->gravity = 0.02;

    // Our vertices. Three consecutive floats give a 3D vertex; Three consecutive vertices give a triangle.
    // A cube has 6 faces with 2 triangles each, so this makes 6*2=12 triangles, and 12*3 vertices
    static GLfloat vertex_buffer_data_circle[]={
         0.2,0.0,0.0,
         -0.2,0.0,0.0,
         0.0,-0.3,0.0
    };
    this->circle= create3DObject(GL_TRIANGLES, 3, vertex_buffer_data_circle, COLOR_ORANGE, GL_FILL);
}

void Propulsion::draw(glm::mat4 VP) {
    Matrices.model = glm::mat4(1.0f);
    glm::mat4 translate = glm::translate (this->position);    // glTranslatef
    glm::mat4 rotate    = glm::rotate((float) (this->rotation * M_PI / 180.0f), glm::vec3(0, 1, 0));
    // No need as coords centered at 0, 0, 0 of cube arouund which we waant to rotate
    // rotate          = rotate * glm::translate(glm::vec3(0, -0.6, 0));
    Matrices.model *= (translate * rotate);
    glm::mat4 MVP = VP * Matrices.model;
    glUniformMatrix4fv(Matrices.MatrixID, 1, GL_FALSE, &MVP[0][0]);
    draw3DObject(this->circle);
}

void Propulsion::set_position(float x, float y) {
    this->position = glm::vec3(x, y, 0);
}

void Propulsion::tick() {
   if(this->position.y>-3){
     this->speed_y+=this->gravity;
     this->position.y-=this->speed_y;
   }
}
///////////////////////////////////////////////////////////////////////////////////////////////////////
Iceball::Iceball(float x, float y) {
    this->position = glm::vec3(x, y, 0);
    this->rotation = 0;
    this->speed_x = 0.05;

    // Our vertices. Three consecutive floats give a 3D vertex; Three consecutive vertices give a triangle.
    // A cube has 6 faces with 2 triangles each, so this makes 6*2=12 triangles, and 12*3 vertices
    static GLfloat vertex_buffer_data_circle[900] ;
    for (int i=0;i<100;++i){
      vertex_buffer_data_circle[9*i]=(0.1*cos(i*2*3.14159/100));
      vertex_buffer_data_circle[9*i+1]=(0.1*sin(i*2*3.14159/100));
      vertex_buffer_data_circle[9*i+2]=0.0;

      vertex_buffer_data_circle[9*i+3]=(0.1*cos((i+1)*2*3.14159/100));
      vertex_buffer_data_circle[9*i+4]=(0.1*sin((i+1)*2*3.14159/100));
      vertex_buffer_data_circle[9*i+5]=0.0;

      vertex_buffer_data_circle[9*i+6]=0.0;
      vertex_buffer_data_circle[9*i+7]=0.0;
      vertex_buffer_data_circle[9*i+8]=0.0;
    }
    this->circle= create3DObject(GL_TRIANGLES, 300, vertex_buffer_data_circle, COLOR_GRAY, GL_FILL);
}

void Iceball::draw(glm::mat4 VP) {
    Matrices.model = glm::mat4(1.0f);
    glm::mat4 translate = glm::translate (this->position);    // glTranslatef
    glm::mat4 rotate    = glm::rotate((float) (this->rotation * M_PI / 180.0f), glm::vec3(0, 1, 0));
    // No need as coords centered at 0, 0, 0 of cube arouund which we waant to rotate
    // rotate          = rotate * glm::translate(glm::vec3(0, -0.6, 0));
    Matrices.model *= (translate * rotate);
    glm::mat4 MVP = VP * Matrices.model;
    glUniformMatrix4fv(Matrices.MatrixID, 1, GL_FALSE, &MVP[0][0]);
    draw3DObject(this->circle);
}

void Iceball::set_position(float x, float y) {
    this->position = glm::vec3(x, y, 0);
}

void Iceball::tick() {
     this->position.x-=this->speed_x;
}

bounding_box_t Iceball::return_box(){
  bounding_box_t coin_bb;
  coin_bb.x = this->position.x;
  coin_bb.y = this->position.y;
  coin_bb.width = 0.3f;
  coin_bb.height = 0.3f;
  return coin_bb;
}
