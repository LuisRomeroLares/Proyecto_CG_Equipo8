#include <iostream>
#include <cmath>

// GLEW
#include <GL/glew.h>

// GLFW
#include <GLFW/glfw3.h>

// Other Libs
#include "stb_image.h"

// GLM Mathematics
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

//Load Models
#include "SOIL2/SOIL2.h"


// Other includes
#include "Shader.h"
#include "Camera.h"
#include "Model.h"
#include "Texture.h"

// Function prototypes
void KeyCallback(GLFWwindow *window, int key, int scancode, int action, int mode);
void MouseCallback(GLFWwindow *window, double xPos, double yPos);
void DoMovement();
void animacion();

// Window dimensions
const GLuint WIDTH = 800, HEIGHT = 600;
int SCREEN_WIDTH, SCREEN_HEIGHT;

// Camera
Camera  camera(glm::vec3(-100.0f, 2.0f, -45.0f));
GLfloat lastX = WIDTH / 2.0;
GLfloat lastY = HEIGHT / 2.0;
bool keys[1024];
bool firstMouse = true;
float range = 0.0f;
float rot = 0.0f;

//////////////////////////////
float rot_brazo = 0.0f;
float rot_brazo2 = 0.0f;
float rot_gorro = 0.0f;
bool active_brazo;
bool anim_brazo = false;
bool recorrido1_brazo = true;
bool recorrido2_brazo = false;
bool recorrido3_brazo = false;
bool recorrido4_brazo = false;
bool recorrido5_brazo = false;
bool recorrido6_brazo = false;
float mov_gorro = 0.0f;
////////////////////////////

////////////////////////////
bool anim = false;
float rot_tren = 0.0f;
bool recorrido1 = true;
bool recorrido2 = false;
bool recorrido3 = false;
bool recorrido4 = false;
float movx = 0.0f;
float movz = 0.0f;
float rotvehiculo = 0.0;
bool active_tren;
/////////////////////////////

//////////////////////////////
float movy = 0.0f;
bool arriba1 = true;
bool arriba_giro = false;
bool arriba2 = false;
bool abajo_giro = false;
float rot_nieve = 0.0f;
float rot_nieve2 = 0.0f;
float movy2 = 0.0f;

bool active_nieve;
bool anim_nieve = false;
////////////////////////////////

////////////////////////////////
float rot_ala1 = 0.0f;
float rot_ala2 = 0.0f;
float rot_brazo_angel = 0.0f;
bool active_angel;
bool anim_angel = false;
float piel_angel1 = 0.0f;
float piel_angel2 = 0.0f;

bool recorrido1_angel = true;
bool recorrido2_angel = false;
bool recorrido3_angel = true;
bool recorrido4_angel = false;
bool recorrido5_angel = true;
bool recorrido6_angel = false;
bool recorrido7_angel = true;
bool recorrido8_angel = false;
bool recorrido9_angel = true;
bool recorrido10_angel = false;
//////////////////////////////////

// Light attributes
glm::vec3 lightPos(0.0f, 0.0f, 0.0f);
//glm::vec3 PosIni(-95.0f, 1.0f, -45.0f);
bool active;


// Deltatime
GLfloat deltaTime = 0.0f;	// Time between current frame and last frame
GLfloat lastFrame = 0.0f;  	// Time of last frame

glm::vec3 pointLightPositions[] = {
	glm::vec3(0.0f,0.0f,0.0f),
	glm::vec3(0.0f,0.0f,0.0f),
	glm::vec3(0.0f,0.0f,0.0f),
	glm::vec3(0.0f,0.0f,0.0f)
};
glm::vec3 LightP1;







int main()
{
	// Init GLFW
	glfwInit();


	// Create a GLFWwindow object that we can use for GLFW's functions
	GLFWwindow* window = glfwCreateWindow(WIDTH, HEIGHT, "Proyecto Final Equipo 8", nullptr, nullptr);

	if (nullptr == window)
	{
		std::cout << "Failed to create GLFW window" << std::endl;
		glfwTerminate();

		return EXIT_FAILURE;
	}

	glfwMakeContextCurrent(window);

	glfwGetFramebufferSize(window, &SCREEN_WIDTH, &SCREEN_HEIGHT);

	// Set the required callback functions
	glfwSetKeyCallback(window, KeyCallback);
	glfwSetCursorPosCallback(window, MouseCallback);
	printf("%f", glfwGetTime());

	// GLFW Options
	glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);

	// Set this to true so GLEW knows to use a modern approach to retrieving function pointers and extensions
	glewExperimental = GL_TRUE;
	// Initialize GLEW to setup the OpenGL Function pointers
	if (GLEW_OK != glewInit())
	{
		std::cout << "Failed to initialize GLEW" << std::endl;
		return EXIT_FAILURE;
	}

	// Define the viewport dimensions
	glViewport(0, 0, SCREEN_WIDTH, SCREEN_HEIGHT);

	// OpenGL options
	glEnable(GL_DEPTH_TEST);
	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
/////////////////////////////////////////////////////////////////////////////
	Shader shader("Shaders/modelLoading.vs", "Shaders/modelLoading.frag");
	Shader lightingShader("Shaders/lighting.vs", "Shaders/lighting.frag");
	Shader lampShader("Shaders/lamp.vs", "Shaders/lamp.frag");
	Shader SkyBoxshader("Shaders/SkyBox.vs", "Shaders/SkyBox.frag");
////////////////////////////////////////////////////////////////////////////

/////////////////////////////////////////////////////////////////
	Model Casa((char*)"Models/Casa/casa3.obj");
	Model Piso((char*)"Models/Piso/piso.obj");
/////////////////////////////////////////////////////////////////

///////////////////////////////////////////////////////////////////////////
	Model muneco((char*)"Models/BLANCO/MUNECO.obj");
	Model muneco1((char*)"Models/BLANCO/MUNECO1.obj");
	Model brazo1((char*)"Models/BLANCO/BRAZO.obj");
	Model gorro((char*)"Models/BLANCO/GORRO.obj");
	Model brazo2((char*)"Models/BLANCO/BRAZO2.obj");
//////////////////////////////////////////////////////////////////////////

//////////////////////////////////////////////////////////////////////////
	Model tren2((char*)"Models/TREN/TREN2.obj");
	Model tren((char*)"Models/TREN/TREN.obj");
	Model tren3((char*)"Models/TREN/TREN3.obj");
	Model llanta1((char*)"Models/TREN/LLANTA1.obj");
	Model llanta2((char*)"Models/TREN/LLANTA1.obj");
	Model llanta3((char*)"Models/TREN/LLANTA2.obj");
	Model llanta4((char*)"Models/TREN/LLANTA2.obj");
	Model llanta5((char*)"Models/TREN/LLANTA2.obj");
	Model llanta6((char*)"Models/TREN/LLANTA2.obj");
/////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////
	Model nieve((char*)"Models/TREN/NIEVE.obj");
	Model nieve2((char*)"Models/TREN/NIEVE2.obj");
///////////////////////////////////////////////////////////////////////

	Model modelo((char*)"Models/Prueba/proyectoEscenario.obj");
