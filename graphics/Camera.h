#pragma once
#include "..\math\Vector3.h"

namespace owen
{
namespace math
{
class Matrix4X4;
class Vector3;
}
namespace graph
{
constexpr static float YAW = -90.0f;
constexpr static float PITCH = 0.0f;
constexpr static float SPEED = 2.5f;
constexpr static float SENSITIVITY = 0.1f;
constexpr static float ZOOM = 45.0f;
constexpr static float PI = 3.1415926;

class Camera
{
public:
	Camera();
	Camera(const Camera& other);
	Camera& operator=(const Camera& other);
	Camera(Camera&&) = delete;
	Camera& operator=(Camera&&) = delete;
	virtual ~Camera() = default;

	void SetYaw(float value);
	void SetPitch(float value);

	inline void SetPosition(const math::Vector3& pos) { mCameraPosition = pos; };
	inline const math::Vector3& GetPostion() const { return mCameraPosition; };

	inline void SetUp(const math::Vector3& up) { mCameraUp = up; };
	inline const math::Vector3& GetUp() const { return mCameraUp; }

	inline void SetDirection(const math::Vector3& direction) { mCameraDirection = direction; };
	inline const math::Vector3& GetDirection() const { return mCameraDirection; };

	inline float GetYaw() const { return mYaw; }
	inline float GetPitch()const { return mPitch; };
	math::Matrix4X4 GetViewMatrix() const;

private:
	void updateCamera();
	math::Vector3 mCameraPosition;
	math::Vector3 mCameraDirection;
	math::Vector3 mCameraUp;
	math::Vector3 mCameraRight;
	math::Vector3 mWorldUp;

	//Euler angles
	float mYaw{ YAW };
	float mPitch{ PITCH };
	float mRoll;

	//Cameras
	float mMoveSpeed{ SPEED };
	float mMouseSensity{ SENSITIVITY };
	float mZoom{ ZOOM };

};
}
}


