#include "firebeams.h"
#include "main.h"
#include <stdlib.h>


FireBeams::FireBeams(float x, float y, float angle) {
    this->position = glm::vec3(x, y, 0);
    this->rotation = 0;
    // this->length = (rand()%3)+2;
    this->angle = angle;

    static GLfloat vertex_buffer_data_balls[1800];
    for (int i=0;i<100;++i){
      vertex_buffer_data_balls[9*i]=(0.2*cos(i*2*3.14159/100));
      vertex_buffer_data_balls[9*i+1]=(0.2*sin(i*2*3.14159/100));
      vertex_buffer_data_balls[9*i+2]=0.0;

      vertex_buffer_data_balls[9*i+3]=(0.2*cos((i+1)*2*3.14159/100));
      vertex_buffer_data_balls[9*i+4]=(0.2*sin((i+1)*2*3.14159/100));
      vertex_buffer_data_balls[9*i+5]=0.0;

      vertex_buffer_data_balls[9*i+6]=0.0;
      vertex_buffer_data_balls[9*i+7]=0.0;
      vertex_buffer_data_balls[9*i+8]=0.0;
    }
    for (int i=100;i<200;++i){
      vertex_buffer_data_balls[9*i]=2*cos((angle/360)*2*3.14159)+(0.2*cos(i*2*3.14159/100));
      vertex_buffer_data_balls[9*i+1]=2*sin((angle/360)*2*3.14159)+(0.2 *sin(i*2*3.14159/100));
      vertex_buffer_data_balls[9*i+2]=0.0;

      vertex_buffer_data_balls[9*i+3]=2*cos((angle/360)*2*3.14159)+(0.2*cos((i+1)*2*3.14159/100));
      vertex_buffer_data_balls[9*i+4]=2*sin((angle/360)*2*3.14159)+(0.2*sin((i+1)*2*3.14159/100));
      vertex_buffer_data_balls[9*i+5]=0.0;

      vertex_buffer_data_balls[9*i+6]=2*cos((angle/360)*2*3.14159);
      vertex_buffer_data_balls[9*i+7]=2*sin((angle/360)*2*3.14159);
      vertex_buffer_data_balls[9*i+8]=0.0;
    }
    this->balls = create3DObject(GL_TRIANGLES,600, vertex_buffer_data_balls, COLOR_DARKGREEN, GL_FILL);

    static GLfloat vertex_buffer_data_line[18];
    // 0.1,0.0,0.0,
    // -0.1,-0.0,0.0,
    // 2*cos((angle/360)*2*3.14159)+0.1,2*sin((angle/360)*2*3.14159),0.0,//
    //
    // -0.1,-0.0,0.0,
    // 2*cos((angle/360)*2*3.14159)+0.1,2*sin((angle/360)*2*3.14159),0.0,
    // 2*cos((angle/360)*2*3.14159)-0.1,2*sin((angle/360)*2*3.14159),0.0
    //
    // };
    vertex_buffer_data_line[0]= 0.1  ;
    vertex_buffer_data_line[1]= 0.0 ;
    vertex_buffer_data_line[2]= 0.0  ;
    vertex_buffer_data_line[3]= -0.1 ;
    vertex_buffer_data_line[4]= 0.0  ;
    vertex_buffer_data_line[5]= 0.0  ;
    vertex_buffer_data_line[6]=  2*cos((angle/360)*2*3.14159)+0.1  ;
    vertex_buffer_data_line[7]=  2*sin((angle/360)*2*3.14159) ;
    vertex_buffer_data_line[8]= 0.0  ;

    vertex_buffer_data_line[9]=  2*cos((angle/360)*2*3.14159)+0.1 ;
    vertex_buffer_data_line[10]= 2*sin((angle/360)*2*3.14159)  ;
    vertex_buffer_data_line[11]=  0.0 ;
    vertex_buffer_data_line[12]= 2*cos((angle/360)*2*3.14159)-0.1  ;
    vertex_buffer_data_line[13]= 2*sin((angle/360)*2*3.14159)  ;
    vertex_buffer_data_line[14]= 0.0  ;
    vertex_buffer_data_line[15]= -0.1  ;
    vertex_buffer_data_line[16]= 0.0  ;
    vertex_buffer_data_line[17]= 0.0  ;


    this->line = create3DObject(GL_TRIANGLES,6, vertex_buffer_data_line, COLOR_SKYBLUE, GL_FILL);
}

void FireBeams::draw(glm::mat4 VP) {
    Matrices.model = glm::mat4(1.0f);
    glm::mat4 translate = glm::translate (this->position);    // glTranslatef
    glm::mat4 rotate    = glm::rotate((float) (this->rotation * M_PI / 180.0f), glm::vec3(1, 0, 0));
    // rotate          = rotate * glm::translate(glm::vec3(0, -0.6, 0));
    Matrices.model *= (translate * rotate);
    glm::mat4 MVP = VP * Matrices.model;
    glUniformMatrix4fv(Matrices.MatrixID, 1, GL_FALSE, &MVP[0][0]);
    draw3DObject(this->line);
    draw3DObject(this->balls);
}

void FireBeams::set_position(float x, float y) {
    this->position = glm::vec3(x, y, 0);
}
//
// void FireBeams::tick() {
//
//     if(this->position.y+speed>up_max && this->speed>0){
//       this->speed*=-1;
//     }
//     else if(this->position.y+speed<down_max && this->speed<0){
//       this->speed*=-1;
//     }
//     this->position.y+=this->speed;
//
// }
bounding_box_t FireBeams::return_box(){
  bounding_box_t coin_bb;
  coin_bb.x = this->position.x+1.5;
  coin_bb.y = this->position.y;
  coin_bb.width = 3.0f;
  coin_bb.height = 0.1f;
  return coin_bb;
}
