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
        "layout (location = 1) in vec3 aColor;\n"
        "out vec3 color;\n"
        "uniform mat4 transform;\n"
        "uniform float scale;\n"
        "uniform mat4 model;\n"
        "uniform mat4 view;\n"
        "uniform mat4 proj;\n"
        "void main()\n"
        "{\n"
        "   gl_Position = proj * view * model * vec4(aPos, 1.0);\n"
        "   color = aColor;\n"
        "}\0";

    const char* fragmentShaderSource = "#version 330 core\n"
        "out vec4 FragColor;\n"
        "in vec3 color;\n"
        "uniform vec3 myColors[5];\n"
        "void main()\n"
        "{\n"
        "   int index = gl_PrimitiveID % 3;\n"
        "   FragColor = vec4(myColors[index], 1.0) * vec4(color, 1.0);\n"
        "}\n\0";

    GLfloat vertices[] =
    { //     COORDINATES     /        COLORS      //
    // Bottom face (red)
    -0.5f, 0.0f,  0.5f,     1.0f, 0.0f, 0.0f,
    -0.5f, 0.0f, -0.5f,     1.0f, 0.0f, 0.0f,
    0.5f, 0.0f, -0.5f,     1.0f, 0.0f, 0.0f,
    0.5f, 0.0f,  0.5f,     1.0f, 0.0f, 0.0f,
    // Front face (green)
    0.5f, 0.0f,  0.5f,     0.0f, 1.0f, 0.0f,
    0.5f, 0.0f, -0.5f,     0.0f, 1.0f, 0.0f,
    0.0f, 1.0f,  0.0f,     0.0f, 1.0f, 0.0f,
    // Right face (blue)
    0.5f, 0.0f, -0.5f,     0.0f, 0.0f, 1.0f,
    -0.5f, 0.0f, -0.5f,     0.0f, 0.0f, 1.0f,
    0.0f, 1.0f,  0.0f,     0.0f, 0.0f, 1.0f,
    // Back face (yellow)
    -0.5f, 0.0f, -0.5f,     1.0f, 1.0f, 0.0f,
    -0.5f, 0.0f,  0.5f,     1.0f, 1.0f, 0.0f,
    0.0f, 1.0f,  0.0f,     1.0f, 1.0f, 0.0f,
    // Left face (purple)
    -0.5f, 0.0f,  0.5f,     1.0f, 0.0f, 1.0f,
    0.5f, 0.0f,  0.5f,     1.0f, 0.0f, 1.0f,
    0.0f, 1.0f,  0.0f,     1.0f, 0.0f, 1.0f,
    };

    // Indices for vertices order
    GLuint indices[] =
    {
    0, 1, 2, // Bottom face
    0, 2, 3,
    4, 5, 6, // Front face
    7, 8, 9, // Right face
    10, 11, 12, // Back face
    13, 14, 15 // Left face
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

        GLuint VBO, VAO, indi;
        glGenVertexArrays(1, &VAO);
        glGenBuffers(1, &indi);
        glGenBuffers(1, &VBO);

        glBindVertexArray(VAO);

        glBindBuffer(GL_ARRAY_BUFFER, VBO);
        glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

        glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, indi);

        glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);

        glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*)0);
        glEnableVertexAttribArray(0);
        glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*)(3 * sizeof(float)));
        glEnableVertexAttribArray(1);


        glBindBuffer(GL_ARRAY_BUFFER, 0);
        glBindVertexArray(0);
        glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);

        GLuint uniID = glGetUniformLocation(shaderProgram, "scale");

        glm::vec3 red(1.0f, 0.0f, 0.0f);
        glm::vec3 green(0.0f, 1.0f, 0.0f);
        glm::vec3 blue(0.0f, 0.0f, 1.0f);
        glm::vec3 yellow(1.0f, 1.0f, 0.0f);
        glm::vec3 purple(1.0f, 0.0f, 1.0f);
        glm::vec3 myColors[] = { red, green, blue, yellow, purple};
        glClearColor(0.07f, 0.13f, 0.17f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT);
        glfwSwapBuffers(window);

        float rotation = 0.0f;
        double prevTime = glfwGetTime();

        glEnable(GL_DEPTH_TEST);
        
        while (!glfwWindowShouldClose(window))
        {
            glClearColor(0.07f, 0.13f, 0.17f, 1.0f);
            glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
            glUseProgram(shaderProgram);
            double crntTime = glfwGetTime();
            if (crntTime - prevTime >= 1 / 60)
            {
                rotation += 0.5f;
                prevTime = crntTime;
            }
            glm::mat4 model = glm::mat4(1.0f);
            glm::mat4 view = glm::mat4(1.0f);
            glm::mat4 proj = glm::mat4(1.0f);

            model = glm::rotate(model, glm::radians(rotation), glm::vec3(0.0f, 1.0f, 0.0f));
            view = glm::translate(view, glm::vec3(0.0f, -0.5f, -2.0f));
            proj = glm::perspective(glm::radians(45.0f), (float)1920 / 1080, 0.1f, 100.0f);

            int modelLoc = glGetUniformLocation(shaderProgram, "model");
            glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model));
            int viewLoc = glGetUniformLocation(shaderProgram, "view");
            glUniformMatrix4fv(viewLoc, 1, GL_FALSE, glm::value_ptr(view));
            int projLoc = glGetUniformLocation(shaderProgram, "proj");
            glUniformMatrix4fv(projLoc, 1, GL_FALSE, glm::value_ptr(proj));

            glUniform1f(uniID, 0.5f);

            int myColorsLoc = glGetUniformLocation(shaderProgram, "myColors");
            glUniform3fv(myColorsLoc, 5, glm::value_ptr(myColors[0]));

            glBindVertexArray(VAO);
            glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, indi);
            glDrawElements(GL_TRIANGLES, sizeof(indices) / sizeof(int), GL_UNSIGNED_INT, 0);
            glfwSwapBuffers(window);
            glfwPollEvents();
        }

        glDeleteVertexArrays(1, &VAO);
        glDeleteBuffers(1, &VBO);
        glDeleteBuffers(1, &indi);
        glDeleteProgram(shaderProgram);

        glfwTerminate();
        return 0;
}