#include "main.h"
#include "timer.h"
#include "ball.h"
#include "ground.h"
#include "coin.h"
#include "firelines.h"
#include "firebeams.h"
#include "magnet.h"
#include "powerups.h"
#include "boomerang.h"
#include "score.h"


#include <stdlib.h>


using namespace std;

GLMatrices Matrices;
GLuint     programID;
GLFWwindow *window;

/**************************
* Customizable functions *
**************************/
vector<Viserion> viserion;
// Viserion v;
Ball ball;
Ground ground;
vector<Coin> coins;
vector<Firelines> firelines;
vector<FireBeams> firebeams;
vector<Magnet> magnets;
vector<Coin_double> coin_dbl;
vector<Strength> strength;
vector<Waterball> waterballs;
vector<Boomerang> boomerangs;
vector<Iceball> iceballs;
vector<Semicircle> semicircles;

Score display;
Number life;
vector<Propulsion> props;
int th=0;
int tth=0;
// Coin coin;//test coin

int IMMUNITY=0;
int DBL_SCORE=0;
int WATER_TANK=0;
int PROPULSION=0;
int VISERION = 0;
int lives=10;
long long int score = 0;
float screen_zoom = 0.25;
float screen_center_x = 0, screen_center_y = 0;
float camera_rotation_angle = 0;
float player_max_x=0;
float magnet_pull_amount = 0.02;
int magnet_pull=0;
int stage=1;
// int in_semicircle=180;

Timer t60(1.0 / 60);

