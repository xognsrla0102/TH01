#pragma once
#include "cObject.h"
class cButton : public cObject
{
public:
	string m_key;
	string m_path;

	cButton* m_left =	nullptr;
	cButton* m_right=	nullptr;
	cButton* m_up   =	nullptr;
	cButton* m_down =	nullptr;

	int m_isOn = false;

	float m_alpha = 255.f;

	float m_oldSize = 1.f;
	float m_deltaSize = 0.5f;

public:
	cButton(const string& key, VEC2 size = VEC2(1.f, 1.f), float deltaSize = 0.5f);

	bool isLinkedLeft() { return (m_left != nullptr); }
	bool isLinkedRight(){ return (m_right != nullptr);}
	bool isLinkedUp()   { return (m_up != nullptr);   }
	bool isLinkedDown() { return (m_down != nullptr); }

	virtual void Update() override;
	virtual void Render() override;
};

