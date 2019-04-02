//
// Created by tursh on 3/29/19.
//

#include <cmath>
#include <Utils/Log.h>
#include <tuple>
#include <glm/vec2.hpp>
#include <Grid/GridShader.h>
#include <Loader/Loader.h>
#include <glm/gtx/transform.hpp>
#include "Grid/Grid.h"

const unsigned int PIECE_COUNT = 8;
const unsigned int SINGLE_TILE_PIECE_ID = 7;

const static bool PIECES_FORM[] =
        {
                1, 1,
                1, 1,

                1, 1, 1, 1,

                1, 0, 0,
                1, 1, 1,

                0, 0, 1,
                1, 1, 1,

                1, 1, 0,
                0, 1, 1,

                0, 1, 1,
                1, 1, 0,

                0, 1, 0,
                1, 1, 1,

                1,
        };


//<dimension, form location>
const static std::tuple<const glm::ivec2, const bool *> PIECES[] =
        {
                {glm::ivec2(2, 2), &PIECES_FORM[0]},
                {glm::ivec2(1, 4), &PIECES_FORM[4]},
                {glm::ivec2(3, 2), &PIECES_FORM[8]},
                {glm::ivec2(3, 2), &PIECES_FORM[14]},
                {glm::ivec2(3, 2), &PIECES_FORM[20]},
                {glm::ivec2(3, 2), &PIECES_FORM[26]},
                {glm::ivec2(3, 2), &PIECES_FORM[32]},
                {glm::ivec2(1, 1), &PIECES_FORM[38]}
        };

float TEXTURE_COORDS[] =
        {
                0, 0,
                0, 1,
                1, 0,
                1, 1
        };

GridShader *shader;


Grid::Grid(float top, float bottom, float right, float left, unsigned int width)
        : top_(top), bottom_(bottom), right_(right), left_(left), width_(width)
{
    if (right < left || top < bottom)
    logError("The grid should not have negative dimension");
    tileSize_ = (right - left) / width;
    height_ = (unsigned int) std::round((top - bottom) / tileSize_);

    grid_ = new int[width_ * height_];
    //Fill the grid wipiecesth false
    for (int i = 0; i < width_ * height_; ++i)
        grid_[i] = false;

    srand(time(nullptr));
    unsigned int pieceID = rand() % 7;
    pieceID = 3;
    scrollingPiece_ = {pieceID, {width_ / 2, height_ - std::get<0>(PIECES[pieceID]).y - 1, 0}, rand() & 0xffffff};

    if (shader == nullptr)
        shader = new GridShader;

    //Load piece models
    pieceModels_.reserve(PIECE_COUNT);
    for (const auto & piece : PIECES)
    {
        //Get piece info
        const auto &dim = std::get<0>(piece);
        const auto &form = std::get<1>(piece);
        //Get tile count
        unsigned int tileCount = 0;
        for (int j = 0; j < dim.x * dim.y; ++j)
            if (form[j])
                ++tileCount;

        auto *vertexPosition = new float[tileCount * 4 * 2];
        auto *vertexTexCoords = new float[tileCount * 4 * 2];
        auto *indices = new unsigned int[tileCount * 6];

        unsigned int count = 0;
        for (int j = 0; j < dim.x * dim.y; j++)
        {
            if (form[j])
            {
                int x = j % dim.x;
                int y = j / dim.x;

                vertexPosition[count * 8] = x * tileSize_;
                vertexPosition[count * 8 + 1] = y * tileSize_;
                vertexPosition[count * 8 + 2] = x * tileSize_;
                vertexPosition[count * 8 + 3] = (y + 1) * tileSize_;
                vertexPosition[count * 8 + 4] = (x + 1) * tileSize_;
                vertexPosition[count * 8 + 5] = y * tileSize_;
                vertexPosition[count * 8 + 6] = (x + 1) * tileSize_;
                vertexPosition[count * 8 + 7] = (y + 1) * tileSize_;

                std::copy(TEXTURE_COORDS, TEXTURE_COORDS + 8, vertexTexCoords + count * 8);

                indices[count * 6] = count * 4;
                indices[count * 6 + 1] = count * 4 + 1;
                indices[count * 6 + 2] = count * 4 + 2;
                indices[count * 6 + 3] = count * 4 + 2;
                indices[count * 6 + 4] = count * 4 + 1;
                indices[count * 6 + 5] = count * 4 + 3;

                ++count;
            }
        }

        CGE::Loader::Data<float> positionData(vertexPosition, tileCount * 8);
        CGE::Loader::Data<float> textureCoordsData(vertexTexCoords, tileCount * 8);
        CGE::Loader::Data<unsigned int> indicesData(indices, tileCount * 6);

        pieceModels_.push_back(CGE::Loader::DataToVAO(positionData, textureCoordsData, indicesData, false));

    }
    texture_.loadTexture("tile.png");
}

