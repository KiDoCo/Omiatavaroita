#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <Headers/ShaderClass.h>
#include <Headers/stb_image.h>
#include <iostream>
#include <time.h>
#include <filesystem>
#include "Headers/Camera.h"

CameraClass *camera = new CameraClass(glm::vec3(0.0f, 0.0f, 3.0f));
extern "C";

#pragma region Prototypes

void FramebufferSizeCallback(GLFWwindow *window, int width, int height);
void processInput(GLFWwindow *window);
void scroll_callback(GLFWwindow *window, double xoffset, double yoffset);
void mouse_callback(GLFWwindow *window, double xpos, double ypos);
int SuccessCheck(unsigned char *data, int width, int height, bool png);
void BindTextures(unsigned int &texture, char const *path, bool png, int *success);
int BoxRender(GLFWwindow *window);
int LightRender(GLFWwindow *window);

#pragma endregion

int success;
float deltaTime = 0.0f, lastFrame = 0.0f;
const int ScreenWidth = 800, ScreenHeight = 600;

float lastX = ScreenWidth / 2, lastY = ScreenHeight / 2;
bool firstmouse = true;
glm::vec3 lightPos(2.2f, 1.0f, 2.0f);

char infoLog[512];


int main(int argc, TCHAR argv[])
{
	glfwInit();
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);


	GLFWwindow *window = glfwCreateWindow(ScreenWidth, ScreenHeight, "Learnibduoterb", NULL, NULL);


	if (window == NULL)
	{
		std::cout << "Failed to create GLFW window" << std::endl;
		glfwTerminate();
		return -1;
	}

	glfwMakeContextCurrent(window);
	glfwSetFramebufferSizeCallback(window, FramebufferSizeCallback);
	glfwSetCursorPosCallback(window, mouse_callback);
	glfwSetScrollCallback(window, scroll_callback);


	glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);
	if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
	{
		std::cout << "Failed to init glad" << std::endl;
		return -1;
	}
	glEnable(GL_DEPTH_TEST);
	//glEnableClientState(GL_VERTEX_ARRAY);
	//glEnableClientState(GL_NORMAL_ARRAY);
	//glEnableClientState(GL_COLOR_ARRAY);
	//glEnableClientState(GL_TEXTURE_COORD_ARRAY);
	BoxRender(window);
	//LightRender(window);
	glfwTerminate();
	return 0;


	//assign values as subdatas
//	glBufferSubData(GL_ARRAY_BUFFER, 0, sizeof(vertices), vertices);
	//glBufferSubData(GL_ARRAY_BUFFER, sizeof(vertices), sizeof(vertices2), vertices2);
}

void FramebufferSizeCallback(GLFWwindow *window, int width, int height)
{
	glViewport(0, 0, width, height);
}

void processInput(GLFWwindow *window)
{
	if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
		glfwSetWindowShouldClose(window, true);
	if (glfwGetKey(window, GLFW_KEY_W) == GLFW_PRESS)
		camera->ProcessKey(FORWARD, deltaTime);
	if (glfwGetKey(window, GLFW_KEY_S) == GLFW_PRESS)
		camera->ProcessKey(BACKWARD, deltaTime);
	if (glfwGetKey(window, GLFW_KEY_A) == GLFW_PRESS)
		camera->ProcessKey(LEFT, deltaTime);
	if (glfwGetKey(window, GLFW_KEY_D) == GLFW_PRESS)
		camera->ProcessKey(RIGHT, deltaTime);
}

void BindTextures(unsigned int &texture, char const *path, bool png, int *success)
{
	glGenTextures(1, &texture);
	glBindTexture(GL_TEXTURE_2D, texture);
	//texture wrapping params
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
	//texture filtering params
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

	int width, height, nrChannels;
	unsigned char *data = stbi_load(path, &width, &height, &nrChannels, 0);
	
	*success = SuccessCheck(data, width, height, png);
	stbi_image_free(data);
}

int SuccessCheck(unsigned char *data, int width, int height, bool png)
{
	if (data)
	{
		if (!png)
			glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, data);
		else
			glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_RGBA, GL_UNSIGNED_BYTE, data);

		glGenerateMipmap(GL_TEXTURE_2D);
		return -1;
	}

	else
	{
		std::cout << "spurgumaa on paras paikka" << std::endl;
		return 0;
	}
}

void mouse_callback(GLFWwindow *window, double xpos, double ypos)
{
	if (firstmouse)
	{
		lastX = xpos;
		lastY = ypos;
		firstmouse = false;
	}

	float xoffset = xpos - lastX;
	float yoffset = lastY - ypos;

	lastX = xpos;
	lastY = ypos;

	camera->ProcessMouse(xoffset, yoffset);
}

