#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <Shaders/shader.h>
#include <Camera/Cam.h>
#include <Obj/Object.h>
#include <glm/glm/glm.hpp>
#include <glm/glm/gtc/matrix_transform.hpp>
#include <glm/glm/gtc/type_ptr.hpp>
#include <iostream>
#include <string>
#include <vector>



using namespace glm;
bool firstMouse = true;
unsigned int VBO;

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

const vector<float> AE_CUBE = {
	   -0.5f, -0.5f, -0.5f,
		0.5f, -0.5f, -0.5f,
		0.5f,  0.5f, -0.5f,
		0.5f,  0.5f, -0.5f,
	   -0.5f,  0.5f, -0.5f,
	   -0.5f, -0.5f, -0.5f,

	   -0.5f, -0.5f,  0.5f,
		0.5f, -0.5f,  0.5f,
		0.5f,  0.5f,  0.5f,
		0.5f,  0.5f,  0.5f,
	   -0.5f,  0.5f,  0.5f,
	   -0.5f, -0.5f,  0.5f,

	   -0.5f,  0.5f,  0.5f,
	   -0.5f,  0.5f, -0.5f,
	   -0.5f, -0.5f, -0.5f,
	   -0.5f, -0.5f, -0.5f,
	   -0.5f, -0.5f,  0.5f,
	   -0.5f,  0.5f,  0.5f,

		0.5f,  0.5f,  0.5f,
		0.5f,  0.5f, -0.5f,
		0.5f, -0.5f, -0.5f,
		0.5f, -0.5f, -0.5f,
		0.5f, -0.5f,  0.5f,
		0.5f,  0.5f,  0.5f,

	   -0.5f, -0.5f, -0.5f,
		0.5f, -0.5f, -0.5f,
		0.5f, -0.5f,  0.5f,
		0.5f, -0.5f,  0.5f,
	   -0.5f, -0.5f,  0.5f,
	   -0.5f, -0.5f, -0.5f,

	   -0.5f,  0.5f, -0.5f,
		0.5f,  0.5f, -0.5f,
		0.5f,  0.5f,  0.5f,
		0.5f,  0.5f,  0.5f,
	   -0.5f,  0.5f,  0.5f,
	   -0.5f,  0.5f, -0.5f
};

const vector<float> AE_N_CUBE = {
		 0.0f,  0.0f, -1.0f,
		  0.0f,  0.0f, -1.0f,
		  0.0f,  0.0f, -1.0f,
		  0.0f,  0.0f, -1.0f,
		 0.0f,  0.0f, -1.0f,
		 0.0f,  0.0f, -1.0f,

		 0.0f,  0.0f,  1.0f,
		  0.0f,  0.0f,  1.0f,
		  0.0f,  0.0f,  1.0f,
		  0.0f,  0.0f,  1.0f,
		 0.0f,  0.0f,  1.0f,
		 0.0f,  0.0f,  1.0f,

		-1.0f,  0.0f,  0.0f,
		-1.0f,  0.0f,  0.0f,
		-1.0f,  0.0f,  0.0f,
		-1.0f,  0.0f,  0.0f,
		-1.0f,  0.0f,  0.0f,
		-1.0f,  0.0f,  0.0f,

		  1.0f,  0.0f,  0.0f,
		  1.0f,  0.0f,  0.0f,
		  1.0f,  0.0f,  0.0f,
		  1.0f,  0.0f,  0.0f,
		  1.0f,  0.0f,  0.0f,
		  1.0f,  0.0f,  0.0f,

		 0.0f, -1.0f,  0.0f,
		  0.0f, -1.0f,  0.0f,
		  0.0f, -1.0f,  0.0f,
		  0.0f, -1.0f,  0.0f,
		 0.0f, -1.0f,  0.0f,
		 0.0f, -1.0f,  0.0f,

		 0.0f,  1.0f,  0.0f,
		  0.0f,  1.0f,  0.0f,
		  0.0f,  1.0f,  0.0f,
		  0.0f,  1.0f,  0.0f,
		 0.0f,  1.0f,  0.0f,
		 0.0f,  1.0f,  0.0f
};


