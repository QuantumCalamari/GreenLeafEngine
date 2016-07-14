#include <iostream>
#include <fstream>
#include <string>

#include "src/graphics/window.h"
#include "src/maths/maths.h"
#include "src/graphics/shader.h"
//#include "src/utils/fileUtils.h"
#include <GLFW/glfw3.h>

std::string read_file(const char* filepath) {
	std::string fileData;
	std::ifstream stream(filepath, std::ios::in);

	if (stream.is_open()) {
		std::string line = "";

		while (getline(stream, line)) {
			fileData += "\n" + line;
		}
		stream.close();
	}

	fileData.erase(0, 4);

	return fileData;
}

GLuint LoadShader(const char* vertpath, const char* fragpath) {

	GLuint vertShader = glCreateShader(GL_VERTEX_SHADER);
	GLuint fragShader = glCreateShader(GL_FRAGMENT_SHADER);

	std::string vertSourceString = "void main(void) { gl_Position = position; }";
	std::string fragSourceString = read_file(fragpath);

	const char* vertSource = vertSourceString.c_str();
	const char* fragSource = fragSourceString.c_str();

	std::cout << vertSourceString << std::endl;
	std::cout << fragSourceString << std::endl;

	glShaderSource(vertShader, 1, &vertSource, NULL);
	glShaderSource(fragShader, 1, &fragSource, NULL);

	glCompileShader(vertShader);
	glCompileShader(fragShader);

	GLuint program = glCreateProgram();
	glAttachShader(program, vertShader);
	glAttachShader(program, fragShader);
	glLinkProgram(program);

	return program;
}

int main() {

	using namespace GreenLeaf;
	using namespace graphics;
	using namespace maths;	

	Window window("Green Leaf", 800, 600);
	glClearColor(0.0f, 0.3f, 0.0f, 0.2f);

	//std::string vertSourceString = "void main(void) { gl_Position = position; }";
	//std::string fragSourceString = "void main(void) {color = vec4(0.5, 0.4, 0.1, 0.5);}";

	//std::string file = read_file("main.cpp");

	//fragSourceString = read_file("src/shaders/basic.frag");

	//GLuint program = LoadShader("/src/shaders/basic.vert", "/src/shaders/basic.frag");
	//glUseProgram(program);

	std::cout << glGetString(GL_VERSION) << std::endl;

	GLfloat vertices[] = {
			-0.5f, -0.6f, 0.0f,
			-0.5f,  0.5f, 0.0f,
			 0.5f,  0.5f, 0.0f,
			 0.5f,  0.5f, 0.0f,
			 0.5f, -0.6f, 0.0f,
			-0.5f, -0.5f, 0.0f,
	};

	GLuint vbo;
	
	glGenBuffers(1, &vbo);
	glBindBuffer(GL_ARRAY_BUFFER, vbo);
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, 0);
	glEnableVertexAttribArray(0);

	mat4 ortho = mat4::orthographic(0.0, 16.0f, 0.0f, 0.9f, -1.0f, 1.0f);

	Shader shader("src/shaders/basic.vert", "src/shaders/basic.frag");
	shader.enable();


	glUniformMatrix4fv(glGetUniformLocation(shader.m_ShaderID, "pr_matrix"), 1, GL_FALSE, ortho.elements);
	while (!window.closed())
		{
			window.clear();
			glDrawArrays(GL_TRIANGLES, 0, 6);
			window.update();
		}
	system("PAUSE");
	return 0;
}