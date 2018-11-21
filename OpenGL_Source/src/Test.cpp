#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <Headers/ShaderClass.h>
#include <Headers/stb_image.h>
#include <iostream>
#include <experimental/filesystem>


void FramebufferSizeCallback(GLFWwindow *window, int width, int height);
void processInput(GLFWwindow *window);
int SuccessCheck(unsigned char *data, int width, int height, bool png);
void BindTextures(unsigned int &texture, char const *path, bool png, int *success);
int success;
char infoLog[512];

int main(int argc, TCHAR argv[])
{
	glfwInit();
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

	GLFWwindow *window = glfwCreateWindow(800, 600, "Learnibduoterb", NULL, NULL);

	if (window == NULL)
	{
		std::cout << "Failed to create GLFW window" << std::endl;
		glfwTerminate();
		return -1;
	}
	glfwMakeContextCurrent(window);
	glfwSetFramebufferSizeCallback(window, FramebufferSizeCallback);

	if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
	{
		std::cout << "Failed to init glad" << std::endl;
		return -1;
	}


	//Shader subShader("C:/Users/JoonasTuo/Desktop/asdf/x64/Debug/Shaders/vertexshader.vs", "C:/Users/JoonasTuo/Desktop/asdf/x64/Debug/Shaders/fragmentshader.fs");
	Shader subShader("Shaders/ImageLoad.vs", "Shaders/ImageLoad.fs");

	float vertices[] = {
		//positions			 //Colors			//Texture coords
		0.8f, 0.8f,0.0f,	 1.0f, 0.0f, 0.0f,	1.f,1.f,
		0.8f,-0.8f,0.0f,	 0.0f, 1.0f, 0.0f,	1.0f, 0.0f,
		-0.8f,-0.8f, 0.0f,	 0.0f, 0.0f, 1.0f,	0.f,0.0f,
		-0.8f,0.8f,0.0f,	 1.0f,1.0f,0.0f,	0.0f,1.f,
	};

	unsigned int indices[] =
	{
		//fisrt
		0,1,3,
		//second
		1,2,3
	};

	unsigned int VBO, VAO, EBO;
	glGenBuffers(1, &VBO);
	glGenBuffers(1, &EBO);
	glGenVertexArrays(1, &VAO);

	glBindVertexArray(VAO);
	glBindBuffer(GL_ARRAY_BUFFER, VBO);
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);

	//binding vertex coords
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)0);
	glEnableVertexAttribArray(0);
	//binding color values
	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)(3 * sizeof(float)));
	glEnableVertexAttribArray(1);
	//binding texture coords
	glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)(6 * sizeof(float)));
	glEnableVertexAttribArray(2);

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



	///glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);

	while (!glfwWindowShouldClose(window))
	{
		//input
		processInput(window);

		//rendering
		glClearColor(0.2f, 0.2f, 0.1f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT);

		//binding
		glActiveTexture(GL_TEXTURE0);
		glBindTexture(GL_TEXTURE_2D, texture1);
		glActiveTexture(GL_TEXTURE1);
		glBindTexture(GL_TEXTURE_2D, texture2);

		//render container
		subShader.Use();
		glBindVertexArray(VAO);
		glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);
		glBindVertexArray(0);

		//check and call events and swap the buffers
		glfwSwapBuffers(window);
		glfwPollEvents();
	}


	glfwTerminate();
	return 0;
}

void FramebufferSizeCallback(GLFWwindow *window, int width, int height)
{
	glViewport(0, 0, width, height);
}

void processInput(GLFWwindow *window)
{
	if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
		glfwSetWindowShouldClose(window, true);
}

void BindTextures(unsigned int &texture, char const *path, bool png , int *success)
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


