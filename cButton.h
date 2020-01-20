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

	bool m_isOn = false;

	int m_alpha = 255;

public:
	cButton(const string& key);

	bool isLinkedLeft() { return (m_left != nullptr); }
	bool isLinkedRight(){ return (m_right != nullptr);}
	bool isLinkedUp()   { return (m_up != nullptr);   }
	bool isLinkedDown() { return (m_down != nullptr); }

	virtual void Update() override;
	virtual void Render() override;
};

