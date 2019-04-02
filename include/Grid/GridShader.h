//
// Created by tursh on 3/30/19.
//

#pragma once

#include <tuple>
#include <Shader/ShaderProgram.h>

class GridShader : public CGE::Shader::ShaderProgram
{
    unsigned int transformationMatrixLocation = 0,
            color_inLocation = 0;

protected:
    void getAllUniformLocation() override;

public:
    GridShader();

    void loadPiece(glm::mat4 transformationMatrix, unsigned int color);
};
