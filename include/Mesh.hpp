//
// Created by Iannis on 04/03/2023.
//

#pragma once

#include <memory>
#include <vector>
#include "glm/glm.hpp"

#include "Triangle.hpp"
#include "IndexBuffer.hpp"
#include "VertexBuffer.hpp"
#include "VertexBufferLayout.hpp"

namespace Sayama::OpenGLLearning {

	class Mesh {
	private:
		std::vector<struct Vertex> m_Vertices;
		std::vector<unsigned int> m_Indexes;
	public:
		Mesh();
		Mesh(int verticesCount, int indexesCount);
		Mesh(const std::vector<struct Vertex>& vertices, const std::vector<unsigned int>& indexes);

		int* AddTriangle(const struct Triangle& tri);
        int* AddTriangles(const std::vector<struct Triangle>& tris);

		void AddIndex(int index);
		void AddIndex(std::vector<int> index);
		void AddIndex(int* index, int count);

		IndexBuffer GetIndexBuffer() const;
		VertexBuffer GetVertexBuffer() const;

	private:
		int FindVertex(const struct Vertex& vertex) const;

		/// Trying to find a said index.
		/// \param vertex The vertex we are searching for.
		/// \param index The index found.
		/// \return Return whether we found it.
		bool TryFindVertex(const struct Vertex& vertex, int* index = nullptr) const;

		/// Function that push back a vertex into the vector and return its index.
		/// \param vertex The vertex we want to add onto the vector.
		/// \return The index of the pushed back vertex.
		int PushBackVertex(const struct Vertex& vertex);
	};
} // OpenGLLearning
