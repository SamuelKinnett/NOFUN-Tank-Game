#include <iostream>
#include <stdlib.h>
#include <stdio.h>
#include <math.h>
#include <GLFW/glfw3.h>
#include "include/Tank.hpp"

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

/*
// Replaces gluPerspective. Sets the frustum to perspective mode.
// fovY     - Field of vision in degrees in the y direction
// aspect   - Aspect ratio of the viewport
// zNear    - The near clipping distance
// zFar     - The far clipping distance

void perspectiveGL( GLdouble fovY, GLdouble aspect, GLdouble zNear, GLdouble zFar )
{
    const GLdouble pi = 3.1415926535897932384626433832795;
    GLdouble fW, fH;
    fH = tan( (fovY / 2) / 180 * pi ) * zNear;
    fH = tan( fovY / 360 * pi ) * zNear;
    fW = fH * aspect;
    glFrustum( -fW, fW, -fH, fH, zNear, zFar );
}*/

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

    glEnable (GL_BLEND);
    glBlendFunc (GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);


    Tank tnk(90, 42, 18000, 1000, 90, 100), tnk2;
    tnk2.moveFwd();
    tnk2.update(1);
    tnk2.traverseLeft();
    tnk2.target(tnk);
    tnk2.update(0.5);
    glfwSetTime(0); //reset time before entering game loop
    double dt = 0; //time
    double cx, cy, tx, ty;
    char buf[32];
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

        glColor3d(0, 0, 0);
        glPushMatrix();
        tx = -tnk.getPosX() + width / 2.0 - sin(-tnk.getHullRotation())*tnk.getVel()*0.25;
        ty = -tnk.getPosY() + height / 2.0 - cos(-tnk.getHullRotation())*tnk.getVel()*0.25;
        glTranslatef(tx, ty, 0);
        
        tnk.draw();
        tnk2.draw();
        glPopMatrix();

        glfwSwapBuffers(window);
        glfwPollEvents();

        dt = glfwGetTime(); //get frametime
        glfwSetTime(0);
        sprintf(buf, "%fms", dt*1000);
        glfwSetWindowTitle(window, buf); //print frametime to window title

        glfwGetCursorPos(window, &cx, &cy);
        cx -= tx; //translate cursor corrdinates
        cy -= ty;
        tnk.processKeys(window, cx, cy);
        tnk.update(dt);
        
        //tnk2.moveFwd();
        tnk2.target(tnk);
        tnk2.interpolate(dt);
    }
    glfwDestroyWindow(window);
    glfwTerminate();
    return EXIT_SUCCESS;
}
