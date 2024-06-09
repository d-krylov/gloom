#include "graphics.h"
#include "window.h"
#include <iostream>

using Gloom::operator""_KiB;
using Gloom::operator""_MiB;

int main() {

  Gloom::Window window("Texture", 800, 600);
  Gloom::EnableDebug();
  auto root = Gloom::GetRoot();
  Gloom::GraphicsPipeline pipeline(root / "shaders/gloom_2d.vert",
                                   root / "shaders/gloom_2d.frag");
  pipeline.Bind();
  Gloom::VertexArray vao;
  Gloom::VertexBuffer position_buffer(4_KiB, {Gloom::DataType::VECTOR3}, 0);
  Gloom::VertexBuffer color_buffer(4_KiB, {Gloom::DataType::VECTOR3}, 1);
  Gloom::VertexBuffer uv_buffer(4_KiB, {Gloom::DataType::VECTOR2}, 2);
  Gloom::Image image(root / "assets/images/container.png");
  Gloom::Texture texture(Gloom::TextureTarget::TEXTURE_2D, image);
  texture.SetData(image.GetData());
  texture.Bind(0);
  Gloom::Vector3f position[] = {
    {+0.5f, +0.5f, 0.0f}, {+0.5f, -0.5f, 0.0f}, {-0.5f, -0.5f, 0.0f}, {-0.5f, +0.5f, 0.0f}};

  Gloom::Vector3f color[] = {
    {1.0f, 0.0f, 0.0f}, {0.0f, 1.0f, 0.0f}, {0.0f, 0.0f, 1.0f}, {1.0f, 1.0f, 0.0f}};

  Gloom::Vector2f uv[] = {{1.0f, 1.0f}, {1.0f, 0.0f}, {0.0f, 0.0f}, {0.0f, 1.0f}};

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
    Gloom::Commands::DrawElements(Gloom::PrimitiveKind::TRIANGLES, i);
    window.Update();
  }
}