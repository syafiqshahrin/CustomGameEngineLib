#pragma once
class Vector3;
class EmitterShape
{
public:
	virtual Vector3 GetEmitterSpawnPosition(const Vector3& particleSystemPos) = 0;
};