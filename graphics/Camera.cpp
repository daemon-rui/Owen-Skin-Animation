#pragma warning (disable:26495)
#include "Camera.h"
#include "..\math\Matrix4X4.h"
#include <math.h>
#include <memory>

namespace owen
{
namespace graph
{
Camera::Camera()
	:mCameraPosition(math::Vector3(0.0f, 0.0f, 0.0f))
	, mCameraUp(math::Vector3(0.0f, 1.0f, 0.0f))
	, mCameraDirection(math::Vector3(0.0f, 0.0f, -1.0f))
{
	mWorldUp = mCameraUp;
	updateCamera();
}

Camera::Camera(const Camera& other)
{
	*this = other;
}

Camera& Camera::operator=(const Camera& other)
{
	if (this != &other)
	{
		//POD type, memory copy is OK.
		memcpy(this, &other, sizeof(Camera));
	}
	return *this;
}

//Attention, the value should be radian
void Camera::SetYaw(float value)
{
	if (value > 2 * PI)
	{
		value = value - 2 * PI;
	}
	else if (value < 0)
	{
		value = value + 2 * PI;
	}
	mYaw = value;
	updateCamera();
}

//Attention, the value should be radian
void Camera::SetPitch(float value)
{
	if (value > 2 * PI)
	{
		value = value - 2 * PI;
	}
	else if (value < 0)
	{
		value = value + 2 * PI;
	}
	mPitch = value;
	updateCamera();
}

math::Matrix4X4 Camera::GetViewMatrix() const
{
	math::Vector3 target = mCameraPosition + mCameraDirection;
	return math::Matrix4X4::LookAt(mCameraPosition, target, mCameraUp);
}

void Camera::updateCamera()
{
	math::Vector3 front;
	front.x = cosf(mYaw) * cosf(mPitch);
	front.y = sinf(mPitch);
	front.z = sinf(mYaw) * cosf(mPitch);
	mCameraDirection = math::Vector3::Normalize(front);
	mCameraRight = math::Vector3::Normalize(math::Vector3::Cross(mCameraDirection, mWorldUp));
	mCameraUp = math::Vector3::Normalize(math::Vector3::Cross(mCameraRight, mCameraDirection));
}
}
}
