#ifndef APPLICATION_H
#define APPLICATION_H
#endif // !1

#include <iostream>
#include "GameObject.h"
#include <time.h>
#include "Random.h"
#include "ParticleSystemh.h"


const int RESOLUTION_X = 1280;
const int RESOLUTION_Y = 720;
const int GAMEOBJECT_COUNT = 2;

class Application
{
private:

	//For fps counter
	float prevTime;
	float initTime;
	int frameCount;
	float rot;
	float deltaTime, curTime;

	//For testing sprite
	Sprite* m_dummySprite;
	Sprite* m_dummySprite2;
	Sprite* m_dummySprite3;
	Sprite* m_dummySprite4;

	//For testing gameobject
	GameObject* m_gameobjectArray[GAMEOBJECT_COUNT];
	float maxWidth;
	float maxheight;

	//for particle system
	Particlesystem* m_particleSystem0;
	Particlesystem* m_particleSystem1;

public:
	Application();
	virtual ~Application();
	virtual void Start();
	virtual void Update();
	virtual void Draw();
};

#pragma once
