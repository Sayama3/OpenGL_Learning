//
// Created by Sayama on 20/03/2023.
//

#include "Camera.hpp"

namespace Sayama::OpenGLLearning {
	Camera::Camera(const Display &display) : m_Display(display), m_Fov(90.0f), m_ZNear(0.0f), m_ZFar(1000.0f), m_Position(0,0,0), m_Rotation()
	{

	}

	float OpenGLLearning::Camera::GetNormalizedZ() const {
		return m_ZFar / (m_ZFar - m_ZNear);
	}

	float OpenGLLearning::Camera::GetFOVScalingFactor() const {
		return (1.0f / glm::tan(GetRadiansFOV() / 2.0f));
	}

	glm::mat4x4 Camera::GetProjectionMatrix() const {

		return glm::perspective(GetRadiansFOV(),m_Display.GetAspectRatio(),m_ZNear, m_ZFar);
//		float a = m_Display.GetAspectRatio();
//		float f = GetFOVScalingFactor();
//		float zNear = GetZNear();
//		float q = GetNormalizedZ();
//		glm::mat4x4 projectionMatrix {
//				{
//						a*f, 0, 0, 0,
//				},
//				{
//						0, f, 0, 0,
//				},
//				{
//						0, 0, q, -zNear*q,
//				},
//				{
//						0,0,1,0
//				}
//		};
//		return projectionMatrix;
	}
} // OpenGLLearning