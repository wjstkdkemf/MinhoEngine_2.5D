#pragma once
#include "MinEntity.h"

namespace min {
	class Resource : public Entity // 추상 클래스 -> 자체로는 메모리 할당 x
	{
	public:
		Resource(enums::eResourceType type);
		virtual ~Resource();

		virtual HRESULT Save(const std::wstring path) = 0;
		virtual HRESULT Load(const std::wstring path) = 0; // 순수 가상함수 -> 반드시 상속받아 사용되야함.
		//HRESULT 는 Bool과 비슷하다
		const std::wstring& GetPath() { return mPath; }
		void SetPath(const std::wstring& path) { mPath = path; }

	private:
		enums::eResourceType mType;
		std::wstring mPath;
	};
}

