#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <Shaders/shader.h>
#include <glm/glm/glm.hpp>
#include <glm/glm/gtc/matrix_transform.hpp>
#include <glm/glm/gtc/type_ptr.hpp>

#include <iostream>
#include <string>

using namespace glm;
bool firstMouse = true;

vec3 light(1.2f, 1.0f, 2.0f);

vec4 vec(1.0f, 0.0f, 0.0f, 1);
vec4 vec_2(1.0f, 0.0f, 0.0f, 1);
vec3 camera(0.0f, 0.0f, 5.0f);
vec3 cFnt(0.0f, 0.0f, -1.0f);
vec3 cTar(0.0f, 0.0f, 0.0f);
vec3 cdir = normalize(camera - cTar);
vec3 up(0.0f, 1.0f, 0.0f);
//vec3 rght = normalize(cross(cFnt, up));


void framebuffer_size_callback(GLFWwindow* window, int width, int height);
void processInput(GLFWwindow* window);
void mouse_callback(GLFWwindow* window, double xp, double yp);


// settings
const unsigned int SCR_WIDTH = 800;
const unsigned int SCR_HEIGHT = 600;

float YAW = -90.0f;
float PIT = 0.0f;

//const char* vertexShaderSource = "#version 330 core\n"
//"layout (location = 0) in vec3 aPos;\n"
//"layout (location = 1) in vec3 aColor;\n"
//"out vec3 vertexColor;\n"
//"void main()\n"
//"{\n"
//"   gl_Position = vec4(aPos, 1.0f);\n"
//"	vertexColor = aColor;\n"
//"}\0";
//const char* fragmentShaderSource = "#version 330 core\n"
//"out vec4 FragColor;\n"
//"in vec3 vertexColor;\n"
//"void main()\n"
//"{\n"
//"   FragColor = vec4(vertexColor, 1.0f);\n"
//"}\n\0";

void initialize_GLFW() {
	glfwInit();
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);



	//return 0;
}

GLFWwindow* create_Window() {
	GLFWwindow* window = glfwCreateWindow(SCR_WIDTH, SCR_HEIGHT, "Ayden_Alexander", NULL, NULL);
	if (window == NULL)
	{
		std::cout << "Failed to create GLFW window" << std::endl;
		glfwTerminate();
		//return -1;
	}
	glfwMakeContextCurrent(window);
	glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);

	return window;

}


float lf = 0.0f;
float dt = 0.0f;
float cf;
float lX = 400.0f;
float lY = 300.0f;







