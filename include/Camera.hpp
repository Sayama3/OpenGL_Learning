//
// Created by Sayama on 20/03/2023.
//

#pragma once
#include "glm/glm.hpp"
#include "glm/gtc/quaternion.hpp"
#include "glm/gtc/matrix_transform.hpp"
#include "Display.hpp"

namespace Sayama::OpenGLLearning {

    class Camera {
    private:
        const Display& m_Display;
        /**
         * The field of view in degrees.
         */
        float m_Fov;
	public:
        float m_ZNear;
        float m_ZFar;
	    glm::vec3 m_Position;
	    glm::quat m_Rotation;

        Camera(const Display& display);

        // Basic Get/Set of the fov
        inline void SetFOV(float value, bool isDegree = true) { m_Fov = isDegree ? value : glm::degrees(value); }
        inline float GetFOV(bool isDegree = true) const { return isDegree ? GetDegreeFOV() : GetRadiansFOV(); }
        inline float GetDegreeFOV() const { return m_Fov; }
        inline float GetRadiansFOV() const { return glm::radians(m_Fov); }

        float GetNormalizedZ() const;
        float GetFOVScalingFactor() const;
		glm::mat4x4 GetProjectionMatrix() const;
    };

} // OpenGLLearning
