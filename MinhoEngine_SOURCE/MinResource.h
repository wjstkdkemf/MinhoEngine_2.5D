#pragma once
#include "MinEntity.h"

namespace min {
	class Resource : public Entity // �߻� Ŭ���� -> ��ü�δ� �޸� �Ҵ� x
	{
	public:
		Resource(enums::eResourceType type);
		virtual ~Resource();

		virtual HRESULT Save(const std::wstring path) = 0;
		virtual HRESULT Load(const std::wstring path) = 0; // ���� �����Լ� -> �ݵ�� ��ӹ޾� ���Ǿ���.
		//HRESULT �� Bool�� ����ϴ�
		const std::wstring& GetPath() { return mPath; }
		void SetPath(const std::wstring& path) { mPath = path; }

	private:
		enums::eResourceType mType;
		std::wstring mPath;
	};
}

