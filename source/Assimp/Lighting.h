#pragma once
#include "../MySource/Shader/Shader.h"
#include "BufferObject/BufferObject.h"
#include <vector>
class Camera;

class LightBuffer;
using LightBufferPtr = std::shared_ptr<LightBuffer>;

struct DirectionLight {
	glm::vec3 direction{ 0.57735f, -0.57735f, -0.57735f };	//ό«
	glm::vec3 color{ 1.f, 0.9f, 0.8f };				//Β«F
	//glm::vec3 diffuse{ 0.5f, 0.5f, 0.5f };				//gUF
	//glm::vec3 specular{ 1.0f, 1.0f, 1.0f };				//½ΛF
};

struct PointLight {
	glm::vec3 position{ 1.2f, 1.0f, 2.0f };				//Κu
	glm::vec3 color{ 0.2f, 0.2f, 0.2f };				//Β«
	//float constant{ 1.f };								//θl
	//float linear{ 0.09f };								//ό  
	//float quadratic{ 0.032f };							//ρ
};

struct SpotLight {
	glm::vec3 direction{ -0.2f, -1.0f, -0.3f };			//ό«
	glm::vec3 position{ 1.2f, 1.0f, 2.0f };				//Κu
	glm::vec3 color{ 0.2f, 0.2f, 0.2f };				//Β«
	float cutOff{ glm::cos(glm::radians(12.5f)) };		//ΰ€Μpx spot
	float outerCutOff{ glm::cos(glm::radians(15.0f)) };	//O€Μpx spot	s	
	float constant{ 1.f };								//θl spot & point 
	float linear{ 0.09f };								//ό spot & point
	float quadratic{ 0.032f };							//ρ spot & point
};

class LightBuffer
{
public:
	static LightBufferPtr Create(size_t lightCount) {
		return std::make_shared<LightBuffer>(lightCount);
	}
	explicit LightBuffer(size_t lightCount);
	~LightBuffer() = default;

	LightBuffer(const LightBuffer&) = delete;
	LightBuffer& operator=(const LightBuffer&) = delete;

	//Cgf[^μ¬
	void BeginUpdate();

	void AddDirectionLight(DirectionLight& light);

	void AddPointLight(PointLight& light);

	void AddSpotLight(SpotLight& light);

	void EndUpdate();
	void SwapBuffers();

	void Bind();
	void Unbind();
	template <typename T>
	void MemoryCopy(MappedBufferObjectPtr& ssbo, std::vector<T>& buffer) {
		ssbo->WaitSync();
		uint8_t* p = ssbo->GetMappedAddress();
		const int lightCount[4] = { static_cast<int>(buffer.size()) };
		memcpy(p, lightCount, sizeof(lightCount));
		if (!buffer.empty()) {
			p += sizeof(lightCount);
			const size_t size = (std::min<size_t>)(
				ssbo->GetSize(), buffer.size() * sizeof(T));
			memcpy(p, buffer.data(), size);

			//bufferΜΕ¬»
			buffer.clear();
			buffer.shrink_to_fit();
		}
	}

	int type = 0;
private:
	DirectionLight dirLightBuffer = {};
	std::vector<PointLight> pointLightBuffer = {};
	std::vector<SpotLight> spotLightBuffer = {};

	MappedBufferObjectPtr dirSsbo;
	MappedBufferObjectPtr pointSsbo;
	MappedBufferObjectPtr spotSsbo;

	bool isUpdating = false;
};
