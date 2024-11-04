#pragma once
#include <vector.h>
#include <matrix.h>
#include <vector>
#include <cassert>
#include "Application2D.h"
#include "Renderer2D.h"
#include <Texture.h>
#include "BoundingVolumes.h"


//using namespace Application2D;

class SceneObject {
	public:
		SceneObject() {}
		SceneObject* getParent() const { return m_parent; }
		size_t childCount() const { return m_children.size(); }

		const Matrix3& SceneObject::getLocalTransform() const {
			return m_localTransform;
		}
		const Matrix3& SceneObject::getGlobalTransform() const {
			return m_globalTransform;
		}

		SceneObject* getChild(unsigned int index) const {
			return m_children[index];
		}

		void SceneObject::addChild(SceneObject* child) {
			//ensure the child is unparented
			assert(child->m_parent == nullptr);
			//assign parent
			child->m_parent = this;
			//add new child
			m_children.push_back(child);
		}

		void SceneObject::removeChild(SceneObject* child) {
			//find child
			auto iter = std::find(m_children.begin(), m_children.end(), child);

			//remove if found
			if (iter != m_children.end()) {
				m_children.erase(iter);
				//unassign barent
				child->m_parent = nullptr;
			}
		}

		void SceneObject::update(float deltaTime) {
			onUpdate(deltaTime); //run onUpdate
			for (auto child : m_children) child->update(deltaTime);//honey update the children
		}

		void SceneObject::draw(aie::Renderer2D* renderer) {
			onDraw(renderer); //run ondraw
			for (auto child : m_children) child->draw(renderer); //draw children
		}

		virtual void SceneObject::onUpdate(float deltaTime) { }
		virtual void SceneObject::onDraw(aie::Renderer2D* renderer) { }

		void SceneObject::updateTransform() {
			if (m_parent != nullptr)
				m_globalTransform = m_parent->m_globalTransform * m_localTransform;
			else
				m_globalTransform = m_localTransform;
			for (auto child : m_children)
				child->updateTransform();
		}

		virtual ~SceneObject() {
			if (m_parent != nullptr) m_parent->removeChild(this); //detach from parent
			for (auto child : m_children) child->m_parent = nullptr; //remove children

		}

		void SceneObject::setPosition(float x, float y) {
			m_localTransform[2] = { x, y, 1 };
			updateTransform();
		}
		void SceneObject::setRotate(float radians) {
			m_localTransform.setRotateZ(radians);
			updateTransform();
		}
		void SceneObject::setScale(float width, float height) {
			m_localTransform.setScaled(width, height, 1);
			updateTransform();
		}
		void SceneObject::translate(float x, float y) {
			m_localTransform.translate(x, y);
			updateTransform();
		}
		void SceneObject::rotate(float radians) {
			m_localTransform.rotateZ(radians);
			updateTransform();
		}
		void SceneObject::scale(float width, float height) {
			m_localTransform.scale(width, height, 1);
			updateTransform();
		}


	protected:
		SceneObject* m_parent = nullptr;
		std::vector<SceneObject*> m_children;

		Matrix3 m_localTransform;
		Matrix3 m_globalTransform;


};

class my2DApp : public aie::Application {
public:
	my2DApp();
	virtual ~my2DApp();

	virtual bool startup();
	virtual void shutdown();

	virtual void update(float deltaTime);
	virtual void draw();
protected:
	aie::Renderer2D* m_2dRenderer;
};

class SpriteObject : public SceneObject {
public:
	SpriteObject() {}
	SpriteObject(const char* filename) { load(filename); }
	virtual ~SpriteObject() { delete m_texture; }
	bool load(const char* filename) {
		delete m_texture;
		m_texture = nullptr;
		m_texture = new aie::Texture(filename);
		return m_texture != nullptr;
	}
		//AABB* m_collisionBox;

	virtual void SpriteObject::onDraw(aie::Renderer2D* renderer)
	{
		if (m_texture != nullptr)
		{
			//m_globalTransform[0][0] = 0.5;
			//m_globalTransform[1][1] = 0.5;
			//float width = m_texture->getWidth();
			//float height = m_texture->getHeight();
			//Vector3 pos = getGlobalTransform().zAxis;
			//m_collisionBox = new AABB({ pos.x + width / 2, pos.y + height / 2}, { pos.x - width / 2, pos.y - height / 2});
			renderer->drawSpriteTransformed3x3(m_texture, (float*)&m_globalTransform);
		}
	}
protected:
	aie::Texture* m_texture = nullptr;
};

class RealtimeMotionDemo
{
	float m_gravity = 10.0f;
	float m_numberSteps = 3000.0f;
	float m_stepSize = 0.5f;
	float m_size = 25;
	aie::Renderer2D* m_2dRenderer;
	aie::Texture* m_texture;
	void mathematicalModel(float theta, float velocity);
	void numericalModel(float theta, float velocity);
public:
	void runModels(float theta, float velocity, aie::Renderer2D* m_2dRenderer, aie::Texture* m_texture);
};