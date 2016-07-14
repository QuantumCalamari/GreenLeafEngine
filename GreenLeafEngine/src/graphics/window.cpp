#include "window.h"
#include <iostream>

namespace GreenLeaf {
	namespace graphics {

		void window_resize(GLFWwindow *window, int width, int height);
		void key_callback(GLFWwindow* window, int key, int scancode, int action, int mods);
		void mouse_button_callback(GLFWwindow* window, int button, int action, int mods);
		void cursor_position_callback(GLFWwindow* window, double xpos, double ypos);

		Window::Window(const char *title, int width, int height)
		{
			m_Title = title;
			m_Width = width;
			m_Height = height;
			//init(); not sure I need this
			
			if (!init())
				glfwTerminate();

			glfwSetKeyCallback(m_Window, key_callback);
			glfwSetMouseButtonCallback(m_Window, mouse_button_callback);
			glfwSetCursorPosCallback(m_Window, cursor_position_callback);
		}

		Window::~Window()
		{
			glfwTerminate();
		}

		bool Window::init()
		{

			if (!glfwInit())
			{
				std::cout << "Failed to initialise GLFW" << std::endl;
				return false;
			}

			m_Window = glfwCreateWindow(m_Width, m_Height, m_Title, NULL, NULL);
			if (!m_Window)
			{
				glfwTerminate();
				std::cout << "Failed to create game window" << std::endl;
				return false;
			}
			glfwMakeContextCurrent(m_Window);
			glfwSetWindowUserPointer(m_Window, this);
			glfwSetWindowSizeCallback(m_Window, window_resize);

			if (glewInit() != GLEW_OK) {
				std::cout << "Could not initialise GLEW" << std::endl;
				return false;
			}

			return true;
		}

		void Window::clear() const
		{
			glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
		}

		void Window::update()
		{
			glfwPollEvents();
			glfwGetFramebufferSize(m_Window, &m_Width, &m_Height);
			glViewport(0, 0, m_Width, m_Height);
			glfwSwapBuffers(m_Window);
		}

		bool Window::closed() const
		{
			return glfwWindowShouldClose(m_Window) == 1;
		}

		void window_resize(GLFWwindow *window, int width, int height) {
			glViewport(0, 0, width, height);
		}

		void key_callback(GLFWwindow* window, int key, int scancode, int action, int mods) {
			if (key == GLFW_KEY_W && action == GLFW_PRESS)
				std::cout << "W is pressed" << std::endl;
			if (key == GLFW_KEY_S && action == GLFW_PRESS)
				std::cout << "S is pressed" << std::endl;
			if (key == GLFW_KEY_A && action == GLFW_PRESS)
				std::cout << "A is pressed" << std::endl;
			if (key == GLFW_KEY_D && action == GLFW_PRESS)
				std::cout << "D is pressed" << std::endl;
		}

		void mouse_button_callback(GLFWwindow* window, int button, int action, int mods) {
			if (button == GLFW_MOUSE_BUTTON_LEFT && action == GLFW_PRESS)
				std::cout << "Left Click" << std::endl;
			if (button == GLFW_MOUSE_BUTTON_RIGHT && action == GLFW_PRESS)
				std::cout << "Right Click" << std::endl;
		}

		static void cursor_position_callback(GLFWwindow* window, double xpos, double ypos) {
			std::cout << "X pos: " << xpos << std::endl;
			std::cout << "Y pos: " << ypos << std::endl;
				
		}

	}
}