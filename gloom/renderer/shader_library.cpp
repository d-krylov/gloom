#include "gloom/renderer/include/shader_library.h"
#include "gloom/core/include/tools.h"

namespace Gloom {

ShaderLibrary *ShaderLibrary::shader_library_instance_ = nullptr;

ShaderLibrary::ShaderLibrary()
  : graphics_pipelines_{
      GraphicsPipeline{SHADERS_DIR / "mesh" / "mesh.vert", SHADERS_DIR / "mesh" / "mesh.frag"},
      GraphicsPipeline{SHADERS_DIR / "canvas" / "canvas.vert",
                       SHADERS_DIR / "canvas" / "canvas.frag"},
      GraphicsPipeline{SHADERS_DIR / "mesh" / "shadow_mapping.vert",
                       SHADERS_DIR / "mesh" / "shadow_mapping.frag"},
      GraphicsPipeline{SHADERS_DIR / "mesh" / "mesh_shadow.vert",
                       SHADERS_DIR / "mesh" / "mesh_shadow.frag"},
      GraphicsPipeline{SHADERS_DIR / "primitives" / "box.vert",
                       SHADERS_DIR / "primitives" / "primitives.frag"}

    } {
  shader_library_instance_ = this;
}

} // namespace Gloom