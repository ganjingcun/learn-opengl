#include <iostream>

#define GLEW_STATIC
#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <math.h>

using namespace std;

// Function prototypes
void key_callback(GLFWwindow* window, int key, int scancode, int action, int mode);

// Window dimensions
const GLuint WIDTH = 800, HEIGHT = 600;

// Shaders
const GLchar* vertexShaderSource =
        "#version 330 core "
        "layout (location = 0) in vec3 position;"
        "out vec4 vertexColor; // 为片段着色器指定一个颜色输出\n"
        "void main(){"
            "gl_Position = vec4(position.x, position.y, position.z, 1.0);"
            "vertexColor = vec4(0.5f, 0.0f, 1.0f, 1.0f); "
        "}";
const GLchar* fragmentShader1Source =
        "#version 330 core "
        "in vec4 vertexColor;"
        "out vec4 color;"
        "void main(){"
            "color = vertexColor;"
        "}";
const GLchar* fragmentShader2Source =
        "#version 330 core "
        "out vec4 color;"
        "uniform vec4 ourColor;"
        "void main(){"
            "color = ourColor; "
        "}";

int main() {
    // Init GLFW
    glfwInit();
    // Set all the required options for GLFW
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
    glfwWindowHint(GLFW_RESIZABLE, GL_FALSE);
    //osx 系统需要加这行才能正常运行
    glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);

    // Create a GLFWwindow object that we can use for GLFW's functions
    GLFWwindow* window = glfwCreateWindow(WIDTH, HEIGHT, "LearnOpenGL", nullptr, nullptr);
    glfwMakeContextCurrent(window);

    // Set the required callback functions
    glfwSetKeyCallback(window, key_callback);

    // Set this to true so GLEW knows to use a modern approach to retrieving function pointers and extensions
    glewExperimental = GL_TRUE;
    // Initialize GLEW to setup the OpenGL Function pointers
    glewInit();

    // Define the viewport dimensions
    int width, height;
    glfwGetFramebufferSize(window, &width, &height);
    glViewport(0, 0, width, height);


    // Build and compile the shader programs (we ignored compile log checks for readability (if you do encounter issues, add the compile-checks!))
    GLuint vertexShader = glCreateShader(GL_VERTEX_SHADER);
    GLuint fragmentShaderOrange = glCreateShader(GL_FRAGMENT_SHADER); // The first fragment shader that outputs the color orange
    GLuint fragmentShaderYellow = glCreateShader(GL_FRAGMENT_SHADER); // The second fragment shader that outputs the color yellow
    GLuint shaderProgramOrange = glCreateProgram();
    GLuint shaderProgramYellow = glCreateProgram(); // The second shader program
    glShaderSource(vertexShader, 1, &vertexShaderSource, NULL);
    glCompileShader(vertexShader);
    glShaderSource(fragmentShaderOrange, 1, &fragmentShader1Source, NULL);
    glCompileShader(fragmentShaderOrange);
    glShaderSource(fragmentShaderYellow, 1, &fragmentShader2Source, NULL);
    glCompileShader(fragmentShaderYellow);

    // Link the first program object
    glAttachShader(shaderProgramOrange, vertexShader);
    glAttachShader(shaderProgramOrange, fragmentShaderOrange);
    glLinkProgram(shaderProgramOrange);
    // Then link the second program object using a different fragment shader (but same vertex shader) this time.
    // This is perfectly allowed since the inputs and outputs of both the vertex and fragment shaders are equally matched.
    glAttachShader(shaderProgramYellow, vertexShader);
    glAttachShader(shaderProgramYellow, fragmentShaderYellow);
    glLinkProgram(shaderProgramYellow);

    // Set up vertex data (and buffer(s)) and attribute pointers
    // We add a new set of vertices to form a second triangle (a total of 6 vertices); the vertex attribute configuration remains the same (still one 3-float position vector per vertex)
    GLfloat firstTriangle[] = {
            -0.9f, -0.5f, 0.0f,  // Left
            -0.0f, -0.5f, 0.0f,  // Right
            -0.45f, 0.5f, 0.0f,  // Top
    };
    GLfloat secondTriangle[] = {
            0.0f, -0.5f, 0.0f,  // Left
            0.9f, -0.5f, 0.0f,  // Right
            0.45f, 0.5f, 0.0f   // Top
    };
    GLuint VBOs[2], VAOs[2];
    glGenVertexArrays(2, VAOs); // We can also generate multiple VAOs or buffers at the same time
    glGenBuffers(2, VBOs);
    // ================================
    // First Triangle setup
    // ===============================
    glBindVertexArray(VAOs[0]);
    glBindBuffer(GL_ARRAY_BUFFER, VBOs[0]);
    glBufferData(GL_ARRAY_BUFFER, sizeof(firstTriangle), firstTriangle, GL_STATIC_DRAW);
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(GLfloat), (GLvoid*)0);	// Vertex attributes stay the same
    glEnableVertexAttribArray(0);
    glBindVertexArray(0);
    // ================================
    // Second Triangle setup
    // ===============================
    glBindVertexArray(VAOs[1]);	// Note that we bind to a different VAO now
    glBindBuffer(GL_ARRAY_BUFFER, VBOs[1]);	// And a different VBO
    glBufferData(GL_ARRAY_BUFFER, sizeof(secondTriangle), secondTriangle, GL_STATIC_DRAW);
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, (GLvoid*)0); // Because the vertex data is tightly packed we can also specify 0 as the vertex attribute's stride to let OpenGL figure it out.
    glEnableVertexAttribArray(0);
    glBindVertexArray(0);

    GLint nrAttributes;
    glGetIntegerv(GL_MAX_VERTEX_ATTRIBS, &nrAttributes);
    std::cout << "Maximum nr of vertex attributes supported: " << nrAttributes << std::endl;

    // Game loop
    while (!glfwWindowShouldClose(window))
    {
        // Check if any events have been activiated (key pressed, mouse moved etc.) and call corresponding response functions
        glfwPollEvents();

        // Render
        // Clear the colorbuffer
        glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT);

        // Now when we want to draw the triangle we first use the vertex and orange fragment shader from the first program.
        glUseProgram(shaderProgramOrange);
        // Draw the first triangle using the data from our first VAO
        glBindVertexArray(VAOs[0]);
        glDrawArrays(GL_TRIANGLES, 0, 3);	// This call should output an orange triangle
        // Then we draw the second triangle using the data from the second VAO
        // When we draw the second triangle we want to use a different shader program so we switch to the shader program with our yellow fragment shader.
        glUseProgram(shaderProgramYellow);

        //set ourColor
        GLfloat timeValue = glfwGetTime();
        GLfloat greenValue = (sin(timeValue) / 2) + 0.5;
        cout<< "time:" << timeValue << ",greenValue:" << sin(timeValue)<<endl;
        GLint vertexColorLocation = glGetUniformLocation(shaderProgramYellow, "ourColor");
        glUniform4f(vertexColorLocation, 1.0f, greenValue, 1.0f, 1.0f);

        glBindVertexArray(VAOs[1]);
        glDrawArrays(GL_TRIANGLES, 0, 3);	// This call should output a yellow triangle
        glBindVertexArray(0);

        // Swap the screen buffers
        glfwSwapBuffers(window);
    }
    // Properly de-allocate all resources once they've outlived their purpose
    glDeleteVertexArrays(2, VAOs);
    glDeleteBuffers(2, VBOs);
    // Terminate GLFW, clearing any resources allocated by GLFW.
    glfwTerminate();
    return 0;
}

// Is called whenever a key is pressed/released via GLFW
void key_callback(GLFWwindow* window, int key, int scancode, int action, int mode)
{
    // 当用户按下ESC键,我们设置window窗口的WindowShouldClose属性为true
    // 关闭应用程序
    if(key == GLFW_KEY_Q && action == GLFW_PRESS){
        glfwSetWindowShouldClose(window, GL_TRUE);
    }

    if(key == GLFW_KEY_W && action == GLFW_PRESS){
        glfwSetWindowSize(window,400,300);
        int width, height;
        glfwGetFramebufferSize(window, &width, &height);
        glViewport(0, 0, width, height);
    }

    if(key == GLFW_KEY_S && action == GLFW_PRESS){
        glfwSetWindowSize(window,800,600);
        int width, height;
        glfwGetFramebufferSize(window, &width, &height);
        glViewport(0, 0, width, height);
    }

}
