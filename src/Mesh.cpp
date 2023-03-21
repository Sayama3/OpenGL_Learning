//
// Created by Iannis on 04/03/2023.
//

#include "Mesh.hpp"
#include <algorithm>

namespace Sayama::OpenGLLearning {

	// Mesh
	Mesh::Mesh() : m_Vertices(), m_Indexes() {

	}

	Mesh::Mesh(int verticesCount, int indexesCount) : m_Vertices(), m_Indexes() {
		m_Vertices.reserve(verticesCount);
		m_Indexes.reserve(indexesCount);
	}

	Mesh::Mesh(const std::vector<struct Vertex> &vertices, const std::vector<unsigned int> &indexes) : m_Vertices(vertices), m_Indexes(indexes) {
	}

	int* Mesh::AddTriangle(const Triangle &tri) {
		int* indexes = new int[Triangle::VertexPerTriangle];

		for (int i = 0; i < Triangle::VertexPerTriangle; ++i) {
			int index;
			indexes[i] = TryFindVertex(tri.vertices[i], &index) ? index : PushBackVertex(tri.vertices[i]);
		}

		return indexes;
	}
	int* Mesh::AddTriangles(const std::vector<struct Triangle>& tris) {
		int* indexes = new int[Triangle::VertexPerTriangle * tris.size()];
		for (int i = 0; i < tris.size(); ++i) {
			auto index = i * Triangle::VertexPerTriangle;
			auto t = AddTriangle(tris[i]);
			for (int j = 0; j < Triangle::VertexPerTriangle; ++j) {
				indexes[index + j] = t[j];
			}
			delete t;
		}
		return indexes;
	}

	int Mesh::FindVertex(const Vertex &vertex) const {
		int index = -1;
		auto it = std::find(m_Vertices.begin(), m_Vertices.end(), vertex);

		// If element was found
		if (it != m_Vertices.end())
		{
			// calculating the index
			index = it - m_Vertices.begin();
		}

		return index;
	}

	bool Mesh::TryFindVertex(const Vertex &vertex, int* index) const {
		if(index != nullptr) {
			*index = FindVertex(vertex);
			return *index >= 0;
		} else {
			return FindVertex(vertex) >= 0;
		}
	}

	int Mesh::PushBackVertex(const Vertex &vertex) {
		m_Vertices.push_back(vertex);
		return m_Vertices.size() - 1;
	}

	void Mesh::AddIndex(int index) {
		this->m_Indexes.push_back(index);
	}

	void Mesh::AddIndex(std::vector<int> index) {
		this->m_Indexes.insert(std::end(m_Indexes), std::begin(index), std::end(index));
	}

	void Mesh::AddIndex(int *index, int count) {
		this->m_Indexes.insert(std::end(m_Indexes), index, index + count);
	}

	IndexBuffer Mesh::GetIndexBuffer() const {
		return {
				this->m_Indexes.data(),
				static_cast<unsigned int>(this->m_Indexes.size())
		};
	}

	VertexBuffer Mesh::GetVertexBuffer() const {
		return {
				this->m_Vertices.data(),
				static_cast<unsigned int>(this->m_Vertices.size() * Vertex::GetLayout().GetStride())
		};
	}


} // OpenGLLearning