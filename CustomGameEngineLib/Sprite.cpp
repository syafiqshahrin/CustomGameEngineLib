#include "stb_image.h"
#include "Shader.h"
#include "Vector.h"
#include "Sprite.h"

Color::Color()
{
	r = 1.0f;
	g = 1.0f;
	b = 1.0f;
	a = 1.0f;
}
Color::Color(float r, float g, float b, float a)
{
	this->r = r;
	this->g = g;
	this->b = b;
	this->a = a;
}

const Color Color::WHITE(1.0f, 1.0f, 1.0f, 1.0f);
const Color Color::RED(1.0f, 0.0f, 0.0f, 1.0f);
const Color Color::BLUE(0.0f, 0.0f, 1.0f, 1.0f);
const Color Color::GREEN(0.0f, 1.0f, 0.0f, 1.0f);

Sprite::Sprite()
{
	m_TextureID = -1;
	float aspectRatio = 1600.0f / 1000.0f;
	m_Shader = new Shader("../Shaders/basicSpriteVert.vert", "../Shaders/basicSpriteFrag.frag");
	m_gOthorMatrix = Matrix4::ortho((1600.0f / 2.0f) * -1.0f, (1600.0f / 2.0f) * 1.0f, (1000.0f / 2.0f) * -1.0f, (1000.0f / 2.0f) * 1.0f, -1.0f, 1.0f);
	m_gViewMatrix = Matrix4::translate(Vector3(0.0f, 0.0f, -2.0f));
	m_Dimensions = Vector2(1.0f, 1.0f);
	InitQuad();
}
Sprite::Sprite(const std::string& textureFile)
{
	float aspectRatio = 1600.0f / 1000.0f;
	m_Shader = new Shader("../Shaders/basicSpriteVert.vert", "../Shaders/basicSpriteFrag.frag");
	m_gOthorMatrix = Matrix4::ortho((1600.0f /2.0f) * -1.0f, (1600.0f / 2.0f) * 1.0f, (1000.0f/2.0f)*-1.0f, (1000.0f / 2.0f) * 1.0f, -1.0f, 1.0f);
	m_gViewMatrix = Matrix4::translate(Vector3(0.0f, 0.0f, -1.0f));
	GenerateTextureID();
	loadTexturePNG(textureFile.c_str(), m_TextureID);
	InitQuad();

}
Sprite::~Sprite()
{
	
}

void Sprite::Draw(Matrix4 mat, Color col, Blendmode bMode)
{
	m_Col = col;
	m_spriteMatrix = mat;
	m_OrthoViewSpriteMatrix = m_gOthorMatrix * m_gViewMatrix * m_spriteMatrix;
	m_Shader->use();
	m_Shader->setMat4("uModelMatrix", m_spriteMatrix.data);
	m_Shader->setMat4("uOrthoModelMatrix", m_OrthoViewSpriteMatrix.data);

	m_Shader->setInt("Main_Tex", 0);
	m_Shader->setVec4("Color", m_Col.r, m_Col.g, m_Col.b, m_Col.a);
	glActiveTexture(GL_TEXTURE0 + 0);
	glBindTexture(GL_TEXTURE_2D, m_TextureID);
	switch(bMode)
	{
		case Blendmode::None:
			glDisable(GL_BLEND);
			glDepthMask(GL_TRUE);
			break;
		case Blendmode::Alpha:
			glEnable(GL_BLEND);
			glDepthMask(GL_TRUE);
			glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
			break;
		case Blendmode::Additive:
			glEnable(GL_BLEND);
			glDepthMask(GL_FALSE);
			glBlendFunc(GL_SRC_ALPHA, GL_ONE);
			break;
		case Blendmode::Multiply:
			glEnable(GL_BLEND);
			glDepthMask(GL_FALSE);
			glBlendFunc(GL_DST_COLOR, GL_ONE_MINUS_SRC_ALPHA);

			break;
		default:
			glDisable(GL_BLEND);
			glDepthMask(GL_TRUE);
			break;
	}
	DrawQuad();
}

void Sprite::SetShader(Shader* shader)
{
	m_Shader = shader;
}

void Sprite::DrawQuad()
{
	glBindVertexArray(VAO);
	glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);
}
void Sprite::InitQuad()
{


	//Create buffer objects
	glGenVertexArrays(1, &VAO); //vertex array object
	glGenBuffers(1, &VBO); // vertex buffer object
	glGenBuffers(1, &EBO); //element buffer object

	//bind buffers
	glBindVertexArray(VAO);
	glBindBuffer(GL_ARRAY_BUFFER, VBO);
	glBufferData(GL_ARRAY_BUFFER, sizeof(m_meshQuadVertices), m_meshQuadVertices, GL_STATIC_DRAW); //send vertex data to vbo

	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(m_vertexQuadIndices), m_vertexQuadIndices, GL_STATIC_DRAW); //send vertex indices data

	//linking vertex attribute for vertex pos
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 5 * sizeof(GLfloat), (void*)0);
	glEnableVertexAttribArray(0);

	//linking vertex attribute for tex coord
	glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 5 * sizeof(GLfloat), (void*)(0 + 3 * sizeof(GLfloat)));
	glEnableVertexAttribArray(1);

	//unbinding the buffers
	glBindVertexArray(0);
	//unbind vertex array first before unbind the element buffer/vbo
	glBindBuffer(GL_ARRAY_BUFFER, 0);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
}
void Sprite::GenerateTextureID()
{
	glGenTextures(1, &m_TextureID);

}
void Sprite::loadTexturePNG(const char* path, GLuint textureID)
{
	glBindTexture(GL_TEXTURE_2D, textureID);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT); //Apply texture wrapping along horizontal part
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT); //Apply texture wrapping along vertical part

	//old school (minecraft) filtering
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR); // near filtering. (For when textures needs to scale up on screen)
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR); // far filtering. (For when textures needs to scale down on screen)

	stbi_set_flip_vertically_on_load(true);
	int width, height, nrChannels;
	unsigned char* data = stbi_load(path, &width, &height, &nrChannels, 4);

	if (data)
	{
		glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, width, height, 0, GL_RGBA, GL_UNSIGNED_BYTE, data);
		m_Dimensions = Vector2(width, height);
	}
	else
	{

		std::cout << "Failed to load texture: " << stbi_failure_reason() << std::endl;
	}

	//glGenerateMipmap(GL_TEXTURE_2D);
	stbi_image_free(data);
}
