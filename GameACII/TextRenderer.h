#pragma once

#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <glm/glm.hpp>
#include <map>
#include <string>

// Structure to hold character data from the font atlas texture
struct Character {
    GLuint textureID;   // ID of the glyph texture
    glm::ivec2 size;    // Size of the glyph
    glm::ivec2 bearing; // Offset from the baseline to the left/top of the glyph
    GLuint advance;     // Horizontal offset to advance to the next glyph
};

class TextRenderer {
public:
    TextRenderer(const std::string& fontAtlasPath);
    ~TextRenderer();

    void initShaders();
    void loadFontAtlas(const std::string& fontAtlasPath);
    void renderText(const std::string& text, float x, float y, float scale, const glm::vec3& color);

    void createProgram(const std::string& vertexShaderSource, const std::string& fragmentShaderSource);

private:
    GLuint program;
    GLuint VAO, VBO;
    std::map<char, Character> characters;

    void createProgram(const char* vertexShaderSource, const char* fragmentShaderSource);
    GLuint compileShader(GLenum shaderType, const char* shaderSource);
};
