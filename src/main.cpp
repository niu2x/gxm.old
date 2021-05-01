#include <GLFW/glfw3.h>

#include "log.h"

int main(void)
{
	LOG_T << "startup";

    GLFWwindow* window;

    if (!glfwInit()){
    	LOG_F << "glfw init failed";
        return -1;
    }


	LOG_T << "create window";
    window = glfwCreateWindow(640, 480, "Hello World", NULL, NULL);
    if (!window)
    {
    	LOG_F << "create window failed";
        glfwTerminate();
        return -1;
    }

    glfwMakeContextCurrent(window);

    while (!glfwWindowShouldClose(window))
    {
        glClear(GL_COLOR_BUFFER_BIT);
        glfwSwapBuffers(window);
        glfwPollEvents();
    }

    glfwTerminate();
	LOG_T << "stop";
    return 0;
}