void scroll_callback(GLFWwindow *window, double xoffset, double yoffset)
{
	camera->ProcessMouseScroll(yoffset);
}

GLfloat* DrawCircle(GLfloat x, GLfloat y, GLfloat z, GLfloat r, GLint num_segments)
{
	int numberOfVertices = num_segments + 2;

	GLfloat doublePi = 2.0f * glm::pi<GLfloat>();
	GLfloat* circleVerticesX = new GLfloat[numberOfVertices];
	GLfloat* circleVerticesY = new GLfloat[numberOfVertices];
	GLfloat* circleVerticesZ = new GLfloat[numberOfVertices];
	circleVerticesX[0] = x;
	circleVerticesY[0] = y;
	circleVerticesZ[0] = z;
	for (int i = 1; i < numberOfVertices; i++)
	{
		circleVerticesX[i] = x + (r * cos(i * doublePi / num_segments));
		circleVerticesY[i] = y + (r * sin(i * doublePi / num_segments));
		circleVerticesZ[i] = z;

	}

	GLfloat* allcircleVertices = new GLfloat[numberOfVertices * 3];

	for (int i = 0; i < numberOfVertices; i++)
	{
		allcircleVertices[i * 3] = circleVerticesX[i];
		allcircleVertices[(i * 3) + 1] = circleVerticesY[i];
		allcircleVertices[(i * 3) + 2] = circleVerticesZ[i];

	}
	return allcircleVertices;
}


