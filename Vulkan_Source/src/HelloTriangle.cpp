#include "Headers/TriangleApplication.h"
#include <map>


///debugmessenger constructor and deconstructor
VkResult CreateDebugUtilsMessageEXT(
	VkInstance instance,
	const VkDebugUtilsMessengerCreateInfoEXT *pCreateInfo,
	const VkAllocationCallbacks * pAllocator,
	VkDebugUtilsMessengerEXT *pCallback)
{

	auto func = (PFN_vkCreateDebugUtilsMessengerEXT)vkGetInstanceProcAddr(instance, "vkCreateDebugUtilsMessengerEXT");

	if (func != nullptr)
	{
		return func(instance, pCreateInfo, pAllocator, pCallback);
	}
	else
	{
		return VK_ERROR_EXTENSION_NOT_PRESENT;
	}
}

void DestroyDebugUtilsMessengerExt(VkInstance instance,
	VkDebugUtilsMessengerEXT callback, 
	VkAllocationCallbacks* pAllocator)
{
	auto func = (PFN_vkDestroyDebugUtilsMessengerEXT)vkGetInstanceProcAddr(instance, "vkDestroyDebugUtilsMessengerEXT");
	if (func != NULL)
	{
		func(instance, callback, pAllocator);
	}
}


///Hellotriangle header function declarations

///initVulkan
void HelloTriangleApplication::initWindow()
{
	const int WIDTH = 800;
	const int HEIGHT = 600;
	glfwInit();

	glfwWindowHint(GLFW_CLIENT_API, GLFW_NO_API);
	glfwWindowHint(GLFW_RESIZABLE, GLFW_FALSE);
	window = glfwCreateWindow(WIDTH, HEIGHT, "ASDF", NULL, NULL);


	glm::mat4 matrix;
	glm::vec4 vec;
	auto test = matrix * vec;

	while (!glfwWindowShouldClose(window))
	{
		glfwPollEvents();
	}

	glfwDestroyWindow(window);

	glfwTerminate();
}

void HelloTriangleApplication::ApplicationInfoGet()
{
	appInfo.sType = VK_STRUCTURE_TYPE_APPLICATION_INFO;
	appInfo.pApplicationName = "FAGGGOT";
	appInfo.applicationVersion = VK_MAKE_VERSION(1, 0, 0);
	appInfo.pEngineName = "NULL";
	appInfo.engineVersion = VK_MAKE_VERSION(1, 0, 0);
	appInfo.apiVersion = VK_API_VERSION_1_0;

}

void HelloTriangleApplication::createInstance()
{

	createinfo.sType = VK_STRUCTURE_TYPE_INSTANCE_CREATE_INFO;
	createinfo.pApplicationInfo = &appInfo;
	auto extensions = getRequiredExtensions();
	createinfo.enabledExtensionCount = static_cast<uint32_t>(extensions.size());
	createinfo.ppEnabledExtensionNames = extensions.data();

	if (enableValidationLayers)
	{
		createinfo.enabledLayerCount = static_cast<uint32_t>(validationLayers.size());
		createinfo.ppEnabledLayerNames = validationLayers.data();
	}
	else
	{
		createinfo.enabledLayerCount = 0;
	}


	VkResult result = vkCreateInstance(&createinfo, NULL, &instance);

	if (vkCreateInstance(&createinfo, NULL, &instance) != VK_SUCCESS)
	{
		throw std::runtime_error("FUKC OSKEFPESG INSTANCE");
	}

	ApplicationInfoGet();
}

bool HelloTriangleApplication::checkValidationLayerSupport()
{
	uint32_t layerCount;
	vkEnumerateInstanceLayerProperties(&layerCount, NULL);

	std::vector<VkLayerProperties> avaiableLayers(layerCount);
	vkEnumerateInstanceLayerProperties(&layerCount, avaiableLayers.data());

	for (const char* layerName : validationLayers)
	{
		bool layerFound = false;

		for (const auto &layerProperties : avaiableLayers)
		{
			if (strcmp(layerName, layerProperties.layerName) == 0)
			{
				layerFound = true;
				break;
			}
		}

		if (!layerFound)
		{
			return false;
		}
	}

	return true;
}

void HelloTriangleApplication::createLogicalDevice()
{
	QueueFamilyIndices indices = findQueueFamilies(physicalDevice);

	VkDeviceQueueCreateInfo queueCreateInfo = {};
	queueCreateInfo.sType = VK_STRUCTURE_TYPE_DEVICE_QUEUE_CREATE_INFO;
	queueCreateInfo.queueFamilyIndex = indices.graphicsFamily.value();
	queueCreateInfo.queueCount = 1;
	float queuePriority = 1.0f;
	queueCreateInfo.pQueuePriorities = &queuePriority;
	VkPhysicalDeviceFeatures deviceFeatures = {};
	
	VkDeviceCreateInfo createinfo = {};
	createinfo.sType = VK_STRUCTURE_TYPE_DEVICE_CREATE_INFO;
	createinfo.pQueueCreateInfos = &queueCreateInfo;
	createinfo.queueCreateInfoCount = 1;
	createinfo.pEnabledFeatures = &deviceFeatures;

	createinfo.enabledExtensionCount = 0;

	if (enableValidationLayers)
	{
		createinfo.enabledLayerCount = static_cast<uint32_t>(validationLayers.size());
		createinfo.ppEnabledLayerNames = validationLayers.data();
	}
	else
	{
		createinfo.enabledLayerCount = 0;
	}

	if (vkCreateDevice(physicalDevice, &createinfo, NULL, &device) != VK_SUCCESS)
	{
		throw std::runtime_error("Failed to find didney logical derrrvice");
	}

	vkGetDeviceQueue(device, indices.graphicsFamily.value(), 0, &graphicsQueue);
}

