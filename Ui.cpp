#include "Ui.h"
#include <iostream>

Ui::Ui(int screenWidth, int screenHeight)
{
    _screenWidth = screenWidth;
    _screenHeight = screenHeight;
}

bool Ui::Initialize() {
    if (!InitializeText())
        return false;

    _shader = Shader("assets/shaders/OrthoShader.vs", "assets/shaders/OrthoShader.fs");

    _screenWidth = _screenWidth;
    _screenHeight = _screenHeight;
    _orthoMatrix = glm::ortho(0.0f, (float)_screenWidth, 0.0f, (float)_screenHeight);
    _quad2D[0] = glm::vec2(0, 1);
    _quad2D[1] = glm::vec2(0, 0);
    _quad2D[2] = glm::vec2(1, 1);
    _quad2D[3] = glm::vec2(1, 0);

    _console.x = 0;
    _console.y = _screenHeight;
    _console.width = _screenWidth;
    _console.height = 50;


    glGenVertexArrays(1, &_VAO);
    glGenBuffers(1, &_VBO);
    // bind the Vertex Array Object first, then bind and set vertex buffer(s), and then configure vertex attributes(s).
    glBindVertexArray(_VAO);

    glBindBuffer(GL_ARRAY_BUFFER, _VBO);
    glBufferData(GL_ARRAY_BUFFER, sizeof(_quad2D), _quad2D, GL_STATIC_DRAW);

    glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, sizeof(glm::vec2), (void*)0);
    glEnableVertexAttribArray(0);

    // note that this is allowed, the call to glVertexAttribPointer registered VBO as the vertex attribute's bound vertex buffer object so afterwards we can safely unbind
    glBindBuffer(GL_ARRAY_BUFFER, 0);

    // remember: do NOT unbind the EBO while a VAO is active as the bound element buffer object IS stored in the VAO; keep the EBO bound.
    //glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);

    // You can unbind the VAO afterwards so other VAO calls won't accidentally modify this VAO, but this rarely happens. Modifying other
    // VAOs requires a call to glBindVertexArray anyways so we generally don't unbind VAOs (nor VBOs) when it's not directly necessary.
    glBindVertexArray(0);

    return true;
}

bool Ui::InitializeText() {
    
    if (FT_Init_FreeType(&_freeFontLib))
    {
        std::cout << "ERROR::FREETYPE: Could not init FreeType Library" << std::endl;
        return false;
    }

    FT_Face face;
    if (FT_New_Face(_freeFontLib, "assets/fonts/arial.ttf", 0, &face))
    {
        std::cout << "ERROR::FREETYPE: Failed to load font" << std::endl;
        return false;
    }

    FT_Set_Pixel_Sizes(face, 0, 48);

    if (FT_Load_Char(face, 'X', FT_LOAD_RENDER))
    {
        std::cout << "ERROR::FREETYTPE: Failed to load Glyph" << std::endl;
        return false;
    }

    return true;
}

void Ui::Draw()
{
    _shader.use();
    _shader.setMat4("projection", _orthoMatrix);
    glm::mat4 model = glm::mat4(1.0);
    model = glm::scale(model, glm::vec3(_screenWidth, 100, 1));
    _shader.setMat4("model", model);
    glBindVertexArray(_VAO); // seeing as we only have a single VAO there's no need to bind it every time, but we'll do so to keep things a bit more organized
    //glDrawArrays(GL_TRIANGLE_STRIP, 0, 4);

    model = glm::translate(glm::mat4(1.0f), glm::vec3(_console.x, _console.y, 1));
    model = glm::scale(model, glm::vec3(_console.width, _console.height, 1));
    _shader.setMat4("model", model);
    glDrawArrays(GL_TRIANGLE_STRIP, 0, 4);
    
}

void Ui::ToggleConsole()
{
    _console.enabled = !_console.enabled;
    UpdateConsole();
}

void Ui::UpdateConsole()
{
    if (_console.enabled) {
        _console.x = 0;
        _console.y = _screenHeight;
        _console.width = _screenWidth;
        _console.height = 50;
    } else {
        _console.x = 0;
        _console.y = _screenHeight - 50;
        _console.width = _screenWidth;
        _console.height = 50;
    }
}