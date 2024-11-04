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
AABB* collisionBox;
std::vector<SpriteObject*> m_bullet;
aie::Texture* m_ball;

Application2D::Application2D()
{
	
}

Application2D::~Application2D()
{
}

bool Application2D::startup() {
	m_2dRenderer = new aie::Renderer2D();
	m_texture = new aie::Texture("./textures/numbered_grid.tga");
	m_shipTexture = new aie::Texture("./textures/ship.png");
	m_font = new aie::Font("./font/consolas.ttf", 32);
	m_timer = 0;
	m_tank = new SpriteObject();
	m_tank->load("./textures/TankBody.png");
	m_tank->setPosition(getWindowWidth() / 2.f, getWindowHeight() / 2.f);
	m_tank->setRotate(0);
	m_turret = new SpriteObject();
	m_turret->load("./textures/TankGun.png");
	m_turret->setPosition(getWindowWidth() / 2.f, getWindowHeight() / 2.f);
	m_turret->setRotate(0);
	m_tank->addChild(m_turret);
	m_ball = new aie::Texture("./textures/ball.png");
	collisionBox->fit((getWindowWidth() / 2.f, getWindowHeight() / 2.f), unsigned int count)
	//m_bullet = new SpriteObject();
	//for (SpriteObject* i : m_bullet) {
	//m_bullet.push_back(i = new SpriteObject());
	//}
	return true;
}

void Application2D::shutdown() {
	
	delete m_font;
	delete m_texture;
	delete m_shipTexture;
	delete m_2dRenderer;
}

void Application2D::update(float deltaTime) {

	SpriteObject* m_turretBase{};
	m_timer += deltaTime;
	m_tank->update(deltaTime);
	for (SpriteObject* i : m_bullet) {
		i->update(deltaTime);
	}
	runBullet(deltaTime);
	aie::Input* input = aie::Input::getInstance();
	movePlayer(deltaTime, input);

	RealtimeMotionDemo realtimeDemo;
	realtimeDemo.runModels(1.1f, 120, m_2dRenderer, m_ball);

	

	// access input
	//auto input = aie::Input::getInstance();


	
}

void Application2D::movePlayer(float deltaTime, aie::Input* input) {
	// input example
	// rotate tank, using deltaTime as the rotation speed
	if (input->isKeyDown(aie::INPUT_KEY_A))
		m_tank->rotate(deltaTime);
	if (input->isKeyDown(aie::INPUT_KEY_D))
		m_tank->rotate(-deltaTime);

	// move tank, the 100 magic-number represents speed
	if (input->isKeyDown(aie::INPUT_KEY_W)) {
		auto facing = m_tank->getLocalTransform()[1] *
			deltaTime * 100;
		m_tank->translate(facing.x, facing.y);
	}
	if (input->isKeyDown(aie::INPUT_KEY_S)) {
		auto facing = m_tank->getLocalTransform()[1] *
			deltaTime * -100;
		m_tank->translate(facing.x, facing.y);
	}
	// rotate turret
	if (input->isKeyDown(aie::INPUT_KEY_Q))
		m_turret->rotate(deltaTime);
	if (input->isKeyDown(aie::INPUT_KEY_E))
		m_turret->rotate(-deltaTime);

	if (input->isKeyDown(aie::INPUT_KEY_SPACE)) {
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

void Application2D::runBullet(float deltaTime)
{
	for (SpriteObject* i : m_bullet) {
		auto facing = i->getLocalTransform()[1] * deltaTime * 100;
		i->translate(facing.x, facing.y);
	}
}

void Application2D::draw() {

	// wipe the screen to the background colour
	clearScreen();

	// begin drawing sprites
	m_2dRenderer->begin();

	m_tank->draw(m_2dRenderer);
	for (SpriteObject* i : m_bullet) {
		i->draw(m_2dRenderer);
	}
	collisionBox->debugDraw(m_2dRenderer);

	/*// demonstrate animation
	m_2dRenderer->setUVRect(int(m_timer) % 8 / 8.0f, 0, 1.f / 8, 1.f / 8);
	m_2dRenderer->drawSprite(m_texture, 200, 200, 100, 100);

	// demonstrate spinning sprite
	m_2dRenderer->setUVRect(0,0,1,1);
	m_2dRenderer->drawSprite(m_shipTexture, 600, 400, 0, 0, m_timer, 1);

	// draw a thin line
	m_2dRenderer->drawLine(300, 300, 600, 400, 2, 1);

	// draw a moving purple circle
	m_2dRenderer->setRenderColour(1, 0, 1, 1);
	m_2dRenderer->drawCircle(sin(m_timer) * 100 + 600, 150, 50);

	// draw a rotating red box
	m_2dRenderer->setRenderColour(1, 0, 0, 1);
	m_2dRenderer->drawBox(600, 500, 60, 20, m_timer);

	// draw a slightly rotated sprite with no texture, coloured yellow
	m_2dRenderer->setRenderColour(1, 1, 0, 1);
	m_2dRenderer->drawSprite(nullptr, 400, 400, 50, 50, 3.14159f * 0.25f, 1);
	*/
	// output some text, uses the last used colour
	char fps[32];
	sprintf_s(fps, 32, "FPS: %i", getFPS());
	m_2dRenderer->drawText(m_font, fps, 0, 720 - 32);
	m_2dRenderer->drawText(m_font, "Press ESC to quit!", 0, 720 - 64);
	
	// done drawing sprites
	m_2dRenderer->end();
}


void RealtimeMotionDemo::runModels(float theta, float velocity, aie::Renderer2D* renderer, aie::Texture*texture)
{
	m_2dRenderer = renderer;
	m_texture = texture;
	//numericalModel(theta, velocity);
	mathematicalModel(theta, velocity);
}

void RealtimeMotionDemo::mathematicalModel(float theta, float speed)
{
	for (float t = 0; t < m_numberSteps; t += m_stepSize)
	{
		//float x = t * cos(theta) * speed;
		//float y = t * sin(theta) * speed - .5 * m_gravity * pow(t, 2);
		//m_2dRenderer->setRenderColour(255, 255, 255, 1);
		//m_2dRenderer->drawSprite(m_texture, x, y, m_size, m_size);
	}
}