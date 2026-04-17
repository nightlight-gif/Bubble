#include "raylib.h"
#include <ctime>
#include <iostream>

class bubble{
  public:
    Vector2 position;
    Texture2D myTexture;
    int getscore =1;
    bubble(){
      position = { 
        (float)GetRandomValue(0, GetScreenWidth()-50), 
        (float)GetRandomValue(0, GetScreenHeight()-50) 
    };
      myTexture = LoadTexture("resources/bubble.png");
      if (myTexture.id == 0) {
        TraceLog(LOG_WARNING, "無法載入圖片！請檢查路徑或格式。");
      }
    }
    void draw(){
      DrawTextureEx(myTexture, position, 0.0f, 0.05f, WHITE);
    }
    void RE(){
      position = { 
        (float)GetRandomValue(0, GetScreenWidth()-50), 
        (float)GetRandomValue(0, GetScreenHeight()-50) 
    };
    }
    Rectangle bubbleRect(){
      return Rectangle{position.x, position.y, myTexture.width * 0.05f, myTexture.height * 0.05f};
    }
};

class bomb{
  public:
    Vector2 position;
    Texture2D myTexture;
    float speed = 15;
    int getscore =-5;

    bomb(){
      position = { 
        (float)GetRandomValue(0, GetScreenWidth()-50), 
        (float)GetRandomValue(0, GetScreenHeight()-50) 
    };
      myTexture = LoadTexture("resources/bomb.png");
      if (myTexture.id == 0) {
        TraceLog(LOG_WARNING, "無法載入圖片！請檢查路徑或格式。");
      }
    }
    void draw(){
      DrawTextureEx(myTexture, position, 0.0f, 0.09f, WHITE);
    }
    void RE(){
      position = { 
        (float)GetRandomValue(0, GetScreenWidth()-50), 
        (float)GetRandomValue(0, GetScreenHeight()-50) 
      };
    }
    void newplace(){
      if(GetRandomValue(0,1) == 0){
        position.x += speed;
        if(position.x > GetScreenWidth()){
          RE();
        }
      }
      else{
        position.y += speed;
        if(position.y > GetScreenHeight()){
          RE();
        }
      }

      }
    
    
    Rectangle bubbleRect(){
      return Rectangle{position.x, position.y, myTexture.width * 0.09f, myTexture.height * 0.09f};
    }
};

int main() {
  int score = 0;
  int life = 3;
  InitWindow(800, 450, "Raylib OOP");
  SetTargetFPS(60);
  bubble myBubble;
  bomb myBomb;

  SetRandomSeed(time(NULL));
  while (!WindowShouldClose()) {
    BeginDrawing();
    ClearBackground(RAYWHITE);
    DrawText(TextFormat("Score: %d", score), 10, 10, 20, DARKGRAY);
    DrawText(TextFormat("life: %d", life), 10, 40, 20, DARKGRAY);
    myBubble.draw();
    myBomb.draw();
    if(life>0) myBomb.newplace();
    if (IsMouseButtonPressed(MOUSE_BUTTON_LEFT) && life > 0) {
      if(CheckCollisionPointRec(GetMousePosition(), myBubble.bubbleRect())){ 
        myBubble.RE();
        score+=myBubble.getscore;
      }
      if(CheckCollisionPointRec(GetMousePosition(), myBomb.bubbleRect())){ 
        myBomb.RE();
        score+=myBomb.getscore;
        life--;
      }


    }
    if(life <= 0){
        UnloadTexture(myBubble.myTexture);
        UnloadTexture(myBomb.myTexture);
        DrawText("GAME OVER", 120, 160, 80, RED);
        DrawText(TextFormat("Final Score: %d", score), 250, 260, 30, DARKGRAY);
        DrawText("Press ESC to Exit", 280, 320, 20, GRAY);
      }

    EndDrawing();
  }
  if(life == 0){
    DrawText(TextFormat("Game Over"), 10, 10, 20, DARKGRAY);
  }
  CloseWindow();
  return 0;
}
