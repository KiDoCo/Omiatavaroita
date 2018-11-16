#ifndef _TRIANGLEAPPLICATION_H_INCLUDED_
#define _TRIANGLEAPPLICATION_H_INCLUDED_

#define GLFW_INCLUDE_VULKAN
#include <GLFW/glfw3.h>

#define GLM_FORCE_RADIANS
#define GLM_FORCE_DEPTH_ZERO_TO_NONE
#include <glm/vec4.hpp>
#include <glm/mat4x4.hpp>

#include <iostream>
#include <stdexcept>
#include <functional>
#include <cstdlib>
#include <vector>
#include <optional>

const std::vector<const char*> validationLayers = {
	"VK_LAYER_LUNARG_standard_validation"
};

struct  QueueFamilyIndices
{
	std::optional<uint32_t> graphicsFamily;

	bool isComplete()
	{
		return graphicsFamily.has_value();
	}
	};

#ifdef NDEBUG
const bool enableValidationLayers = false;
#else
const bool enableValidationLayers = true;
#endif 

class HelloTriangleApplication {
public:


	void initVulkan()
	{
		createInstance();
		setupDebugCallBack();
		createSurface();
		pickPhysicalDevice();
		createLogicalDevice();
	}
	void run()
	{
		initWindow();
		cleanup();
	}

	void mainLoop()
	{
		while (!glfwWindowShouldClose(window))
		{
			glfwPollEvents();
			drawFrame();
		}

	}

private:

	VkInstanceCreateInfo createinfo = {};
	VkApplicationInfo appInfo = {};
	VkInstance instance;
	VkDebugUtilsMessengerEXT callback;
	VkPhysicalDevice physicalDevice = VK_NULL_HANDLE;
	VkQueue graphicsQueue;
	VkDevice device;
	VkSurfaceKHR surface;
	GLFWwindow *window;
	std::vector<const char*> getRequiredExtensions();

	//init vulkan
	void createInstance();
	void ApplicationInfoGet();
	bool checkValidationLayerSupport();
	void setupDebugCallBack();
	void pickPhysicalDevice();
	void createLogicalDevice();
	void createSurface();
	bool isDeviceSuitable(VkPhysicalDevice device);
	QueueFamilyIndices findQueueFamilies(VkPhysicalDevice device);
	int rateDeviceSuitability(VkPhysicalDevice device);
	//main loop
	void drawFrame();
	//run
	void cleanup();
	void initWindow();

	static VKAPI_ATTR VkBool32 VKAPI_CALL debugCallback(VkDebugUtilsMessageSeverityFlagBitsEXT messageSeverity, 
		VkDebugUtilsMessageTypeFlagsEXT messageType, 
		const VkDebugUtilsMessengerCallbackDataEXT* pCallbackData, 
		void* pUserData)
	{
		std::cerr << "validation layer: " << pCallbackData->pMessage << std::endl;

		return VK_FALSE;
	}
};

#endif 