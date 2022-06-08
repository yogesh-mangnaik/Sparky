#include "window.h"
#include <iostream>

#define FULL_SCREEN 0

namespace sparky {
	namespace graphics {

		int* screenWidth;
		int* screenHeight;
		void window_resize(GLFWwindow* window, int width, int height);

		Window::Window(const char* name, int width, int height, int* swidth, int* sheight)
		{
			m_Title = name;
			m_Width = width;
			m_Height = height;

			screenWidth = swidth;
			screenHeight = sheight;


			if (!init()) {
				glfwTerminate();
			}

			for (int i = 0; i < MAX_KEYS; i++) {
				m_Keys[i] = false;
			}
			for (int i = 0; i < MAX_BUTTONS; i++) {
				m_MouseButtons[i] = false;
			}
		}

		Window::~Window() {
			glfwTerminate();
		}

		void Window::update() {
			glfwSwapBuffers(m_Window);
			glfwGetFramebufferSize(m_Window, &m_Width, &m_Height);
			glfwPollEvents();
		}

		bool Window::init() {

			if (!glfwInit()) {
				std::cout << "Error initializing glfw" << std::endl;
				return false;
			}

			m_Window = glfwCreateWindow(m_Width, m_Height, m_Title, NULL, NULL);

			if (!m_Window) {
				glfwTerminate();
				std::cout << "Could not start window" << std::endl;
				return false;
			}
			glfwMakeContextCurrent(m_Window);
			glfwSetWindowUserPointer(m_Window, this);
			glfwSetWindowSizeCallback(m_Window, window_resize);
			glfwSetKeyCallback(m_Window, key_callback);
			glfwSetMouseButtonCallback(m_Window, mouse_button_callback);
			glfwSetCursorPosCallback(m_Window, cursor_position_callback);
			glfwSwapInterval(0.0);

			if (glewInit() != GLEW_OK) {
				std::cout << "Could not initialize GLEW!" << std::endl;
				return false;
			}

			std::cout << glGetString(GL_VERSION) << std::endl;

			
#if FULL_SCREEN
		

#endif
			return true;
		}

		void Window::setTitle(const char* title) {
			glfwSetWindowTitle(m_Window, title);
		}

		bool Window::isKeyPressed(unsigned int keycode) const {
			//TODO: Log this
			if (keycode >= MAX_KEYS)
				return false;
			return m_Keys[keycode];
		}

		bool Window::isMouseButtonPressed(unsigned int button) const {
			//TODO : LOG THIS
			
			if (button >= MAX_BUTTONS) 
				return false;
			return m_MouseButtons[button];
		}

		void Window::getMousePosition(double &x, double &y) const {
			x = mx;
			y = my;
		}

		bool Window::closed() const{
			return glfwWindowShouldClose(m_Window) == GL_TRUE;
		}

		void Window::clear() const {
			glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
		}

		void key_callback(GLFWwindow* window, int key, int scancode, int action, int mods) {
			Window* win = (Window*)glfwGetWindowUserPointer(window);
			win->m_Keys[key] = action != GLFW_RELEASE;;
		}

		void mouse_button_callback(GLFWwindow* window, int button, int action, int mods) {
			Window* win = (Window*)glfwGetWindowUserPointer(window);
			win->m_MouseButtons[button] = action != GLFW_RELEASE;
		}

		void cursor_position_callback(GLFWwindow *window, double xpos, double ypos) {
			Window* win = (Window*)glfwGetWindowUserPointer(window);
			win->mx = xpos;
			win->my = ypos;
		}

		void window_resize(GLFWwindow *window, int width, int height) {
			glViewport(0, 0, width, height);
			*screenWidth = width;
			*screenHeight = height;
		}


} }