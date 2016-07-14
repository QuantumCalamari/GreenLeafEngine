#include "shader.h"
//#include "fileUtils.h"
#include <string>
#include <vector>
#include <iostream>
#include <fstream>

namespace GreenLeaf{
	namespace graphics {



		Shader::Shader(const char* vertPath, const char* fragPath) 
			: m_VertPath(vertPath), m_FragPath(fragPath)
		{
			m_ShaderID = load();
		}

		Shader::~Shader() {
			glDeleteProgram(m_ShaderID);
		}


		GLuint Shader::load() {
				GLuint prog = glCreateProgram();
				GLuint vertex = glCreateShader(GL_VERTEX_SHADER);
				GLuint fragment = glCreateShader(GL_FRAGMENT_SHADER);

			//	std::string vertSourceString = read_file(m_VertPath);
				std::string fragSourceString = read_file(m_FragPath);

				//std::string fragSourceString = "#version 330 core\n in vec3 color;\n\n void main() {\n\t color = vec4(0.5, 0.4, 0.1, 1, 0);\n}";
				std::string vertSourceString = "#version 330 core\n\n layout(location = 0) out vec4 position;\n\n uniform mat4 pr_matrix;\n	uniform mat4 vw_matrix = mat4(1.0);\n uniform mat4 ml_matrix = mat4(1.0);\n\n void main() {\n\t	gl_Position = pr_matrix * position;\n}";
				//vertSourceString = "void main(void) { gl_Position = position; }";
				//fragSourceString = "void main(void) {color = vec4(0.5, 0.4, 0.1, 0.5);}";

				fragSourceString.erase(0, 3);
				//vertSourceString = fragSourceString;
				//vertSourceString.replace(177, 190, "gl_Position = position;\n}");

				const char* vertSource = read_file(m_VertPath).c_str();
				const char* fragSource = read_file(m_FragPath).c_str();				
				
				//not reading the shader properly?
				std::cout << "vert: \n" << vertSourceString << std::endl;
				std::cout << "frag: \n" << fragSourceString << std::endl;
				//std::cout << "vert: \n" << vertSource << std::endl;
				//std::cout << "frag: \n" << fragSource << std::endl;

				//vertex shader
				glShaderSource(vertex, 1, &vertSource, NULL);
				glCompileShader(vertex);

				GLint logInt;
				glGetShaderiv(vertex, GL_COMPILE_STATUS, &logInt);
				if (logInt == GL_FALSE) {
					GLint length;
					glGetShaderiv(vertex, GL_INFO_LOG_LENGTH, &length);
					std::vector<char> error(length);
					glGetShaderInfoLog(vertex, length, &length, &error[0]);
					std::cout << "Failed to compile vertex with error: " << &error[0] << std::endl;
					
					for (int i = 0; i < error.size(); i++) {
						std::cout << &error[i] << std::endl;

					}

					glDeleteShader(vertex);

					return 0;
				}
				else {
					std::cout << "logInt: " << logInt << std::endl;
				}

				//fragment shader
				glShaderSource(fragment, 1, &fragSource, NULL);
				glCompileShader(fragment);

				glGetShaderiv(fragment, GL_COMPILE_STATUS, &logInt);
				if (logInt == GL_FALSE) {
					GLint length;
					glGetShaderiv(fragment, GL_INFO_LOG_LENGTH, &length);
					std::vector<char> error(length);
					glGetShaderInfoLog(fragment, length, &length, &error[0]);
					std::cout << "Failed to compile fragment with error: " << &error[0] << std::endl;
					glDeleteShader(fragment);

					return 0;
				}
				else {
					std::cout << "logInt: " << logInt << std::endl;
				}

				glAttachShader(prog, vertex);
				glAttachShader(prog, fragment);

				glLinkProgram(prog);
				glValidateProgram(prog);

				glDeleteShader(vertex);
				glDeleteShader(fragment);

				return prog;
			}

		void Shader::enable() const {
			glUseProgram(m_ShaderID);
		}

		void Shader::disable() const {
			glUseProgram(0);
		}

		std::string Shader::read_file(const char* filepath)	{
			FILE* file = fopen(filepath, "rt");
			fseek(file, 0, SEEK_END);
			unsigned long length = ftell(file);
			char* data = new char[length + 1];
			memset(data, 0, length + 1);
			fseek(file, 0, SEEK_SET);
			fread(data, 1, length, file);
			fclose(file);

			std::string result(data);
			delete[] data;

			return result;
		}

	}
}