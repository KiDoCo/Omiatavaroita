#ifndef CAMERA_HEADER
#define CAMERA_HEADER

#include <glm/fwd.hpp>

enum Camera_Movement {
	FORWARD,
	BACKWARD,
	LEFT,
	RIGHT
};

const float YAW = -90.0f;
const float PITCH = 0.0f;
const float SPEED = 2.5f;
const float SENSITIVITY = 0.1f;
const float FOV = 45.0f;

class  CameraClass
{
public:

	glm::vec3 Position;
	glm::vec3 Front;
	glm::vec3 Up;
	glm::vec3 Right;
	glm::vec3 WorldUp;

	float cameraSpeed = 2.5f;
	float sensitivity = 0.05f;
	float Yaw, Pitch, Fov;

	CameraClass(float posX, float posY, float posZ, float upX, float upY, float upZ, float yaw, float pitch) : Front(glm::vec3(0.0f, 0.0f, -1.0f)), cameraSpeed(SPEED), sensitivity(SENSITIVITY), Fov(FOV)
	{
		Position = glm::vec3(posX, posY, posZ);
		WorldUp = glm::vec3(upX, upY, upZ);
		Yaw = yaw;
		Pitch = pitch;
		UpdateCameraVectors();
	};
	CameraClass(glm::vec3 position = glm::vec3(0.0f, 0.0f, 0.0f), glm::vec3 up = glm::vec3(0.0f, 1.0f, 0.0f), float yaw = YAW, float pitch = PITCH) 
		: Front(glm::vec3(0.0f, 0.0f, -1.0f)),cameraSpeed(SPEED), sensitivity(SENSITIVITY), Fov(FOV) 
	{
		Position = position;
		WorldUp = up;
		Yaw = yaw;
		Pitch = pitch;
		UpdateCameraVectors();
	};

	~CameraClass();
	void ProcessMouse(double xpos, double ypos,GLboolean constraint = true);
	void ProcessKey(Camera_Movement a, float delta);
	void ProcessMouseScroll(float yoffset);
	glm::mat4 ViewMatrix();

	

private:
	void UpdateCameraVectors();

};


#endif // !CAMERA_HEADER

