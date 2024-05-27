#include "raylib.h"
#include <string>

int main()
{
    const int screenWidth = 800;
    const int screenHeight = 450;

    InitWindow(screenWidth, screenHeight, "Login Interface");

    std::string username = "";
    std::string password = "";

    bool loginSuccess = false;

    SetTargetFPS(60);

    while (!WindowShouldClose())
    {
        BeginDrawing();

        ClearBackground(RAYWHITE);

        // Vẽ các thành phần của giao diện đăng nhập
        DrawText("Username:", 320, 200, 20, DARKGRAY);
        DrawText(username.c_str(), 420, 200, 20, DARKGRAY);
        DrawText("Password:", 320, 240, 20, DARKGRAY);
        DrawText(password.c_str(), 420, 240, 20, DARKGRAY);

        if (loginSuccess)
        {
            DrawText("Login successful!", 320, 280, 20, GREEN);
        }

        // Kiểm tra sự kiện bàn phím để nhập tên người dùng và mật khẩu
        if (IsKeyPressed(KEY_BACKSPACE))
        {
            if (!username.empty())
            {
                username.pop_back();
            }
        }
        else if (IsKeyPressed(KEY_ENTER))
        {
            if (!username.empty() && !password.empty())
            {
                // Kiểm tra tên người dùng và mật khẩu ở đây
                // Nếu đúng, set loginSuccess = true;
                loginSuccess = true;
            }
        }
        else if (IsKeyPressed(KEY_SPACE) || IsKeyPressed(KEY_ZERO) || IsKeyPressed(KEY_ONE) || IsKeyPressed(KEY_TWO) || IsKeyPressed(KEY_THREE) || IsKeyPressed(KEY_FOUR) || IsKeyPressed(KEY_FIVE) || IsKeyPressed(KEY_SIX) || IsKeyPressed(KEY_SEVEN) || IsKeyPressed(KEY_EIGHT) || IsKeyPressed(KEY_NINE) || IsKeyPressed(KEY_A) || IsKeyPressed(KEY_B) || IsKeyPressed(KEY_C) || IsKeyPressed(KEY_D) || IsKeyPressed(KEY_E) || IsKeyPressed(KEY_F) || IsKeyPressed(KEY_G) || IsKeyPressed(KEY_H) || IsKeyPressed(KEY_I) || IsKeyPressed(KEY_J) || IsKeyPressed(KEY_K) || IsKeyPressed(KEY_L) || IsKeyPressed(KEY_M) || IsKeyPressed(KEY_N) || IsKeyPressed(KEY_O) || IsKeyPressed(KEY_P) || IsKeyPressed(KEY_Q) || IsKeyPressed(KEY_R) || IsKeyPressed(KEY_S) || IsKeyPressed(KEY_T) || IsKeyPressed(KEY_U) || IsKeyPressed(KEY_V) || IsKeyPressed(KEY_W) || IsKeyPressed(KEY_X) || IsKeyPressed(KEY_Y) || IsKeyPressed(KEY_Z))
        {
            char key = GetKeyPressed();
            username += key;
        }

        // Vẽ một hình chữ nhật để hiển thị kí tự đang được nhập
        DrawRectangleLines(420, 200, 180, 20, BLACK);

        EndDrawing();
    }

    CloseWindow();

    return 0;
}
