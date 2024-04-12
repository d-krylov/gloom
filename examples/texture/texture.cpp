#include "GLFW_window.h"
#include "gloom.h"
#include <array>
#include <iostream>

using Gloom::operator""_KiB;
using Gloom::operator""_MiB;

int main() {

  Gloom::GLFW_window window("Texture", 800, 600);
  Gloom::Debug::EnableDebug();
  auto root = Gloom::Tools::GetRoot();
  Gloom::ShaderPipeline pipeline(root / "gloom_shaders/gloom_2d.vert",
                                 root / "gloom_shaders/gloom_2d.frag");
  pipeline.Bind();
  Gloom::VertexArray vao;

  Gloom::Image image(root / "assets/images/container.png");
  Gloom::Texture texture(Gloom::Types::TextureTarget::TEXTURE_2D, image);

  texture.SetData(image.GetData());
  texture.Bind(0);

  // clang-format off
  Gloom::VertexPCT data[] = { 
    {{+0.5f, +0.5f, 0.0f}, {1.0f, 0.0f, 0.0f}, {1.0f, 1.0f}},   // top right
    {{+0.5f, -0.5f, 0.0f}, {0.0f, 1.0f, 0.0f}, {1.0f, 0.0f}},   // bottom right
    {{-0.5f, -0.5f, 0.0f}, {0.0f, 0.0f, 1.0f}, {0.0f, 0.0f}},   // bottom left
    {{-0.5f, +0.5f, 0.0f}, {1.0f, 1.0f, 0.0f}, {0.0f, 1.0f}}    // top left 
  };
  // clang-format on

  std::array<uint32_t, 6> i = {0, 1, 2, 2, 3, 0};

  Gloom::VertexBuffer vbo(Gloom::Types::BufferStorage::DYNAMIC_STORAGE, 4_KiB,
                          Gloom::VertexPCT::GetFormat());

  vbo().SetData(std::as_bytes(std::span(data)));

  vao.AddVertexBuffer(vbo);
  vao.Bind();

  while (window.ShouldClose() == false) {
    window.PollEvents();
    Gloom::Commands::Clear();
    Gloom::Commands::DrawElements(Gloom::Types::PrimitiveKind::TRIANGLES, i);
    window.Update();
  }

  return 0;
}