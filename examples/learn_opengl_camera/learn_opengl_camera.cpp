#include "GLFW_window.h"
#include "gloom.h"
#include <array>

using Gloom::operator""_KiB;

int main() {

  Gloom::GLFW_window window("Learn OpenGL: Camera", 800, 600);
  Gloom::Debug::EnableDebug();

  std::array<Gloom::VertexPT, 36> vertices = {
      Gloom::VertexPT{{-0.5f, -0.5f, -0.5f}, {0.0f, 0.0f}},
      Gloom::VertexPT{{+0.5f, -0.5f, -0.5f}, {1.0f, 0.0f}},
      Gloom::VertexPT{{+0.5f, +0.5f, -0.5f}, {1.0f, 1.0f}},
      Gloom::VertexPT{{+0.5f, +0.5f, -0.5f}, {1.0f, 1.0f}},
      Gloom::VertexPT{{-0.5f, +0.5f, -0.5f}, {0.0f, 1.0f}},
      Gloom::VertexPT{{-0.5f, -0.5f, -0.5f}, {0.0f, 0.0f}},

      Gloom::VertexPT{{-0.5f, -0.5f, +0.5f}, {0.0f, 0.0f}},
      Gloom::VertexPT{{+0.5f, -0.5f, +0.5f}, {1.0f, 0.0f}},
      Gloom::VertexPT{{+0.5f, +0.5f, +0.5f}, {1.0f, 1.0f}},
      Gloom::VertexPT{{+0.5f, +0.5f, +0.5f}, {1.0f, 1.0f}},
      Gloom::VertexPT{{-0.5f, +0.5f, +0.5f}, {0.0f, 1.0f}},
      Gloom::VertexPT{{-0.5f, -0.5f, +0.5f}, {0.0f, 0.0f}},

      Gloom::VertexPT{{-0.5f, +0.5f, +0.5f}, {1.0f, 0.0f}},
      Gloom::VertexPT{{-0.5f, +0.5f, -0.5f}, {1.0f, 1.0f}},
      Gloom::VertexPT{{-0.5f, -0.5f, -0.5f}, {0.0f, 1.0f}},
      Gloom::VertexPT{{-0.5f, -0.5f, -0.5f}, {0.0f, 1.0f}},
      Gloom::VertexPT{{-0.5f, -0.5f, +0.5f}, {0.0f, 0.0f}},
      Gloom::VertexPT{{-0.5f, +0.5f, +0.5f}, {1.0f, 0.0f}},

      Gloom::VertexPT{{+0.5f, +0.5f, +0.5f}, {1.0f, 0.0f}},
      Gloom::VertexPT{{+0.5f, +0.5f, -0.5f}, {1.0f, 1.0f}},
      Gloom::VertexPT{{+0.5f, -0.5f, -0.5f}, {0.0f, 1.0f}},
      Gloom::VertexPT{{+0.5f, -0.5f, -0.5f}, {0.0f, 1.0f}},
      Gloom::VertexPT{{+0.5f, -0.5f, +0.5f}, {0.0f, 0.0f}},
      Gloom::VertexPT{{+0.5f, +0.5f, +0.5f}, {1.0f, 0.0f}},

      Gloom::VertexPT{{-0.5f, -0.5f, -0.5f}, {0.0f, 1.0f}},
      Gloom::VertexPT{{+0.5f, -0.5f, -0.5f}, {1.0f, 1.0f}},
      Gloom::VertexPT{{+0.5f, -0.5f, +0.5f}, {1.0f, 0.0f}},
      Gloom::VertexPT{{+0.5f, -0.5f, +0.5f}, {1.0f, 0.0f}},
      Gloom::VertexPT{{-0.5f, -0.5f, +0.5f}, {0.0f, 0.0f}},
      Gloom::VertexPT{{-0.5f, -0.5f, -0.5f}, {0.0f, 1.0f}},

      Gloom::VertexPT{{-0.5f, +0.5f, -0.5f}, {0.0f, 1.0f}},
      Gloom::VertexPT{{+0.5f, +0.5f, -0.5f}, {1.0f, 1.0f}},
      Gloom::VertexPT{{+0.5f, +0.5f, +0.5f}, {1.0f, 0.0f}},
      Gloom::VertexPT{{+0.5f, +0.5f, +0.5f}, {1.0f, 0.0f}},
      Gloom::VertexPT{{-0.5f, +0.5f, +0.5f}, {0.0f, 0.0f}},
      Gloom::VertexPT{{-0.5f, +0.5f, -0.5f}, {0.0f, 1.0f}}};

  auto root = Gloom::Tools::GetRoot();
  Gloom::GraphicsPipeline pipeline(root / "shaders/position3_texture2.vert",
                                   root / "shaders/position3_texture2.frag");

  pipeline.Bind();
  Gloom::VertexArray vao;

  Gloom::Image image(root / "assets/images/container.png");
  Gloom::Texture texture(Gloom::Types::TextureTarget::TEXTURE_2D, image);

  texture.SetData(image.GetData());
  texture.Bind(0);

  Gloom::VertexBuffer vbo(Gloom::Types::BufferStorage::DYNAMIC_STORAGE, 4_KiB,
                          Gloom::VertexPT::GetFormat());

  vbo.SetData(std::span<Gloom::VertexPT>(vertices));

  vao.AddVertexBuffer(vbo);
  vao.Bind();

  while (window.ShouldClose() == false) {
    window.PollEvents();
    Gloom::Commands::Clear();
    Gloom::Commands::DrawArrays(Gloom::Types::PrimitiveKind::TRIANGLES, 0,
                                vertices.size());
    window.Update();
  }

  return 0;
}