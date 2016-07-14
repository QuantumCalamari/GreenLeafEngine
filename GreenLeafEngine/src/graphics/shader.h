#pragma once

#include <iostream>
#include <vector>
#include <GL\glew.h>

namespace GreenLeaf {
	namespace graphics {

		class Shader
		{
		public :
			GLuint m_ShaderID;
			const char *m_VertPath, *m_FragPath;
		public:
			Shader(const char* vertPath, const char* fragPath);
			~Shader();

			void enable() const;
			void disable() const;
			std::string read_file(const char* filepath);
		private:
			GLuint load();
		};

	}
}