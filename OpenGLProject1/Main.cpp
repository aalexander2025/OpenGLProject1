#include <AE.h>


vec3 light(1.2f, 1.0f, 2.0f);
GLFWwindow* window;
Shader myShader;
Shader lightShader;

Object ob;
Object og;
Object lg;



void setup() {
	initialize_GLFW();
	window = create_Window(800, 600);

	glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);
	glEnable(GL_DEPTH_TEST);

	myShader = createShader("Shaders/lvert.VS", "Shaders/lfrag.FS");
	lightShader = createShader("Shaders/Light/lightV.VS", "Shaders/Light/lightF.FS");
	ob = createObject(vec3(0.0f), vec3(1.0f), AE_CUBE, AE_N_CUBE);
	og = createObject(vec3(1.0f, -0.0f, 0.0f), vec3(1.0f), AE_CUBE, AE_N_CUBE);
	lg = createObject(light, vec3(0.1f), AE_CUBE, AE_N_CUBE);
}

void draw() {
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


int main()
{
	setup();
	while (!glfwWindowShouldClose(window))
	{
		draw();
	}


	ob.deleteBuffers();
	og.deleteBuffers();
	lg.deleteBuffers();


	glfwTerminate();
	return 0;
}