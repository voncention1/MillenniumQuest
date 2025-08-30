#include <raylib.h>
#include <millenniumquest/gmconfig.hpp>
#include <millenniumquest/sprite.hpp>

int main(){
    InitWindow(MQUEST_WIN_WIDTH, MQUEST_WIN_HEIGHT, "Millennium - Arisu Quest");
    SetTargetFPS(60);

    float delta = 0.0f;
    Rectangle groundframe = {0, MQUEST_WIN_HEIGHT / 2, MQUEST_WIN_WIDTH, MQUEST_WIN_HEIGHT / 2};

    mquest::Sprite aris_sprite{
        LoadTexture("sprites/aris_sprite.png"),
        Vector2{0, groundframe.y - 30},
        mquest::SpriteSheets{1U, 5U}
    };
    
    while(!WindowShouldClose()){
        PollInputEvents();
        delta = GetFrameTime();
        auto &aris_velocity = aris_sprite.velocity();
        auto &aris_position = aris_sprite.position();
        auto &aris_frame_rect = aris_sprite.frame_rect();
        if(IsKeyPressed(KEY_SPACE) || IsKeyPressed(KEY_LEFT)){
            aris_velocity.y = -250;
            aris_sprite.ground() = false;
        }
        if(CheckCollisionRecs(Rectangle{aris_position.x, aris_position.y, aris_frame_rect.width, aris_frame_rect.height}, groundframe)){
            aris_velocity.y = 0;
            aris_position.y = aris_velocity.y - aris_sprite.frame_rect().height;
            aris_sprite.ground() = true;
        } else {
            aris_sprite.ground() = false;
        }
        aris_sprite.update(delta);
        BeginDrawing();
        ClearBackground(RAYWHITE);
        DrawFPS(0,0);
        DrawRectangleRec(groundframe, DARKBROWN);
        aris_sprite.draw_sprite();
        EndDrawing();
    }
    aris_sprite.unload_sprite();
    CloseWindow();
    return 0;
}