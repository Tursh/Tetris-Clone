//
// Created by tursh on 3/29/19.
//

#pragma once

#include <vector>
#include <glm/vec3.hpp>
#include <glm/mat4x4.hpp>
#include <Loader/Models/Model.h>
#include <Loader/Texture.h>
#include <memory>

enum Movement
{
    LEFT, RIGHT, DOWN, CLOCKWISE, COUNTER_CLOCKWISE
};

class Grid
{
    unsigned int width_, height_;
    float tileSize_;
    float top_, bottom_, right_, left_;

    std::vector<std::shared_ptr<CGE::Loader::Model>> pieceModels_;
    CGE::Loader::Texture texture_;

    //<form index, position + rotation, color>
    std::tuple<unsigned int, glm::ivec3, unsigned int> scrollingPiece_;
    int *grid_;

    bool isColliding(glm::ivec3 futurPosition);

public:
    Grid(float top, float bottom, float right, float left, unsigned int width);

    void tick();
    void render();

    void movePiece(Movement move);
    glm::mat4 getTransformationMatrix(std::tuple<unsigned int, glm::ivec3, unsigned int> piece);
    glm::mat4 getTransformationMatrix(glm::ivec2 position);
};


