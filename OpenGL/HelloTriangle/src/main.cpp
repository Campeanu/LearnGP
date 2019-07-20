//  The first thing we need to do to create a stunning graphics is to create an OpenGl context and an application window to draw in.
// ! Be sure to include GLAD before GLFW. The include file for GLAD contains the correct OpenGL header includes (like GL/gl.h) so including GLAD before other header files that require OpenGL does the trick.
//  GLAD, this library provide us with the ability to access OpenGL drivers.
#include "GLAD/glad.h"

// GLFW, this is on of the most popular OpenGL library. This provide as the posibily to create a window and a context.
#include <GLFW/glfw3.h>

// Here we will include the STL libraries
#include <iostream>

// * --------------- Global functions ---------------

/**
 * When the window is first displayed framebuffer_size_callback gets called as well with the resulting window dimensions.  
 * * We register the callback functions after we've created the window and before the game loop is initiated.
 */
void framebuffer_size_callback(GLFWwindow* window, int width, int height);  

/**
 * @param[GLFWwindow]
 *      Take the window object as argument.  
 */
void processInput(GLFWwindow* window);

// * SETTINGS

const unsigned int WINDOW_WIDTH  = 800;  
const unsigned int WINDOW_HEIGHT = 600;

// Next, we create the main function where we will instantiate the GLFW window:
int main()
{
    // In the main function we firt initializate GLFW with -- glfwInit() --
    if(!glfwInit())
    {
        std::cout << "Failed to initialize GLFW" << std::endl;
        return -1;
    }
    
    // Now we can configure GLFW using glfwWindowHint. 
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 1);
	glfwWindowHint(GLFW_OPENGL_ANY_PROFILE, GLFW_OPENGL_CORE_PROFILE);

    /** glfwCreateWindow(int, int, const char*, GLFWmonitor, GLFWwindow)
     *
     * Next we're required to create a window object. This window object holds all the windowing data 
     * and is used quite frequently by GLFW's other functions.
     * 
     * @param[int] "width"
     *      The glfwCreateWindow function requires the window width as it first parameter.
     * @param[int] "height"
     *      The glfwCreateWindow function requires the window height as it seccond parameter.
     * @param[const* char] "title"
     *      The third argument allows us to create a name for the window; for now we call it "Hello Triangle".
     * @param[GLFWmonitor] "monitor"
     *      The four argument require the monito to use for the full screen mode, or NULL to use windowe mode.
     * @param[GLFWwindow] "share"
     *      The last argument ... the window whose context to share resources with, or NULL to not share resources.
     * 
     * @return a GLFWwindow object
     *      The function returns a GLFWwindow object that we'll later need for other GLFW operations.
     */
    GLFWwindow* window = glfwCreateWindow(WINDOW_WIDTH, WINDOW_HEIGHT, "Hello Triangle", NULL, NULL);
    if(window == NULL)
    {
        std::cout << "Failed to create GLFW window" << std::endl;
        glfwTerminate();
        return -1;
    }
    /**
     * This function makes the context of the specific window current on the calling thread.
     * A context can only be made current on a single thread at a time and each thread can have only a single context at a time.
     * @note: Check what is the meaning of a thread.
     */
    glfwMakeContextCurrent(window);
    
    /**
     * We have to tell GLFW we want to call this function on every window resize by registering it.
     */
    glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);  
    
    // * We want to initialize GLAD before we call any OpenGL function:
    if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
    {
        std::cout << "Failed to initialize GLAD" << std::endl;
        return -1;
    }
    /**
     * We pass GLAD the function to load the adress of the OpenGL function pointers which is OS-specific. 
     * GLFW gives us glfwGetProcAddress that defines the correct function based on which OS we're compiling for.
     */

    /**
     * The glfwWindowShouldClose function checks at the start of each loop iteration if GLFW has been instructed to close. 
     * If so, the function returns true and the game loop stops running, after which we can close the application.
     * 
     * @param[GLFWwindow]
     *      Take the window object as argument.  
     * @return {GL_TRUE or GL_FALSE}
     *      Returns GL_TRUE if window has been instructed to close
     *      The function will thus continously return GL_FALSE until instructed otherwise.  
     */
    while(!glfwWindowShouldClose(window))
    {   
		// Input  ----- 
		processInput(window);

        // Render ----- 
        glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT);

        /**
         * glfwSwapBuffers will swap the color buffer (a large buffer that contains color values for each pixel in GLFW's window) 
         * that has been used to draw in during this iteration and show it as output to the screen.
         * 
         * @param[GLFWwindow]
         *      Take the window object as argument.  
         */
        glfwSwapBuffers(window);

        /**
         * The glfwPollEvents function checks if any events are triggered (like keyboard input or mouse movement events), 
         * updates the window state, and calls the corresponding functions (which we can set via callback methods). 
         */
        glfwPollEvents();
    }
    
	glfwTerminate();
	return 0;
} 

void framebuffer_size_callback(GLFWwindow* window, int width, int height)
{
    /**
     * The first two parametres of glViewport set the location of the lower left corer of the window.
     * The third and four parameters set the width and the height of the rendering window in pixels, which we set equal to GLFW's window size;
     */
    glViewport(0, 0, width, height);
}

void processInput(GLFWwindow* window)
{
    if(glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
        glfwSetWindowShouldClose(window, true);
}