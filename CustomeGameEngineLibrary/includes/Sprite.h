#pragma once
#include <string>
#include <glad/glad.h>
#include <glfw3.h>
#include "Matrix.h"
class Shader;
enum Blendmode
{
	None = 0,
	Alpha,
	Additive,
	Multiply
	
};

struct Color
{
	Color();
	Color(float r, float g, float b, float a);
	float r, g, b, a;

	static const Color WHITE;
	static const Color RED;
	static const Color GREEN;
	static const Color BLUE;
};

class Sprite
{
public:
	Sprite();
	Sprite(const std::string & file);
	~Sprite();

	void Draw(Matrix4 mat, Color col = Color::WHITE , Blendmode bMode = Alpha);
	Vector2 m_Dimensions;
	void SetShader(Shader* shader);

	Shader* m_Shader;

private:
	GLuint m_TextureID;
	Matrix4 m_gOthorMatrix;
	Matrix4 m_gViewMatrix;
	Matrix4 m_spriteMatrix;
	Matrix4 m_OrthoViewSpriteMatrix;
	
	Color m_Col;
	GLfloat m_meshQuadVertices[20] = {
		-1.0f, -1.0f, 0.0f, //position
		0.0f, 0.0f,  //Tex Coord
		-1.0f, 1.0f, 0.0f, //position
		0.0f, 1.0f,  //Tex Coord
		1.0f, -1.0f, 0.0f, //position
		1.0f, 0.0f, //Tex Coord
		1.0f, 1.0f, 0.0f, //position
		1.0f, 1.0f //Tex Coord
	};

	GLint m_vertexQuadIndices[6] =
	{
		0, 1, 2,
		3, 2, 1
	};
	GLuint VAO;
	GLuint VBO;
	GLuint EBO;
	void InitQuad();
	void DrawQuad();
	void GenerateTextureID();
	void loadTexturePNG(const char* path, GLuint textureID);
};