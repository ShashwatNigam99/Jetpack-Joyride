#include "ball.h"
#include "main.h"

Ball::Ball(float x, float y, color_t color) {
    this->position = glm::vec3(x, y, 0);
    this->rotation = 0;

    this->default_speed_x = 0.005; // default player movement
    this->speed_x = 0.05;// due to key press
    this->speed_up_y = 0.05;//due to key press
    this->speed_down_y = 0.05;// due to key press

    this->speed_y = 0;
    this->gravity = 0.005;

    // Our vertices. Three consecutive floats give a 3D vertex; Three consecutive vertices give a triangle.
    // A cube has 6 faces with 2 triangles each, so this makes 6*2=12 triangles, and 12*3 vertices
    // static GLfloat vertex_buffer_data[] = {
    // -0.5f,1.0f,0.0f,
    // 0.0f,0.0f,0.0f,
    // -0.5f,0.0f,0.0f,//
    //
    // -0.5f,1.0f,0.0f,
    // 0.0f,0.0f,0.0f,
    // 0.0f,1.0f,0.0f
    //
    // };
    //
    // this->object = create3DObject(GL_TRIANGLES, 2*3, vertex_buffer_data, color, GL_FILL);

        const float poly_angle = 360.0 / 20;
        const float poly_rad = (poly_angle * 3.14159) / 180.0;

        GLfloat vertex_buffer_data[9 * 24];

        float x_coord = 0.1;
        float y_coord = 0.0;
        float temp_x = 0.0;
        float temp_y = 0.0;

        for (int i = 0; i <= 3 * 20; ++i)
        {
            if (i < 3 * 20)
            {
                if (i % 3 == 0)
                {
                    vertex_buffer_data[3 * i] = 0.0;
                    vertex_buffer_data[3 * i + 1] = 0.4;
                    vertex_buffer_data[3 * i + 2] = 0.0;
                }
                else
                {
                    vertex_buffer_data[3 * i] = x_coord;
                    vertex_buffer_data[3 * i + 1] = 0.4 + (y_coord);
                    vertex_buffer_data[3 * i + 2] = 0.0;
                    if ((i + 1) % 3 != 0)
                    {
                        temp_x = (x_coord * cos(poly_rad)) - (y_coord * sin(poly_rad));
                        temp_y = (x_coord * sin(poly_rad)) + (y_coord * cos(poly_rad));
                        x_coord = temp_x;
                        y_coord = temp_y;
                    }
                }
            }
            else
            {
                // Body (top-left)
                vertex_buffer_data[(3 * i) + 0] = 0.1f;
                vertex_buffer_data[(3 * i) + 1] = 0.3f;
                vertex_buffer_data[(3 * i) + 2] = 0.0f;

                vertex_buffer_data[(3 * i) + 3] = -0.15f;
                vertex_buffer_data[(3 * i) + 4] = -0.1f;
                vertex_buffer_data[(3 * i) + 5] = 0.0f;

                vertex_buffer_data[(3 * i) + 6] = -0.15f;
                vertex_buffer_data[(3 * i) + 7] = 0.3f;
                vertex_buffer_data[(3 * i) + 8] = 0.0f;

                // Body (bottom-right)
                vertex_buffer_data[(3 * i) + 9] = 0.1f;
                vertex_buffer_data[(3 * i) + 10] = 0.3f;
                vertex_buffer_data[(3 * i) + 11] = 0.0f;

                vertex_buffer_data[(3 * i) + 12] = 0.1f;
                vertex_buffer_data[(3 * i) + 13] = -0.1f;
                vertex_buffer_data[(3 * i) + 14] = 0.0f;

                vertex_buffer_data[(3 * i) + 15] = -0.15f;
                vertex_buffer_data[(3 * i) + 16] = -0.1f;
                vertex_buffer_data[(3 * i) + 17] = 0.0f;

                // Legs
                vertex_buffer_data[(3 * i) + 18] = -0.1f;
                vertex_buffer_data[(3 * i) + 19] = 0.1f;
                vertex_buffer_data[(3 * i) + 20] = 0.0f;

                vertex_buffer_data[(3 * i) + 21] = -0.1f;
                vertex_buffer_data[(3 * i) + 22] = -0.2f;
                vertex_buffer_data[(3 * i) + 23] = 0.0f;

                vertex_buffer_data[(3 * i) + 24] = 0.1f;
                vertex_buffer_data[(3 * i) + 25] = -0.2f;
                vertex_buffer_data[(3 * i) + 26] = 0.0f;

                // Jetpack
                vertex_buffer_data[(3 * i) + 27] = -0.15f;
                vertex_buffer_data[(3 * i) + 28] = 0.3f;
                vertex_buffer_data[(3 * i) + 29] = 0.0f;

                vertex_buffer_data[(3 * i) + 30] = -0.25f;
                vertex_buffer_data[(3 * i) + 31] = 0.0f;
                vertex_buffer_data[(3 * i) + 32] = 0.0f;

                vertex_buffer_data[(3 * i) + 33] = -0.15f;
                vertex_buffer_data[(3 * i) + 34] = 0.0f;
                vertex_buffer_data[(3 * i) + 35] = 0.0f;
            }
        }

        this->object = create3DObject(GL_TRIANGLES, 24 * 3, vertex_buffer_data, color, GL_FILL);
}

