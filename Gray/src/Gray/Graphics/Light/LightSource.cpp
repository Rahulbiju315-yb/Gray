#include "grpch.h"

#include "LightSource.h"
#include "Gray/Graphics/Defaults.h"

namespace Gray
{
	template<typename T>
	std::shared_ptr<T> CreateLight(std::shared_ptr<Source> s, LightColor color)
	{
		return std::make_shared<T>(color, s);
	}

	LightSource::LightSource(LightType type,LightColor color, std::shared_ptr<Source> source) :
		color(color), source(source),
		k0(Defaults::DEFAULT_K0), k1(Defaults::DEFAULT_K1), k2(Defaults::DEFAULT_K2),
		index(0), type(type)
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

	void LightSource::SetIndex(unsigned int index)
	{
		this->index = index;
	}

	unsigned int LightSource::GetIndex()
	{
		return index;
	}

	LightType LightSource::GetType() { return type; }
	
}
