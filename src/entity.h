#pragma once

#include <glm/glm.hpp>
#include <memory>
#include <string>
#include <unordered_map>

struct PositionComponent {
	glm::vec3 position;
};

struct InputComponent {
	glm::vec3 movement_direction;
};

struct MeshComponent {
	Mesh mesh;
};

class Entity {
public:
	friend class EntitySystem;
	bool marked_for_removal = false;
	std::unordered_map<std::string, std::shared_ptr<void>> components;

	template<typename T>
	void addComponent(const std::string& name, std::shared_ptr<T> component)
	{
		components[name] = component;
	}

	template<typename T>
	std::shared_ptr<T> getComponent(const std::string& name) const
	{
		auto it = components.find(name);
		if (it != components.end())
		{
			return std::static_pointer_cast<T>(it->second);
		}
		return nullptr;  // Component not found
	}

	int getId() const { return id; }

private:
	int id;
};