vec3 light(1.2f, 1.0f, 2.0f);


void framebuffer_size_callback(GLFWwindow* window, int width, int height);
void processInput(GLFWwindow* window);
void mouse_callback(GLFWwindow* window, double xp, double yp);



const unsigned int SCR_WIDTH = 800;
const unsigned int SCR_HEIGHT = 600;


void initialize_GLFW() {
	glfwInit();
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);






}

GLFWwindow* create_Window(float wdth, float hght) {
	GLFWwindow* window = glfwCreateWindow(wdth, hght, "Ayden_Alexander", NULL, NULL);
	if (window == NULL)
	{
		std::cout << "Failed to create GLFW window" << std::endl;
		glfwTerminate();

	}
	glfwMakeContextCurrent(window);
	glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);

	if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
	{
		std::cout << "Failed to initialize GLAD" << std::endl;

	}

	return window;

}


float lf = 0.0f;
float dt = 0.0f;
float cf;
float lX = 400.0f;
float lY = 300.0f;

//class Object {
//
//
//public:
//	vector<float> verts;
//	vec3 pos;
//	vec3 scl;
//	vec3 rot;
//	mat4 obj;
//	mat4 pro = perspective(radians(45.0f), (float)SCR_WIDTH / (float)SCR_HEIGHT, 0.1f, 100.0f);
//	unsigned int vao;
//	unsigned int vbo;
//
//
//
//
//	Object(vec3 Pos = vec3(0.0f), vec3 Scale = vec3(1.0f), vec3 Rot = vec3(0.0f)) {
//
//		pos = Pos;
//		scl = Scale;
//		rot = Rot;
//
//		createObject();
//
//
//	}
//
//	void createObject() {
//
//		
//
//		glGenVertexArrays(1, &vao);
//		glGenBuffers(1, &vbo);
//
//		glBindVertexArray(vao);
//		glBindBuffer(GL_ARRAY_BUFFER, vbo);
//
//		glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);
//
//
//		// vertex positions
//		glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*)0);
//		glEnableVertexAttribArray(0);
//
//		glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*)(3 * sizeof(float)));
//		glEnableVertexAttribArray(1);
//
//		glBindVertexArray(0);
//
//
//		cout << vbo << " , " << vao;
//
//
//		
//
//	}
//
//	void applyMatrix(Shader& s, Camera& c) {
//
//		//perspective
//
//		obj = mat4(1.0f);
//		obj = translate(obj, pos);
//		obj = rotate(obj, 0.0f, rot);
//		obj = scale(obj, scl);
//
//		//apply
//		unsigned int modelM = glGetUniformLocation(s.ID, "trans");
//		glUniformMatrix4fv(modelM, 1, GL_FALSE, value_ptr(obj));
//		unsigned int viewM = glGetUniformLocation(s.ID, "view");
//		glUniformMatrix4fv(viewM, 1, GL_FALSE, value_ptr(c.getView()));
//		unsigned int proM = glGetUniformLocation(s.ID, "pro");
//		glUniformMatrix4fv(proM, 1, GL_FALSE, value_ptr(pro));
//
//
//
//
//		glBindVertexArray(vao);
//		glDrawArrays(GL_TRIANGLES, 0, 36);
//		glBindVertexArray(0);
//		
//
//		//glDeleteVertexArrays(1, &vao);
//	}
//
//
//};


Camera myCam(vec3(0.0f, 0.0f, 5.0f));








