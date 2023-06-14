#include<iostream>
#include<glad/glad.h>
#include<GLFW/glfw3.h>
#include "Functions.h"

int draw_two_triangle()
{
	const char* vertexShaderSource = "#version 330 core\n"
		"layout (location = 0) in vec3 aPos;\n"
		"void main()\n"
		"{\n"
		"   gl_Position = vec4(aPos.x, aPos.y, aPos.z, 1.0);\n"
		"}\0";

	const char* fragmentShaderSource = "#version 330 core\n"
		"out vec4 FragColor;\n"
		"void main()\n"
		"{\n"
		"   FragColor = vec4(0.0f, 0.0f, 0.0f, 1.0f);\n"
		"}\n\0";

	const char* fragmentShaderSource2 = "#version 330 core\n"
		"out vec4 FragColor;\n"
		"uniform vec4 myColor;\n"
		"void main()\n"
		"{\n"
		"   FragColor = myColor;\n"
		"}\n\0";

	glfwInit();

	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);


	GLfloat vertices[] =
	{
		-0.5f - 0.5f, -0.5f * float(sqrt(3)) / 3, 0.0f, // Lower left corner
		-0.5f + 0.5f, -0.5f * float(sqrt(3)) / 3, 0.0f, // Lower right corner
		-0.5f + 0.0f, 0.5f * float(sqrt(3)) * 2 / 3, 0.0f, // Upper corner
		-0.5f - 0.5f / 2, 0.5f * float(sqrt(3)) / 6, 0.0f, // Inner left
		-0.5f + 0.5f / 2, 0.5f * float(sqrt(3)) / 6, 0.0f, // Inner right
		-0.5f + 0.0f, -0.5f * float(sqrt(3)) / 3, 0.0f // Inner down
	};

	GLfloat vertices2[] =
	{
		0.5f - 0.5f, -0.5f * float(sqrt(3)) / 3, 0.0f, // Lower left corner
		0.5f + 0.5f, -0.5f * float(sqrt(3)) / 3, 0.0f, // Lower right corner
		0.5f + 0.0f, 0.5f * float(sqrt(3)) * 2 / 3, 0.0f, // Upper corner
		0.5f - 0.5f / 2, 0.5f * float(sqrt(3)) / 6, 0.0f, // Inner left
		0.5f + 0.5f / 2, 0.5f * float(sqrt(3)) / 6, 0.0f, // Inner right
		0.5f + 0.0f, -0.5f * float(sqrt(3)) / 3, 0.0f // Inner down
	};

	GLuint indices[] =
	{
		0, 3, 5,
		3, 2, 4,
		5, 4, 1
	};
	GLuint indices2[] =
	{
		0, 3, 5,
		3, 2, 4,
		5, 4, 1
	};

	GLFWwindow* window = glfwCreateWindow(1920, 1080, "MyOpenGL", NULL, NULL);
	if (window == NULL)
	{
		glfwTerminate();
		return -1;
	}
	glfwMakeContextCurrent(window);

	gladLoadGL();

	glViewport(0, 0, 1920, 1080);

	GLuint vertexShader = glCreateShader(GL_VERTEX_SHADER);
	glShaderSource(vertexShader, 1, &vertexShaderSource, NULL);
	glCompileShader(vertexShader);

	GLuint fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);
	glShaderSource(fragmentShader, 1, &fragmentShaderSource, NULL);
	glCompileShader(fragmentShader);

	GLuint fragmentShader2 = glCreateShader(GL_FRAGMENT_SHADER);
	glShaderSource(fragmentShader2, 1, &fragmentShaderSource2, NULL);
	glCompileShader(fragmentShader2);

	GLuint shaderProgram = glCreateProgram();

	glAttachShader(shaderProgram, vertexShader);
	glAttachShader(shaderProgram, fragmentShader);
	glLinkProgram(shaderProgram);



	glDeleteShader(fragmentShader);

	GLuint shaderProgram2 = glCreateProgram();

	glAttachShader(shaderProgram2, vertexShader);
	glAttachShader(shaderProgram2, fragmentShader2);
	glLinkProgram(shaderProgram2);

	glDeleteShader(fragmentShader2);
	glDeleteShader(vertexShader);

	GLuint BRUH, Cringe, indi;
	glGenBuffers(1, &indi);
	glGenVertexArrays(1, &Cringe);
	glGenBuffers(1, &BRUH);
	glBindVertexArray(Cringe);

	glBindBuffer(GL_ARRAY_BUFFER, BRUH);

	glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, indi);

	glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);

	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);
	glEnableVertexAttribArray(0);

	glBindBuffer(GL_ARRAY_BUFFER, 0);
	glBindVertexArray(0);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);


	GLuint BRUH2, Cringe2, indi2;
	glGenBuffers(1, &indi2);
	glGenVertexArrays(1, &Cringe2);
	glGenBuffers(1, &BRUH2);
	glBindVertexArray(Cringe2);

	glBindBuffer(GL_ARRAY_BUFFER, BRUH2);

	glBufferData(GL_ARRAY_BUFFER, sizeof(vertices2), vertices2, GL_STATIC_DRAW);

	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, indi2);

	glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices2), indices2, GL_STATIC_DRAW);

	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);
	glEnableVertexAttribArray(0);

	glBindBuffer(GL_ARRAY_BUFFER, 0);
	glBindVertexArray(0);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);



	glClearColor(0.07f, 0.13f, 0.17f, 1.0f);
	glClear(GL_COLOR_BUFFER_BIT);
	glfwSwapBuffers(window);

	while (!glfwWindowShouldClose(window))
	{
		glClearColor(0.07f, 0.13f, 0.17f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT);
		glUseProgram(shaderProgram);
		glBindVertexArray(Cringe);

		//glDrawArrays(GL_TRIANGLES, 0, 3);
		glDrawElements(GL_TRIANGLES, 9, GL_UNSIGNED_INT, 0);

		glUseProgram(shaderProgram2);
		glBindVertexArray(Cringe2);
		GLint vertexColorLocation = glGetUniformLocation(shaderProgram2, "myColor");
		glUniform4f(vertexColorLocation, 0.8f, 1.0f, 0.02f, 1.0f);
		glDrawElements(GL_TRIANGLES, 3, GL_UNSIGNED_INT, 0);

		glUniform4f(vertexColorLocation, 1.0f, 0.0f, 0.0f, 1.0f);
		glDrawElements(GL_TRIANGLES, 3, GL_UNSIGNED_INT, (void*)(3 * sizeof(GLuint)));

		glUniform4f(vertexColorLocation, 0.0f, 1.0f, 0.0f, 1.0f);
		glDrawElements(GL_TRIANGLES, 3, GL_UNSIGNED_INT, (void*)(6 * sizeof(GLuint)));

		glfwSwapBuffers(window);
		glfwPollEvents();
	}

	glDeleteVertexArrays(1, &Cringe);
	glDeleteBuffers(1, &BRUH);
	glDeleteBuffers(1, &indi);
	glDeleteProgram(shaderProgram);

	glDeleteVertexArrays(1, &Cringe2);
	glDeleteBuffers(1, &BRUH2);
	glDeleteBuffers(1, &indi2);
	glDeleteProgram(shaderProgram2);

	glfwDestroyWindow(window);
	glfwTerminate();
	return 0;
}