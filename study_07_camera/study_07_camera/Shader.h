#pragma once
#include<string>
#include <glm.hpp>
#include <gtc/matrix_transform.hpp>
#include <gtc/type_ptr.hpp>

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
	void SetValue(std::string name, int value);
	void SetValue(std::string name, glm::mat4 trans);


private:
	const char* m_vertexSource;
	const char* m_fragmentSource;
	unsigned int m_ID; // shader program ID
	std::string m_vertexCode;
	std::string m_fragmentCode;
};