int BoxRender(GLFWwindow *window)
{
	
	Shader subShader("Shaders/Translation.vs", "Shaders/ImageLoad.fs");
	//Shader circShader("Shaders/vertexshader.vs", "Shaders/fragmentshader.fs");
	GLfloat vertices[] =
	{
		//positions			//Texture coords
	-0.5f, -0.5f, -0.5f,  0.0f, 0.0f,
	 0.5f, -0.5f, -0.5f,  1.0f, 0.0f,
	 0.5f,  0.5f, -0.5f,  1.0f, 1.0f,
	 0.5f,  0.5f, -0.5f,  1.0f, 1.0f,
	-0.5f,  0.5f, -0.5f,  0.0f, 1.0f,
	-0.5f, -0.5f, -0.5f,  0.0f, 0.0f,

	-0.5f, -0.5f,  0.5f,  0.0f, 0.0f,
	 0.5f, -0.5f,  0.5f,  1.0f, 0.0f,
	 0.5f,  0.5f,  0.5f,  1.0f, 1.0f,
	 0.5f,  0.5f,  0.5f,  1.0f, 1.0f,
	-0.5f,  0.5f,  0.5f,  0.0f, 1.0f,
	-0.5f, -0.5f,  0.5f,  0.0f, 0.0f,

	-0.5f,  0.5f,  0.5f,  1.0f, 0.0f,
	-0.5f,  0.5f, -0.5f,  1.0f, 1.0f,
	-0.5f, -0.5f, -0.5f,  0.0f, 1.0f,
	-0.5f, -0.5f, -0.5f,  0.0f, 1.0f,
	-0.5f, -0.5f,  0.5f,  0.0f, 0.0f,
	-0.5f,  0.5f,  0.5f,  1.0f, 0.0f,

	 0.5f,  0.5f,  0.5f,  1.0f, 0.0f,
	 0.5f,  0.5f, -0.5f,  1.0f, 1.0f,
	 0.5f, -0.5f, -0.5f,  0.0f, 1.0f,
	 0.5f, -0.5f, -0.5f,  0.0f, 1.0f,
	 0.5f, -0.5f,  0.5f,  0.0f, 0.0f,
	 0.5f,  0.5f,  0.5f,  1.0f, 0.0f,

	-0.5f, -0.5f, -0.5f,  0.0f, 1.0f,
	 0.5f, -0.5f, -0.5f,  1.0f, 1.0f,
	 0.5f, -0.5f,  0.5f,  1.0f, 0.0f,
	 0.5f, -0.5f,  0.5f,  1.0f, 0.0f,
	-0.5f, -0.5f,  0.5f,  0.0f, 0.0f,
	-0.5f, -0.5f, -0.5f,  0.0f, 1.0f,

	-0.5f,  0.5f, -0.5f,  0.0f, 1.0f,
	 0.5f,  0.5f, -0.5f,  1.0f, 1.0f,
	 0.5f,  0.5f,  0.5f,  1.0f, 0.0f,
	 0.5f,  0.5f,  0.5f,  1.0f, 0.0f,
	-0.5f,  0.5f,  0.5f,  0.0f, 0.0f,
	-0.5f,  0.5f, -0.5f,  0.0f, 1.0f
	};

	glm::vec3 cubePositions[] =
	{
	  glm::vec3(0.0f,  0.0f,  0.0f),
	  glm::vec3(1.0f,  0.0f, 0.0f),
	  glm::vec3(2.0f, 0.0f, 0.0f),
	  glm::vec3(3.0f, 0.0f, 0.0f),
	  glm::vec3(4.0f, 0.0f, 0.0f),
	  glm::vec3(5.0f,  0.0f, 0.0f),
	  glm::vec3(6.0f, 0.0f, 0.0f),
	  glm::vec3(7.0f, 0.0f, 0.0f),
	  glm::vec3(8.0f,  0.0f, 0.0f),
	  glm::vec3(9.0f,  0.0f, 0.0f)
	};

	unsigned int VBO, VBO2, CubeVAO, CircleVAO;

	//vertex buffer generation
	glGenVertexArrays(1, &CubeVAO);
	glBindVertexArray(CubeVAO);
	//glGenVertexArrays(1, &CircleVAO);
	//glBindVertexArray(CircleVAO);

	glGenBuffers(1, &VBO);
	glBindBuffer(GL_ARRAY_BUFFER, VBO);
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

	//glGenBuffers(1, &VBO2);
	//glBindBuffer(GL_ARRAY_BUFFER, VBO2);
	//glBufferData(GL_ARRAY_BUFFER, sizeof(DrawCircle(2.0f, 2.0f, 2.0f, 2.0f, 2)), 0, GL_STATIC_DRAW);

	//set the texture wrapping/filtering
	unsigned int texture1, texture2;

	BindTextures(texture1, "Resources/test.jpg", false, &success);
	if (!success) return -1;
	stbi_set_flip_vertically_on_load(true);
	BindTextures(texture2, "Resources/Aku.png", true, &success);
	if (!success) return -1;

	subShader.Use();
	subShader.SetInt("texture1", 0);
	subShader.SetInt("texture2", 1);


	while (!glfwWindowShouldClose(window))
	{
		
		float currentFrame = glfwGetTime();
		deltaTime = currentFrame - lastFrame;
		lastFrame = currentFrame;
		subShader.SetFloat("Time", glfwGetTime());
		//input
		processInput(window);

		//rendering
		glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

		glm::mat4 model = glm::mat4(1.0);
		glm::mat4 projection;
		projection = glm::perspective(glm::radians(camera->Fov), (float)ScreenWidth / (float)ScreenHeight, 0.1f, 100.0f);
		//projection = glm::ortho(0.0f, 2.0f, 0.0f, 2.0f,-2.0f,1.0f);
		glm::mat4 view;
		view = camera->ViewMatrix();


		glBindVertexArray(CubeVAO);
		//binding
		glActiveTexture(GL_TEXTURE0);
		glTexParameteri(texture1, GL_TEXTURE_WRAP_S, GL_REPEAT);
		glBindTexture(GL_TEXTURE_2D, texture1);
		glActiveTexture(GL_TEXTURE1);
		glTexParameteri(texture2, GL_TEXTURE_WRAP_S, GL_REPEAT);
		glBindTexture(GL_TEXTURE_2D, texture2);

		//cube vertex attribute array
		glEnableVertexAttribArray(0);
		glEnableVertexAttribArray(1);
		//binding vertex coords
		glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 5 * sizeof(float), (void*)0);
		//binding texture coords
		glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 5 * sizeof(float), (void*)(3 * sizeof(float)));
		glBindBuffer(GL_ARRAY_BUFFER, VBO);
		//Cube shader attributes
		subShader.Use();

		subShader.SetMat4("projection", projection);

		subShader.SetMat4("view", view);

		//Cube render
		for (unsigned int i = 0; i < 10; i++)
		{
			model = glm::mat4(1.0);
			model = glm::translate(model, cubePositions[i]);
			float angle = 20.0f * i;
			//model = glm::rotate(model, (float)glfwGetTime() * glm::radians(angle), glm::vec3(0.0f, 2.0f, 0.0f));
			subShader.SetMat4("model", model);
			glDrawArrays(GL_TRIANGLES, 0, 36);
		}

		/*		glBindVertexArray(CircleVAO);
				circShader.Use();
				glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(GLfloat), (void*)0)*/;
//		glBindBuffer(GL_ARRAY_BUFFER, VBO2);
	//	glDrawArrays(GL_TRIANGLES, 0, (GLint)DrawCircle(2.0f, 2.0f, 2.0f, 2.0f, 2));
		//check and call events and swap the buffers
		glfwSwapBuffers(window);
		glfwPollEvents();
	}
	glDeleteVertexArrays(1, &CubeVAO);
	glDeleteVertexArrays(1, &CircleVAO);
	glDeleteBuffers(1, &VBO);
	glDeleteBuffers(1, &VBO2);

	return 0;
}

