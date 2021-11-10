#ifndef CUBE_H
#define CUBE_H

#include <array>
using std::array;

#include "../engine/Vector2.h"
#include "../engine/Vector3.h"
#include "../engine/Matrix4.h"
#include "../engine/Shader.h"
#include "Color.h"

enum class CubeType
{
    NONE,
    Spawner,
    WALL,
    FOOD,
    PFOOD,
    PACMAN,
    GHOST
};
class Cube {
public:
    Cube() = default;
    Cube(Vector2 tilePosP, Color colorP, CubeType type);

    Vector2 getTilePos() const { return tilePos; }
    void ChangeColor(Color newColor);
    void setTransform(const Matrix4& newTransform) { transform = newTransform; }

    void load();
    void draw(Shader& shader);
    void clean();
    void setTilePos(Vector2& pos) {tilePos = pos;}
    void setCubeType(CubeType type) {cubeType = type;}
    CubeType GetCubeType() const {return cubeType;}
    Color GetCubeColor() const {return color;};
    Vector3 getTranslation() const {return transform.getTranslation();}
private:
    Color color { WHITE };
    Vector2 tilePos { 0.0f, 0.0f };
    Vector3 pos { 0.0f, 0.0f, 0.0f };
    Matrix4 transform { Matrix4::identity };
    CubeType cubeType {CubeType::WALL};
    uint32_t vao { 0 };
    uint32_t vbo { 0 };
    static const array<float, 108> vertexPositions;
};

#endif