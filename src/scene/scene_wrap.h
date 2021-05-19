#pragma once

namespace Scene
{
    // forward declaration
    class Scene;

    // singleton that represent current used scene class
    class scene_wrap final
    {
        Scene* curr_scene = nullptr;

    public:
        scene_wrap() = default;
        // create empty scene
        void construct();
        scene_wrap(scene_wrap const &) = delete;
        scene_wrap(scene_wrap &&) = delete;
        scene_wrap operator=(scene_wrap const&) = delete;
        scene_wrap operator=(scene_wrap&&) = delete;

        Scene & GetScene();
        Scene const& GetScene() const;

        ~scene_wrap();
    };
}