/* Render the scene with openGL */
/* Edit this function according to your assignment */
void draw() {
    // clear the color and depth in the frame buffer
    glClear (GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    // use the loaded shader program
    // Don't change unless you know what you are doing
    glUseProgram (programID);
    // screen_center_x+=0.01;
    // Eye - Location of camera. Don't change unless you are sure!!
    glm::vec3 eye ( screen_center_x,screen_center_y,100 );

    // glm::vec3 eye ( 5*cos(camera_rotation_angle*M_PI/180.0f), 0, 5*sin(camera_rotation_angle*M_PI/180.0f) );
    // Target - Where is the camera looking at.  Don't change unless you are sure!!
    glm::vec3 target (screen_center_x, screen_center_y, 0);
    // Up - Up vector defines tilt of camera.  Don't change unless you are sure!!
    glm::vec3 up (0, 1, 0);

    // Compute Camera matrix (view)
    Matrices.view = glm::lookAt( eye, target, up ); // Rotating Camera for 3D
    // Don't change unless you are sure!!
    // Matrices.view = glm::lookAt(glm::vec3(0, 0, 3), glm::vec3(0, 0, 0), glm::vec3(0, 1, 0)); // Fixed camera for 2D (ortho) in XY plane

    // Compute ViewProject matrix as view/camera might not be changed for this frame (basic scenario)
    // Don't change unless you are sure!!
    glm::mat4 VP = Matrices.projection * Matrices.view;

    // Send our transformation to the currently bound shader, in the "MVP" uniform
    // For each model you render, since the MVP will be different (at least the M part)
    // Don't change unless you are sure!!
    glm::mat4 MVP;  // MVP = Projection * View * Model

    // Scene render
    ground.draw(VP);
    for(int i=0;i<semicircles.size();++i){
      semicircles[i].draw(VP);
    }
    ball.draw(VP);
    for(int i=0;i<coins.size();++i){
      coins[i].draw(VP);
    }
    for(int i=0;i<firelines.size();++i){
      firelines[i].draw(VP);
    }
    for(int i=0;i<firebeams.size();++i){
      firebeams[i].draw(VP);
    }
    for(int i=0;i<magnets.size();++i){
      magnets[i].draw(VP);
    }
    for(int i=0;i<strength.size();++i){
      strength[i].draw(VP);
    }
    for(int i=0;i<coin_dbl.size();++i){
      coin_dbl[i].draw(VP);
    }
    for(int i=0;i<waterballs.size();++i){
      waterballs[i].draw(VP);
    }
    for(int i=0;i<boomerangs.size();++i){
      boomerangs[i].draw(VP);
    }
    for(int i=0;i<props.size();++i){
      props[i].draw(VP);
    }
    for(int i=0;i<viserion.size();++i){
      viserion[i].draw(VP);
    }
    for(int i=0;i<iceballs.size();++i){
      iceballs[i].draw(VP);
    }

    display.draw(VP);
    life.draw(VP);
    // v.draw(VP);
}

void tick_input(GLFWwindow *window) {
    int left  = glfwGetKey(window, GLFW_KEY_LEFT);
    int right = glfwGetKey(window, GLFW_KEY_RIGHT);
    int up = glfwGetKey(window, GLFW_KEY_UP);
    int space = glfwGetKey(window, GLFW_KEY_SPACE);
    int water = glfwGetKey(window, GLFW_KEY_W);
    int down = glfwGetKey(window, GLFW_KEY_DOWN);


        if(water && WATER_TANK<=0){
           waterballs.push_back(Waterball(ball.position.x,ball.position.y));
           WATER_TANK+=200;
           cout<<"FIRED! YAY\n";
        }
    //cout<<"limit"<<screen_center_x+(4.0/screen_zoom)<<"\n";
    if((right && up)||(right && space)){
      //cout<<"RIGHTUP!\n";
      ball.right();
      // screen_center_x+=0.01;
      ball.up();// jetpack thrust so put all velocity gained due to falling to zero
      props.push_back(Propulsion(ball.position.x-0.5,ball.position.y));
    }
    else if((left && up)||(left && space)){
      //cout<<"LEFTUP!\n";
      ball.left();
      ball.up();// jetpack thrust so put all velocity gained due to falling to zero
      props.push_back(Propulsion(ball.position.x-0.5,ball.position.y));

    }
    else if (right) {
        //cout<<"RIGHT!\n";
        ball.right();
        if(magnet_pull==0)
        ball.gravity_fall();
    }
    else if (left) {
      //cout<<"LEFT!\n";
      ball.left();
      if(magnet_pull==0)
      ball.gravity_fall();
    }
    else if (up||space){
      //cout<<"UP!\n";
      props.push_back(Propulsion(ball.position.x-0.5,ball.position.y));
      ball.up();// jetpack thrust so put all velocity gained due to falling to zero
    }
    else if(down){
      //cout<<"DOWN!\n";
      ball.down();
      if(magnet_pull==0)
      ball.gravity_fall();
    }
    else{
  //    std:://cout<<"Nothing shit fuck\n";
     if(magnet_pull==0)
      ball.gravity_fall();
    }

}

void tick_elements() {
    ball.tick();
    if(IMMUNITY>0){
      IMMUNITY--;
    }
    if(DBL_SCORE>0){
      DBL_SCORE--;
    }
    if(WATER_TANK>0){
      WATER_TANK--;
    }
    if(VISERION>0){
      VISERION--;
    }
    // coin.position.x = screen_center_x;
    //coin.tick();
    // Bounding box for player Barry
    bounding_box_t ball_bb;
    ball_bb.width = 0.5f;
    ball_bb.height = 1.0f;
    ball_bb.x = ball.position.x-0.25;
    ball_bb.y = ball.position.y+0.5;

    for(int i=0;i<waterballs.size();i++){
      waterballs[i].tick();
      if(waterballs[i].position.y<=-3){
        waterballs.erase(waterballs.begin()+i);
        break;
      }
      int flag=0;
      for(int i=0;i<firebeams.size();i++){
        if(detect_collision_firebeam(waterballs[i].return_box(),firebeams[i].position.x,firebeams[i].position.y,firebeams[i].angle)){
          cout<<"Destroyed firebeam "<<i<<"\n";
          firebeams.erase(firebeams.begin()+i);
          waterballs.erase(waterballs.begin()+i);
          score+=100;
          flag=1;
          break;
          }
        }
      if(flag==0){
      for(int i=0;i<firelines.size();i++){
          if(detect_collision(waterballs[i].return_box(),firelines[i].return_box())){
            cout<<"Destroyed fireline "<<i<<"\n";
            firelines.erase(firelines.begin()+i);
            waterballs.erase(waterballs.begin()+i);
            score+=50;
            break;
            }
          }
      }
    }

    for(int i=0;i<coins.size();i++){
      coins[i].tick();

      if(coins[i].position.x<player_max_x-10)
         coins.erase(coins.begin()+i);

      if(detect_collision(coins[i].return_box(),ball_bb)){
        // cout<<"Collided with "<<i<<" :"<<coins[i].special<<"\n";
        if(coins[i].special==1){
           if(DBL_SCORE>0)
              score+=200;
           else
              score+=100;
         }
        else{
           if(DBL_SCORE>0)
              score+=50;
           else
              score+=25;
         }
        coins.erase(coins.begin()+i);
    }
  }
  for(int i=0;i<firelines.size();i++){
    firelines[i].tick();
    if(firelines[i].position.x<player_max_x-10)
       firelines.erase(firelines.begin()+i);
    if(detect_collision(firelines[i].return_box(),ball_bb)){
      cout<<"Collided with fireline "<<i<<"\n";
      if(IMMUNITY<=0)lives--;
      cout<<lives<<" iiiiiiiiii\n";
      if(lives>0){
         firelines.erase(firelines.begin()+i);
          ball.position.y =-3;//put player on ground
      }
      else{
        cout<<"DEAD!\n";
        exit(0);
      }
  }
}
    for(int i=0;i<firebeams.size();i++){

      if(firebeams[i].position.x<player_max_x-10)
         firebeams.erase(firebeams.begin()+i);

      if(detect_collision_firebeam(ball_bb,firebeams[i].position.x,firebeams[i].position.y,firebeams[i].angle)){
        cout<<"Collided with firebeam "<<i<<"\n";
      if(IMMUNITY<=0)lives--;
        if(lives>0){
          cout<<lives<<" iiiiiiiiii\n";
           firebeams.erase(firebeams.begin()+i);
            ball.position.y =-3;//put player on ground
        }
        else{
          cout<<"DEAD!\n";
          exit(0);
        }
    }
   }

   if(rand()%(53*7)==0){
     strength.push_back(Strength(player_max_x+8,-2+(rand()%6)));
   }
   if(rand()%(53*7)==0){
     coin_dbl.push_back(Coin_double(player_max_x+8,-2+(rand()%6)));
   }
   for(int i=0;i<strength.size();i++){
     strength[i].tick();
     if(strength[i].position.x<player_max_x-10)
        strength.erase(strength.begin()+i);
     if(detect_collision(strength[i].return_box(),ball_bb)){
       IMMUNITY+=500;
       strength.erase(strength.begin()+i);
     }
   }
   for(int i=0;i<coin_dbl.size();i++){
     coin_dbl[i].tick();
     if(coin_dbl[i].position.x<player_max_x-10)
        coin_dbl.erase(coin_dbl.begin()+i);
     if(detect_collision(coin_dbl[i].return_box(),ball_bb)){
       score+=500;
       DBL_SCORE+=500;
       coin_dbl.erase(coin_dbl.begin()+i);
     }
   }

   for(int i=0;i<magnets.size();i++){

     if(magnets[i].position.x<player_max_x-15)
        magnets.erase(magnets.begin()+i);

     if(ball.position.x>(magnets[i].position.x-4) && ball.position.x<=magnets[i].position.x){
      float theta = atan((magnets[i].position.y-ball.position.y)/(magnets[i].position.x-ball.position.x));
        ball.position.x+= magnet_pull_amount*cos(theta);
        ball.position.y+= magnet_pull_amount*sin(theta);
        magnet_pull=1;
        break;
     }
     else if(ball.position.x<(magnets[i].position.x+4) && ball.position.x>magnets[i].position.x){
      float theta = atan((magnets[i].position.y-ball.position.y)/(magnets[i].position.x-ball.position.x));
        ball.position.x-= magnet_pull_amount*cos(theta);
        ball.position.y-= magnet_pull_amount*sin(theta);
        magnet_pull=1;
        break;
     }
     else{
        magnet_pull=0;
     }
   }
   if(rand()%(47*7)==0){
     boomerangs.push_back(Boomerang(player_max_x+2,3.2));
   }
   for(int i=0;i<boomerangs.size();i++){
     boomerangs[i].tick();
     if(boomerangs[i].position.x<player_max_x-25|| boomerangs[i].position.y<=-3.5)
        boomerangs.erase(boomerangs.begin()+i);
     if(detect_collision(boomerangs[i].return_box(),ball_bb)){
       if(lives>0){
         lives--;
         cout<<lives<<" iiiiiiiiii\n";
       }
       cout<<"Collided with boomerang"<<i<<"\n";
      if(lives<=0){
        cout<<"Dead\n";
        exit(0);
      }
       boomerangs.erase(boomerangs.begin()+i);
     }
   }
   for(int i=0;i<props.size();i++){
     props[i].tick();
     if(props[i].position.x<player_max_x-10 || props[i].position.y<=-2.5)
        props.erase(props.begin()+i);
        // cout<<"deleteeee\n";
   }
   life.tick(screen_center_x+6,4.0,lives);
   display.tick(screen_center_x,4.0,score);

   if(score/1000>th){
     th = score/1000;
     cout<<"wow "<<th<<"\n";
     VISERION=500;
     viserion.push_back(Viserion(ball.position.x+5,ball.position.y));
   }
   if(score/1700>tth){
     tth = score/1700;
     viserion.pop_back();
   }
   for(int i=0;i<viserion.size();i++){
     viserion[i].position.x = ball.position.x+3;
     viserion[i].position.y = ball.position.y+0.5;
     cout<<VISERION<<" ___\n";
   }
   if(VISERION>0 && VISERION%60==0 && viserion.size()>0){
     iceballs.push_back(Iceball(viserion[0].position.x,viserion[0].position.y));
     cout<<"ICEBALL!\n";
   }
   for(int i=0;i<iceballs.size();i++){
       iceballs[i].tick();
       if(iceballs[i].position.x<player_max_x-10)
          iceballs.erase(iceballs.begin()+i);
       if(detect_collision(iceballs[i].return_box(),ball_bb)){
         cout<<"Collided with iceball "<<i<<"\n";
         if(IMMUNITY<=0)lives--;
         cout<<lives<<" iiiiiiiiii\n";
         if(lives>0){
            iceballs.erase(iceballs.begin()+i);
          //   ball.position.y =-3;//put player on ground
         }
         else{
           cout<<"DEAD!\n";
           exit(0);
         }
       }
   }
   for(int i=0;i<semicircles.size();i++){
       if(semicircles[i].position.x<player_max_x-10)
          semicircles.erase(semicircles.begin()+i);
       if(detect_collision_semi(ball_bb,semicircles[i].position.x,semicircles[i].position.y)){
         cout<<"Collided with semi"<<i<<"\n";
         // in_semicircle=semicircles[i].position.x;
         screen_center_x= semicircles[i].position.x+8;
         ball.position.x = semicircles[i].position.x+8;
       }
   }
}
/* Initialize the OpenGL rendering properties */
/* Add all the models to be created here */
void initGL(GLFWwindow *window, int width, int height) {
    /* Objects should be created before any other gl function and shaders */
    // Create the models
    // v = Viserion(7,2);
    ball       = Ball(-3, -3, COLOR_RED);
    ground     = Ground(0,0, COLOR_BROWN);
    for(int i=0;i<1000;i++){
       int p = (rand()%5==0)?1:0;
       if(p==0)
          coins.push_back(Coin(-4 + (rand() % 1005),-2 + (rand() % 5), COLOR_GOLD,p));
      else
          coins.push_back(Coin(-4 + (rand() % 1005),-2 + (rand() % 5), COLOR_RUBY,p));
    }
    for(int i=0;i<400;i+=10){
      firelines.push_back(Firelines(i + (rand()%6), float(-2 + (rand()%5)), 3.5-(rand()%3), -2.5+(rand()%2), 0.02+float(rand()%3)/100));
    }
    for(int i=5;i<400;i+=10){
      firebeams.push_back(FireBeams(i+rand()%6,float(-2.5 + (rand()%5)),float(20+(rand()%140))));
    }
    for(int i=15;i<400;i+=30){
      magnets.push_back(Magnet(i+rand()%3,float(0 + (rand()%4))));
    }
    for(int i=60;i<400;i+=100){
      semicircles.push_back(Semicircle(i,-3.0));
    }
    display = Score(screen_center_x,4.0,score);
    life = Number(screen_center_x+6,4.0,lives);
    // Create and compile our GLSL program from the shaders
    programID = LoadShaders("Sample_GL.vert", "Sample_GL.frag");
    // Get a handle for our "MVP" uniform
    Matrices.MatrixID = glGetUniformLocation(programID, "MVP");


    reshapeWindow (window, width, height);

    // Background color of the scene
    glClearColor (COLOR_BACKGROUND.r / 256.0, COLOR_BACKGROUND.g / 256.0, COLOR_BACKGROUND.b / 256.0, 0.0f); // R, G, B, A
    glClearDepth (1.0f);

    glEnable (GL_DEPTH_TEST);
    glDepthFunc (GL_LEQUAL);

    cout << "VENDOR: " << glGetString(GL_VENDOR) << endl;
    cout << "RENDERER: " << glGetString(GL_RENDERER) << endl;
    cout << "VERSION: " << glGetString(GL_VERSION) << endl;
    cout << "GLSL: " << glGetString(GL_SHADING_LANGUAGE_VERSION) << endl;
}
// int theta=180;
// void moveplayer(int semicircle){
//    theta--;
//    if(theta>=0){
//      in_semicircle=0;
//      theta=180;
//      cout<<"ended\n";
//      return;
//    }
//    ball.position.x = in_semicircle + 6* cos(theta/360*2*3.14159);
//    screen_center_x+=0.17;
//    ball.position.y = -3 + 6*sin(theta/360*2*3.14159);
// }

int main(int argc, char **argv) {
    srand(time(0));
    int width  = 1500;
    int height = 1000;

    window = initGLFW(width, height);

    initGL (window, width, height);

    /* Draw in loop */
    while (!glfwWindowShouldClose(window)) {
        // Process timers

        if (t60.processTick()) {
            // 60 fps
            // OpenGL Draw commands
            // cout<<in_semicircle<<"lol\n";
            draw();
            // Swap Frame Buffer in double buffering
            glfwSwapBuffers(window);

            // if(in_semicircle==180)
            // {
              tick_input(window);
              tick_elements();
            // }
            // else{
            //    moveplayer(in_semicircle);
            //    tick_elements();
            // }
        }

        // Poll for Keyboard and mouse events
        glfwPollEvents();
    }

    quit(window);
}

int detect_collision(bounding_box_t a, bounding_box_t b) {
    if ((abs(a.x - b.x) * 2 < (a.width + b.width)) &&
           (abs(a.y - b.y) * 2 < (a.height + b.height)))
           return 1;
    else
    return 0;
}
int detect_collision_semi(bounding_box_t a, float x,float y) {
  if( ((x-a.x)*(x-a.x))+((y-a.y)*(y-a.y)) < 6.5*6.5){
    cout<<"semicircle!\n";
    return 1;
  }
  return 0;

}
int detect_collision_firebeam(bounding_box_t a, float pos_x,float pos_y,float angle) {
    float m = tan((angle/360)*2*3.14159);
    float costheta = cos((angle/360)*2*3.14159);
    float sintheta = sin((angle/360)*2*3.14159);
    float c = pos_y - pos_x*m;
    // check top of player
    float x = (a.y + (a.height/2) - c)/m;
    if( x < (a.x+(a.width/2)) && x > (a.x-(a.width/2)) && x<(pos_x+2*costheta) && x>(pos_x) ){
       return 1;
    }
    x = (a.y - (a.height/2) - c)/m;
    if( x < (a.x+(a.width/2)) && x > (a.x-(a.width/2)) && x<(pos_x+2*costheta) && x>(pos_x) ){
       return 1;
    }
    float y = m*(a.x+a.width/2)+c;
    if( y < (a.y+(a.height/2)) && y > (a.y-(a.height/2)) && y>pos_y && y<(pos_y+2*sintheta) ){
       return 1;
    }
    y = m*(a.x-a.width/2)+c;
    if( y < (a.y+(a.height/2)) && y > (a.y-(a.height/2)) && y>pos_y && y<(pos_y+2*sintheta) ){
       return 1;
    }
    return 0;
}

void reset_screen(double screen_zoom) {
    float top    = screen_center_y + (4 / screen_zoom);
    float bottom = screen_center_y - (4 / screen_zoom);
    float left   = screen_center_x - (4 / screen_zoom);
    float right  = screen_center_x + (4 / screen_zoom);
    Matrices.projection = glm::ortho(left, right, bottom, top, 0.1f, 500.0f);
}
