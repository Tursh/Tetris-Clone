//
// Created by tursh on 3/29/19.
//

#pragma once

#include <vector>
#include <glm/vec3.hpp>
#include <glm/mat4x4.hpp>
#include <Loader/Models/Model.h>
#include <Loader/Texture.h>
#include <Grid/GridShader.h>
#include <memory>

enum Movement
{
    LEFT, RIGHT, DOWN, CLOCKWISE, COUNTER_CLOCKWISE, DROP
};

class Grid
{
    unsigned int width_, height_;
    float tileSize_;
    float top_, bottom_, right_, left_;

    std::vector<std::shared_ptr<CGE::Loader::Model>> pieceModels_;
    CGE::Loader::Texture tileTexture_, ghostTileTexture_;
    GridShader *shader_;

    //<form index, position + rotation, color>
    std::tuple<unsigned int, glm::ivec3, unsigned int> scrollingPiece_;
    //<form index, color>
    std::tuple<unsigned int, unsigned int> futurPiece_;
    glm::vec3 futurPiecePosition_;

    int *grid_;
    unsigned int level_ = 0, score_ = 0, lines_ = 0;

    bool isColliding(glm::ivec3 futurPosition);
    glm::mat4 getTransformationMatrix(std::tuple<unsigned int, glm::ivec3, unsigned int> piece);
    glm::mat4 getTransformationMatrix(glm::ivec2 position);

public:
    Grid(float top, float bottom, float right, float left, unsigned int width);
    ~Grid();

    void tick();
    void render();

    void movePiece(Movement move);

    //<level, score, cleared lines>
    std::tuple<unsigned int, unsigned int, unsigned int> getInfo();

    void setFuturPieceLocation(glm::vec3 newPosition);
};


