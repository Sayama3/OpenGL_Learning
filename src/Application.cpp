#include "imgui.h"
#include "imgui_impl_glfw.h"
#include "imgui_impl_opengl3.h"

#include <fstream>
#include <iostream>
#include <sstream>
#include <vector>
#include <algorithm>

#include "glm/glm.hpp"
#include "glm/gtc/matrix_transform.hpp"

#include "Display.hpp"
#include "Camera.hpp"
#include "Renderer.hpp"
#include "IndexBuffer.hpp"
#include "VertexBuffer.hpp"
#include "VertexArray.hpp"
#include "ShaderProgram.hpp"
#include "Texture.hpp"
#include "Mesh.hpp"

using namespace Sayama::OpenGLLearning;


int main() {
	Display display("OpenGL Window", 980, 480);
	Camera camera(display);

	Mesh mesh(8, 36);
	float minDimension = glm::min(display.GetNormalizedWidth(), display.GetNormalizedHeight());
	float size = minDimension * 0.25f;
	std::vector<Triangle> tris = {
			{ // South face
					{-(size * 0.5f),-(size * 0.5f),-(size * 0.5f)},
					{+(size * 0.5f),-(size * 0.5f),-(size * 0.5f)},
					{+(size * 0.5f),+(size * 0.5f),-(size * 0.5f)},
			},
			{
					{-(size * 0.5f),-(size * 0.5f),-(size * 0.5f)},
					{+(size * 0.5f),+(size * 0.5f),-(size * 0.5f)},
					{-(size * 0.5f),+(size * 0.5f),-(size * 0.5f)},
			},
			{ // East Face
					{+(size * 0.5f),-(size * 0.5f),-(size * 0.5f)},
					{+(size * 0.5f),-(size * 0.5f),+(size * 0.5f)},
					{+(size * 0.5f),+(size * 0.5f),+(size * 0.5f)},
			},
			{
					{+(size * 0.5f),-(size * 0.5f),-(size * 0.5f)},
					{+(size * 0.5f),+(size * 0.5f),+(size * 0.5f)},
					{+(size * 0.5f),+(size * 0.5f),-(size * 0.5f)},
			},
			{ // North Face
					{+(size * 0.5f),-(size * 0.5f),+(size * 0.5f)},
					{-(size * 0.5f),-(size * 0.5f),+(size * 0.5f)},
					{-(size * 0.5f),+(size * 0.5f),+(size * 0.5f)},
			},
			{
					{+(size * 0.5f),-(size * 0.5f),+(size * 0.5f)},
					{-(size * 0.5f),+(size * 0.5f),+(size * 0.5f)},
					{+(size * 0.5f),+(size * 0.5f),+(size * 0.5f)},
			},
			{ // West Face
					{-(size * 0.5f),-(size * 0.5f),+(size * 0.5f)},
					{-(size * 0.5f),-(size * 0.5f),-(size * 0.5f)},
					{-(size * 0.5f),+(size * 0.5f),-(size * 0.5f)},
			},
			{
					{-(size * 0.5f),-(size * 0.5f),+(size * 0.5f)},
					{-(size * 0.5f),+(size * 0.5f),-(size * 0.5f)},
					{-(size * 0.5f),+(size * 0.5f),+(size * 0.5f)},
			},
			{ // Up Face
					{-(size * 0.5f),+(size * 0.5f),-(size * 0.5f)},
					{+(size * 0.5f),+(size * 0.5f),-(size * 0.5f)},
					{+(size * 0.5f),+(size * 0.5f),+(size * 0.5f)},
			},
			{
					{-(size * 0.5f),+(size * 0.5f),-(size * 0.5f)},
					{+(size * 0.5f),+(size * 0.5f),+(size * 0.5f)},
					{-(size * 0.5f),+(size * 0.5f),+(size * 0.5f)},
			},
			{ // Down Face
					{-(size * 0.5f),-(size * 0.5f),+(size * 0.5f)},
					{+(size * 0.5f),-(size * 0.5f),+(size * 0.5f)},
					{+(size * 0.5f),-(size * 0.5f),-(size * 0.5f)},
			},
			{
					{-(size * 0.5f),-(size * 0.5f),+(size * 0.5f)},
					{+(size * 0.5f),-(size * 0.5f),-(size * 0.5f)},
					{-(size * 0.5f),-(size * 0.5f),-(size * 0.5f)},
			},
	};
	auto indexes = mesh.AddTriangles(tris);
	mesh.AddIndex(indexes,tris.size() * Triangle::VertexPerTriangle);
	delete indexes;

	VertexArray vertexArray;
	VertexBuffer vertexBuffer = mesh.GetVertexBuffer();
	VertexBufferLayout layout = Vertex::GetLayout();
	vertexArray.AddBuffer(vertexBuffer, layout);
	IndexBuffer indexBuffer = mesh.GetIndexBuffer();

	ShaderProgram shaderProgram("resources/shaders/shader.vert", "resources/shaders/shader.frag");
	shaderProgram.Bind();

	shaderProgram.SetUniform<float>("u_Color", 1.0,1.0,1.0,1.0);

	vertexArray.Unbind();
	shaderProgram.Unbind();
	vertexBuffer.Unbind();
	indexBuffer.Unbind();

	Renderer renderer;
	display.InitializeImGUI();

	// OpenGL Z go backward (from the screen to me)
	glm::vec3 modelPos = glm::vec3(0.5f,0.5f,-1.0f);

	/* Loop until the user closes the window */
	while (!display.ShouldClose()) {
		renderer.Clear();
		display.BeginFrame();

		// Projection Matrix to go from pixel to camera space.
		glm::mat4 proj = camera.GetProjectionMatrix();
		// View matrix to simulate camera position (i.e. moving camera 100 to the right means moving everything 100 to the left)
		glm::mat4 view = glm::translate(glm::mat4(1.0f), -camera.m_Position);
		// Model matrix that position (and later on rotate and scale) the object in the scene.
		glm::mat4 model = glm::translate(glm::mat4(1.0f), modelPos);
		// Order important, might change depending on the graphical API. In OpenGL it's reverse from the acronym.
		// Link to the memory layout. In OpenGL it's in column major instead of row layout.
		glm::mat4 mvp = proj * view * model;

		shaderProgram.Bind();
		shaderProgram.SetUniform("u_MVP", mvp);
		renderer.Draw(vertexArray, indexBuffer, shaderProgram);

		// Our ImGUI Window
		{
			ImGui::Begin("Rendering Parameters");

			ImGui::InputFloat3("Camera Translation", &camera.m_Position.x);
			ImGui::NewLine();

            ImGui::InputFloat3("Position Cube", &modelPos.x);
			ImGui::NewLine();

			ImGui::Text("Application average %.3f ms/frame (%.1f FPS)", 1000.0f / ImGui::GetIO().Framerate, ImGui::GetIO().Framerate);
			ImGui::End();
		}

		display.EndFrame();
	}

	return 0;
}
