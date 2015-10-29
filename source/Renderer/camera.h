#pragma once

#include <glm/vec3.hpp>
using namespace glm;

class Renderer;


class Camera {
public:
	Camera(Renderer* pRenderer);

	// Set/Get
	void SetPosition(const vec3 &position) { m_position = position; }
	void SetFacing(const vec3 &facing) { m_facing = facing; }
	void SetUp(const vec3 &up) { m_up = up; }
	void SetRight(const vec3 &right) { m_right = right; }
	const void SetZoomAmount(float amount) { m_zoomAmount = amount; }
	const vec3 GetPosition() const { return m_position; }
	const vec3 GetFacing()const { return vec3(m_facing.x, m_facing.y, m_facing.z); }
	const vec3 GetUp() const { return m_up; }
	const vec3 GetRight() const { return m_right; }
	const float GetZoomAmount() const { return m_zoomAmount; }

	// Camera movement
	void Fly(const float speed);
	void Move(const float speed);
	void Levitate(const float speed);
	void Strafe(const float speed);
	void Rotate(const float xAmount, const float yAmount, const float zAmount);
	void RotateAroundPoint(const float xAmount, const float yAmount, const float zAmount);
	void Zoom(const float amount);

	// Viewing
	void Look() const;

private:
	Renderer *m_pRenderer;

	vec3 m_position;

	vec3 m_up;
	vec3 m_facing;
	vec3 m_right;

	float m_zoomAmount;
	float m_minZoomAmount;
	float m_maxZoomAmount;
};
