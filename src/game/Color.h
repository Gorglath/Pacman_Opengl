#ifndef COLOR_H
#define COLOR_H

struct Color
{
    float r;
    float g;
    float b;
    float a;

    array<GLfloat,4> toFloatArray() {return { r, g, b, a };}
};

constexpr Color BLUE { 0.0f, 0.0f, 0.7f, 1.0f };
constexpr Color GREEN { 0.0f, 0.7f, 0.0f, 1.0f };
constexpr Color RED { 0.7f, 0.0f, 0.0f, 1.0f };
constexpr Color YELLOW { 1.0f, 1.0f , 0.0f, 1.0f };
constexpr Color PURPLE {1.0f,0.0f,1.0f,1.0f};
constexpr Color ORANGE {1.0f,0.6f,0.1f,1.0f};
constexpr Color WHITE {1.0f,1.0f,1.0f,1.0f};
constexpr Color LIGHTBLUE{0.f,0.8f,1.0f,1.0f};

#endif