int main()
{


	initialize_GLFW();


	


	GLFWwindow* window = create_Window();
	glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);

	



	if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
	{
		std::cout << "Failed to initialize GLAD" << std::endl;
		return -1;
	}

	glEnable(GL_DEPTH_TEST);




	//glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);

	Shader myShader("Shaders/lvert.VS", "Shaders/lfrag.FS");
	Shader lightShader("Shaders/Light/lightV.VS", "Shaders/Light/lightF.FS");

	float vertices[] = {
	   -0.5f, -0.5f, -0.5f,  0.0f,  0.0f, -1.0f,
		0.5f, -0.5f, -0.5f,  0.0f,  0.0f, -1.0f,
		0.5f,  0.5f, -0.5f,  0.0f,  0.0f, -1.0f,
		0.5f,  0.5f, -0.5f,  0.0f,  0.0f, -1.0f,
	   -0.5f,  0.5f, -0.5f,  0.0f,  0.0f, -1.0f,
	   -0.5f, -0.5f, -0.5f,  0.0f,  0.0f, -1.0f,

	   -0.5f, -0.5f,  0.5f,  0.0f,  0.0f,  1.0f,
		0.5f, -0.5f,  0.5f,  0.0f,  0.0f,  1.0f,
		0.5f,  0.5f,  0.5f,  0.0f,  0.0f,  1.0f,
		0.5f,  0.5f,  0.5f,  0.0f,  0.0f,  1.0f,
	   -0.5f,  0.5f,  0.5f,  0.0f,  0.0f,  1.0f,
	   -0.5f, -0.5f,  0.5f,  0.0f,  0.0f,  1.0f,

	   -0.5f,  0.5f,  0.5f, -1.0f,  0.0f,  0.0f,
	   -0.5f,  0.5f, -0.5f, -1.0f,  0.0f,  0.0f,
	   -0.5f, -0.5f, -0.5f, -1.0f,  0.0f,  0.0f,
	   -0.5f, -0.5f, -0.5f, -1.0f,  0.0f,  0.0f,
	   -0.5f, -0.5f,  0.5f, -1.0f,  0.0f,  0.0f,
	   -0.5f,  0.5f,  0.5f, -1.0f,  0.0f,  0.0f,

		0.5f,  0.5f,  0.5f,  1.0f,  0.0f,  0.0f,
		0.5f,  0.5f, -0.5f,  1.0f,  0.0f,  0.0f,
		0.5f, -0.5f, -0.5f,  1.0f,  0.0f,  0.0f,
		0.5f, -0.5f, -0.5f,  1.0f,  0.0f,  0.0f,
		0.5f, -0.5f,  0.5f,  1.0f,  0.0f,  0.0f,
		0.5f,  0.5f,  0.5f,  1.0f,  0.0f,  0.0f,

	   -0.5f, -0.5f, -0.5f,  0.0f, -1.0f,  0.0f,
		0.5f, -0.5f, -0.5f,  0.0f, -1.0f,  0.0f,
		0.5f, -0.5f,  0.5f,  0.0f, -1.0f,  0.0f,
		0.5f, -0.5f,  0.5f,  0.0f, -1.0f,  0.0f,
	   -0.5f, -0.5f,  0.5f,  0.0f, -1.0f,  0.0f,
	   -0.5f, -0.5f, -0.5f,  0.0f, -1.0f,  0.0f,

	   -0.5f,  0.5f, -0.5f,  0.0f,  1.0f,  0.0f,
		0.5f,  0.5f, -0.5f,  0.0f,  1.0f,  0.0f,
		0.5f,  0.5f,  0.5f,  0.0f,  1.0f,  0.0f,
		0.5f,  0.5f,  0.5f,  0.0f,  1.0f,  0.0f,
	   -0.5f,  0.5f,  0.5f,  0.0f,  1.0f,  0.0f,
	   -0.5f,  0.5f, -0.5f,  0.0f,  1.0f,  0.0f
	};
	

	//buffer
	unsigned int VBO;
	glGenBuffers(1, &VBO);
	

	glBindBuffer(GL_ARRAY_BUFFER, VBO);
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

	//cube
	unsigned int VAO;
	glGenVertexArrays(1, &VAO);
	glBindVertexArray(VAO);

	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*)0);
	glEnableVertexAttribArray(0);

	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*)(3 * sizeof(float)));
	glEnableVertexAttribArray(1);

	

	//light
	unsigned int LVAO;
	glGenVertexArrays(1, &LVAO);
	glBindVertexArray(LVAO);
	
	

	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*)0);
	glEnableVertexAttribArray(0);








	while (!glfwWindowShouldClose(window))
	{
		processInput(window);
		
		glfwSetCursorPosCallback(window, mouse_callback);

		cf = glfwGetTime();
		dt = cf - lf;
		lf = cf;

		


		glClearColor(0.4, 0.5, 0.5, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

		//cam 
		mat4 v = mat4(1.0f);
		v = lookAt(camera, camera + cFnt, up);
		mat4 pro = perspective(radians(45.0f), (float)SCR_WIDTH / (float)SCR_HEIGHT, 0.1f, 100.0f);


		////////////////////////////cube//////////////////////////////////
		myShader.use();
		myShader.setvec3("oColor", 1.0f, 1.0f, 1.0f);
		myShader.setvec3("lColor", 1.0f, 1.0f, 1.0f);
		myShader.setvec3("lPos", light.x, light.y, light.z);
		myShader.setvec3("vPos", camera.x, camera.y, camera.z);
		mat4 t = mat4(1.0f);
		t = translate(t, vec3(0.0f, 0.0f, 0.0f));
		t = rotate(t, 0.0f, vec3(0.0f, 0.0f, 1.0f));
		t = scale(t, vec3(1.0f, 1.0f, 1.0f));
		
		//vec = t * vec;
		unsigned int modelM = glGetUniformLocation(myShader.ID, "transMat");
		glUniformMatrix4fv(modelM, 1, GL_FALSE, value_ptr(t));
		unsigned int viewM = glGetUniformLocation(myShader.ID, "view");
		glUniformMatrix4fv(viewM, 1, GL_FALSE, value_ptr(v));
		unsigned int proM = glGetUniformLocation(myShader.ID, "pro");
		glUniformMatrix4fv(proM, 1, GL_FALSE, value_ptr(pro));

		glBindVertexArray(VAO);
		glDrawArrays(GL_TRIANGLES, 0, 36);

	
		///////////////////////////lightcube///////////////////////////////////
		
		lightShader.use();
		
		mat4 l = mat4(1.0f);
		l = translate(l, light);
		l = rotate(l, 0.0f, vec3(0.0f, 0.0f, 1.0f));
		l = scale(l, vec3(0.1f, 0.1f, 0.1f));

		unsigned int modelL = glGetUniformLocation(lightShader.ID, "transMat");
		glUniformMatrix4fv(modelL, 1, GL_FALSE, value_ptr(l));
		unsigned int viewL = glGetUniformLocation(lightShader.ID, "view");
		glUniformMatrix4fv(viewL, 1, GL_FALSE, value_ptr(v));
		unsigned int proL = glGetUniformLocation(lightShader.ID, "pro");
		glUniformMatrix4fv(proL, 1, GL_FALSE, value_ptr(pro));

		glBindVertexArray(LVAO);
		glDrawArrays(GL_TRIANGLES, 0, 36);
			
		
		



		glfwSwapBuffers(window);
		glfwPollEvents();
	}


	glDeleteVertexArrays(1, &VAO);
	glDeleteVertexArrays(1, &LVAO);
	glDeleteBuffers(1, &VBO);
	//glDeleteProgram(shaderProgram);


	glfwTerminate();
	return 0;
}


