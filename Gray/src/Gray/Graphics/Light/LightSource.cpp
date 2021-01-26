#include "grpch.h"

#include "LightSource.h"
#include "Gray/Graphics/Defaults.h"

namespace Gray
{


	LightSource::LightSource() :
		color(LightColor()), source(nullptr),
		k0(Defaults::DEFAULT_K0), k1(Defaults::DEFAULT_K1), k2(Defaults::DEFAULT_K2),
		index(0), type(LightType::PointLight)
	{
		
	}


	std::tuple<float, float, float> LightSource::GetAttenuation()
	{
		return std::make_tuple(k0, k1, k2);
	}

	void LightSource::SetAttenuation(float k0, float k1, float k2)
	{
		this->k0 = k0;
		this->k1 = k1;
		this->k2 = k2;
	}

	void LightSource::SetIndex(uint index)
	{
		this->index = index;
	}

	uint LightSource::GetIndex()
	{
		return index;
	}

	LightType LightSource::GetType() { return type; }
	
}