int main()
{

	


	initialize_GLFW();


	


	GLFWwindow* window = create_Window(800, 600);
	glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);
	glEnable(GL_DEPTH_TEST);


	Shader myShader("Shaders/lvert.VS", "Shaders/lfrag.FS");
	Shader lightShader("Shaders/Light/lightV.VS", "Shaders/Light/lightF.FS");






	Object ob(vec3(0.0f), vec3(1.0f), AE_CUBE, AE_N_CUBE);
	Object og(vec3(1.0f, -0.0f, 0.0f), vec3(1.0f), AE_CUBE, AE_N_CUBE);
	Object lg(light, vec3(0.1f), AE_CUBE, AE_N_CUBE);



	





	while (!glfwWindowShouldClose(window))
	{
		processInput(window);

		glfwSetCursorPosCallback(window, mouse_callback);

		cf = glfwGetTime();
		dt = cf - lf;
		lf = cf;


		glClearColor(0.4, 0.5, 0.5, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

		//perspective
		mat4 pro = perspective(radians(45.0f), (float)SCR_WIDTH / (float)(SCR_WIDTH * (3.0f / 4.0f)), 0.1f, 100.0f);
		
		ob.setPro(pro);
		og.setPro(pro);
		lg.setPro(pro);

		////////////////////////////cube//////////////////////////////////
		myShader.use();
		myShader.setvec3("oColor", 1.0f, 1.0f, 1.0f);
		myShader.setvec3("lColor", 1.0f, 1.0f, 1.0f);
		myShader.setvec3("lPos", light.x, light.y, light.z);
		myShader.setvec3("vPos", myCam.pos.x, myCam.pos.y, myCam.pos.z);
		myShader.setvec3("ambient", 40.0f / 255.0f, 176.0f / 255.0f, 50.0f / 255.0f);
		myShader.setvec3("diffuse", 40.0f / 255.0f, 176.0f / 255.0f, 50.0f / 255.0f);
		myShader.setvec3("specular", 0.5f, 0.5f, 0.5f);


		ob.display(myShader, myCam);

		myShader.setvec3("oColor", 1.0f, 1.0f, 1.0f);
		myShader.setvec3("lColor", 1.0f, 1.0f, 1.0f);
		myShader.setvec3("lPos", light.x, light.y, light.z);
		myShader.setvec3("vPos", myCam.pos.x, myCam.pos.y, myCam.pos.z);
		myShader.setvec3("ambient", 0.765, 0.765, 0.765);
		myShader.setvec3("diffuse", 0.765, 0.765, 0.765);
		myShader.setvec3("specular", 0.5f, 0.5f, 0.5f);

		og.display(myShader, myCam);



		///////////////////////////lightcube///////////////////////////////////

		lightShader.use();
		lg.display(lightShader, myCam);

		






		glfwSwapBuffers(window);
		glfwPollEvents();
	}


	ob.deleteBuffers();
	og.deleteBuffers();
	lg.deleteBuffers();


	glfwTerminate();
	return 0;
}


void processInput(GLFWwindow* window)
{

	if (glfwGetKey(window, GLFW_KEY_Q) == GLFW_PRESS)
		glfwSetWindowShouldClose(window, true);
	if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)

		glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_NORMAL);

	if (glfwGetKey(window, GLFW_KEY_R) == GLFW_PRESS)
		glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);

	if (glfwGetKey(window, GLFW_KEY_W) == GLFW_PRESS) {
		myCam.key(FWD, dt);
	}
	if (glfwGetKey(window, GLFW_KEY_S) == GLFW_PRESS) {
		myCam.key(BWD, dt);
	}
	if (glfwGetKey(window, GLFW_KEY_A) == GLFW_PRESS) {
		myCam.key(LFT, dt);
	}
	if (glfwGetKey(window, GLFW_KEY_D) == GLFW_PRESS) {
		myCam.key(RGT, dt);
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

	myCam.mouseMov(xoff, yoff);

}

void framebuffer_size_callback(GLFWwindow* window, int width, int height)
{

	glViewport(0, 0, width, (int)(width * (3.0f / 4.0f)));
	
}