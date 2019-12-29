#pragma once

class cTexture;
class cScene abstract
{
private:
	cTexture* m_BG = nullptr;
public:
	cScene() {}
	virtual ~cScene() {}

	virtual void Init() PURE;
	virtual void Update() PURE;
	virtual void Render() PURE;
	virtual void Release() PURE;
};

