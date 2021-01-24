#pragma once

#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <string>

namespace Resources
{
	// There is a singlton
	// Class that wraps bahavior of GLFW
	class GFLW_wrap final
	{
	public:
		// Set up GLFW properties
		GFLW_wrap();
		GFLW_wrap(GFLW_wrap const&)					= delete;
		GFLW_wrap(GFLW_wrap&&)						= delete;
		GFLW_wrap& operator= (GFLW_wrap const&)		= delete;
		GFLW_wrap& operator= (GFLW_wrap&&)			= delete;

		~GFLW_wrap();
	};

	// Class that contaisn properies of the window for global access of GLFW, but nobody else
	struct WindowSizeProperty final
	{
		int width = 0;
		int height = 0;

		WindowSizeProperty& operator=(std::initializer_list<int>& list);
	};

	// Class implemented behavior of the window
	class glWindow final
	{
		// global __WindowProperty is a property of glWindow!
		// default window name
		std::string const name;
		// The first initialization of the gflw
		GFLW_wrap const gflwProperties;
		// window pointer
		GLFWwindow* pWindow = nullptr;


	public:
		glWindow()								= delete;
		glWindow(glWindow const &)				= delete;
		glWindow(glWindow &&)					= delete;
		glWindow& operator= (glWindow const&)	= delete;
		glWindow& operator= (glWindow &&)		= delete;

		// Create window with size width, height and name(or gEngine as Default)
		glWindow(int width, int height, std::string const &);

		// Check if window is still active
		operator bool() const noexcept;

		// Return global window properties
		WindowSizeProperty const &  GetWindowSize() const noexcept;
		WindowSizeProperty& GetWindowSize() noexcept;

		// draw
		void Draw() const noexcept;

		// TODO THIS IS WRONG WAY TO DO IT!!!!
		// Return true if window is still active
		bool ProcessInput() const noexcept;



	private:
		/// Functions what overrides behavior
		// Override size changes
		static void glfwWindowSizeCallback(GLFWwindow* window, int width, int height);
		// Override keyboard events
		static void glfwKeyCallback(GLFWwindow* window, int key, int scanmode, int action, int mode);
		// Override mouse movement
		static void mouse_callback(GLFWwindow* window, double xpos, double ypos);
		// Override scrolls
		static void scroll_callback(GLFWwindow* window, double xoffset, double yoffset);
	};
}