void Ball::draw(glm::mat4 VP) {
    Matrices.model = glm::mat4(1.0f);
    glm::mat4 translate = glm::translate (this->position);    // glTranslatef
    glm::mat4 rotate    = glm::rotate((float) (this->rotation * M_PI / 180.0f), glm::vec3(1, 0, 0));
    // No need as coords centered at 0, 0, 0 of cube arouund which we waant to rotate
    // rotate          = rotate * glm::translate(glm::vec3(0, -0.6, 0));
    Matrices.model *= (translate * rotate);
    glm::mat4 MVP = VP * Matrices.model;
    glUniformMatrix4fv(Matrices.MatrixID, 1, GL_FALSE, &MVP[0][0]);
    draw3DObject(this->object);
}

void Ball::set_position(float x, float y) {
    this->position = glm::vec3(x, y, 0);
}

void Ball::tick() {
  if(this->position.x< screen_center_x+(4.0/screen_zoom))
      this->position.x += this->default_speed_x;

  if(player_max_x<this->position.x){
    player_max_x = this->position.x;
  }
  // std::cout<<"max x "<<player_max_x<<"\n";
  //  std::cout<<this->position.x<<","<<this->position.y<<"\n";
}
void Ball::up() {
  if(this->position.y<(3.5/screen_zoom)){
    this->position.y += this->speed_up_y;
    this->speed_y = 0;//putting all falling velocity gained to zero again
  }
}
void Ball::down() {
  if(this->position.y>-3){
      if(this->position.y-this->speed_down_y<-3)
        {
          this->position.y=-3;
        }
      else{
      this->position.y -= this->speed_down_y;
    }
  }
}

void Ball::right() {
  if(this->position.x< screen_center_x+(4.0/screen_zoom))
    this->position.x += this->speed_x;

  screen_center_x+=0.05;

}
void Ball::left() {
  if(this->position.x>screen_center_x+(-3.5/screen_zoom))
    this->position.x -= this->speed_x;
}
void Ball::gravity_fall(){
  if(this->position.y>-3){
    this->speed_y+=this->gravity;
    if(this->position.y-this->speed_y<-3)
      {
        this->position.y=-3;
        this->speed_y=0;
      }
    else{
    this->position.y -= this->speed_y;
    }
  }
  else{
    this->speed_y=0;//reached ground
  }
}
//////////////////////////////////////////////////////////////////////////////////////////
Viserion::Viserion(float x, float y) {
    this->position = glm::vec3(x, y, 0);
    this->rotation = 0;

    static GLfloat vertex_buffer_data_p1[]={
         -0.3*2,0.1*2,0.0*2,
         -0.1*2,0.1*2,0.0*2,
         -0.1*2,0.3*2,0.0*2,//

          -0.1*2,-0.1*2,0.1*2,
          -0.1*2,0.3*2,0.0*2,
          0.2*2,-0.1*2,0.0*2,

          -0.3*2,-0.3*2,0.0*2,
          -0.1*2,-0.1*2,0.0*2,
          -0.1*2,-0.3*2,0.0*2,

          0.2*2,-0.1*2,0.0*2,
          0.0*2,-0.3*2,0.0*2,
          0.2*2,-0.3*2,0.0
    };
    this->p1= create3DObject(GL_TRIANGLES, 3*4, vertex_buffer_data_p1, COLOR_PURPLE, GL_FILL);
    static GLfloat vertex_buffer_data_p2[]={
         -0.15*2,0.15*2,0.0*2,
         -0.15*2,0.25*2,0.0*2,
         -0.25*2,0.15*2,0.0*2,

         -0.1*2,0.3*2,0.0*2,
         0.0*2,0.3*2,0.0*2,
         0.0*2,0.2*2,0.0*2,

         0.0*2,0.2*2,0.0*2,
         0.2*2,0.2*2,0.0*2,
         0.2*2,-0.1*2,0.0
    };
    this->p2= create3DObject(GL_TRIANGLES, 3*3, vertex_buffer_data_p2, COLOR_PINK, GL_FILL);
}

