#ifndef VERTEX_HEADER
#define VERTEX_HEADER
#include <glm/fwd.hpp>
#include <vector>
struct Vertex
{
	std::vector<glm::vec3> positions;
	std::vector<glm::vec3> color;
	std::vector<glm::vec3> normals;
	std::vector<glm::vec2> texture;
};



#endif // !VERTEX_HEADER

