//
// Created by tursh on 3/30/19.
//

#include <glm/gtx/transform.hpp>
#include "Grid/GridShader.h"

const char *BASICVERTEXSHADER = R"glsl(
#version 130
in vec4 in_Position;
in vec2 in_TexCoords;
out vec2 passTexCoords;

uniform mat4 transformationMatrix;

void main()
{
	gl_Position = transformationMatrix * in_Position;
	passTexCoords = in_TexCoords;
}
)glsl";

const char *BASICFRAGMENTSHADER = R"glsl(
#version 130
in vec2 passTexCoords;
out vec4 color;

uniform vec4 in_color;
uniform sampler2D tex;

void main()
{
    vec4 texColor = texture(tex, passTexCoords);

	color = texColor * in_color;
}
)glsl";

GridShader::GridShader()
        : ShaderProgram(BASICVERTEXSHADER, BASICFRAGMENTSHADER, false)
{
    getAllUniformLocation();
    start();
    loadMat4(transformationMatrixLocation, glm::mat4(1));
    loadVec4(color_inLocation, glm::vec4(1));
    stop();
}

void GridShader::getAllUniformLocation()
{
    transformationMatrixLocation = getUniformLocation("transformationMatrix");
    color_inLocation = getUniformLocation("in_color");
}

void GridShader::loadPiece(glm::mat4 transformationMatrix, unsigned int color)
{
    loadMat4(transformationMatrixLocation, transformationMatrix);

    //TODO LOAD TEXTURE
    float r = ((color >> 16) & 0xff) / 255.0f;
    float b = ((color >> 8) & 0xff) / 255.0f;
    float g = (color & 0xff) / 255.0f;
    loadVec4(color_inLocation, glm::vec4(r, b, g, 1));
}