/////////////////////////////////////////////////////////////////////
	Model MarcoVentana1((char*)"Models/Ventana/marcoVentana.obj");
	Model Ventana1((char*)"Models/Ventana/ventana.obj");
	Model MarcoVentana2((char*)"Models/Ventana/marcoVentana2.obj");
	Model Ventana2((char*)"Models/Ventana/ventana2.obj");
////////////////////////////////////////////////////////////////////

///////////////////////////////////////////////////////////////////
	Model MarcoPuerta1((char*)"Models/Puerta/marcoPuerta1.obj");
	Model Puerta1((char*)"Models/Puerta/Puerta1.obj");
	Model MarcoPuerta2((char*)"Models/Puerta/marcoPuerta2.obj");
	Model Puerta2((char*)"Models/Puerta/Puerta2.obj");
	Model MarcoPuerta3((char*)"Models/Puerta/marcoPuerta3.obj");
	Model Puerta3((char*)"Models/Puerta/Puerta3.obj");
///////////////////////////////////////////////////////////////////

//////////////////////////////////////////////////////////////////
	Model Among((char*)"Models/Among/among.obj");
	Model Jardin((char*)"Models/Jardin/jardin.obj");
	Model Rosas((char*)"Models/Rose/rosas.obj");
/////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////
	Model Arbol((char*)"Models/Arbol/arbolNavideno.obj");
	Model Estrella((char*)"Models/Estrella/estrella.obj");
	Model Chimenea((char*)"Models/Chimenea/chimenea.obj");
	Model Adorno((char*)"Models/Chimenea/Venado/adornoVenado.obj");
	Model Sofa((char*)"Models/Sofa/sofa.obj");
	Model Calcetin1((char*)"Models/Calcetines/calcetin1.obj");
	Model Calcetin2((char*)"Models/Calcetines/calcetin2.obj");
	Model Mesa((char*)"Models/Mesa/mesa.obj");
////////////////////////////////////////////////////////////////

///////////////////////////////////////////////////////////////
	Model Pollo((char*)"Models/Pollo/PolloFinal/pollo.obj");
	Model Plato((char*)"Models/Plato/plato.obj");
	Model Dulce((char*)"Models/Dulce/dulceNavideno.obj");
	Model Botella1((char*)"Models/Botellas/botella1.obj");
	Model Botella2((char*)"Models/Botellas/botella2.obj");
	Model Botella3((char*)"Models/Botellas/botella3.obj");
	Model Botella4((char*)"Models/Botellas/botella4.obj");
	Model Botella5((char*)"Models/Botellas/botella5.obj");
	Model Botella6((char*)"Models/Botellas/botella6.obj");
	Model Botella7((char*)"Models/Botellas/botella7.obj");
	Model Botella8((char*)"Models/Botellas/botella8.obj");
//////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////
	Model Regalo1((char*)"Models/Regalo/regalo1.obj");
	Model Regalo2((char*)"Models/Regalo/regalo2.obj");
////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////
	Model sala((char*)"Models/SALA/SALA.obj");
////////////////////////////////////////////////////////////

/////////////////////////////////////////////////////////////
	Model recamara_piso((char*)"Models/RECAMARA/PISORECAMARA.obj");
	Model recamara1((char*)"Models/RECAMARA/RECAMARA1.obj");
	Model recamara2((char*)"Models/RECAMARA/RECAMARA2.obj");
	Model recamara3((char*)"Models/RECAMARA/RECAMARA3.obj");
	Model recamara4((char*)"Models/RECAMARA/RECAMARA4.obj");
	Model recamara5((char*)"Models/RECAMARA/RECAMARA5.obj");
///////////////////////////////////////////////////////////////

/////////////////////////////////////////////////////////////
	Model angel((char*)"Models/ANGEL/ANGEL.obj");
	Model ala1((char*)"Models/ANGEL/ALA1.obj");
	Model ala2((char*)"Models/ANGEL/ALA2.obj");
	Model angel_brazo((char*)"Models/ANGEL/ANGEL_BRAZO.obj");

	Model angel1((char*)"Models/ANGEL/ANGEL.obj");
	Model ala11((char*)"Models/ANGEL/ALA1.obj");
	Model ala21((char*)"Models/ANGEL/ALA2.obj");
	Model angel_brazo1((char*)"Models/ANGEL/ANGEL_BRAZO.obj");

	Model angel2((char*)"Models/ANGEL/ANGEL.obj");
	Model ala12((char*)"Models/ANGEL/ALA1.obj");
	Model ala22((char*)"Models/ANGEL/ALA2.obj");
	Model angel_brazo2((char*)"Models/ANGEL/ANGEL_BRAZO.obj");


	Model angel3((char*)"Models/ANGEL/ANGEL.obj");
	Model ala13((char*)"Models/ANGEL/ALA1.obj");
	Model ala23((char*)"Models/ANGEL/ALA2.obj");
	Model angel_brazo23((char*)"Models/ANGEL/ANGEL_BRAZO.obj");

	Model angel4((char*)"Models/ANGEL/ANGEL.obj");
	Model ala14((char*)"Models/ANGEL/ALA1.obj");
	Model ala24((char*)"Models/ANGEL/ALA2.obj");
	Model angel_brazo24((char*)"Models/ANGEL/ANGEL_BRAZO.obj");

	Model angel5((char*)"Models/ANGEL/ANGEL.obj");
	Model ala15((char*)"Models/ANGEL/ALA1.obj");
	Model ala25((char*)"Models/ANGEL/ALA2.obj");
	Model angel_brazo25((char*)"Models/ANGEL/ANGEL_BRAZO.obj");
