#include <cmath>
#include <glm/glm.hpp>
#include <glm/gtc/quaternion.hpp>

#include "Renderer.h"

#include "camera.h"


// Angle conversions
inline float DegToRad(const float degrees)
{
	return (degrees * PI) / 180;
}

inline float RadToDeg(const float radians)
{
	return (radians * 180) / PI;
}


// Constructor
Camera::Camera(Renderer* pRenderer)
{
	m_pRenderer = pRenderer;

	SetPosition(vec3(0.0f, 0.0f, 0.0f));
	SetFacing(vec3(0.0f, 0.0f, -1.0f));
	SetUp(vec3(0.0f, 1.0f, 0.0f));
	SetRight(vec3(1.0f, 0.0f, 0.0f));

	m_zoomAmount = 3.0f;
	m_minZoomAmount = 0.1f;
	m_maxZoomAmount = 100.0f;
}

// Camera movement
void Camera::Fly(const float speed)
{
	m_position.x = m_position.x + m_facing.x * speed;
	m_position.y = m_position.y + m_facing.y * speed;
	m_position.z = m_position.z + m_facing.z * speed;
}

void Camera::Move(const float speed)
{
	vec3 directionToMove = m_facing;
	directionToMove.y = 0.0f;
	directionToMove = glm::normalize(directionToMove);

	m_position.x = m_position.x + directionToMove.x * speed;
	m_position.z = m_position.z + directionToMove.z * speed;
}

void Camera::Levitate(const float speed)
{
	m_position.y = m_position.y + 1.0f * speed;
}

void Camera::Strafe(const float speed)
{
	m_position.x = m_position.x + m_right.x * speed;
	m_position.y = m_position.y + m_right.y * speed;
	m_position.z = m_position.z + m_right.z * speed;
}

void Camera::Rotate(const float xAmount, const float yAmount, const float zAmount)
{
	quat xRotation(DegToRad(xAmount), m_right.x, m_right.y, m_right.z);
	quat yRotation(DegToRad(yAmount), m_up.x, m_up.y, m_up.z);
	quat zRotation(DegToRad(zAmount), m_facing.x, m_facing.y, m_facing.z);

	quat rotation = xRotation * yRotation * zRotation;

	m_right = normalize(rotation * m_right);
	m_up = normalize(rotation * m_up);
	m_facing = normalize(rotation * m_facing);
}

void Camera::RotateAroundPoint(const float xAmount, const float yAmount, const float zAmount)
{
	quat xRotation(DegToRad(xAmount), m_right.x, m_right.y, m_right.z);
	quat yRotation(DegToRad(yAmount), m_up.x, m_up.y, m_up.z);
	quat zRotation(DegToRad(zAmount), m_facing.x, m_facing.y, m_facing.z);

	quat rotation = xRotation * yRotation * zRotation;

	// Get the view position, based on the facing and the zoom amount
	vec3 view = m_position + (m_facing*m_zoomAmount);

	m_position -= view;  // Translate the position to the origin, relative to the view position (that is the facing zoomed)
	m_position = (rotation * m_position);
	m_position += view;  // Translate back to relative view position

	m_right = normalize(rotation * m_right);
	m_facing = normalize(rotation * m_facing);
	m_up = normalize(rotation * m_up);
}

void Camera::Zoom(const float amount)
{
	m_zoomAmount += amount;
	if (m_zoomAmount <= m_minZoomAmount)
	{
		m_zoomAmount = m_minZoomAmount;
	}
	else if (m_zoomAmount >= m_maxZoomAmount)
	{
		m_zoomAmount = m_maxZoomAmount;
	}
	else
	{
		m_position.x = m_position.x - m_facing.x * amount;
		m_position.y = m_position.y - m_facing.y * amount;
		m_position.z = m_position.z - m_facing.z * amount;
	}
}

// Viewing
void Camera::Look() const
{
	vec3 view = m_position + m_facing;
	gluLookAt(m_position.x, m_position.y, m_position.z, view.x, view.y, view.z, m_up.x, m_up.y, m_up.z);
	m_pRenderer->GetFrustum(m_pRenderer->GetActiveViewPort())->SetCamera(m_position, view, m_up);
}