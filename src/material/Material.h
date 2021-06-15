/** Material is arrays of textures:
 * IMatNode * diffuse
 * IMatNode * specular
 * IMatNode * Ambient
 * IMatNode * Emissive
 * IMatNode * Height
 * IMatNode * Normals
 * IMatNode * Shininess
 * IMatNode * Opacity
 * IMatNode * Dispacement
 * IMatNode * LightMat
 * IMatNode * Reflection
 * IMatNode * Base_color
 * IMatNode * Normal_camera
 * IMatNode * Emission_color
 * IMatNode * Metalness
 * IMatNode * Diffuse_roughness
 * IMatNode * Ambient_occlusion
 * std::unordered_map<aiTexture_Type, std::vector<IMatNode *>> materials
 * */

#pragma once

#include <assimp/material.h>

#include <unordered_map>


namespace Material {

class IMatNode;

class Material {
 IMatNode * Diffuse             {nullptr};
 IMatNode * Specular            {nullptr};
 IMatNode * Ambient             {nullptr};
 IMatNode * Emissive            {nullptr};
 IMatNode * Heigh               {nullptr};
 IMatNode * Normals             {nullptr};
 IMatNode * Shininess           {nullptr};
 IMatNode * Opacity             {nullptr};
 IMatNode * Dispacement         {nullptr};
 IMatNode * LightMat            {nullptr};
 IMatNode * Reflectio           {nullptr};
 IMatNode * Base_colo           {nullptr};
 IMatNode * Normal_camera       {nullptr};
 IMatNode * Emission_colo       {nullptr};
 IMatNode * Metalness           {nullptr};
 IMatNode * Diffuse_roughness   {nullptr};
 IMatNode * Ambient_occlusion   {nullptr};
 std::unordered_map<aiTextureType, std::vector<IMatNode *>> materials {};
    
};

} // namespace Material