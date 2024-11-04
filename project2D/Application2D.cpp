#include "Application2D.h"
#include "Renderer2D.h"
#include "Texture.h"
#include "Font.h"
#include "Input.h"
#include <vector.h>
#include <vector>
#include <matrix.h>
#include "MatrixTransform.h"
#include "BoundingVolumes.h"
#include <Application.h>
SpriteObject* m_tank;
SpriteObject* m_turret;
AABB* m_bulletBox;
std::vector<SpriteObject*> m_bullet;
aie::Texture* m_ball;
bool slowMode = false;

Application2D::Application2D()
{
	
}

Application2D::~Application2D()
{
}

bool Application2D::startup() {//renders all objects
	m_2dRenderer = new aie::Renderer2D();
	m_texture = new aie::Texture("./textures/numbered_grid.tga");
	m_shipTexture = new aie::Texture("./textures/ship.png");
	m_font = new aie::Font("./font/consolas.ttf", 32);
	m_timer = 0;
	m_tank = new SpriteObject();
	m_tank->load("./textures/TankBody.png");
	m_tank->setPosition(getWindowWidth() / 1.f, getWindowHeight() / 1.f);
	m_tank->setRotate(0);
	m_turret = new SpriteObject();
	m_turret->load("./textures/TankGun.png");
	m_turret->setPosition(getWindowWidth() / 2.f, getWindowHeight() / 2.f);
	m_turret->setRotate(0);
	m_tank->addChild(m_turret);
	Vector2 ScreenCorners[4] = { { 0,0 }, { 0, (float)getWindowHeight() }, {(float)getWindowWidth(), (float)getWindowHeight()}, {(float)getWindowWidth(), 0 } };
	m_bulletBox = new AABB({ ScreenCorners[0].x, ScreenCorners[0].y }, { ScreenCorners[1].x + 20, ScreenCorners[1].y });
	return true;
}

void Application2D::shutdown() {//exit program
	
	delete m_font;
	delete m_texture;
	delete m_shipTexture;
	delete m_2dRenderer;
}

void Application2D::update(float deltaTime) {//called per frame, calls all movement functions

	SpriteObject* m_turretBase{};
	m_timer += deltaTime;
	m_tank->update(deltaTime);
	for (SpriteObject* i : m_bullet) {
		i->update(deltaTime);
	}
	runBullet(deltaTime);
	aie::Input* input = aie::Input::getInstance();
	movePlayer(deltaTime, input);
}

void Application2D::movePlayer(float deltaTime, aie::Input* input) {//handles all player movment
	// input example
	// rotate tank, using deltaTime as the rotation speed
	if (input->isKeyDown(aie::INPUT_KEY_A))
		m_tank->rotate(deltaTime);
	if (input->isKeyDown(aie::INPUT_KEY_D))
		m_tank->rotate(-deltaTime);

	// move tank, the 100 magic-number represents speed
	if (input->isKeyDown(aie::INPUT_KEY_W)) {//forward movement, includes increased speed
		if (slowMode)
		{
			auto facing = m_tank->getLocalTransform()[1] * deltaTime * 200;
			m_tank->translate(facing.x, facing.y);
		}
		else {
			auto facing = m_tank->getLocalTransform()[1] * deltaTime * 100;
			m_tank->translate(facing.x, facing.y);
		}
	}

	if (input->isKeyDown(aie::INPUT_KEY_S)) {//backwards movement, includes increased speed
		if (slowMode)
		{
			auto facing = m_tank->getLocalTransform()[1] * deltaTime * -200;
			m_tank->translate(facing.x, facing.y);
		}
		else {
			auto facing = m_tank->getLocalTransform()[1] * deltaTime * -100;
			m_tank->translate(facing.x, facing.y);
		}
	}

	if (input->isKeyDown(aie::INPUT_KEY_Z)) {//switches on mode where movement speed is increased
		slowMode = true;
	}
	if (input->isKeyUp(aie::INPUT_KEY_Z)) {//switches off once sprint key is released
		slowMode = false;
	}

	// rotate turret
	if (input->isKeyDown(aie::INPUT_KEY_Q))//rotate the turret child
		m_turret->rotate(deltaTime);
	if (input->isKeyDown(aie::INPUT_KEY_E))// accounts for other direction
		m_turret->rotate(-deltaTime);

	if (input->isKeyDown(aie::INPUT_KEY_SPACE)) {//creates the bullets
		SpriteObject* m_bulletInstance = new SpriteObject();
		m_bulletInstance->load("./textures/bullet.png");
		m_bulletInstance->setPosition(m_turret->getGlobalTransform()[2].x, m_turret->getGlobalTransform()[2].y);
		m_bulletInstance->setRotate(0);
		m_bullet.push_back(m_bulletInstance);
		m_turret->addChild(m_bulletInstance);
	}

	//	m_bullet->load("./textures/bullet.png");
	//	m_bullet->setPosition(getWindowWidth() / 2.f, getWindowHeight() / 2.f);
	//	m_bullet->setRotate(0);


	// Update the camera position using the arrow keys
	/*float camPosX;
	float camPosY;
	m_2dRenderer->getCameraPos(camPosX, camPosY);

	if (input->isKeyDown(aie::INPUT_KEY_UP))
		camPosY += 500.0f * deltaTime;

	if (input->isKeyDown(aie::INPUT_KEY_DOWN))
		camPosY -= 500.0f * deltaTime;

	if (input->isKeyDown(aie::INPUT_KEY_LEFT))
		camPosX -= 500.0f * deltaTime;

	if (input->isKeyDown(aie::INPUT_KEY_RIGHT))
		camPosX += 500.0f * deltaTime;

	m_2dRenderer->setCameraPos(camPosX, camPosY);*/

	// exit the application
	//if (input->isKeyDown(aie::INPUT_KEY_ESCAPE))
		//quit();
}

void Application2D::runBullet(float deltaTime)//holds movement and collision functionality for all bullets
{
	for (SpriteObject* i : m_bullet) {
		auto facing = i->getLocalTransform()[1] * deltaTime * 100;
		i->translate(facing.x, facing.y);
		if (i->m_collisionBox->overlaps(*m_bulletBox)) {
			m_turret->removeChild(i);
			i->~SpriteObject(); 
		}
	}
}

void Application2D::draw() {// render all sprites and scene objects

	// wipe the screen to the background colour
	clearScreen();

	// begin drawing sprites
	m_2dRenderer->begin();

	m_tank->draw(m_2dRenderer);
	for (SpriteObject* i : m_bullet) {
		i->draw(m_2dRenderer);
	}
	m_tank->m_collisionBox->debugDraw(m_2dRenderer);
	m_bulletBox->debugDraw(m_2dRenderer);

	// output some text, uses the last used colour
	char fps[32];
	sprintf_s(fps, 32, "FPS: %i", getFPS());
	m_2dRenderer->drawText(m_font, fps, 0, 720 - 32);
	m_2dRenderer->drawText(m_font, "WASD - Move, Q & E - Move Cannon, SPACE - Shoot, Z - Sprint", 0, 720 - 64);
	
	// done drawing sprites
	m_2dRenderer->end();
}