///////////////////////////////////////////////////////////////////////
	// Set up vertex data (and buffer(s)) and attribute pointers
	GLfloat vertices[] =
	{
		// Positions            // Normals              // Texture Coords
		-0.5f, -0.5f, -0.5f,    0.0f,  0.0f, -1.0f,     0.0f,  0.0f,
		0.5f, -0.5f, -0.5f,     0.0f,  0.0f, -1.0f,     1.0f,  0.0f,
		0.5f,  0.5f, -0.5f,     0.0f,  0.0f, -1.0f,     1.0f,  1.0f,
		0.5f,  0.5f, -0.5f,     0.0f,  0.0f, -1.0f,     1.0f,  1.0f,
		-0.5f,  0.5f, -0.5f,    0.0f,  0.0f, -1.0f,     0.0f,  1.0f,
		-0.5f, -0.5f, -0.5f,    0.0f,  0.0f, -1.0f,     0.0f,  0.0f,

		-0.5f, -0.5f,  0.5f,    0.0f,  0.0f,  1.0f,     0.0f,  0.0f,
		0.5f, -0.5f,  0.5f,     0.0f,  0.0f,  1.0f,     1.0f,  0.0f,
		0.5f,  0.5f,  0.5f,     0.0f,  0.0f,  1.0f,     1.0f,  1.0f,
		0.5f,  0.5f,  0.5f,     0.0f,  0.0f,  1.0f,  	1.0f,  1.0f,
		-0.5f,  0.5f,  0.5f,    0.0f,  0.0f,  1.0f,     0.0f,  1.0f,
		-0.5f, -0.5f,  0.5f,    0.0f,  0.0f,  1.0f,     0.0f,  0.0f,

		-0.5f,  0.5f,  0.5f,    -1.0f,  0.0f,  0.0f,    1.0f,  0.0f,
		-0.5f,  0.5f, -0.5f,    -1.0f,  0.0f,  0.0f,    1.0f,  1.0f,
		-0.5f, -0.5f, -0.5f,    -1.0f,  0.0f,  0.0f,    0.0f,  1.0f,
		-0.5f, -0.5f, -0.5f,    -1.0f,  0.0f,  0.0f,    0.0f,  1.0f,
		-0.5f, -0.5f,  0.5f,    -1.0f,  0.0f,  0.0f,    0.0f,  0.0f,
		-0.5f,  0.5f,  0.5f,    -1.0f,  0.0f,  0.0f,    1.0f,  0.0f,

		0.5f,  0.5f,  0.5f,     1.0f,  0.0f,  0.0f,     1.0f,  0.0f,
		0.5f,  0.5f, -0.5f,     1.0f,  0.0f,  0.0f,     1.0f,  1.0f,
		0.5f, -0.5f, -0.5f,     1.0f,  0.0f,  0.0f,     0.0f,  1.0f,
		0.5f, -0.5f, -0.5f,     1.0f,  0.0f,  0.0f,     0.0f,  1.0f,
		0.5f, -0.5f,  0.5f,     1.0f,  0.0f,  0.0f,     0.0f,  0.0f,
		0.5f,  0.5f,  0.5f,     1.0f,  0.0f,  0.0f,     1.0f,  0.0f,

		-0.5f, -0.5f, -0.5f,    0.0f, -1.0f,  0.0f,     0.0f,  1.0f,
		0.5f, -0.5f, -0.5f,     0.0f, -1.0f,  0.0f,     1.0f,  1.0f,
		0.5f, -0.5f,  0.5f,     0.0f, -1.0f,  0.0f,     1.0f,  0.0f,
		0.5f, -0.5f,  0.5f,     0.0f, -1.0f,  0.0f,     1.0f,  0.0f,
		-0.5f, -0.5f,  0.5f,    0.0f, -1.0f,  0.0f,     0.0f,  0.0f,
		-0.5f, -0.5f, -0.5f,    0.0f, -1.0f,  0.0f,     0.0f,  1.0f,

		-0.5f,  0.5f, -0.5f,    0.0f,  1.0f,  0.0f,     0.0f,  1.0f,
		0.5f,  0.5f, -0.5f,     0.0f,  1.0f,  0.0f,     1.0f,  1.0f,
		0.5f,  0.5f,  0.5f,     0.0f,  1.0f,  0.0f,     1.0f,  0.0f,
		0.5f,  0.5f,  0.5f,     0.0f,  1.0f,  0.0f,     1.0f,  0.0f,
		-0.5f,  0.5f,  0.5f,    0.0f,  1.0f,  0.0f,     0.0f,  0.0f,
		-0.5f,  0.5f, -0.5f,    0.0f,  1.0f,  0.0f,     0.0f,  1.0f
	};


	GLfloat skyboxVertices[] = {
		// Positions
		-1.0f,  1.0f, -1.0f,
		-1.0f, -1.0f, -1.0f,
		1.0f, -1.0f, -1.0f,
		1.0f, -1.0f, -1.0f,
		1.0f,  1.0f, -1.0f,
		-1.0f,  1.0f, -1.0f,

		-1.0f, -1.0f,  1.0f,
		-1.0f, -1.0f, -1.0f,
		-1.0f,  1.0f, -1.0f,
		-1.0f,  1.0f, -1.0f,
		-1.0f,  1.0f,  1.0f,
		-1.0f, -1.0f,  1.0f,

		1.0f, -1.0f, -1.0f,
		1.0f, -1.0f,  1.0f,
		1.0f,  1.0f,  1.0f,
		1.0f,  1.0f,  1.0f,
		1.0f,  1.0f, -1.0f,
		1.0f, -1.0f, -1.0f,

		-1.0f, -1.0f,  1.0f,
		-1.0f,  1.0f,  1.0f,
		1.0f,  1.0f,  1.0f,
		1.0f,  1.0f,  1.0f,
		1.0f, -1.0f,  1.0f,
		-1.0f, -1.0f,  1.0f,

		-1.0f,  1.0f, -1.0f,
		1.0f,  1.0f, -1.0f,
		1.0f,  1.0f,  1.0f,
		1.0f,  1.0f,  1.0f,
		-1.0f,  1.0f,  1.0f,
		-1.0f,  1.0f, -1.0f,

		-1.0f, -1.0f, -1.0f,
		-1.0f, -1.0f,  1.0f,
		1.0f, -1.0f, -1.0f,
		1.0f, -1.0f, -1.0f,
		-1.0f, -1.0f,  1.0f,
		1.0f, -1.0f,  1.0f
	};


	GLuint indices[] =
	{  // Note that we start from 0!
		0,1,2,3,
		4,5,6,7,
		8,9,10,11,
		12,13,14,15,
		16,17,18,19,
		20,21,22,23,
		24,25,26,27,
		28,29,30,31,
		32,33,34,35
	};

	// Positions all containers
	glm::vec3 cubePositions[] = {
		glm::vec3(0.0f,  0.0f,  0.0f),
		glm::vec3(2.0f,  5.0f, -15.0f),
		glm::vec3(-1.5f, -2.2f, -2.5f),
		glm::vec3(-3.8f, -2.0f, -12.3f),
		glm::vec3(2.4f, -0.4f, -3.5f),
		glm::vec3(-1.7f,  3.0f, -7.5f),
		glm::vec3(1.3f, -2.0f, -2.5f),
		glm::vec3(1.5f,  2.0f, -2.5f),
		glm::vec3(1.5f,  0.2f, -1.5f),
		glm::vec3(-1.3f,  1.0f, -1.5f)
	};


	// First, set the container's VAO (and VBO)
	GLuint VBO, VAO, EBO;
	glGenVertexArrays(1, &VAO);
	glGenBuffers(1, &VBO);
	glGenBuffers(1, &EBO);

	glBindVertexArray(VAO);
	glBindBuffer(GL_ARRAY_BUFFER, VBO);
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);

	// Position attribute
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(GLfloat), (GLvoid *)0);
	glEnableVertexAttribArray(0);
	// Normals attribute
	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(GLfloat), (GLvoid *)(3 * sizeof(GLfloat)));
	glEnableVertexAttribArray(1);
	// Texture Coordinate attribute
	glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, 8 * sizeof(GLfloat), (GLvoid *)(6 * sizeof(GLfloat)));
	glEnableVertexAttribArray(2);
	glBindVertexArray(0);

	// Then, we set the light's VAO (VBO stays the same. After all, the vertices are the same for the light object (also a 3D cube))
	GLuint lightVAO;
	glGenVertexArrays(1, &lightVAO);
	glBindVertexArray(lightVAO);
	// We only need to bind to the VBO (to link it with glVertexAttribPointer), no need to fill it; the VBO's data already contains all we need.
	glBindBuffer(GL_ARRAY_BUFFER, VBO);
	// Set the vertex attributes (only position data for the lamp))
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(GLfloat), (GLvoid *)0); // Note that we skip over the other data in our buffer object (we don't need the normals/textures, only positions).
	glEnableVertexAttribArray(0);
	glBindVertexArray(0);


	//SkyBox
	GLuint skyboxVBO, skyboxVAO;
	glGenVertexArrays(1, &skyboxVAO);
	glGenBuffers(1,&skyboxVBO);
	glBindVertexArray(skyboxVAO);
	glBindBuffer(GL_ARRAY_BUFFER, skyboxVBO);
	glBufferData(GL_ARRAY_BUFFER, sizeof(skyboxVertices),&skyboxVertices,GL_STATIC_DRAW);
	glEnableVertexAttribArray(0);
	glVertexAttribPointer(0, 3, GL_FLOAT,GL_FALSE, 3 * sizeof(GLfloat), (GLvoid *)0);

	// Load textures
	vector<const GLchar*> faces;
	faces.push_back("SkyBox/right.tga");
	faces.push_back("SkyBox/left.tga");
	faces.push_back("SkyBox/top.tga");
	faces.push_back("SkyBox/bottom.tga");
	faces.push_back("SkyBox/back.tga");
	faces.push_back("SkyBox/front.tga");
	
	GLuint cubemapTexture = TextureLoading::LoadCubemap(faces);

	glm::mat4 projection = glm::perspective(camera.GetZoom(), (GLfloat)SCREEN_WIDTH / (GLfloat)SCREEN_HEIGHT, 0.1f, 1000.0f);

	// Game loop
	while (!glfwWindowShouldClose(window))
	{

		// Calculate deltatime of current frame
		GLfloat currentFrame = glfwGetTime();
		deltaTime = currentFrame - lastFrame;
		lastFrame = currentFrame;

		// Check if any events have been activiated (key pressed, mouse moved etc.) and call corresponding response functions
		glfwPollEvents();
		DoMovement();
		animacion();


		// Clear the colorbuffer
		glClearColor(0.1f, 0.1f, 0.1f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);


		// Use cooresponding shader when setting uniforms/drawing objects
		lightingShader.Use();
		GLint viewPosLoc = glGetUniformLocation(lightingShader.Program, "viewPos");
		glUniform3f(viewPosLoc, camera.GetPosition().x, camera.GetPosition().y, camera.GetPosition().z);
		// Set material properties
		glUniform1f(glGetUniformLocation(lightingShader.Program, "material.shininess"), 32.0f);
	
		// Directional light
		glUniform3f(glGetUniformLocation(lightingShader.Program, "dirLight.direction"), -0.2f, -1.0f, -0.3f);
		glUniform3f(glGetUniformLocation(lightingShader.Program, "dirLight.ambient"), 0.5f, 0.5f, 0.5f);
		glUniform3f(glGetUniformLocation(lightingShader.Program, "dirLight.diffuse"), 0.2f, 0.2f, 0.2f);
		glUniform3f(glGetUniformLocation(lightingShader.Program, "dirLight.specular"), 0.3f, 0.3f, 0.3f);


		// Point light 1
		glUniform3f(glGetUniformLocation(lightingShader.Program, "pointLights[0].position"), pointLightPositions[0].x, pointLightPositions[0].y, pointLightPositions[0].z);
		glUniform3f(glGetUniformLocation(lightingShader.Program, "pointLights[0].ambient"), 0.0f, 0.0f, 0.0f);
		glUniform3f(glGetUniformLocation(lightingShader.Program, "pointLights[0].diffuse"), LightP1.x, LightP1.y, LightP1.z);
		glUniform3f(glGetUniformLocation(lightingShader.Program, "pointLights[0].specular"), LightP1.x, LightP1.y, LightP1.z);
		glUniform1f(glGetUniformLocation(lightingShader.Program, "pointLights[0].constant"), 1.0f);
		glUniform1f(glGetUniformLocation(lightingShader.Program, "pointLights[0].linear"), 0.09f);
		glUniform1f(glGetUniformLocation(lightingShader.Program, "pointLights[0].quadratic"), 0.032f);



		// Point light 2
		glUniform3f(glGetUniformLocation(lightingShader.Program, "pointLights[1].position"), pointLightPositions[1].x, pointLightPositions[1].y, pointLightPositions[1].z);
		glUniform3f(glGetUniformLocation(lightingShader.Program, "pointLights[1].ambient"), 0.0f, 0.0f, 0.0f);
		glUniform3f(glGetUniformLocation(lightingShader.Program, "pointLights[1].diffuse"), 1.0f, 1.0f, 0.0f);
		glUniform3f(glGetUniformLocation(lightingShader.Program, "pointLights[1].specular"), 1.0f, 1.0f, 0.0f);
		glUniform1f(glGetUniformLocation(lightingShader.Program, "pointLights[1].constant"), 1.0f);
		glUniform1f(glGetUniformLocation(lightingShader.Program, "pointLights[1].linear"), 0.09f);
		glUniform1f(glGetUniformLocation(lightingShader.Program, "pointLights[1].quadratic"), 0.032f);

		// Point light 3
		glUniform3f(glGetUniformLocation(lightingShader.Program, "pointLights[2].position"), pointLightPositions[2].x, pointLightPositions[2].y, pointLightPositions[2].z);
		glUniform3f(glGetUniformLocation(lightingShader.Program, "pointLights[2].ambient"), 0.0f, 0.0f, 0.0f);
		glUniform3f(glGetUniformLocation(lightingShader.Program, "pointLights[2].diffuse"), 0.0f, 1.0f, 1.0f);
		glUniform3f(glGetUniformLocation(lightingShader.Program, "pointLights[2].specular"), 0.0f, 1.0f, 1.0f);
		glUniform1f(glGetUniformLocation(lightingShader.Program, "pointLights[2].constant"), 1.0f);
		glUniform1f(glGetUniformLocation(lightingShader.Program, "pointLights[2].linear"), 0.09f);
		glUniform1f(glGetUniformLocation(lightingShader.Program, "pointLights[2].quadratic"), 0.032f);

		// Point light 4
		glUniform3f(glGetUniformLocation(lightingShader.Program, "pointLights[3].position"), pointLightPositions[3].x, pointLightPositions[3].y, pointLightPositions[3].z);
		glUniform3f(glGetUniformLocation(lightingShader.Program, "pointLights[3].ambient"), 0.0f, 0.0f, 0.0f);
		glUniform3f(glGetUniformLocation(lightingShader.Program, "pointLights[3].diffuse"), 1.0f, 0.0f, 1.0f);
		glUniform3f(glGetUniformLocation(lightingShader.Program, "pointLights[3].specular"), 1.0f, 0.0f, 1.0f);
		glUniform1f(glGetUniformLocation(lightingShader.Program, "pointLights[3].constant"), 1.0f);
		glUniform1f(glGetUniformLocation(lightingShader.Program, "pointLights[3].linear"), 0.09f);
		glUniform1f(glGetUniformLocation(lightingShader.Program, "pointLights[3].quadratic"), 0.032f);

		// SpotLight
		glUniform3f(glGetUniformLocation(lightingShader.Program, "spotLight.position"), camera.GetPosition().x, camera.GetPosition().y, camera.GetPosition().z);
		glUniform3f(glGetUniformLocation(lightingShader.Program, "spotLight.direction"), camera.GetFront().x, camera.GetFront().y, camera.GetFront().z);
		glUniform3f(glGetUniformLocation(lightingShader.Program, "spotLight.ambient"), 0.0f, 0.0f, 0.0f);
		glUniform3f(glGetUniformLocation(lightingShader.Program, "spotLight.diffuse"), 0.0f, 0.0f, 0.0f);
		glUniform3f(glGetUniformLocation(lightingShader.Program, "spotLight.specular"), 0.0f, 0.0f, 0.0f);
		glUniform1f(glGetUniformLocation(lightingShader.Program, "spotLight.constant"), 1.0f);
		glUniform1f(glGetUniformLocation(lightingShader.Program, "spotLight.linear"), 0.09f);
		glUniform1f(glGetUniformLocation(lightingShader.Program, "spotLight.quadratic"), 0.032f);
		glUniform1f(glGetUniformLocation(lightingShader.Program, "spotLight.cutOff"), glm::cos(glm::radians(12.5f)));
		glUniform1f(glGetUniformLocation(lightingShader.Program, "spotLight.outerCutOff"), glm::cos(glm::radians(15.0f)));

		// Set material properties
		glUniform1f(glGetUniformLocation(lightingShader.Program, "material.shininess"), 32.0f);

		// Create camera transformations
		glm::mat4 view;
		view = camera.GetViewMatrix();


		// Get the uniform locations
		GLint modelLoc = glGetUniformLocation(lightingShader.Program, "model");
		GLint viewLoc = glGetUniformLocation(lightingShader.Program, "view");
		GLint projLoc = glGetUniformLocation(lightingShader.Program, "projection");

		// Pass the matrices to the shader
		glUniformMatrix4fv(viewLoc, 1, GL_FALSE, glm::value_ptr(view));
		glUniformMatrix4fv(projLoc, 1, GL_FALSE, glm::value_ptr(projection));

		glBindVertexArray(VAO);
		glm::mat4 tmp = glm::mat4(1.0f); //Temp

		glm::mat4 model(1);
		

		model = glm::mat4(1);
		glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model));
		Casa.Draw(shader);

		model = glm::mat4(1);
		model = glm::translate(model, glm::vec3(9.701f, 11.833f, 0.0f));
		glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model));
		angel.Draw(lightingShader);

		model = glm::mat4(1);
		model = glm::translate(model, glm::vec3(9.899f, 9.781f, 1.267f));
		model = glm::rotate(model, glm::radians(rot_brazo_angel), glm::vec3(1.0f, 0.0f, 0.0f));
		glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model));
		angel_brazo.Draw(lightingShader);

		model = glm::mat4(1);
		model = glm::translate(model, glm::vec3(9.283f, 9.032f, -0.5f));
		model = glm::rotate(model, glm::radians(rot_ala1), glm::vec3(0.0f, 1.0f, 0.0f));
		glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model));
		ala1.Draw(lightingShader);

		model = glm::mat4(1);
		model = glm::translate(model, glm::vec3(10.283f, 9.032f, -0.5f));
		model = glm::rotate(model, glm::radians(rot_ala2), glm::vec3(0.0f, 1.0f, 0.0f));
		glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model));
		ala2.Draw(lightingShader);
	
		model = glm::mat4(1);
		model = glm::translate(model, glm::vec3(9.701f, 11.833f, -10.0f));
		glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model));
		angel1.Draw(lightingShader);

		
		model = glm::mat4(1);
		model = glm::translate(model, glm::vec3(9.899f, 9.781f, -8.767f));
		model = glm::rotate(model, glm::radians(rot_brazo_angel), glm::vec3(1.0f, 0.0f, 0.0f));
		glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model));
		angel_brazo1.Draw(lightingShader);

		model = glm::mat4(1);
		model = glm::translate(model, glm::vec3(9.283f, 9.032f, -10.5f));
		model = glm::rotate(model, glm::radians(rot_ala1), glm::vec3(0.0f, 1.0f, 0.0f));
		glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model));
		ala11.Draw(lightingShader);

		model = glm::mat4(1);
		model = glm::translate(model, glm::vec3(10.283f, 9.032f, -10.5f));
		model = glm::rotate(model, glm::radians(rot_ala2), glm::vec3(0.0f, 1.0f, 0.0f));
		glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model));
		ala21.Draw(lightingShader);


		model = glm::mat4(1);
		model = glm::translate(model, glm::vec3(9.701f, 11.833f, -20.0f));
		glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model));
		angel2.Draw(lightingShader);


		model = glm::mat4(1);
		model = glm::translate(model, glm::vec3(9.899f, 9.781f, -18.767f));
		model = glm::rotate(model, glm::radians(rot_brazo_angel), glm::vec3(1.0f, 0.0f, 0.0f));
		glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model));
		angel_brazo2.Draw(lightingShader);

		model = glm::mat4(1);
		model = glm::translate(model, glm::vec3(9.283f, 9.032f, -20.5f));
		model = glm::rotate(model, glm::radians(rot_ala1), glm::vec3(0.0f, 1.0f, 0.0f));
		glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model));
		ala12.Draw(lightingShader);

		model = glm::mat4(1);
		model = glm::translate(model, glm::vec3(10.283f, 9.032f, -20.5f));
		model = glm::rotate(model, glm::radians(rot_ala2), glm::vec3(0.0f, 1.0f, 0.0f));
		glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model));
		ala22.Draw(lightingShader);

		model = glm::mat4(1);
		model = glm::translate(model, glm::vec3(-65.701f, 11.833f, 0.0f));
		glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model));
		angel3.Draw(lightingShader);

		model = glm::mat4(1);
		model = glm::translate(model, glm::vec3(-65.4f, 9.781f, 1.267f));
		model = glm::rotate(model, glm::radians(rot_brazo_angel), glm::vec3(1.0f, 0.0f, 0.0f));
		glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model));
		angel_brazo23.Draw(lightingShader);

		model = glm::mat4(1);
		model = glm::translate(model, glm::vec3(-66.083f, 9.032f, -0.5f));
		model = glm::rotate(model, glm::radians(rot_ala1), glm::vec3(0.0f, 1.0f, 0.0f));
		glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model));
		ala13.Draw(lightingShader);

		model = glm::mat4(1);
		model = glm::translate(model, glm::vec3(-65.983f, 9.032f, -0.5f));
		model = glm::rotate(model, glm::radians(rot_ala2), glm::vec3(0.0f, 1.0f, 0.0f));
		glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model));
		ala23.Draw(lightingShader);

		model = glm::mat4(1);
		model = glm::translate(model, glm::vec3(-65.701f, 11.833f, -10.0f));
		glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model));
		angel4.Draw(lightingShader);

		model = glm::mat4(1);
		model = glm::translate(model, glm::vec3(-65.4f, 9.781f, -8.767f));
		model = glm::rotate(model, glm::radians(rot_brazo_angel), glm::vec3(1.0f, 0.0f, 0.0f));
		glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model));
		angel_brazo24.Draw(lightingShader);

		model = glm::mat4(1);
		model = glm::translate(model, glm::vec3(-66.083f, 9.032f, -10.5f));
		model = glm::rotate(model, glm::radians(rot_ala1), glm::vec3(0.0f, 1.0f, 0.0f));
		glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model));
		ala14.Draw(lightingShader);

		model = glm::mat4(1);
		model = glm::translate(model, glm::vec3(-65.983f, 9.032f, -10.5f));
		model = glm::rotate(model, glm::radians(rot_ala2), glm::vec3(0.0f, 1.0f, 0.0f));
		glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model));
		ala24.Draw(lightingShader);

		model = glm::mat4(1);
		model = glm::translate(model, glm::vec3(-65.701f, 11.833f, -20.0f));
		glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model));
		angel5.Draw(lightingShader);

		model = glm::mat4(1);
		model = glm::translate(model, glm::vec3(-65.4f, 9.781f, -18.767f));
		model = glm::rotate(model, glm::radians(rot_brazo_angel), glm::vec3(1.0f, 0.0f, 0.0f));
		glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model));
		angel_brazo25.Draw(lightingShader);

		model = glm::mat4(1);
		model = glm::translate(model, glm::vec3(-66.083f, 9.032f, -20.5f));
		model = glm::rotate(model, glm::radians(rot_ala1), glm::vec3(0.0f, 1.0f, 0.0f));
		glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model));
		ala15.Draw(lightingShader);

		model = glm::mat4(1);
		model = glm::translate(model, glm::vec3(-65.983f, 9.032f, -20.5f));
		model = glm::rotate(model, glm::radians(rot_ala2), glm::vec3(0.0f, 1.0f, 0.0f));
		glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model));
		ala25.Draw(lightingShader);

		model = glm::mat4(1);
		glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model));
		sala.Draw(shader);

		model = glm::mat4(1);
		glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model));
		recamara1.Draw(shader);

		model = glm::mat4(1);
		glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model));
		recamara2.Draw(shader);

		model = glm::mat4(1);
		glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model));
		recamara3.Draw(shader);

		model = glm::mat4(1);
		glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model));
		recamara4.Draw(shader);

		model = glm::mat4(1);
		glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model));
		recamara5.Draw(shader);

		model = glm::mat4(1);
		glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model));
		recamara_piso.Draw(shader);

	
		model = glm::mat4(1);
		glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model));
		muneco.Draw(shader);


		model = glm::mat4(1);
		model = glm::translate(model, glm::vec3(21.532f, 5.5f, 23.38f));
		glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model));
		muneco1.Draw(shader);

		model = glm::mat4(1);
		model = glm::translate(model, glm::vec3(22.532f, 5.0f  ,23.38f));
		model = glm::rotate(model, glm::radians(rot_brazo), glm::vec3(0.0f, 0.0f, 1.0f));
		glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model));
		brazo1.Draw(lightingShader);

		
		model = glm::mat4(1);
		model = glm::translate(model, glm::vec3(19.0532f, 5.0f, 23.38f));
		model = glm::rotate(model, glm::radians(rot_brazo2), glm::vec3(0.0f, 0.0f, 1.0f));
		glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model));
		brazo2.Draw(shader);

		model = glm::mat4(1);
		model = glm::translate(model, glm::vec3(21.532f + mov_gorro, 8.2f, 23.38f));
		glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model));
		gorro.Draw(shader);

		model = glm::mat4(1);
		glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model));
		Piso.Draw(shader);

		model = glm::mat4(1);
		model = glm::translate(model, glm::vec3(-1.372f + movx, 6.023f, 66.057f + movz)); // Translate it down a bit so it's at the center of the scene
		model = glm::rotate(model, glm::radians(rotvehiculo), glm::vec3(0.0f, 1.0f, 0.0f));
		glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model));
		tren2.Draw(shader);

		model = glm::mat4(1);
		model = glm::translate(model, glm::vec3(-1.372 + movx, 0.0f, 66.057 + movz)); // Translate it down a bit so it's at the center of the scene
		model = glm::rotate(model, glm::radians(rotvehiculo), glm::vec3(0.0f, 1.0f, 0.0f));
		model = glm::translate(model, glm::vec3(-8.434f, 2.209f, 3.056f));
		model = glm::rotate(model, glm::radians(rot_tren), glm::vec3(0.0f, 0.0f, 1.0f)); 	
		glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model));
		llanta1.Draw(shader);

		model = glm::mat4(1);
		model = glm::translate(model, glm::vec3(-1.372 + movx, 0.0f, 66.057 + movz)); // Translate it down a bit so it's at the center of the scene
		model = glm::rotate(model, glm::radians(rotvehiculo), glm::vec3(0.0f, 1.0f, 0.0f));
		model = glm::translate(model, glm::vec3(-8.434f, 2.209f, -3.056f));
		model = glm::rotate(model, glm::radians(rot_tren), glm::vec3(0.0f, 0.0f, 1.0f));
		glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model));
		llanta2.Draw(shader);

		model = glm::mat4(1);
		model = glm::translate(model, glm::vec3(-1.372 + movx, 0.0f, 66.057 + movz)); // Translate it down a bit so it's at the center of the scene
		model = glm::rotate(model, glm::radians(rotvehiculo), glm::vec3(0.0f, 1.0f, 0.0f));
		model = glm::translate(model, glm::vec3(1.434f, 3.5f, -3.056f));
		model = glm::rotate(model, glm::radians(rot_tren), glm::vec3(0.0f, 0.0f, 1.0f));
		glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model));
		llanta3.Draw(shader);

		model = glm::mat4(1);
		model = glm::translate(model, glm::vec3(-1.372 + movx, 0.0f, 66.057 + movz)); // Translate it down a bit so it's at the center of the scene
		model = glm::rotate(model, glm::radians(rotvehiculo), glm::vec3(0.0f, 1.0f, 0.0f));
		model = glm::translate(model, glm::vec3(1.434f, 3.5f, 3.056f));
		model = glm::rotate(model, glm::radians(rot_tren), glm::vec3(0.0f, 0.0f, 1.0f));
		glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model));
		llanta4.Draw(shader);
		
		model = glm::mat4(1);
		model = glm::translate(model, glm::vec3(-1.372 + movx, 0.0f, 66.057 + movz)); // Translate it down a bit so it's at the center of the scene
		model = glm::rotate(model, glm::radians(rotvehiculo), glm::vec3(0.0f, 1.0f, 0.0f));
		model = glm::translate(model, glm::vec3(10.434f, 3.5f, -3.056f));
		model = glm::rotate(model, glm::radians(rot_tren), glm::vec3(0.0f, 0.0f, 1.0f));
		glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model));
		llanta5.Draw(shader);

		model = glm::mat4(1);
		model = glm::translate(model, glm::vec3(-1.372 + movx, 0.0f, 66.057 + movz)); // Translate it down a bit so it's at the center of the scene
		model = glm::rotate(model, glm::radians(rotvehiculo), glm::vec3(0.0f, 1.0f, 0.0f));
		model = glm::translate(model, glm::vec3(10.434f, 3.5f, 3.056f));
		model = glm::rotate(model, glm::radians(rot_tren), glm::vec3(0.0f, 0.0f, 1.0f));
		glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model));
		llanta6.Draw(shader);




		model = glm::mat4(1);
		model = glm::translate(model, glm::vec3(-85.126f, 9.55f + movy2, 39.401f));
		model = glm::rotate(model, glm::radians(rot_nieve2), glm::vec3(0.0f, 1.0f, 0.0f));
		glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model));
		nieve2.Draw(shader);

		model = glm::mat4(1);
		model = glm::translate(model, glm::vec3(-85.126f , 3.269f + movy, 39.401f) );
		model = glm::rotate(model, glm::radians(rot_nieve), glm::vec3(0.0f, 1.0f, 0.0f));
		glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model));
		nieve.Draw(shader);


		model = glm::mat4(1);
		glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model));
		Among.Draw(shader);

		model = glm::mat4(1);
		glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model));
		MarcoVentana1.Draw(shader);

		model = glm::mat4(1);
		glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model));
		MarcoVentana2.Draw(shader);

		model = glm::mat4(1);
		glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model));
		MarcoPuerta1.Draw(shader);

		model = glm::mat4(1);
		glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model));
		Puerta1.Draw(shader);

		model = glm::mat4(1);
		glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model));
		MarcoPuerta2.Draw(shader);

		model = glm::mat4(1);
		glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model));
		Puerta2.Draw(shader);

		model = glm::mat4(1);
		glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model));
		MarcoPuerta3.Draw(shader);

		model = glm::mat4(1);
		glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model));
		Puerta3.Draw(shader);

		model = glm::mat4(1);
		glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model));
		Arbol.Draw(shader);

		model = glm::mat4(1);
		glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model));
		Estrella.Draw(shader);

		model = glm::mat4(1);
		glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model));
		Chimenea.Draw(shader);

		model = glm::mat4(1);
		glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model));
		Adorno.Draw(shader);

		model = glm::mat4(1);
		glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model));
		Sofa.Draw(shader);

		model = glm::mat4(1);
		glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model));
		Calcetin1.Draw(shader);

		model = glm::mat4(1);
		glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model));
		Calcetin2.Draw(shader);

		model = glm::mat4(1);
		glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model));
		Mesa.Draw(shader);

		model = glm::mat4(1);
		glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model));
		Plato.Draw(shader);

		model = glm::mat4(1);
		glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model));
		Dulce.Draw(shader);

		model = glm::mat4(1);
		glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model));
		Pollo.Draw(shader);

		model = glm::mat4(1);
		glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model));
		Botella1.Draw(shader);

		model = glm::mat4(1);
		glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model));
		Botella2.Draw(shader);

		model = glm::mat4(1);
		glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model));
		Botella3.Draw(shader);

		model = glm::mat4(1);
		glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model));
		Botella4.Draw(shader);

		model = glm::mat4(1);
		glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model));
		Botella5.Draw(shader);

		model = glm::mat4(1);
		glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model));
		Botella6.Draw(shader);

		model = glm::mat4(1);
		glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model));
		Botella7.Draw(shader);

		model = glm::mat4(1);
		glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model));
		Botella8.Draw(shader);

		model = glm::mat4(1);
		glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model));
		Regalo1.Draw(shader);

		model = glm::mat4(1);
		glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model));
		Regalo2.Draw(shader);

		model = glm::mat4(1);
		glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model));
		Jardin.Draw(shader);

		model = glm::mat4(1);
		glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model));
		Rosas.Draw(shader);
		
		glBindVertexArray(0);


		// Also draw the lamp object, again binding the appropriate shader
		lampShader.Use();
		// Get location objects for the matrices on the lamp shader (these could be different on a different shader)
		modelLoc = glGetUniformLocation(lampShader.Program, "model");
		viewLoc = glGetUniformLocation(lampShader.Program, "view");
		projLoc = glGetUniformLocation(lampShader.Program, "projection");

		// Set matrices
		glUniformMatrix4fv(viewLoc, 1, GL_FALSE, glm::value_ptr(view));
		glUniformMatrix4fv(projLoc, 1, GL_FALSE, glm::value_ptr(projection));
		model = glm::mat4(1);
		model = glm::translate(model, lightPos);
		//model = glm::scale(model, glm::vec3(0.2f)); // Make it a smaller cube
		glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model));
		// Draw the light object (using light's vertex attributes)
		glBindVertexArray(lightVAO);
		for (GLuint i = 0; i < 4; i++)
		{
			model = glm::mat4(1);
			model = glm::translate(model, pointLightPositions[i]);
			model = glm::scale(model, glm::vec3(0.2f)); // Make it a smaller cube
			glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model));
			glDrawArrays(GL_TRIANGLES, 0, 36);
		}
		glBindVertexArray(0);


		// Draw skybox as last
		glDepthFunc(GL_LEQUAL);  // Change depth function so depth test passes when values are equal to depth buffer's content
		SkyBoxshader.Use();
		view = glm::mat4(glm::mat3(camera.GetViewMatrix()));	// Remove any translation component of the view matrix
		glUniformMatrix4fv(glGetUniformLocation(SkyBoxshader.Program, "view"), 1, GL_FALSE, glm::value_ptr(view));
		glUniformMatrix4fv(glGetUniformLocation(SkyBoxshader.Program, "projection"), 1, GL_FALSE, glm::value_ptr(projection));

		// skybox cube
		glBindVertexArray(skyboxVAO);
		glActiveTexture(GL_TEXTURE1);
		glBindTexture(GL_TEXTURE_CUBE_MAP, cubemapTexture);
		glDrawArrays(GL_TRIANGLES, 0, 36);
		glBindVertexArray(0);
		glDepthFunc(GL_LESS); // Set depth function back to default




		// Swap the screen buffers
		glfwSwapBuffers(window);
	}




	glDeleteVertexArrays(1, &VAO);
	glDeleteVertexArrays(1, &lightVAO);
	glDeleteBuffers(1, &VBO);
	glDeleteBuffers(1, &EBO);
	glDeleteVertexArrays(1, &skyboxVAO);
	glDeleteBuffers(1, &skyboxVBO);
	// Terminate GLFW, clearing any resources allocated by GLFW.
	glfwTerminate();




	return 0;
}


