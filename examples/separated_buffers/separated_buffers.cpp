#include "GLFW_window.h"
#include "gloom.h"
#include <iostream>

auto STORAGE = Gloom::Types::BufferStorage::DYNAMIC_STORAGE;

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
  Gloom::VertexBuffer position_buffer(STORAGE, 4_KiB, Gloom::MakePosition3f());
  Gloom::VertexBuffer color_buffer(STORAGE, 4_KiB, Gloom::MakeColor());
  Gloom::VertexBuffer uv_buffer(STORAGE, 4_KiB, Gloom::MakeUV());
  Gloom::Image image(root / "assets/images/container.png");
  Gloom::Texture texture(Gloom::Types::TextureTarget::TEXTURE_2D, image);
  texture.SetData(image.GetData());
  texture.Bind(0);
  Gloom::Types::Vector3f position[] = {{+0.5f, +0.5f, 0.0f},
                                       {+0.5f, -0.5f, 0.0f},
                                       {-0.5f, -0.5f, 0.0f},
                                       {-0.5f, +0.5f, 0.0f}};

  Gloom::Types::Vector3f color[] = {{1.0f, 0.0f, 0.0f},
                                    {0.0f, 1.0f, 0.0f},
                                    {0.0f, 0.0f, 1.0f},
                                    {1.0f, 1.0f, 0.0f}};

  Gloom::Types::Vector2f uv[] = {
      {1.0f, 1.0f}, {1.0f, 0.0f}, {0.0f, 0.0f}, {0.0f, 1.0f}};

  std::array<uint32_t, 6> i = {0, 1, 2, 2, 3, 0};

  position_buffer.SetData(std::as_bytes(std::span(position)));
  color_buffer.SetData(std::as_bytes(std::span(color)));
  uv_buffer.SetData(std::as_bytes(std::span(uv)));

  vao.AddVertexBuffer(position_buffer);
  vao.AddVertexBuffer(color_buffer);
  vao.AddVertexBuffer(uv_buffer);

  vao.Bind();

  while (window.ShouldClose() == false) {
    window.PollEvents();
    Gloom::Commands::Clear();
    Gloom::Commands::DrawElements(Gloom::Types::PrimitiveKind::TRIANGLES, i);
    window.Update();
  }
}