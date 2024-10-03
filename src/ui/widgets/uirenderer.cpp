#include "uirenderer.h"
#include "button.h"
#include "textlabel.h"

UIRenderer::UIRenderer() {
    Initialize();
}

UIRenderer::~UIRenderer() {
    glDeleteVertexArrays(1, &_quadVAO);
    glDeleteBuffers(1, &_quadVBO);
}

void UIRenderer::RenderButton(Button* button) {
    _buttonShader.use();

    if (button->GetIsHovered())
        DrawQuad(button->GetPosition(), button->GetSize(), {0.f, 0.f, 1.f});
    else if (button->GetIsDown())
        DrawQuad(button->GetPosition(), button->GetSize(), { 0.f, 1.f, 0.f });
    else
        DrawQuad(button->GetPosition(), button->GetSize(), button->GetColor());

    

    glm::vec2 paddedPosition = button->GetPosition() + glm::vec2(button->GetPadding(), button->GetPadding());
    RenderTextLabel(button->GetLabel(), paddedPosition, 1.f);
}

void UIRenderer::RenderText(TextLabel* textLabel) {
    RenderTextLabel(textLabel->GetText(), textLabel->GetPosition() + glm::vec2(0.f, 0.f), 1.f);
}

void UIRenderer::RenderTextLabel(const std::string& text, const glm::vec2& position, float scale) {
    _textShader.use();
    _fontRenderer.RenderText(_textShader, text, position, scale, glm::vec3(1.0f, 1.0f, 1.0f));
}

void UIRenderer::Initialize() {
    _buttonShader = Shader("assets/shaders/OrthoShader.vs", "assets/shaders/OrthoShader.fs");
    _textShader = Shader("assets/shaders/textShader.vs", "assets/shaders/textShader.fs");

    InitializeQuad();
    _fontRenderer.LoadFont("assets/fonts/arial.ttf", 24);
}

void UIRenderer::UpdateProjectionMatrix(float screenWidth, float screenHeight) {
    projectionMatrix = glm::ortho(0.0f, (float)screenWidth, (float)screenHeight, 0.0f); // Top-left origin
    _fontRenderer.UpdateProjectionMatrix(screenWidth, screenHeight);
}

void UIRenderer::DrawQuad(const glm::vec2& position, const glm::vec2& size, const glm::vec3& color) {
    _buttonShader.use();

    _buttonShader.setMat4("projection", projectionMatrix);
    _buttonShader.setVec3("color", color);
    _buttonShader.setVec3("borderColor", glm::vec3(0.f, 1.f, 0.f));
    _buttonShader.setFloat("borderWidth", 2.f);
    _buttonShader.setFloat("borderRadius", 5.f);
    _buttonShader.setVec2("resolution", size);

    glm::mat4 model = glm::mat4(1.0f);
    model = glm::translate(model, glm::vec3(position, 0.0f));
    model = glm::scale(model, glm::vec3(size, 1.0f));

    _buttonShader.setMat4("model", model);

    glBindVertexArray(_quadVAO);
    glDrawArrays(GL_TRIANGLE_STRIP, 0, 4);
    glBindVertexArray(0);
}

void UIRenderer::InitializeQuad() {
    // Define the vertices for a quad (2D rectangle)
    // Positions: Two triangles that form a rectangle using TRIANGLE_STRIP
    float quadVertices[] = {
        // X, Y (in normalized device coordinates)
        // Positions    // Texture coords
        0.0f, 1.0f,     0.0f, 1.0f,   // Top-left
        0.0f, 0.0f,     0.0f, 0.0f,   // Bottom-left
        1.0f, 1.0f,     1.0f, 1.0f,   // Top-right
        1.0f, 0.0f,     1.0f, 0.0f    // Bottom-right
    };

    // Create and bind the VAO
    glGenVertexArrays(1, &_quadVAO);
    glGenBuffers(1, &_quadVBO);

    glBindVertexArray(_quadVAO);

    // Create and bind the VBO
    glBindBuffer(GL_ARRAY_BUFFER, _quadVBO);
    glBufferData(GL_ARRAY_BUFFER, sizeof(quadVertices), quadVertices, GL_STATIC_DRAW);

    // Define the vertex attributes for position (location = 0 in the vertex shader)
    glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, 4 * sizeof(float), (void*)0); // 2 floats per vertex
    glEnableVertexAttribArray(0);

    // Define the vertex attributes for the texture coordinates (location = 1 in the vertex shader)
    glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 4 * sizeof(float), (void*)(2 * sizeof(float))); // 2 floats per vertex
    glEnableVertexAttribArray(1);

    // Unbind VBO and VAO
    glBindBuffer(GL_ARRAY_BUFFER, 0);
    glBindVertexArray(0);
}