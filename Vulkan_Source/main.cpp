


#include "src/Headers/TriangleApplication.h"
#include <iostream>



int main()
{
	HelloTriangleApplication app;

	try
	{
		app.initVulkan();
		app.run();
	}
	catch (const std::exception& e)
	{
		std::cerr << e.what() << std::endl;
		return EXIT_FAILURE;
	}

	return EXIT_SUCCESS;
}