int LightRender(GLFWwindow *window)
{
	Shader lightShader("Shaders/LightShader.vs", "Shaders/LightShader.fs");
	Shader lampShader("Shaders/Lamp.vs", "Shaders/Lamp.fs");
	float vertices[] =
	{
		//positions			//Texture coords
	-0.5f, -0.5f, -0.5f,
	 0.5f, -0.5f, -0.5f,
	 0.5f,  0.5f, -0.5f,
	 0.5f,  0.5f, -0.5f,
	-0.5f,  0.5f, -0.5f,
	-0.5f, -0.5f, -0.5f,

	-0.5f, -0.5f,  0.5f,
	 0.5f, -0.5f,  0.5f,
	 0.5f,  0.5f,  0.5f,
	 0.5f,  0.5f,  0.5f,
	-0.5f,  0.5f,  0.5f,
	-0.5f, -0.5f,  0.5f,

	-0.5f,  0.5f,  0.5f,
	-0.5f,  0.5f, -0.5f,
	-0.5f, -0.5f, -0.5f,
	-0.5f, -0.5f, -0.5f,
	-0.5f, -0.5f,  0.5f,
	-0.5f,  0.5f,  0.5f,

	 0.5f,  0.5f,  0.5f,
	 0.5f,  0.5f, -0.5f,
	 0.5f, -0.5f, -0.5f,
	 0.5f, -0.5f, -0.5f,
	 0.5f, -0.5f,  0.5f,
	 0.5f,  0.5f,  0.5f,

	-0.5f, -0.5f, -0.5f,
	 0.5f, -0.5f, -0.5f,
	 0.5f, -0.5f,  0.5f,
	 0.5f, -0.5f,  0.5f,
	-0.5f, -0.5f,  0.5f,
	-0.5f, -0.5f, -0.5f,

	-0.5f,  0.5f, -0.5f,
	 0.5f,  0.5f, -0.5f,
	 0.5f,  0.5f,  0.5f,
	 0.5f,  0.5f,  0.5f,
	-0.5f,  0.5f,  0.5f,
	-0.5f,  0.5f, -0.5f
	};

	unsigned int VBO, CubeVAO;

	glGenVertexArrays(1, &CubeVAO);
	//vertex buffer generation
	glGenBuffers(1, &VBO);
	glBindBuffer(GL_ARRAY_BUFFER, VBO);
	//give the allocation to bufferdata
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

	//bind light vertex array w/ cube array size offset
	glBindVertexArray(CubeVAO);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);
	glEnableVertexAttribArray(0);

	unsigned int lightVAO;
	glGenVertexArrays(1, &lightVAO);
	glBindVertexArray(lightVAO);
	glBindBuffer(GL_ARRAY_BUFFER, VBO);


	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);
	glEnableVertexAttribArray(0);

	while (!glfwWindowShouldClose(window))
	{
		float currentFrame = glfwGetTime();
		deltaTime = currentFrame - lastFrame;
		lastFrame = currentFrame;

		//input
		processInput(window);

		//rendering
		glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

		lightShader.Use();
		lightShader.SetVec3("objectColor", glm::vec3(1.0f, 0.5f, 0.31f));
		lightShader.SetVec3("lightColor", glm::vec3(1.0f, 1.0f, 1.0f));


		glm::mat4 projection;
		projection = glm::perspective(glm::radians(camera->Fov), (float)ScreenWidth / (float)ScreenHeight, 0.1f, 100.0f);
		glm::mat4 view;
		view = camera->ViewMatrix();
		lightShader.SetMat4("projection", projection);
		lightShader.SetMat4("view", view);

		glm::mat4 model = glm::mat4(1.0);
		lightShader.SetMat4("model", model);


		glBindVertexArray(CubeVAO);
		glDrawArrays(GL_TRIANGLES, 0, 36);

		//Light shader attributes
		lampShader.Use();
		lampShader.SetMat4("projection", projection);
		lampShader.SetMat4("view", view);
		model = glm::mat4(1.0);
		model = glm::translate(model, lightPos);
		model = glm::scale(model, glm::vec3(0.2f));
		lampShader.SetMat4("model", model);

		glBindVertexArray(lightVAO);
		glDrawArrays(GL_TRIANGLES, 0, 36);

		//light render

		//check and call events and swap the buffers
		glfwSwapBuffers(window);
		glfwPollEvents();
	}

	glDeleteVertexArrays(1, &lightVAO);
	glDeleteBuffers(1, &VBO);
	return 0;
}