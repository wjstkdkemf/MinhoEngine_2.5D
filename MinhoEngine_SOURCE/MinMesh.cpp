#include "MinMesh.h"

namespace min
{
	Mesh::Mesh()
		: Resource(enums::eResourceType::Mesh)
	{
	}
	Mesh::~Mesh()
	{
	}
	HRESULT Mesh::Load(const std::wstring path)
	{
		return E_NOTIMPL;
	}
}