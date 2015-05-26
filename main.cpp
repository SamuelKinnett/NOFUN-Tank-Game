#include <iostream>
#include <stdlib.h>
#include <stdio.h>
#include <GLFW/glfw3.h>

const int VERSION = 1;

static void error_callback(int error, const char* description)
{
    fputs(description, stderr);
}

static void key_callback(GLFWwindow* window, int key, int scancode, int action, int mods)
{
    if(key == GLFW_KEY_ESCAPE && action == GLFW_PRESS)
    {
        glfwSetWindowShouldClose(window, GL_TRUE);
    }
}

static void scroll_callback(GLFWwindow* window, double xoffset, double yoffset)
{

}

int main(int argc, char** argv)
{
    if(!glfwInit())
    {
        fputs("GLFW Init failed", stderr);
        exit(EXIT_FAILURE);
    }

    GLFWwindow* window;
    glfwSetErrorCallback(error_callback);

    const GLFWvidmode * mode = glfwGetVideoMode(glfwGetPrimaryMonitor());
    int width = mode->width/2, height = mode->height/2;
    int posX = mode->width/2-width/2, posY = mode->height/2-height/2;

    window = glfwCreateWindow(width, height, "NOFUN Tank Game", NULL, NULL);
    glfwSetWindowPos(window, posX, posY);
    glfwMakeContextCurrent(window);

    glfwSetKeyCallback(window, key_callback);
    glfwSetScrollCallback(window, scroll_callback);

    glClearColor(1.0, 1.0, 1.0, 1.0);

    double tankX = 50, tankY = 50; //keep tank position
    while(!glfwWindowShouldClose(window))
    {
        glfwGetFramebufferSize(window, &width, &height);
        glViewport(0, 0, width, height);
        glClear(GL_COLOR_BUFFER_BIT);

        glMatrixMode(GL_PROJECTION);
        glLoadIdentity();
        glOrtho(0, width, height, 0, -1, +1);

        glMatrixMode(GL_MODELVIEW);
        glLoadIdentity();

        glColor3d(0.0,0.0,0.0);
        glBegin(GL_QUADS);
        {
            glVertex2d(tankX, tankY);
            glVertex2d(tankX+50, tankY);
            glVertex2d(tankX+50, tankY+20);
            glVertex2d(tankX, tankY+20);
        }
        glEnd();

        double xmov = 0.15, ymov = 0.07; //how much to move the tank in the directions
        if(glfwGetKey(window, GLFW_KEY_UP) == GLFW_PRESS)
        {
            tankY-=ymov;
        }
        if(glfwGetKey(window, GLFW_KEY_DOWN) == GLFW_PRESS)
        {
            tankY+=ymov;
        }
        if(glfwGetKey(window, GLFW_KEY_LEFT) == GLFW_PRESS)
        {
            tankX-=xmov;
        }
        if(glfwGetKey(window, GLFW_KEY_RIGHT) == GLFW_PRESS)
        {
            tankX+=xmov;
        }

        glfwSwapBuffers(window);
        glfwPollEvents();
    }
    glfwDestroyWindow(window);
    glfwTerminate();
    return EXIT_SUCCESS;
}
