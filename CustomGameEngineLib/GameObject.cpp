#include <glad/glad.h>
#include <glfw3.h>
#include "Shader.h"
#include "Matrix.h"
#include "Vector.h"
#include "Sprite.h"
#include "Behavior.h"
#include "Collider.h"
#include "GameObject.h"
GameObject::GameObject()
{
	m_Position = Vector3(0.0f, 0.0f, 0.0f);
	m_Scale = Vector3(1.0f, 1.0f, 1.0f);
	m_Rotation = 0.0f;
	m_Color = Color::WHITE;
	m_Blend = Blendmode::Alpha;
	parent = nullptr;
	m_Sprite = nullptr;
	enabled = true;
	collider = nullptr;
	colliderEnabled = false;
	UpdatePosMatrix();
}

GameObject::~GameObject()
{

	//std::cout << "GameObject destructed" << std::endl;
}

GameObject::GameObject(Sprite* sprite)
{
	m_Sprite = sprite;
	m_Position = Vector3(0.0f, 0.0f, 0.0f);
	m_Scale = Vector3(1.0f, 1.0f, 1.0f);
	m_Rotation = 0.0f;
	m_Color = Color::WHITE;
	m_Blend = Blendmode::Alpha;
	parent = nullptr;
	enabled = true;
	collider = nullptr;
	colliderEnabled = false;
	UpdatePosMatrix();
}

GameObject::GameObject(Sprite* sprite, Vector3 pos)
{
	m_Sprite = sprite;
	m_Position = pos;
	m_Scale = Vector3(1.0f, 1.0f, 1.0f);
	m_Rotation = 0.0f;
	m_Color = Color::WHITE;
	m_Blend = Blendmode::Alpha;
	parent = nullptr;
	enabled = true;
	collider = nullptr;
	colliderEnabled = false;
	UpdatePosMatrix();
}

GameObject::GameObject(Sprite* sprite, Vector3 pos, GameObject* par)
{
	m_Sprite = sprite;
	m_Position = pos;
	m_Scale = Vector3(1.0f, 1.0f, 1.0f);
	m_Rotation = 0.0f;
	m_Color = Color::WHITE;
	m_Blend = Blendmode::Alpha;
	parent = par;
	enabled = true;
	collider = nullptr;
	colliderEnabled = false;
	UpdatePosMatrix();
}

void GameObject::SetPosition(Vector3 pos)
{
	m_Position = pos;
	UpdatePosMatrix();
}

Vector3 GameObject::GetPosition()
{
	return m_Position;
}

void GameObject::SetScale(Vector3 scale)
{
	m_Scale = scale;
	UpdatePosMatrix();
	if (collider != nullptr)
	{
		collider->CalculateRadius();
	}
}

Vector3 GameObject::GetScale()
{
	return m_Scale;
}

void GameObject::SetRotation(float rad)
{
	m_Rotation = rad;
	UpdatePosMatrix();
}

float GameObject::GetRotation()
{
	return m_Rotation;
}

void GameObject::SetColor(Color col)
{
	m_Color = col;
}

Color GameObject::GetColor()
{
	return m_Color;
}

void GameObject::SetBlendmode(Blendmode mode)
{
	m_Blend = mode;
}

Blendmode GameObject::GetBlendmode()
{
	return m_Blend;
}

void GameObject::SetEnable(bool e)
{
	enabled = e;
}

bool GameObject::GetEnabled()
{
	return enabled;
}



void GameObject::SetParent(GameObject* par)
{
	parent = par;
}

Matrix4 GameObject::GetMatrix()
{
	return m_GameObjectMatrix;
}

void GameObject::AddBehavior(Behavior* behavior)
{
	behavior->gameObject = this;
	attachedBehaviors.push_back(behavior);
}

void GameObject::StartBehaviors()
{
	if (!attachedBehaviors.empty())
	{
		for (it = attachedBehaviors.begin(); it != attachedBehaviors.end(); it++)
		{
			(*it)->Start();
		}
	}
}

void GameObject::EnableCollider()
{
	if (collider == nullptr)
	{
		collider = new Collider(this);
		colliderEnabled = true;
	}
}

void GameObject::DisableCollider()
{
	colliderEnabled = false;
}

void GameObject::Update(float deltaTime, Input& inputData)
{
	if (enabled)
	{
		if (!attachedBehaviors.empty())
		{
			for (it = attachedBehaviors.begin(); it != attachedBehaviors.end(); it++)
			{
				(*it)->Update(deltaTime, inputData);
			}
		}
		if (colliderEnabled)
		{
			collider->CheckCollision();
		}
	}

}

void GameObject::Draw()
{
	if (enabled)
	{
		if (!attachedBehaviors.empty())
		{
			for (it = attachedBehaviors.begin(); it != attachedBehaviors.end(); it++)
			{
				(*it)->Draw();
			}
		}

		UpdatePosMatrix();
		Matrix4 mat = m_GameObjectMatrix;
		if (parent != nullptr)
		{
			m_GameObjectMatrix =
				Matrix4::translate(Vector3(m_Position.x, m_Position.y, 0.0f)) *
				Matrix4::rotate(m_Rotation, Vector3(0, 0, 1))
				//Matrix4::scale(Vector3(scaleX, scaleY, 0.0f))
				;
			mat = parent->m_GameObjectMatrix * m_GameObjectMatrix;
		}
		if (m_Sprite != nullptr)
		{
			m_Sprite->Draw(m_GameObjectMatrix, m_Color, m_Blend);
		}
	}
}

void GameObject::UpdatePosMatrix()
{
	translateMatrix = Matrix4::translate(Vector3(m_Position.x, m_Position.y, 0.0f));
	rotateMatrix = Matrix4::rotate(m_Rotation, Vector3(0, 0, 1));
	if (m_Sprite != nullptr)
	{
		m_GameObjectMatrix =
			translateMatrix *
			rotateMatrix
			//Matrix4::scale(Vector3(scaleX, scaleY, 0.0f))
			* Matrix4::scale(Vector3(m_Scale.x * m_Sprite->m_Dimensions.x, m_Scale.y * m_Sprite->m_Dimensions.y, 0.0f));
	}
	else
	{
		m_GameObjectMatrix =
			translateMatrix *
			rotateMatrix
			//Matrix4::scale(Vector3(scaleX, scaleY, 0.0f))
			* Matrix4::scale(Vector3(m_Scale.x, m_Scale.y, 1.0f));
	}
	
}