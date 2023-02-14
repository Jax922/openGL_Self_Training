#pragma once
#include<string>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

class Shader
{
public:
	Shader(const char* vertexPath, const char* fragmentPath);
	//~Shader();
	inline const char* GetVertexSource() const { return m_vertexSource; };
	inline const char* GetFragmentSource() const { return m_fragmentSource; };

	void Build(); // build shader source code
	void Use(); 

public:
	//template <typename T> // T can be one of : bool, int, float
	void SetValue(const std::string& name, float &value) const;
	void SetValue(const std::string& name, int value) const;
	void SetValue(const std::string& name, bool &value) const;
	void SetValue(const std::string& name, glm::vec3& value) const;
	void SetValue(const std::string& name, float &x, float &y, float &z) const;
	void SetValue(const std::string& name, glm::mat4& value) const;

private:
	const char* m_vertexSource;
	const char* m_fragmentSource;
	unsigned int m_ID; // shader program ID
	std::string m_vertexCode;
	std::string m_fragmentCode;
};

