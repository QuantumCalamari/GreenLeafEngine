#pragma once

#define GLEW_STATIC
#include <GL/glew.h>
#include <GLFW/glfw3.h>

namespace GreenLeaf {
	namespace graphics {

#define MAX_KEYS	1024
#define MAX_BUTTONS	32

		class Window
		{
		private:
			friend struct GLFWwindow;
			const char *m_Title;
			int m_Width, m_Height;
			GLFWwindow *m_Window;
			bool m_Closed;

		public:
			Window(const char *name, int width, int height);
			~Window();
			void clear() const;
			void update();
			bool closed() const;

			inline int getWidth() const
			{
				return m_Width;
			}
			inline int getHeight() const
			{
				return m_Height;
			}

		private:
			bool init();
			friend static void key_callback(GLFWwindow* window, int key, int scancode, int action, int mods);
			friend static void mouse_button_callback(GLFWwindow* window, int button, int action, int mods);
			friend static void cursor_position_callback(GLFWwindow* window, double xpos, double ypos);
		};
	}
}