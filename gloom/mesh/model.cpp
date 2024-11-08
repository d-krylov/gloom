#include "mesh/include/model.h"

namespace Gloom {

Model::Model() = default;

Model::Model(Model &&) = default;

Model &Model::operator=(Model &&) = default;

Model::Model(const std::filesystem::path &path) : path_(path) { LoadWavefront(path_); }

} // namespace Gloom