void Grid::tick()
{
    glm::ivec3 futurPosition = std::get<1>(scrollingPiece_);
    --futurPosition.y;
    if (isColliding(futurPosition))
    {
        //Get the scrolling piece info
        auto &scrollingPiece = PIECES[std::get<0>(scrollingPiece_)];
        auto &position = std::get<1>(scrollingPiece_);
        auto dimension = std::get<0>(scrollingPiece);
        const auto &form = std::get<1>(scrollingPiece);
        auto &color = std::get<2>(scrollingPiece_);
        auto rotation = futurPosition.z % 4;
        if (rotation < 0)
            rotation += 4;

        //Apply rotation to the dimension
        dimension = {(rotation % 2 == 0) ? dimension.x : dimension.y, (rotation % 2 == 0) ? dimension.y : dimension.x};

        //Set the piece in the grid
        for (int x = 0; x < dimension.x; ++x)
            for (int y = 0; y < dimension.y; ++y)
                if ((rotation == 0 && form[x + y * dimension.x])
                    || (rotation == 1 && form[y + (dimension.x - 1 - x) * dimension.y])
                    || (rotation == 2 && form[(dimension.x - 1 - x) + (dimension.y - 1 - y) * dimension.x])
                    || (rotation == 3 && form[(dimension.y - 1- y) + x * dimension.y]))
                    grid_[(position.x + x) + (position.y + y) * width_] = color;

        for (int i = 0; i < height_; ++i)
        {
            bool full = true;
            for(int j = 0; j < width_; ++j)
            {
                if(!grid_[j + i * width_])
                {
                    full = false;
                    break;
                }
            }
            if(full)
            {
                std::move(grid_ + (i + 1) * width_, grid_ + width_ * height_, grid_ + i * width_);
                --i;
            }
        }



        unsigned int pieceID = rand() % 7;
        scrollingPiece_ = {pieceID, {width_ / 2, height_ - std::get<0>(PIECES[pieceID]).y - 1, 0}, rand() & 0xffffff};
    } else
        std::get<1>(scrollingPiece_) = futurPosition;
}

void Grid::render()
{
    for (int i = 0; i < width_ * height_; ++i)
    {
        auto &pieceModel = pieceModels_[SINGLE_TILE_PIECE_ID];

        shader->start();
        shader->loadPiece(getTransformationMatrix({i % width_, i / width_}), grid_[i]);
        texture_.bind();
        pieceModels_[SINGLE_TILE_PIECE_ID]->render();
        shader->stop();
    }
    auto &pieceID = std::get<0>(scrollingPiece_);
    auto &pieceModel = pieceModels_[pieceID];

    shader->start();
    shader->loadPiece(getTransformationMatrix(scrollingPiece_), std::get<2>(scrollingPiece_));
    texture_.bind();
    pieceModels_[pieceID]->render();
    shader->stop();
}

void Grid::movePiece(Movement move)
{
    glm::ivec3 futurPosition = std::get<1>(scrollingPiece_);
    switch (move)
    {
        case LEFT:
            --futurPosition.x;
            break;
        case RIGHT:
            ++futurPosition.x;
            break;
        case DOWN:
            --futurPosition.y;
            break;
        case CLOCKWISE:
            --futurPosition.z;
            break;
        case COUNTER_CLOCKWISE:
            ++futurPosition.z;
            break;
    }
    if (!isColliding(futurPosition))
        std::get<1>(scrollingPiece_) = futurPosition;
}

bool Grid::isColliding(glm::ivec3 futurPosition)
{

    //Get the scrolling piece info
    auto &scrollingPiece = PIECES[std::get<0>(scrollingPiece_)];

    auto dimension = std::get<0>(scrollingPiece);
    const auto &form = std::get<1>(scrollingPiece);
    auto rotation = futurPosition.z % 4;

    if (rotation < 0)
        rotation += 4;

    //Apply rotation to the dimension
    dimension = {(rotation % 2 == 0) ? dimension.x : dimension.y, (rotation % 2 == 0) ? dimension.y : dimension.x};

    //Is out of bound
    if (0 > futurPosition.x || futurPosition.x + dimension.x > width_ || futurPosition.y < 0)
        return true;

    for (int x = 0; x < dimension.x; ++x)
        for (int y = 0; y < dimension.y; ++y)
            if (grid_[(futurPosition.x + x) + (futurPosition.y + y) * width_]
                && ((rotation == 0 && form[x + y * dimension.x])
                    || (rotation == 1 && form[y + (dimension.x - 1 - x) * dimension.y])
                    || (rotation == 2 && form[(dimension.x - 1 - x) + (dimension.y - 1 - y) * dimension.x])
                    || (rotation == 3 && form[(dimension.y - 1- y) + x * dimension.y])))
                return true;
    return false;
}

glm::mat4 Grid::getTransformationMatrix(std::tuple<unsigned int, glm::ivec3, unsigned int> piece)
{
    auto &pieceID = std::get<0>(piece);
    auto &piecePosition = std::get<1>(piece);
    auto dimension = std::get<0>(PIECES[pieceID]);
    int rotation = piecePosition.z % 4;
    if (rotation < 0)
        rotation += 4;
    //Apply rotation to the dimension
    dimension = {(rotation % 2 == 0) ? dimension.x : dimension.y, (rotation % 2 == 0) ? dimension.y : dimension.x};

    glm::vec3 position{left_ + tileSize_ * (piecePosition.x + dimension.x * (rotation >= 1 && rotation <= 2)),
                       bottom_ + tileSize_ * (piecePosition.y + dimension.y * (rotation >= 2)), 0};

    return glm::rotate(glm::translate(position), rotation * M_PI_2f32, glm::vec3(0, 0, 1));

}

glm::mat4 Grid::getTransformationMatrix(glm::ivec2 position)
{
    glm::vec3 relativePosition{left_ + tileSize_ * position.x,
                       bottom_ + tileSize_ * position.y, 0};
    return glm::translate(relativePosition);
}

