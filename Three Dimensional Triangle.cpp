#include<glad/glad.h>
#include<GLFW/glfw3.h>
#include "Functions.h"
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

int draw_3d_triangle()
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

    GLfloat vertices[] = {
    -0.5f, -0.5f * float(sqrt(3)) / 3, 0.0f,
     0.5f, -0.5f * float(sqrt(3)) / 3, 0.0f,
     0.0f,  0.5f * float(sqrt(3)) * 2  / 3, 0.0f
    };


        glfwInit();
        glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
        glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
        glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

        GLFWwindow* window = glfwCreateWindow(1920, 1080, "MyOpenGL", NULL, NULL);
        if (window == NULL)
        {
            glfwTerminate();
            return -1;
        }
        glfwMakeContextCurrent(window);

        gladLoadGL();

        glViewport(0, 0, 800, 600);

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

       

        glDeleteShader(vertexShader);
        glDeleteShader(fragmentShader);

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

        glClearColor(0.07f, 0.13f, 0.17f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT);
        glfwSwapBuffers(window);

        glm::mat4 transform;
        transform = glm::translate(transform, glm::vec3(0.5f, -0.5f, 0.0f));

        while (!glfwWindowShouldClose(window))
        {
            glClearColor(0.07f, 0.13f, 0.17f, 1.0f);
            glClear(GL_COLOR_BUFFER_BIT);
            
            
            //transform = glm::rotate(transform, (float)glfwGetTime() * glm::radians(50.0f), glm::vec3(0.0f, 0.0f, 1.0f)); 

            glUseProgram(shaderProgram);

            unsigned int transformLoc = glGetUniformLocation(shaderProgram, "transform");
            glUniformMatrix4fv(transformLoc, 1, GL_FALSE, glm::value_ptr(transform));

            glBindVertexArray(VAO);
            glDrawArrays(GL_TRIANGLES, 0, 3);
            

            glfwSwapBuffers(window);
            glfwPollEvents();
        }

        glDeleteVertexArrays(1, &VAO);
        glDeleteBuffers(1, &VBO);
        glDeleteProgram(shaderProgram);

        glfwTerminate();
        return 0;
}