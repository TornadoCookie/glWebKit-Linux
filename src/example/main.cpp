
#if defined(_WIN32)
#include "windows.h"
#endif

#include <raylib.h>
#include <raymath.h>
#include "rlWebKit/rlWebKit.h"

//#include "glUtil.h"

#include <vector>
#include <iostream>
#include <sstream>
#include <string>

//Screen dimension constants
const int SCREEN_WIDTH = 1280;
const int SCREEN_HEIGHT = 720;

EA::WebKit::View* v;

/*
//OpenGL context
SDL_GLContext gContext;
DrawCall screenQuad;
DrawCall cube;

void initGL()
{
   GLenum err = glewInit();
   if(GLEW_OK != err)
   {
      std::cout << "Error initializing GLEW" << std::endl;
      exit(0);
   }

   //common rendering settings, ideally would be part of the draw call
   glEnable(GL_BLEND);
   glBlendEquation(GL_FUNC_ADD);
   glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

   glEnable(GL_CULL_FACE);
}

void initScreenQuad()
{
   std::vector<DrawVertex> verts;
   std::vector<unsigned short> indexes;
   
   verts.resize(4);
   indexes.resize(6);
   
   verts[0].position = Vector3(0, 0, 0);                        verts[0].uv = Vector2(0, 0);
   verts[1].position = Vector3(SCREEN_WIDTH, 0, 0);             verts[1].uv = Vector2(1, 0);
   verts[2].position = Vector3(SCREEN_WIDTH, SCREEN_HEIGHT, 0); verts[2].uv = Vector2(1, 1);
   verts[3].position = Vector3(0, SCREEN_HEIGHT, 0);            verts[3].uv = Vector2(0, 1);

   indexes[0] = 0; indexes[1] = 1; indexes[2] = 2;
   indexes[3] = 0; indexes[4] = 2; indexes[5] = 3;

   screenQuad.indexCount = indexes.size();

   glGenBuffers(1, &screenQuad.myVertexBuffer);
   glGenBuffers(1, &screenQuad.myIndexBuffer);
   glGenVertexArrays(1, &screenQuad.myVao);
   
   screenQuad.myProgram = createShader(webkitVertexShader, webkitFragmentShader);
   
   //get uniform locations
   screenQuad.myViewUniform = glGetUniformLocation(screenQuad.myProgram, "view");
   screenQuad.myProjectionUniform = glGetUniformLocation(screenQuad.myProgram, "projection");
   screenQuad.myTextureUniform = glGetUniformLocation(screenQuad.myProgram, "tex");

   //setup the buffers
   glBindBuffer(GL_ARRAY_BUFFER, screenQuad.myVertexBuffer);
   glBufferData(GL_ARRAY_BUFFER, verts.size() * sizeof(DrawVertex), &verts[0], GL_STATIC_DRAW);
   glBindBuffer(GL_ARRAY_BUFFER, 0);

   glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, screenQuad.myIndexBuffer);
   glBufferData(GL_ELEMENT_ARRAY_BUFFER, indexes.size() * sizeof(unsigned short), &indexes[0], GL_STATIC_DRAW);
   glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);

   //Setup the VAO
   glBindVertexArray(screenQuad.myVao);
   glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, screenQuad.myIndexBuffer);
   glBindVertexBuffer(0, screenQuad.myVertexBuffer, 0, sizeof(DrawVertex));
   int attrLoc;

   attrLoc = glGetAttribLocation(screenQuad.myProgram, "position");
   glVertexAttribFormat(attrLoc, 3, GL_FLOAT, GL_FALSE, 0);
   glVertexAttribBinding(attrLoc, 0);
   glEnableVertexAttribArray(attrLoc);

   attrLoc = glGetAttribLocation(screenQuad.myProgram, "uv");
   glVertexAttribFormat(attrLoc, 2, GL_FLOAT, GL_FALSE, 12);
   glVertexAttribBinding(attrLoc, 0);
   glEnableVertexAttribArray(attrLoc);

   //cleanup VAO
   glBindVertexArray(0);
   glBindBuffer(GL_ARRAY_BUFFER, 0);
   glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);

   //setup texture
   glCreateTextures(GL_TEXTURE_2D, 1, &screenQuad.myTexture);
   glTextureParameteri(screenQuad.myTexture, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
   glTextureParameteri(screenQuad.myTexture, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
   glTextureParameteri(screenQuad.myTexture, GL_TEXTURE_WRAP_S, GL_CLAMP);
   glTextureParameteri(screenQuad.myTexture, GL_TEXTURE_WRAP_T, GL_CLAMP);
   glTextureStorage2D(screenQuad.myTexture, 1, GL_RGBA8, SCREEN_WIDTH, SCREEN_HEIGHT);
   glBindTexture(GL_TEXTURE_2D, 0);
}

void initCube()
{
   std::vector<DrawVertex> verts;
   std::vector<unsigned short> indexes;

   verts.resize(8);
   indexes.resize(36);

   verts[0].position = Vector3(-1, -1, -1);  verts[0].color = 0xff0000ff; //red
   verts[1].position = Vector3( 1, -1, -1);  verts[1].color = 0xff00ff00; //green
   verts[2].position = Vector3(-1,  1, -1);  verts[2].color = 0xffff0000; //blue
   verts[3].position = Vector3( 1,  1, -1);  verts[3].color = 0xffffffff; //white
   verts[4].position = Vector3(-1, -1,  1);  verts[4].color = 0xff000000; //black
   verts[5].position = Vector3( 1, -1,  1);  verts[5].color = 0xff00ffff; //yellow
   verts[6].position = Vector3(-1,  1,  1);  verts[6].color = 0xffffff00; //aqua
   verts[7].position = Vector3( 1,  1,  1);  verts[7].color = 0xffff00ff; //fuchsia

   int i = 0;
   indexes[i++] = 1; indexes[i++] = 0; indexes[i++] = 2; //front
   indexes[i++] = 1; indexes[i++] = 2; indexes[i++] = 3;
   indexes[i++] = 0; indexes[i++] = 4; indexes[i++] = 6; //left
   indexes[i++] = 0; indexes[i++] = 6; indexes[i++] = 2;
   indexes[i++] = 5; indexes[i++] = 1; indexes[i++] = 3; //right
   indexes[i++] = 5; indexes[i++] = 3; indexes[i++] = 7;
   indexes[i++] = 4; indexes[i++] = 5; indexes[i++] = 7; //back
   indexes[i++] = 4; indexes[i++] = 7; indexes[i++] = 6;
   indexes[i++] = 6; indexes[i++] = 7; indexes[i++] = 3; //top
   indexes[i++] = 6; indexes[i++] = 3; indexes[i++] = 2;
   indexes[i++] = 0; indexes[i++] = 1; indexes[i++] = 5; //bottom
   indexes[i++] = 0; indexes[i++] = 5; indexes[i++] = 4;

   cube.indexCount = indexes.size();

   glGenBuffers(1, &cube.myVertexBuffer);
   glGenBuffers(1, &cube.myIndexBuffer);
   glGenVertexArrays(1, &cube.myVao);

   cube.myProgram = createShader(cubeVertexShader, cubeFragmentShader);

   //get uniform locations
   cube.myViewUniform = glGetUniformLocation(cube.myProgram, "view");
   cube.myProjectionUniform = glGetUniformLocation(cube.myProgram, "projection");
   cube.myModelUniform = glGetUniformLocation(cube.myProgram, "model");

   //setup the buffers
   glBindBuffer(GL_ARRAY_BUFFER, cube.myVertexBuffer);
   glBufferData(GL_ARRAY_BUFFER, verts.size() * sizeof(DrawVertex), &verts[0], GL_STATIC_DRAW);
   glBindBuffer(GL_ARRAY_BUFFER, 0);

   glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, cube.myIndexBuffer);
   glBufferData(GL_ELEMENT_ARRAY_BUFFER, indexes.size() * sizeof(unsigned short), &indexes[0], GL_STATIC_DRAW);
   glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);

   //Setup the VAO
   glBindVertexArray(cube.myVao);
   glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, cube.myIndexBuffer);
   glBindVertexBuffer(0, cube.myVertexBuffer, 0, sizeof(DrawVertex));
   int attrLoc;

   attrLoc = glGetAttribLocation(cube.myProgram, "position");
   glVertexAttribFormat(attrLoc, 3, GL_FLOAT, GL_FALSE, 0);
   glVertexAttribBinding(attrLoc, 0);
   glEnableVertexAttribArray(attrLoc);

   attrLoc = glGetAttribLocation(cube.myProgram, "color");
   glVertexAttribFormat(attrLoc, 4, GL_UNSIGNED_BYTE, GL_TRUE, 20);
   glVertexAttribBinding(attrLoc, 0);
   glEnableVertexAttribArray(attrLoc);

   //cleanup VAO
   glBindVertexArray(0);
   glBindBuffer(GL_ARRAY_BUFFER, 0);
   glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
}

void drawCube()
{
   static float rotx = 0;
   static float roty = 0;

   rotx += 0.001f;
   roty += 0.001f;

   glClearColor(0.2f, 0.2f, 0.2f, 1.0f);
   glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

   glm::mat4 proj = glm::perspective(45.0f, (float)SCREEN_WIDTH / (float)SCREEN_HEIGHT, 0.1f, 100.0f);
   glm::mat4 model = glm::mat4(1.0f);
   model = glm::rotate(model, rotx, glm::vec3(1, 0, 0));
   model = glm::rotate(model, roty, glm::vec3(0, 1, 0));
   glm::mat4 view = glm::lookAt<float>(glm::vec3(0.f, 0.f, 5.0f), glm::vec3(0.f, 0.f, 0.f), glm::vec3(0.0f, 1.0f, 0.0f));

   
   glEnable(GL_BLEND);
   glBindTexture(GL_TEXTURE_2D, cube.myTexture);
   glUseProgram(cube.myProgram);
   glUniformMatrix4fv(cube.myProjectionUniform, 1, GL_FALSE, glm::value_ptr(proj));
   glUniformMatrix4fv(cube.myViewUniform, 1, GL_FALSE, glm::value_ptr(view));
   glUniformMatrix4fv(cube.myModelUniform, 1, GL_FALSE, glm::value_ptr(model));
   glBindVertexArray(cube.myVao);
   glDrawElements(GL_TRIANGLES, cube.indexCount, GL_UNSIGNED_SHORT, 0);
}

void drawInterface(EA::WebKit::View* v)
{
   updateGLTexture(v, screenQuad.myTexture);

   glm::mat4 proj = glm::ortho<float>(0.0f, (float)SCREEN_WIDTH, 0.0f, (float)SCREEN_HEIGHT, 0.1f, 100.0f);
   glm::mat4 view = glm::lookAt<float>(glm::vec3(0.f, 0.f, 5.0f), glm::vec3(0.f, 0.f, 0.f), glm::vec3(0.0f, 1.0f, 0.0f));
   
   glEnable(GL_BLEND);
   glBindTexture(GL_TEXTURE_2D, screenQuad.myTexture);
   glUseProgram(screenQuad.myProgram);
   glUniformMatrix4fv(screenQuad.myProjectionUniform, 1, GL_FALSE, glm::value_ptr(proj));
   glUniformMatrix4fv(screenQuad.myViewUniform, 1, GL_FALSE, glm::value_ptr(view));
   glBindVertexArray(screenQuad.myVao);
   glDrawElements(GL_TRIANGLES, screenQuad.indexCount, GL_UNSIGNED_SHORT, 0);
}
*/
int main(int argc, char** argv, char **envp)
{
   void SDL_SetMainReady(void);

//   for (int i = 0; envp[i] != NULL; i++)
//   {
//       printf("envp[%d]=%s\n",i,envp[i]);
//   }

const char* display_env = getenv("DISPLAY");
    if (display_env == NULL) {
        printf("DISPLAY is not set or accessible.\n");
    } else {
        printf("DISPLAY is set to: %s\n", display_env);
    }

   InitWindow(SCREEN_WIDTH, SCREEN_HEIGHT, "Webkit Test");

   //Main loop flag
   bool quit = false;

   //Event handler

   //initialization
   //initGL();
   //initScreenQuad();
   //initCube();
   initWebkit();

   Image img = GenImageColor(SCREEN_WIDTH, SCREEN_HEIGHT, BLANK);
   Texture2D screenTex = LoadTextureFromImage(img);

   UnloadImage(img);

   //create the web view
   v = createView(SCREEN_WIDTH, SCREEN_HEIGHT);

   SetTargetFPS(60);

   std::string url(argv[1]); //std::string("file:///") + SDL_GetBasePath() + "/UI/actionMenu.html";
   std::cout << "navigating to " << url << '\n';
   setViewUrl(v, url.c_str());

   Camera camera = {0};
   camera.position = (Vector3){10, 10, 0};
   camera.target = (Vector3){0, 0, 0};
   camera.fovy = 70;
   camera.up = (Vector3){0, 1, 0};

      //Handle events on queue
      while(!WindowShouldClose())
      {

         if (IsKeyPressed(KEY_F5))
         {
             reload(v);
         }

        mousemove(v, GetMouseDelta().x, GetMouseDelta().y);

         int mouseButtonPressed = -1;
         bool mouseButtonState;

        // kMouseLeft = 0
        // kMouseMiddle = 1
        // kMouseRight = 2

         if (IsMouseButtonPressed(MOUSE_BUTTON_LEFT))
         {
             mouseButtonPressed = 0;
             mouseButtonState = true;
         }
         else if (IsMouseButtonReleased(MOUSE_BUTTON_LEFT))
         {
             mouseButtonPressed = 0;
             mouseButtonState = false;
         }

         if (mouseButtonPressed != -1)
         {
             mousebutton(v, GetMouseX(), GetMouseY(), mouseButtonPressed, mouseButtonState);
         }

         mousewheel(v, GetMouseX(), GetMouseY(), 0, GetMouseWheelMove()*60);

         UpdateCamera(&camera, CAMERA_ORBITAL);

      BeginDrawing();
      ClearBackground(RAYWHITE);

      BeginMode3D(camera);

      DrawCubeWires((Vector3){0, 0, 0}, 1, 1, 1, RED);

      EndMode3D();

      //update the things
      updateWebkit();
      updateView(v);

      updateGLTexture(v, screenTex.id);
      DrawTexture(screenTex, 0, 0, WHITE);
     
      //draw the things
      //drawCube();
      //drawInterface(v);      

      //Update screen
      EndDrawing();
   }

   //cleanup Webkit
   destroyView(v);
   shutdownWebKit();

   return 0;
}
