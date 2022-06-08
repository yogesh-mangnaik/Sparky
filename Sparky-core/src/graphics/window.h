#pragma once

#include <GL/glew.h>
#include <iostream>
#include <GLFW/glfw3.h>

#define MAX_KEYS 1024
#define MAX_BUTTONS 32

namespace sparky {
	namespace graphics {
		
		class Window {

		private:
			friend struct GLFWwindow;
			int m_Width, m_Height;
			const char* m_Title;
			GLFWwindow* m_Window;
			bool m_Closed;

			bool m_Keys[MAX_KEYS];
			bool m_MouseButtons[MAX_BUTTONS];
			double mx, my;
			

		public:
			Window(const char* name, int width, int height, int* screenWidth, int* scrrenHeight);
			~Window();
			void update();
			bool closed() const;
			void clear() const;

			inline int getWidth() const { return m_Width; };
			inline int getHeight() const { return m_Height; };

			bool isKeyPressed(unsigned int keycode) const;
			bool isMouseButtonPressed(unsigned int button) const;
			void getMousePosition(double &x, double &y) const;

			void setTitle(const char* title);

		private:
			bool init();
			friend static void key_callback(GLFWwindow* window, int key, int scancode, int action, int mods);
			friend static void mouse_button_callback(GLFWwindow* window, int button, int action, int mods);
			friend static void cursor_position_callback(GLFWwindow *window, double xpos, double ypos);

		};
}
}
