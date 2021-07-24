#include "primitives.h"

#include "../process/global.h"
#include "../manager/ResourceManager.h"

using namespace NSModel;

std::string Primitive::getFolderPath() {
    return std::filesystem::path{GLOBAL::GetResManager().getPathToExucutable() / "res/models/primitives/"}.string();
}
void Primitive::Draw() const {};
Primitive::~Primitive() {}




