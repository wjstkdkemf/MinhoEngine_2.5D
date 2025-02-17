#include "MinMaterial.h"

namespace min
{
	Material::Material()
		: Resource(enums::eResourceType::Material)
	{
	}
	Material::~Material()
	{
	}
	HRESULT Material::Load(const std::wstring path)
	{
		return E_NOTIMPL;
	}
}