void processInput(GLFWwindow* window)
{
	float cSpd = 5.0f * dt;

	if (glfwGetKey(window, GLFW_KEY_Q) == GLFW_PRESS)
		glfwSetWindowShouldClose(window, true);
	if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
		//glfwSetWindowShouldClose(window, true);
		glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_NORMAL);

	if (glfwGetKey(window, GLFW_KEY_R) == GLFW_PRESS)
		glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);

	if (glfwGetKey(window, GLFW_KEY_W) == GLFW_PRESS) {
		camera += cFnt * cSpd;
	}
	if (glfwGetKey(window, GLFW_KEY_S) == GLFW_PRESS) {
		camera -= cFnt * cSpd;
	}
	if (glfwGetKey(window, GLFW_KEY_A) == GLFW_PRESS) {
		camera -= normalize(cross(cFnt, up)) * cSpd;
	}
	if (glfwGetKey(window, GLFW_KEY_D) == GLFW_PRESS) {
		camera += normalize(cross(cFnt, up)) * cSpd;
	}

}

void mouse_callback(GLFWwindow* window, double xp, double yp) {
	
	
	if (firstMouse)
	{
		lX = xp;
		lY = yp;
		firstMouse = false;
	}
	
	float xoff = xp - lX;
	float yoff = lY - yp;
	lX = xp;
	lY = yp;
	float sensitivity = 0.1f;
	xoff *= sensitivity;
	yoff *= sensitivity;

	YAW += xoff;
	PIT += yoff;

	if (PIT > 89.0f)
		PIT = 89.0f;
	if (PIT < -89.0f)
		PIT = -89.0f;

	vec3 dir;
	dir.x = cos(radians(YAW)) * cos(radians(PIT));
	dir.y = sin(radians(PIT));
	dir.z = sin(radians(YAW)) * cos(radians(PIT));
	cFnt = normalize(dir);

}

void framebuffer_size_callback(GLFWwindow* window, int width, int height)
{

	glViewport(0, 0, width, (int)(width * (3.0f/4.0f)));
}