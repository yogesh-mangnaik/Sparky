#include <iostream>
#include "src/graphics/window.h"
#include "src/maths/maths.h"

#include "src/graphics/shader.h"
#include "src/graphics/buffers/buffer.h"
#include "src/graphics/buffers/indexbuffer.h"
#include "src/graphics/buffers/vertexarray.h"
#include "src/graphics/simple2drenderer.h"
#include "src/graphics/renderable2d.h"
#include "src/graphics/renderer2d.h"
#include "src/graphics/static_sprite.h"
#include "src/graphics/sprite.h"
#include "src/graphics/batchrenderer2d.h"
#include "src/utils/timer.h"

#include <vector>
#include <time.h>

#include <windows.h>

#define BATCH_RENDERER 1

int WIDTH = 1920;
int HEIGHT = 1080;

using namespace std;
using namespace sparky;
using namespace graphics;
using namespace maths;

int main() {

	Window window("Sparky", WIDTH, HEIGHT, &WIDTH, &HEIGHT);
	cout << WIDTH << "  " << HEIGHT << endl;
	//glClearColor(0.0f, 1.0f, 1.0f, 1.0f);	
	mat4 ortho = mat4::orthographic(0.0f, 16.0f, 0.0f, 9.0f, -1.0f, 1.0f);

	Shader shader("src/shaders/basic.vert", "src/shaders/basic.frag");
	Shader shader1("src/shaders/basic.vert", "src/shaders/basic.frag");
	shader.enable();
	shader.setUniformMat4("pr_matrix", ortho);
	shader.setUniform2f("light_pos", vec2(0.0f, 0.0f));
	shader.setUniform4f("colour", vec4(0.2f, 0.3f, 0.8f, 1.0f));

	//fps calculation
	int frames = 0;	
	int updates = 0;
	DWORD start = GetTickCount();
	srand(time(NULL));
	vector<Renderable2D*> sprites;
	float yOffset, xOffset;
	yOffset = 0.05f;
	xOffset = 0.05f;

	for (float y = 0; y < 9.0f; y += yOffset) {
		for (float x = 0; x < 16.0f; x += xOffset) {
			sprites.push_back(new
#if BATCH_RENDERER
				Sprite
#else 
				StaticSprite
#endif
				(x, y, 0.049, 0.049, maths::vec4(rand() % 1000 / 1000.0f, rand() % 1000 / 1000.0f, rand() % 1000 / 1000.0f, rand() % 1000 / 1000.0f)
#if !BATCH_RENDERER
				, shader
#endif
					));
		}
	}

#if BATCH_RENDERER
	//renderer
	BatchRenderer2D renderer;

#else

	StaticSprite sprite(5, 5, 4, 4, maths::vec4(0.2f, 0.3f, 0.8f, 1.0f), shader);
	Simple2DRenderer renderer;

#endif

	Timer timer;

	while (!window.closed()) {

		timer.reset();
		window.clear();
		double x, y;
		window.getMousePosition(x, y);
		shader.setUniform2f("light_pos", vec2((float)(x * 16.0f / WIDTH), (float)(9.0f - 9.0f * y / HEIGHT)));
		
		frames++;
		updates++;
		if ((((int)(GetTickCount() - start))/1000) > 0) {
			cout << frames << " fps | " << updates << " ups" << endl;
			std::string fps = std::to_string(frames) + " FPS";
			window.setTitle(fps.c_str());
			frames = 0;
			updates = 0;
			start = GetTickCount();
		}

#if BATCH_RENDERER
		renderer.begin();
#endif
		for (int i = 0; i < sprites.size(); i++) {
			renderer.submit(sprites[i]);
		}

#if BATCH_RENDERER
		renderer.end();	
#endif
		renderer.flush();
	
		window.update(); 

	}
	
	return 0;
}