void animacion()
{

}


void DoMovement()
{

	// Camera controls
	if (keys[GLFW_KEY_W] || keys[GLFW_KEY_UP])
	{
		camera.ProcessKeyboard(FORWARD, deltaTime);

	}

	if (keys[GLFW_KEY_S] || keys[GLFW_KEY_DOWN])
	{
		camera.ProcessKeyboard(BACKWARD, deltaTime);


	}

	if (keys[GLFW_KEY_A] || keys[GLFW_KEY_LEFT])
	{
		camera.ProcessKeyboard(LEFT, deltaTime);


	}

	if (keys[GLFW_KEY_D] || keys[GLFW_KEY_RIGHT])
	{
		camera.ProcessKeyboard(RIGHT, deltaTime);


	}

	if (anim)
	{
		if (recorrido1)
		{
			if (movx < -130.0f)
			{
				recorrido1 = false;
				recorrido2 = true;
				rotvehiculo = -90.0f;

			}
			else
			{
				rot_tren += 0.3f;
				movx -= 0.1f;
			}
		}

		if (recorrido2)
		{
			if (movz < -150.0f)
			{
				recorrido2 = false;
				recorrido3 = true;
				rotvehiculo = -180.0f;

			}
			else
			{
				rot_tren += 0.3f;
				movz -= 0.1f;
			}
		}

		if (recorrido3)
		{
			if (movx > 130.0f)
			{
				recorrido3 = false;
				recorrido4 = true;
				rotvehiculo = 90.0f;

			}
			else
			{
				rot_tren += 0.3f;
				movx += 0.1f;
			}
		}

		if (recorrido4)
		{
			if (movx > 150.0f)
			{
				recorrido4 = false;
				recorrido1 = true;
				rotvehiculo = 0.0f;

			}
			else
			{
				rot_tren += 0.3f;
				movx += 0.1f;

			}
		}
	}

	if (anim_nieve)
	{
		if (arriba1)
		{
			if (movy > 8.0f && movy2 > 16.0f)
			{
				arriba1 = false;
				arriba_giro = true;
			}
			else
			{
				movy += 0.1f;
				movy2 += 0.2f;
			}
		}
		if (arriba_giro)
		{
			if (rot_nieve < -360.0f && rot_nieve2 >360.0f)
			{
				arriba_giro = false;
				arriba2 = true;
			}
			else
			{
				rot_nieve -= 1.0f;
				rot_nieve2 += 2.0f;
			}
		}
		if (arriba2)
		{
			if (movy < 0.0f && movy2 < 0.0f)
			{
				abajo_giro = true;
				arriba2 = false;
			}
			else
			{
				movy -= 0.1f;
				movy2 -= 0.2f;
			}
		}
		if (abajo_giro)
		{
			if (rot_nieve > 0.0f && rot_nieve2 < 0.0f)
			{
				abajo_giro = false;
				arriba1 = true;
			}
			else
			{
				rot_nieve += 1.0f;
				rot_nieve2 -= 1.0f;
			}
		}

	}


	if (anim_brazo)
	{
		if (recorrido1_brazo)
		{
			if (rot_brazo > 52.0f) {
				//rot_gorro = -1.0f;
				recorrido1_brazo = false;
				recorrido2_brazo = true;
			}
			else
			{
				rot_brazo += 0.1f;
			}
		}

		if (recorrido2_brazo)
		{
			if (mov_gorro < -1.0f) {
				//rot_gorro = -1.0f;
				recorrido2_brazo = false;
				recorrido3_brazo = true;
				recorrido4_brazo = true;
			}
			else
			{
				mov_gorro -= 0.01f;
			}
		}

		if (recorrido3_brazo)
		{
			if (rot_brazo < 0.0f) {
				recorrido3_brazo = false;
				//recorrido4_brazo = true;
			}
			else
			{
				rot_brazo -= 0.1f;
			}
		}
		if (recorrido4_brazo)
		{
			if (rot_brazo2 < -60.0f) {
				recorrido5_brazo = true;
				recorrido4_brazo = false;
			}
			else
			{
				rot_brazo2 -= 0.1f;
			}
		}
		if (recorrido5_brazo)
		{
			if (mov_gorro > 0.0f) {
				recorrido5_brazo = false;
				recorrido6_brazo = true;
			}
			else
			{
				mov_gorro += 0.01;
			}
		}

		if (recorrido6_brazo)
		{
			if (rot_brazo2 > 0.0f) {
				recorrido6_brazo = false;
				recorrido1_brazo = true;
			}
			else
			{
				rot_brazo2 += 0.1;
			}
		}

	}
	if (anim_angel)
	{
		if (recorrido1_angel)
		{
			if (rot_ala1 > 30.0f)
			{
				recorrido1_angel = false;
				recorrido2_angel = true;
			}
			else
			{
				rot_ala1 += 0.1;
			}

		}
		if (recorrido2_angel)
		{
			if (rot_ala1 < 0.0f)
			{
				recorrido2_angel = false;
				recorrido1_angel = true;
			}
			else
			{
				rot_ala1 -= 0.1;
			}

		}

		if (recorrido3_angel)
		{
			if (rot_ala2 < -30.0f)
			{
				recorrido3_angel = false;
				recorrido4_angel = true;
			}
			else
			{
				rot_ala2 -= 0.1;
			}

		}
		if (recorrido4_angel)
		{
			if (rot_ala2 > 0.0f)
			{
				recorrido4_angel = false;
				recorrido3_angel = true;
			}
			else
			{
				rot_ala2 += 0.1;
			}

		}

		if (recorrido5_angel)
		{
			if (rot_brazo_angel < -15.0f)
			{
				recorrido5_angel = false;
				recorrido6_angel = true;
			}
			else
			{
				rot_brazo_angel -= 0.1;
			}

		}

		if (recorrido6_angel)
		{
			if (rot_brazo_angel > 0.0f)
			{
				recorrido6_angel = false;
				recorrido5_angel = true;
			}
			else
			{
				rot_brazo_angel += 0.1;
			}

		}

	}
}






