#pragma once

#include <string>

namespace Resources
{
	// forward declaration
	class ResourcesManager;

	// singleton that represent current used resources class
	class ResourcesManager_wrap final
	{
		ResourcesManager* curr_mng = nullptr;

	public:
		ResourcesManager_wrap() noexcept;
		void construct(std::string const& path_to_exec);
		ResourcesManager_wrap(ResourcesManager_wrap const&) = delete;
		ResourcesManager_wrap(ResourcesManager_wrap&&) = delete;
		ResourcesManager_wrap& operator=(ResourcesManager_wrap const&) = delete;
		ResourcesManager_wrap& operator=(ResourcesManager_wrap&&) = delete;

		ResourcesManager& GetMenager();
		ResourcesManager const& GetMenager() const;

		~ResourcesManager_wrap();
	};
}