#include<glad/glad.h>
#include<GLFW/glfw3.h>
#include "Functions.h"
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <glm/gtx/rotate_vector.hpp>
#include <glm/gtx/vector_angle.hpp>

int draw_3d_triangle_mouse()
{
    int width = 1920;
    int height = 1080;

    const char* vertexShaderSource = "#version 330 core\n"
        "layout (location = 0) in vec3 aPos;\n"
        "layout (location = 1) in vec3 aColor;\n"
        "out vec3 color;\n"
        "uniform mat4 camMatrix;\n"
        "void main()\n"
        "{\n"
        "   gl_Position = camMatrix * vec4(aPos, 1.0);\n"
        "   color = aColor;\n"
        "}\0";

    const char* fragmentShaderSource = "#version 330 core\n"
        "out vec4 FragColor;\n"
        "in vec3 color;\n"
        "void main()\n"
        "{\n"
        "   FragColor = vec4(color, 1.0);\n"
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

    GLFWwindow* window = glfwCreateWindow(width, height, "MyOpenGL", NULL, NULL);
    if (window == NULL)
    {
        glfwTerminate();
        return -1;
    }
    glfwMakeContextCurrent(window);

    gladLoadGL();

    glViewport(0, 0, width, height);

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
    glm::vec3 myColors[] = { red, green, blue, yellow, purple };

    int numColors = sizeof(myColors) / sizeof(myColors[0]);

    glClearColor(1.0f, 1.0f, 1.0f, 1.0f);
    glClear(GL_COLOR_BUFFER_BIT);
    glfwSwapBuffers(window);

    float rotation = 0.0f;
    double prevTime = glfwGetTime();

    glm::vec3 Position = glm::vec3(0.0f, 0.0f, 2.0f);
    glm::vec3 Orientation;
    Orientation = glm::vec3(0.0f, 0.0f, -1.0f);
    glm::vec3 Up = glm::vec3(0.0f, 1.0f, 0.0f);
    bool firstClick = true;
    
    float speed = 0.1f;
    float sensitivity = 100.0f;

    glEnable(GL_DEPTH_TEST);

    while (!glfwWindowShouldClose(window))
    {
        glClearColor(1.0f, 1.0f, 1.0f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
        glUseProgram(shaderProgram);
        
        if (glfwGetKey(window, GLFW_KEY_W) == GLFW_PRESS)
        {
            Position += speed * Orientation;
        }
        if (glfwGetKey(window, GLFW_KEY_A) == GLFW_PRESS)
        {
            Position += speed * -glm::normalize(glm::cross(Orientation, Up));
        }
        if (glfwGetKey(window, GLFW_KEY_S) == GLFW_PRESS)
        {
            Position += speed * -Orientation;
        }
        if (glfwGetKey(window, GLFW_KEY_D) == GLFW_PRESS)
        {
            Position += speed * glm::normalize(glm::cross(Orientation, Up));
        }
        if (glfwGetKey(window, GLFW_KEY_SPACE) == GLFW_PRESS)
        {
            Position += speed * Up;
        }
        if (glfwGetKey(window, GLFW_KEY_LEFT_CONTROL) == GLFW_PRESS)
        {
            Position += speed * -Up;
        }
        if (glfwGetKey(window, GLFW_KEY_LEFT_SHIFT) == GLFW_PRESS)
        {
            speed = 0.4f;
        }
        else if (glfwGetKey(window, GLFW_KEY_LEFT_SHIFT) == GLFW_RELEASE)
        {
            speed = 0.1f;
        }

        if (glfwGetMouseButton(window, GLFW_MOUSE_BUTTON_LEFT) == GLFW_PRESS)
        {
            glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_HIDDEN);
            if (firstClick)
            {
                glfwSetCursorPos(window, (width / 2), (height / 2));
                firstClick = false;
            }
            double mouseX;
            double mouseY;
            glfwGetCursorPos(window, &mouseX, &mouseY);
            float rotX = sensitivity * (float)(mouseY - (height / 2)) / height;
            float rotY = sensitivity * (float)(mouseX - (width / 2)) / width;
            glm::vec3 newOrientation;
            newOrientation = glm::rotate(Orientation, glm::radians(-rotX), glm::normalize(glm::cross(Orientation, Up)));
            if (abs(glm::angle(newOrientation, Up) - glm::radians(90.0f)) <= glm::radians(85.0f))
            {
                Orientation = newOrientation;
            }
            Orientation = glm::rotate(Orientation, glm::radians(-rotY), Up);
            glfwSetCursorPos(window, (width / 2), (height / 2));
        }
        else if (glfwGetMouseButton(window, GLFW_MOUSE_BUTTON_LEFT) == GLFW_RELEASE)
        {
            glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_NORMAL);
            firstClick = true;
        }

        glm::mat4 view = glm::mat4(1.0f);
        glm::mat4 projection = glm::mat4(1.0f);

        view = glm::lookAt(Position, Position + Orientation, Up);
        projection = glm::perspective(glm::radians(45.0f), (float)width / height, 0.1f, 100.0f);
        glUniformMatrix4fv(glGetUniformLocation(shaderProgram, "camMatrix"), 1, GL_FALSE, glm::value_ptr(projection * view));

        int myColorsLoc = glGetUniformLocation(shaderProgram, "myColors");
        glUniform3fv(myColorsLoc, numColors, glm::value_ptr(myColors[0]));

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