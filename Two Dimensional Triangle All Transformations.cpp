#include<glad/glad.h>
#include<GLFW/glfw3.h>
#include "Functions.h"
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

int draw_all_2d_transformations()
{
	const char* vertexShaderSource = "#version 330 core\n"
        "layout (location = 0) in vec3 aPos;\n"
        "uniform mat4 transform;\n"
        "void main()\n"
        "{\n"
        "   gl_Position = transform * vec4(aPos.x, aPos.y, aPos.z, 1.0);\n"
		"}\0";

	const char* fragmentShaderSource = "#version 330 core\n"
		"out vec4 FragColor;\n"
		"void main()\n"
		"{\n"
		"   FragColor = vec4(0.0f, 0.0f, 0.0f, 1.0f);\n"
		"}\n\0";

	glfwInit();

	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

    GLfloat vertices[] = {
    -0.2f, -0.2f * float(sqrt(3)) / 3, 0.0f,
     0.2f, -0.2f * float(sqrt(3)) / 3, 0.0f,
     0.0f,  0.2f * float(sqrt(3)) * 2  / 3, 0.0f
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

	GLuint shaderProgram = glCreateProgram();

	glAttachShader(shaderProgram, vertexShader);
	glAttachShader(shaderProgram, fragmentShader);
	glLinkProgram(shaderProgram);


	glDeleteShader(fragmentShader);
	glDeleteShader(vertexShader);

    GLuint VBO, VAO;
    glGenVertexArrays(1, &VAO);
    glGenBuffers(1, &VBO);
    glBindVertexArray(VAO);

    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);
    glEnableVertexAttribArray(0);

    glBindBuffer(GL_ARRAY_BUFFER, 0);
    glBindVertexArray(0);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);


	GLuint VBO1, VAO1;
	glGenVertexArrays(1, &VAO1);
	glGenBuffers(1, &VBO1);
	glBindVertexArray(VAO1);

	glBindBuffer(GL_ARRAY_BUFFER, VBO1);
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);
	glEnableVertexAttribArray(0);

	glBindBuffer(GL_ARRAY_BUFFER, 0);
	glBindVertexArray(0);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);

	GLuint VBO2, VAO2;
	glGenVertexArrays(1, &VAO2);
	glGenBuffers(1, &VBO2);
	glBindVertexArray(VAO2);

	glBindBuffer(GL_ARRAY_BUFFER, VBO2);
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);
	glEnableVertexAttribArray(0);

	glBindBuffer(GL_ARRAY_BUFFER, 0);
	glBindVertexArray(0);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);

    glClearColor(0.07f, 0.13f, 0.17f, 1.0f);
    glClear(GL_COLOR_BUFFER_BIT);
    glfwSwapBuffers(window);

	glm::mat4 transform_rotate = glm::mat4(1.0f);
	glm::mat4 transform_scale = glm::mat4(1.0f);
	glm::mat4 transform_offset = glm::mat4(1.0f);
	float size = 0.5f;
	bool check = false;
	float targetSize = 1.3f;
	float offset = 0.5f;


	while (!glfwWindowShouldClose(window))
	{
		glClearColor(0.07f, 0.13f, 0.17f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT);
		glUseProgram(shaderProgram);

		float angle = glfwGetTime() * glm::radians(15.0f);
		transform_rotate = glm::rotate(glm::mat4(1.0f), angle, glm::vec3(0.0f, 0.0f, 1.0f));
		glUseProgram(shaderProgram);
		unsigned int transformLoc1 = glGetUniformLocation(shaderProgram, "transform");
		glUniformMatrix4fv(transformLoc1, 1, GL_FALSE, glm::value_ptr(transform_rotate));

		glBindVertexArray(VAO);
		glDrawArrays(GL_TRIANGLES, 0, 3);


		
		if ((size < targetSize) && (check == false))
		{
			offset+= 0.001f;
			size += 0.001f;
		}
		else if ((size > targetSize) && (check == true))
		{
			offset -= 0.001f;
			size -= 0.001f;
		}
		else
		{
			check = !check;
			targetSize = check ? 0.5f : 1.3f;
		}
		transform_scale = glm::scale(glm::mat4(1.0f), glm::vec3(size));
		glm::vec3 translationVector = glm::vec3(0.5f, size-0.7f, 0.0f);
		glm::mat4 transform_translate = glm::translate(glm::mat4(1.0f), translationVector);
		glm::mat4 finalTransformMatrix = transform_translate * transform_scale;

		glUniformMatrix4fv(glGetUniformLocation(shaderProgram, "transform"), 1, GL_FALSE, glm::value_ptr(finalTransformMatrix));
		glUseProgram(shaderProgram);

		glBindVertexArray(VAO1);
		glDrawArrays(GL_TRIANGLES, 0, 3);


		
		transform_offset[1][0] = offset;
		glUseProgram(shaderProgram);

		glm::vec3 translationVector2 = glm::vec3(-0.5f, 0.0f, 0.0f);
		glm::mat4 transform_translate2 = glm::translate(glm::mat4(1.0f), translationVector2);
		glm::mat4 finalTransformMatrix2 = transform_translate2 * transform_offset;

		glUniformMatrix4fv(glGetUniformLocation(shaderProgram, "transform"), 1, GL_FALSE, glm::value_ptr(finalTransformMatrix2));

		glBindVertexArray(VAO2);
		glDrawArrays(GL_TRIANGLES, 0, 3);

		glfwSwapBuffers(window);
		glfwPollEvents();
	}


	glDeleteVertexArrays(1, &VAO);
	glDeleteBuffers(1, &VBO);
	glDeleteVertexArrays(1, &VAO1);
	glDeleteBuffers(1, &VBO1);
	glDeleteVertexArrays(1, &VAO2);
	glDeleteBuffers(1, &VBO2);
	glDeleteProgram(shaderProgram);

	glfwDestroyWindow(window);
	glfwTerminate();
	return 0;
}