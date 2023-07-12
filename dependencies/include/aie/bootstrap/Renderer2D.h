#pragma once

#include "Bootstrap.h"

namespace aie {

	class Texture;
	class Font;

	// a class for rendering 2D sprites and font
	class Renderer2D {
	public:

		DLL Renderer2D();
		DLL virtual ~Renderer2D();

		// all draw calls must occur between a begin / end pair
		DLL virtual void Begin();
		DLL virtual void End();

		// simple shape rendering
		DLL virtual void DrawBox(float xPos, float yPos, float width, float height, float rotation = 0.0f, float depth = 0.0f);
		DLL virtual void DrawCircle(float xPos, float yPos, float radius, float depth = 0.0f);

		// if texture is nullptr then it renders a coloured sprite
		// depth is in the range [0,100] with lower being closer to the viewer
		DLL virtual void DrawSprite(Texture* texture, float xPos, float yPos, float width = 0.0f, float height = 0.0f, float rotation = 0.0f, float depth = 0.0f, float xOrigin = 0.5f, float yOrigin = 0.5f);
		DLL virtual void DrawSpriteTransformed3x3(Texture* texture, float* transformMat3x3, float width = 0.0f, float height = 0.0f, float depth = 0.0f, float xOrigin = 0.5f, float yOrigin = 0.5f);
		DLL virtual void DrawSpriteTransformed4x4(Texture* texture, float* transformMat4x4, float width = 0.0f, float height = 0.0f, float depth = 0.0f, float xOrigin = 0.5f, float yOrigin = 0.5f);

		// draws a simple coloured line with a given thickness
		// depth is in the range [0,100] with lower being closer to the viewer
		DLL virtual void DrawLine(float x1, float y1, float x2, float y2, float thickness = 1.0f, float depth = 0.0f);

		// draws simple text on the screen horizontally
		// depth is in the range [0,100] with lower being closer to the viewer
		DLL virtual void DrawText(Font* font, const char* text, float xPos, float yPos, float depth = 0.0f);

		// sets the tint colour for all subsequent draw calls
		DLL void SetRenderColour(float r, float g, float b, float a = 1.0f);
		DLL void SetRenderColour(unsigned int colour);

		// can be used to set the texture coordinates of sprites using textures
		// for all subsequent drawSprite calls
		DLL void SetUVRect(float uvX, float uvY, float uvW, float uvH);

		// specify the camera position
		void SetCameraPos(float x, float y) { m_cameraX = x; m_cameraY = y; }
		void GetCameraPos(float& x, float& y) const { x = m_cameraX; y = m_cameraY; }

	protected:

		// helper methods used during drawing
		DLL bool ShouldFlush(int additionalVertices = 0, int additionalIndices = 0);
		DLL void FlushBatch();
		DLL unsigned int PushTexture(Texture* texture);

		// indicates in the middle of a begin/end pair
		bool				m_renderBegun;

		// the camera position
		float				m_cameraX, m_cameraY;

		// texture handling
		enum { TEXTURE_STACK_SIZE = 16 };
		Texture* m_nullTexture;
		Texture* m_textureStack[TEXTURE_STACK_SIZE];
		int					m_fontTexture[TEXTURE_STACK_SIZE];
		unsigned int		m_currentTexture;

		// texture coordinate information
		float				m_uvX, m_uvY, m_uvW, m_uvH;

		// represents colour in red, green, blue and alpha 0.0-1.0 range
		float				m_r, m_g, m_b, m_a;

		// sprite handling
		enum { MAX_SPRITES = 512 };
		struct SBVertex {
			float pos[4];
			float color[4];
			float texcoord[2];
		};

		// data used for opengl to draw the sprites (with padding)
		SBVertex			m_vertices[MAX_SPRITES * 4];
		unsigned short		m_indices[MAX_SPRITES * 6];
		int					m_currentVertex, m_currentIndex;
		unsigned int		m_vao, m_vbo, m_ibo;

		// shader used to render sprites
		unsigned int		m_shader;

		// helper method used to rotate sprites around a pivot
		DLL void	RotateAround(float inX, float inY, float& outX, float& outY, float sin, float cos);

		// data used for a virtual camera
		float	m_projectionMatrix[16];
	};

} // namespace aie