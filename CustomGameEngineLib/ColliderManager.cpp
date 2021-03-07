#include "CoreHeaders.h"
#include "ColliderManager.h"

ColliderManager::ColliderManager()
{
	//instance = this;
	std::cout << "created" << std::endl;
}

void ColliderManager::RemoveCollider(Collider* col)
{
	if (instance == nullptr)
	{
		instance = new ColliderManager();
		instance->AllColliders.remove(col);
	}
	else
	{
		//do whatever here
		instance->AllColliders.remove(col);
	}
}

void ColliderManager::AddCollider(Collider* col)
{

	if (instance == nullptr)
	{
		instance = new ColliderManager();
		instance->AllColliders.push_back(col);
		//std::cout << "added" << std::endl;
	}
	else
	{
		//do whatever here
		instance->AllColliders.push_back(col);
		//std::cout << "added" << std::endl;
		
	}
}

void ColliderManager::UpdateActiveColliders()
{
	if (instance == nullptr)
	{
		instance = new ColliderManager();
		if (!instance->ActiveColliders.empty())
		{
			instance->ActiveColliders.clear();
		}
		else
		{
			if (!instance->AllColliders.empty())
			{
				std::copy(instance->AllColliders.begin(), instance->AllColliders.end(), std::back_inserter(instance->ActiveColliders));
			}

		}
	}
	else
	{
		//do whatever here
		if (!instance->ActiveColliders.empty())
		{
			instance->ActiveColliders.clear();
		}
		else
		{
			if (!instance->AllColliders.empty())
			{
				std::copy(instance->AllColliders.begin(), instance->AllColliders.end(), std::back_inserter(instance->ActiveColliders));
			}
				
		}
	}
	
}

ColliderManager* ColliderManager::instance = nullptr;