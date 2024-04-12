#include "GLFW_window.h"
#include "gloom.h"
#include <iostream>

using Gloom::operator""_KiB;
using Gloom::operator""_MiB;

int main() {

  Gloom::GLFW_window window("hello", 800, 600);

  Gloom::Debug::EnableDebug();

  Gloom::Mesh mesh;
  Gloom::MeshLoader loader;

  Gloom::Commands::EnableFaceCulling();

  Gloom::Commands::EnableDepthTesting();

  Gloom::Scene::Camera camera;

  auto root = Gloom::Tools::GetRoot();

  loader.Load(root / "assets/obj/with_material/tree/Tree.obj", mesh);

  Gloom::ShaderPipeline pipeline(root / "gloom_shaders/gloom_simple.vert",
                                 root / "gloom_shaders/gloom_simple.frag");

  pipeline.Bind();

  Gloom::VertexArray vao;
  Gloom::Buffer vertex_buffer(Gloom::Types::BufferTarget::ARRAY_BUFFER,
                              Gloom::Types::BufferStorage::DYNAMIC_STORAGE,
                              10_MiB);

  float data[] = {
      -0.5f, -0.5f, 0.0f, 0.0f,  0.0f,  1.0f, +0.5f, -0.5f, 0.0f,
      0.0f,  0.0f,  1.0f, +0.0f, +0.5f, 0.0f, 0.0f,  0.0f,  1.0f,
  };

  auto translate =
      linalg::translation_matrix(Gloom::Types::Vector3f(0.0f, 0.0f, 0.0f));

  auto view = linalg::lookat_matrix(Gloom::Types::Vector3f(0.0f, 5.0f, 11.0f),
                                    Gloom::Types::Vector3f(0.0f, 0.0f, 0.0f),
                                    Gloom::Types::Vector3f(0.0f, 1.0f, 0.0f));

  auto sdata = std::as_bytes(std::span<float>(data));

  auto att = mesh.GetAttributes();

  vertex_buffer.SetData(std::as_bytes(std::span(att)),
                        0); // std::as_bytes(std::span(att))

  pipeline.SetUniform(Gloom::Types::ShaderIndex::VERTEX, "ModelMatrix",
                      translate);

  pipeline.SetUniform(Gloom::Types::ShaderIndex::VERTEX, "ProjectionMatrix",
                      camera.GetPerspectiveMatrix());

  pipeline.SetUniform(Gloom::Types::ShaderIndex::VERTEX, "ViewMatrix", view);

  Gloom::VertexFormat vertex_format(
      {Gloom::Types::DataType::VECTOR3, Gloom::Types::DataType::VECTOR3});
  vao.AddVertexBufferAndFormat(vertex_buffer, vertex_format);
  vao.Bind();

  while (window.ShouldClose() == false) {
    window.PollEvents();

    Gloom::Commands::Clear();

    Gloom::Commands::DrawArrays(Gloom::Types::PrimitiveKind::TRIANGLES, 0,
                                mesh.GetVerticesCount());

    window.Update();
  }

  return 0;
}