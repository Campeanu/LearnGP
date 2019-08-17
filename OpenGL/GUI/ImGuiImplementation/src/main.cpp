//  The first thing we need to do to create a stunning graphics is to create an OpenGl context and an application window to draw in.
// ! Be sure to include GLAD before GLFW. The include file for GLAD contains the correct OpenGL header includes (like GL/gl.h) so including GLAD before other header files that require OpenGL does the trick.
//  GLAD, this library provide us with the ability to access OpenGL drivers.

// Here we will include the STL libraries
#include <iostream>
#include <stdio.h>


#include "imgui.h"
#include "ImGui/imgui_impl_glfw.h"
#include "ImGuI/imgui_impl_opengl3.h"

// About OpenGL function loaders: modern OpenGL doesn't have a standard header file and requires individual function pointers to be loaded manually.
// Helper libraries are often used for this purpose! Here we are supporting a few common ones: gl3w, glew, glad.
// You may use another loader/header of your choice (glext, glLoadGen, etc.), or chose to manually implement your own.
#if defined(IMGUI_IMPL_OPENGL_LOADER_GL3W)
#include <GL/gl3w.h>    // Initialize with gl3wInit()
#elif defined(IMGUI_IMPL_OPENGL_LOADER_GLEW)
#include <GL/glew.h>    // Initialize with glewInit()
#elif defined(IMGUI_IMPL_OPENGL_LOADER_GLAD)
#include <glad/glad.h>  // Initialize with gladLoadGL()
#else
#include IMGUI_IMPL_OPENGL_LOADER_CUSTOM
#endif

// Include glfw3.h after our OpenGL definitions
#include <GLFW/glfw3.h>


// [Win32] Our example includes a copy of glfw3.lib pre-compiled with VS2010 to maximize ease of testing and compatibility with old VS compilers.
// To link with VS2010-era libraries, VS2015+ requires linking with legacy_stdio_definitions.lib, which we do using this pragma.
// Your own project should not be affected, as you are likely to link with a newer binary of GLFW that is adequate for your version of Visual Studio.
#if defined(_MSC_VER) && (_MSC_VER >= 1900) && !defined(IMGUI_DISABLE_WIN32_FUNCTIONS)
#pragma comment(lib, "legacy_stdio_definitions")
#endif

// * --------------- Global functions ---------------

static void glfw_error_callback(int error, const char* description)
{
	fprintf(stderr, "Glfw Error %d: %s\n", error, description);
}

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

const unsigned int WINDOW_WIDTH = 800;
const unsigned int WINDOW_HEIGHT = 600;