// Is called whenever a key is pressed/released via GLFW
void KeyCallback(GLFWwindow* window, int key, int scancode, int action, int mode)
{
	if (GLFW_KEY_ESCAPE == key && GLFW_PRESS == action)
	{
		glfwSetWindowShouldClose(window, GL_TRUE);
	}

	if (key >= 0 && key < 1024)
	{
		if (action == GLFW_PRESS)
		{
			keys[key] = true;
		}
		else if (action == GLFW_RELEASE)
		{
			keys[key] = false;
		}
	}

	if (keys[GLFW_KEY_V])
	{
		active = !active;
		anim = !anim;
	}

	if (keys[GLFW_KEY_Z])
	{
		active_nieve = !active_nieve;
		anim_nieve = !anim_nieve;
	}


	if (keys[GLFW_KEY_X])
	{
		active_brazo = !active_brazo;
		anim_brazo = !anim_brazo;
	}

	if (keys[GLFW_KEY_C])
	{
		active_angel = !active_angel;
		anim_angel = !anim_angel;
	}
}

void MouseCallback(GLFWwindow* window, double xPos, double yPos)
{
	if (firstMouse)
	{
		lastX = xPos;
		lastY = yPos;
		firstMouse = false;
	}

	GLfloat xOffset = xPos - lastX;
	GLfloat yOffset = lastY - yPos;  // Reversed since y-coordinates go from bottom to left

	lastX = xPos;
	lastY = yPos;

	camera.ProcessMouseMovement(xOffset, yOffset);
}
