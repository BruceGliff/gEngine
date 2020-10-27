#pragma once

#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <string>

namespace Resources
{
	// There is a singlton
	class GFLW_Wrap final
	{
	public:
		// Set up GLFW properties
		GFLW_Wrap();
		GFLW_Wrap(GFLW_Wrap const&) = delete;
		GFLW_Wrap(GFLW_Wrap&&) = delete;
		GFLW_Wrap& operator= (GFLW_Wrap const&) = delete;
		GFLW_Wrap& operator= (GFLW_Wrap&&) = delete;

		~GFLW_Wrap();
	};

	class glWindows final
	{
		// init window size
		int const x;
		int const y;
		// default window name
		std::string const name;
		// The first initialization of the gflw
		GFLW_Wrap const gflwProperties;
		// window pointer
		GLFWwindow* pWindow = nullptr;


	public:
		glWindows();
		glWindows(glWindows const &)			= delete;
		glWindows(glWindows &&)					= delete;
		glWindows& operator= (glWindows const&) = delete;
		glWindows& operator= (glWindows &&)		= delete;

		// Create window with size x, y and name(or gEngine as Default)
		glWindows(int x, int y, std::string const &);

		// Check if window is still active
		operator bool() const noexcept;

		// draw
		void Draw() const noexcept;

		// TODO THIS IS WRONG WAY TO DO IT!!!!
		// Return key which has been activated
		GLFWwindow* ProcessInput() const noexcept;



	private:
		/// Functions what overrides behavior
		// Override size changes
		static void glfwWindowSizeCallback(GLFWwindow* window, int width, int height);
		// Override keyboard events
		static void glfwKeyCallback(GLFWwindow* window, int key, int scanmode, int action, int mode);
	};
}