// Next, we create the main function where we will instantiate the GLFW window:
int main()
{
	glfwSetErrorCallback(glfw_error_callback);
	// In the main function we firt initializate GLFW with -- glfwInit() --
	if (!glfwInit())
	{
		std::cout << "Failed to initialize GLFW" << std::endl;
		return -1;
	}

	// Now we can configure GLFW using glfwWindowHint. 
	// GL 3.0 + GLSL 130
	const char* glsl_version = "#version 130";
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 0);

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
	if (window == NULL)
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
	glfwSwapInterval(1); // Enable vsync

	/**
	 * We have to tell GLFW we want to call this function on every window resize by registering it.
	 */
	glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);

	// * We want to initialize GLAD before we call any OpenGL function:
	// if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
	// {
	//	std::cout << "Failed to initialize GLAD" << std::endl;
	//	return -1;
	// }
	/**
	 * We pass GLAD the function to load the adress of the OpenGL function pointers which is OS-specific.
	 * GLFW gives us glfwGetProcAddress that defines the correct function based on which OS we're compiling for.
	 */

	#if defined(IMGUI_IMPL_OPENGL_LOADER_GLEW)
	bool err = glewInit() != GLEW_OK;
	#endif
	 // Setup Dear ImGui context
	IMGUI_CHECKVERSION();
	ImGui::CreateContext();
	ImGuiIO& io = ImGui::GetIO(); (void)io;
	//io.ConfigFlags |= ImGuiConfigFlags_NavEnableKeyboard;     // Enable Keyboard Controls
	//io.ConfigFlags |= ImGuiConfigFlags_NavEnableGamepad;      // Enable Gamepad Controls

	// Setup Dear ImGui style
	ImGui::StyleColorsDark();
	//ImGui::StyleColorsClassic();

	// Setup Platform/Renderer bindings
	ImGui_ImplGlfw_InitForOpenGL(window, true);
	ImGui_ImplOpenGL3_Init(glsl_version);

	// Our state
	bool show_demo_window = true;
	bool show_another_window = false;
	ImVec4 clear_color = ImVec4(0.45f, 0.55f, 0.60f, 1.00f);

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
	while (!glfwWindowShouldClose(window))
	{
		// Input  ----- 
		processInput(window);

		/**
		 * The glfwPollEvents function checks if any events are triggered (like keyboard input or mouse movement events),
		 * updates the window state, and calls the corresponding functions (which we can set via callback methods).
		 */
		glfwPollEvents();

		// Start the Dear ImGui frame
		ImGui_ImplOpenGL3_NewFrame();
		ImGui_ImplGlfw_NewFrame();
		ImGui::NewFrame();

		// 1. Show the big demo window (Most of the sample code is in ImGui::ShowDemoWindow()! You can browse its code to learn more about Dear ImGui!).
		if (show_demo_window)
			ImGui::ShowDemoWindow(&show_demo_window);

		// 2. Show a simple window that we create ourselves. We use a Begin/End pair to created a named window.
		{
			static float f = 0.0f;
			static int counter = 0;

			ImGui::Begin("Hello, world!");                          // Create a window called "Hello, world!" and append into it.

			ImGui::Text("This is some useful text.");               // Display some text (you can use a format strings too)
			ImGui::Checkbox("Demo Window", &show_demo_window);      // Edit bools storing our window open/close state
			ImGui::Checkbox("Another Window", &show_another_window);

			ImGui::SliderFloat("float", &f, 0.0f, 1.0f);            // Edit 1 float using a slider from 0.0f to 1.0f
			ImGui::ColorEdit3("clear color", (float*)& clear_color); // Edit 3 floats representing a color

			if (ImGui::Button("Button"))                            // Buttons return true when clicked (most widgets return true when edited/activated)
				counter++;
			ImGui::SameLine();
			ImGui::Text("counter = %d", counter);

			ImGui::Text("Application average %.3f ms/frame (%.1f FPS)", 1000.0f / ImGui::GetIO().Framerate, ImGui::GetIO().Framerate);
			ImGui::End();
		}

		// 3. Show another simple window.
		if (show_another_window)
		{
			ImGui::Begin("Another Window", &show_another_window);   // Pass a pointer to our bool variable (the window will have a closing button that will clear the bool when clicked)
			ImGui::Text("Hello from another window!");
			if (ImGui::Button("Close Me"))
				show_another_window = false;
			ImGui::End();
		}



		// Render ----- 
		ImGui::Render();
		int display_w, display_h;
		glfwGetFramebufferSize(window, &display_w, &display_h);
		glViewport(0, 0, display_w, display_h);
		glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT);
		ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());

		/**
		 * glfwSwapBuffers will swap the color buffer (a large buffer that contains color values for each pixel in GLFW's window)
		 * that has been used to draw in during this iteration and show it as output to the screen.
		 *
		 * @param[GLFWwindow]
		 *      Take the window object as argument.
		 */
		glfwSwapBuffers(window);
	}

	// Cleanup
	ImGui_ImplOpenGL3_Shutdown();
	ImGui_ImplGlfw_Shutdown();
	ImGui::DestroyContext();

	glfwDestroyWindow(window);
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
	if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
		glfwSetWindowShouldClose(window, true);
}