std::vector<const char*> HelloTriangleApplication::getRequiredExtensions()
{
	uint32_t glfwExtensionsCount = 0;

	const char** glfwExtensions;

	glfwExtensions = glfwGetRequiredInstanceExtensions(&glfwExtensionsCount);

	std::vector<const char*> extensions(glfwExtensions, glfwExtensions + glfwExtensionsCount);

	if (enableValidationLayers)
	{
		extensions.push_back(VK_EXT_DEBUG_UTILS_EXTENSION_NAME);
	}

	return extensions;
}

void HelloTriangleApplication::setupDebugCallBack()

{
	if (!enableValidationLayers) return;

	VkDebugUtilsMessengerCreateInfoEXT createinfo = {};
	createinfo.sType = VK_STRUCTURE_TYPE_DEBUG_UTILS_MESSENGER_CREATE_INFO_EXT;
	createinfo.messageSeverity = 
		VK_DEBUG_UTILS_MESSAGE_SEVERITY_VERBOSE_BIT_EXT |
		VK_DEBUG_UTILS_MESSAGE_SEVERITY_WARNING_BIT_EXT |
		VK_DEBUG_UTILS_MESSAGE_SEVERITY_ERROR_BIT_EXT;
	createinfo.messageType = 
		VK_DEBUG_UTILS_MESSAGE_TYPE_GENERAL_BIT_EXT | 
		VK_DEBUG_UTILS_MESSAGE_TYPE_VALIDATION_BIT_EXT |
		VK_DEBUG_UTILS_MESSAGE_TYPE_PERFORMANCE_BIT_EXT;

	createinfo.pfnUserCallback = debugCallback;
	createinfo.pUserData = nullptr;

	if (CreateDebugUtilsMessageEXT(instance, &createinfo, nullptr, &callback) != VK_SUCCESS)
	{
		throw std::runtime_error("failed to set yyp debug callback");
	}
}

void HelloTriangleApplication::pickPhysicalDevice()
{
	uint32_t deviceCount = 0;
	vkEnumeratePhysicalDevices(instance, &deviceCount, NULL);

	if (deviceCount == 0)
	{
		throw std::runtime_error("Failed to find GPUs with vulkan support");
	}

	std::vector<VkPhysicalDevice> devices(deviceCount);
	vkEnumeratePhysicalDevices(instance, &deviceCount, devices.data());

	std::multimap<int, VkPhysicalDevice> canditates;

	for (const auto &device : devices)
	{
		int score = rateDeviceSuitability(device);
		canditates.insert(std::make_pair(score, device));
	}

	if (canditates.rbegin()->first > 0)
	{
		physicalDevice = canditates.rbegin()->second;
	}
	else
	{
		throw std::runtime_error("Failed to find a suitable GPU");
	}


}

int HelloTriangleApplication::rateDeviceSuitability(VkPhysicalDevice device)
{
	VkPhysicalDeviceProperties deviceProperties;
	VkPhysicalDeviceFeatures deviceFeatures;
	vkGetPhysicalDeviceProperties(device, &deviceProperties);
	vkGetPhysicalDeviceFeatures(device, &deviceFeatures);

	int score = 0;

	if (deviceProperties.deviceType == VK_PHYSICAL_DEVICE_TYPE_DISCRETE_GPU)
	{
		score += 1000;
	}

	score += deviceProperties.limits.maxImageDimension2D;

	if (!deviceFeatures.geometryShader)
	{
		return 0;
	}

	return score;
}

bool HelloTriangleApplication::isDeviceSuitable(VkPhysicalDevice device)
{
	QueueFamilyIndices indices = findQueueFamilies(device);

	return indices.isComplete();
}

QueueFamilyIndices HelloTriangleApplication::findQueueFamilies(VkPhysicalDevice device)
{
	QueueFamilyIndices indices;
	uint32_t queueFamilyCount = 0;
	vkGetPhysicalDeviceQueueFamilyProperties(device, &queueFamilyCount, NULL);

	std::vector<VkQueueFamilyProperties> queueFamilies(queueFamilyCount);
	vkGetPhysicalDeviceQueueFamilyProperties(device, &queueFamilyCount, queueFamilies.data());

	int i = 0;
	for (const auto& queuefamily : queueFamilies)
	{
		if (queuefamily.queueCount > 0 && queuefamily.queueFlags & VK_QUEUE_GRAPHICS_BIT)
		{
			indices.graphicsFamily = i;
		}

		if (indices.isComplete())
		{
			break;
		}

		i++;
	}


	return indices;
}

void HelloTriangleApplication::createSurface()
{
	if (glfwCreateWindowSurface(instance, window, NULL, &surface) != VK_SUCCESS)
	{
		throw std::runtime_error("FAILED TO CREATE WINDOW SURFACCE BLYAT");
	}
}

///mainloop
void HelloTriangleApplication::drawFrame()
{


}


void HelloTriangleApplication::cleanup()
{
	if (enableValidationLayers)
	{
		DestroyDebugUtilsMessengerExt(instance, callback, NULL);
	}
	vkDestroyDevice(device, NULL);
	vkDestroyInstance(instance, NULL);
	glfwDestroyWindow(window);
	glfwTerminate();
}
