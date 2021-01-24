#pragma once

#include <string>

namespace Resources
{
	// forward declaration
	class ResourcesManager;
	class glWindow;

	// singleton that represent current used resources class.
	// It contains handling both ResourceManager and glWindow as the destruction order is important(TODO check if it is true)
	class EnvironmentHandler_wrap final
	{
		ResourcesManager* curr_mng = nullptr;
		glWindow* curr_window = nullptr;

		// create new resourses handler context if it is not exist.
		void ConstructManager(std::string const& path_to_exec);
		void ConstructWindow(int width, int height, std::string const& WindowName);

	public:
		// do nothing
		EnvironmentHandler_wrap() noexcept;
		// TODO check if can do void construct(glWindow &&, ResourceManager&&);
		// construct window context and resource handler context. Order is important!
		void construct(int width, int height, std::string const& WindowName, std::string const& path_to_exec);

		EnvironmentHandler_wrap(EnvironmentHandler_wrap const&)				= delete;
		EnvironmentHandler_wrap(EnvironmentHandler_wrap&&)					= delete;
		EnvironmentHandler_wrap& operator=(EnvironmentHandler_wrap const&)	= delete;
		EnvironmentHandler_wrap& operator=(EnvironmentHandler_wrap&&)		= delete;

		// return resourses manager context. throw an execption if it is not created
		ResourcesManager& GetMenager();
		// return resourses manager context. throw an execption if it is not created
		ResourcesManager const& GetMenager() const;
		// return window context. throw an execption if it is not created
		glWindow& GetWindow();
		// return window context. throw an execption if it is not created
		glWindow const& GetWindow() const;

		~EnvironmentHandler_wrap();
	};
}