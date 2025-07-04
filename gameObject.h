#pragma once
#include "sgg/graphics.h"
#include "defines.h"


class Collision
{
public:
	virtual Disk getCollisionDisk() const = 0;
};

class GameObject
{
	static int m_next_id;
protected:
	class GameState* m_state;
	std::string m_name;
	int m_id = 0;
	bool m_active = true;
public:
	GameObject(GameState* gs, const std::string& name = "");
	virtual void update(float dt) {}
	virtual void init(float x, float y) {} // added  x,y  
	virtual void draw() {}
	virtual ~GameObject() {}
	bool isActive() { return m_active; }
	void setActive(bool a) { m_active = a; }
};

