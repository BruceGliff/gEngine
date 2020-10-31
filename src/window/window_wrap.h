#pragma once

#include <string>

namespace Resources
{
	// forward declaration
	class glWindows;

	// singleton that represent current used resources class
	class windows_wrap final
	{
		glWindows* curr_window = nullptr;

	public:
		windows_wrap() noexcept;
		void construct(int width, int height, std::string const& WindowName);
		windows_wrap(windows_wrap const&) = delete;
		windows_wrap(windows_wrap&&) = delete;
		windows_wrap& operator=(windows_wrap const&) = delete;
		windows_wrap& operator=(windows_wrap&&) = delete;

		glWindows& GetWindow();
		glWindows const& GetWindow() const;

		~windows_wrap();
	};
}