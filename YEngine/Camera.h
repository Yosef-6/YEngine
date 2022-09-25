#pragma once
#include <GL/glew.h>
#include "Event.h"
#include "Keyboard.h"
#include "Observer.h"
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
namespace YEngine {

	static const GLfloat YAW = -90.0f;
	static const GLfloat PITCH = 0.0f;
	static const GLfloat SPEED = 0.5f;
	static const GLfloat SENSITIVTY = 3.0f;
	static const GLfloat ZOOM = 45.0f;

    enum CameraMovement {
        FORWARD,
        BACKWARD,
        LEFT,
        RIGHT
    };

	class Camera 
	{
	public:
		glm::vec3 m_position;
		glm::vec3 m_front;
		glm::vec3 m_up;
		glm::vec3 m_right;
		glm::vec3 m_worldUp;
		
		GLfloat m_yaw;
		GLfloat m_pitch;
		// Camera options
		GLfloat m_movementSpeed;
		GLfloat m_mouseSensitivity;
		GLfloat m_zoom;

		Camera(const glm::vec3& position = glm::vec3(0.0f, 0.0f, 3.0f), const glm::vec3& up = glm::vec3(0.0f, 1.0f, 0.0f), GLfloat yaw = YAW, GLfloat pitch = PITCH) :
			m_position(position), m_front(glm::vec3(0.0f, 0.0f, -1.0f)), m_worldUp(up), m_yaw(yaw), m_pitch(pitch), m_movementSpeed(SPEED),m_mouseSensitivity(SENSITIVTY),m_zoom(ZOOM) {

		updateCamera();
		}

        glm::mat4 GetViewMatrix()
        {
            return glm::lookAt(m_position, m_position + m_front, m_up);
        }

        void ProcessKeyboard(CameraMovement direction, GLfloat deltaTime)
        {
            GLfloat velocity = this->m_movementSpeed * deltaTime;
            if (direction == FORWARD)
                this->m_position += this->m_front * velocity;
            if (direction == BACKWARD)
                this->m_position -= this->m_front * velocity;
            if (direction == LEFT)
                this->m_position -= this->m_right * velocity;
            if (direction == RIGHT)
                this->m_position += this->m_right * velocity;
        }
        



        void ProcessMouseMovement(GLfloat xoffset, GLfloat yoffset, GLboolean constrainPitch = true)
        {
            xoffset *= m_mouseSensitivity;
            yoffset *= m_mouseSensitivity;

            m_yaw += xoffset;
            m_pitch += yoffset;

           
            if (constrainPitch)
            {
                if (m_pitch > 89.0f)
                    m_pitch = 89.0f;
                if (m_pitch < -89.0f)
                    m_pitch = -89.0f;
            }

            
            updateCamera();
        }

        void ProcessMouseScroll(GLfloat yoffset)
        {
            if (m_zoom >= 1.0f && m_zoom <= 45.0f)
                m_zoom -= yoffset;
            if (m_zoom <= 1.0f)
                m_zoom = 1.0f;
            if (m_zoom >= 45.0f)
                m_zoom = 45.0f;
        }
#if 0
        void handle(const Event& e, GLfloat delta) override {


            if (e.getType() == "Keyboard") {
                ProcessKeyboard(e.getKeyData(), delta);
            }

        }
#endif // 0


	private:
		void updateCamera() {

			glm::vec3 front;
			front.x = cos(glm::radians(m_yaw)) * cos(glm::radians(m_pitch));
			front.y = sin(glm::radians(m_pitch));
			front.z = sin(glm::radians(m_yaw)) * cos(glm::radians(m_pitch));
			m_front = glm::normalize(front);
			m_right = glm::normalize(glm::cross(m_front,m_worldUp));
			m_up    = glm::normalize(glm::cross(m_right,m_front));


		};

	};

}
