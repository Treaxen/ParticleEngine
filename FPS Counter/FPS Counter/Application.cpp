#include "Application.h"

Application::Application()
{
	//FPS counter
	prevTime = glfwGetTime();
	initTime = glfwGetTime();
	frameCount = 0;

	//Sprite
	m_dummySprite = new Sprite("../media/glass.png");
	m_dummySprite2 = new Sprite("../media/smokeparticle.png");
	m_dummySprite3 = new Sprite("../media/Earth.png");
	m_dummySprite4 = new Sprite("../media/Fireball3.png");
	rot = 0;

	srand(time(NULL));
}

Application::~Application()
{
}

void Application::Start()
{
	std::cout << "Application is Started" << std::endl;

	Random::SetSeed(1234567890);

	//========================Object1================================
	float xPos = Random::randf((-RESOLUTION_X / 2), (RESOLUTION_X / 2));
	float yPos = Random::randf((-RESOLUTION_Y / 2), (RESOLUTION_Y / 2));

	cout << "xPos : " << xPos << " yPos :" << yPos << endl;

	float xDir;
	float yDir;

	do
	{
		xDir = Random::randf(-3, 3) * 5.0f;
		yDir = Random::randf(-3, 3) * 5.0f;
	} while (xDir == 0 && xDir == yDir);

	m_gameobjectArray[0] = new GameObject(m_dummySprite);
	m_gameobjectArray[0]->SetScale(0.1f);
	m_gameobjectArray[0]->SetPos(Vector3(xPos, yPos, 0));
	m_gameobjectArray[0]->setBlendingMode(enumBlend::alpha);
	m_gameobjectArray[0]->SetVeloCity(Vector3(xDir, yDir, 0.0));

	//=========================Object2================================
	m_gameobjectArray[1] = new GameObject(m_dummySprite);
	m_gameobjectArray[1]->SetScale(0.1f);
	m_gameobjectArray[1]->SetPos(Vector3(2.0f, 0.0f, 0));
	m_gameobjectArray[1]->setBlendingMode(enumBlend::alpha);
	
	//==================Particle System ==============================
	m_particleSystem0 = new Particlesystem(m_dummySprite2, 1.0f, 0.5f, 5000, 40.0f);
	m_particleSystem0->addAffector(new ColorAffector(Color::purple, Color::white));
	m_particleSystem0->addAffector(new ScaleAffector(0.1f, 0.3f));

	m_particleSystem1 = new Particlesystem(m_dummySprite2, 5.0f, 1.0f, 5000, 150.0f);
	m_particleSystem1->addAffector(new ColorAffector(Color::yellow, Color::red));
	m_particleSystem1->addAffector(new ScaleAffector(0.1f, 0.01f));
	m_particleSystem1->addAffector(new ForceAffector((Vector3(0.0f, 0.0f, 0.0f)), 0.01f));
	std::cout << "Finished loading at : " << glfwGetTime() << endl;

}

void Application::Update()
{

	/*Calculate delta time and fps*/

	curTime = glfwGetTime();
	deltaTime = curTime - prevTime;
	prevTime = curTime;

	if (curTime - initTime >= 1.0f)
	{
		std::cout << "FPS: " << frameCount << "DeltaTime : " << deltaTime << std::endl;
		frameCount = 0;
		initTime = curTime;
	}
	else
		frameCount++;

	//==================================Bouncing Object1=====================================

	if (m_gameobjectArray[1] != nullptr)
	{
		if (m_gameobjectArray[0]->GetPos().x >= RESOLUTION_X / 2 || m_gameobjectArray[0]->GetPos().x <= -RESOLUTION_X / 2)
		{
			Vector3 newVelo = m_gameobjectArray[0]->GetVelocity();
			newVelo.x = newVelo.x * -1.0f;
			m_gameobjectArray[0]->SetVeloCity(newVelo);
		}

		if (m_gameobjectArray[0]->GetPos().y >= RESOLUTION_Y / 2
			|| m_gameobjectArray[0]->GetPos().y <= -RESOLUTION_Y / 2)
		{
			Vector3 newVelo = m_gameobjectArray[0]->GetVelocity();
			newVelo.y = newVelo.y * -1.0f;
			m_gameobjectArray[0]->SetVeloCity(newVelo);
		}

		m_gameobjectArray[0]->update();
	}

	//==================================Spin object2===============================

	if (m_gameobjectArray[1] != nullptr)
	{
		Vector3 tempVelo;
		tempVelo.x = 0.0f + cos(rot) * 300.0f;
		tempVelo.y = 0.0f + sin(rot) * 300.0f;

		m_gameobjectArray[1]->SetPos(tempVelo);

		rot += deltaTime * 3.0f;
	}

	//=========================Particle System=====================================
	m_particleSystem0->SetPos(m_gameobjectArray[0]->GetPos());
	m_particleSystem1->SetPos(m_gameobjectArray[1]->GetPos());
	m_particleSystem0->update();
	m_particleSystem1->update();

}

void Application::Draw()
{
	//=============Bouncing Object==============
//	for (int i = 0; i < GAMEOBJECT_COUNT; i++)
//	{
//		m_gameobjectArray[i]->draw();
//	}

	//=============Particle System===============
	m_particleSystem0->draw();
	m_particleSystem1->draw();
}