void Viserion::draw(glm::mat4 VP) {
    Matrices.model = glm::mat4(1.0f);
    glm::mat4 translate = glm::translate (this->position);    // glTranslatef
    glm::mat4 rotate    = glm::rotate((float) (this->rotation * M_PI / 180.0f), glm::vec3(0, 1, 0));
    // No need as coords centered at 0, 0, 0 of cube arouund which we waant to rotate
    // rotate          = rotate * glm::translate(glm::vec3(0, -0.6, 0));
    Matrices.model *= (translate * rotate);
    glm::mat4 MVP = VP * Matrices.model;
    glUniformMatrix4fv(Matrices.MatrixID, 1, GL_FALSE, &MVP[0][0]);
    draw3DObject(this->p1);
    draw3DObject(this->p2);
}

void Viserion::set_position(float x, float y) {
    this->position = glm::vec3(x, y, 0);
}

void Viserion::tick() {
//

}
//////////////////////////////////////////////////////////////////////////////////////////////////
Semicircle::Semicircle(float x, float y) {
    this->position = glm::vec3(x, y, 0);
    this->rotation = 0;

    static GLfloat vertex_buffer_data_p1[450];
    for (int i=0;i<=50;++i){
        vertex_buffer_data_p1[9*i]=(6.5*cos(i*2*3.14159/100));
        vertex_buffer_data_p1[9*i+1]=(6.5*sin(i*2*3.14159/100));
        vertex_buffer_data_p1[9*i+2]=0.0;

        vertex_buffer_data_p1[9*i+3]=(6.5*cos((i+1)*2*3.14159/100));
        vertex_buffer_data_p1[9*i+4]=(6.5*sin((i+1)*2*3.14159/100));
        vertex_buffer_data_p1[9*i+5]=0.0;

        vertex_buffer_data_p1[9*i+6]=0.0;
        vertex_buffer_data_p1[9*i+7]=0.0;
        vertex_buffer_data_p1[9*i+8]=0.0;
      }
    this->p1= create3DObject(GL_TRIANGLES, 3*50, vertex_buffer_data_p1, COLOR_SKYBLUE, GL_FILL);

    static GLfloat vertex_buffer_data_p2[450];
    for (int i=0;i<=50;++i){
        vertex_buffer_data_p2[9*i]=(5.5*cos(i*2*3.14159/100));
        vertex_buffer_data_p2[9*i+1]=(5.5*sin(i*2*3.14159/100));
        vertex_buffer_data_p2[9*i+2]=0.0;

        vertex_buffer_data_p2[9*i+3]=(5.5*cos((i+1)*2*3.14159/100));
        vertex_buffer_data_p2[9*i+4]=(5.5*sin((i+1)*2*3.14159/100));
        vertex_buffer_data_p2[9*i+5]=0.0;

        vertex_buffer_data_p2[9*i+6]=0.0;
        vertex_buffer_data_p2[9*i+7]=0.0;
        vertex_buffer_data_p2[9*i+8]=0.0;
      }
    this->p2= create3DObject(GL_TRIANGLES, 3*50, vertex_buffer_data_p2, COLOR_BACKGROUND, GL_FILL);
}

void Semicircle::draw(glm::mat4 VP) {
    Matrices.model = glm::mat4(1.0f);
    glm::mat4 translate = glm::translate (this->position);    // glTranslatef
    glm::mat4 rotate    = glm::rotate((float) (this->rotation * M_PI / 180.0f), glm::vec3(0, 1, 0));
    // No need as coords centered at 0, 0, 0 of cube arouund which we waant to rotate
    // rotate          = rotate * glm::translate(glm::vec3(0, -0.6, 0));
    Matrices.model *= (translate * rotate);
    glm::mat4 MVP = VP * Matrices.model;
    glUniformMatrix4fv(Matrices.MatrixID, 1, GL_FALSE, &MVP[0][0]);
    draw3DObject(this->p1);
    draw3DObject(this->p2);
}

void Semicircle::set_position(float x, float y) {
    this->position = glm::vec3(x, y, 0);
}
