#pragma once
template <typename T>
class singleton
{
private:
	static T* p = nullptr;
	singleton() {}
public:
	virtual ~singleton() {}

	static T* GetInst() {
		if (p == nullptr) p = new T;
		return p;
	}
	void ReleaseInst() {
		if (p != nullptr) delete p;
		p = nullptr;
	}
};