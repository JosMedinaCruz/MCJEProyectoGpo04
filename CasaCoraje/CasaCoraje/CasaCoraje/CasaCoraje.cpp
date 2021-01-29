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
void KeyCallback(GLFWwindow* window, int key, int scancode, int action, int mode);
void MouseCallback(GLFWwindow* window, double xPos, double yPos);
void DoMovement();
void animacion();
//Para posicionar la cámara en los diferentes cuartos
void my_input(GLFWwindow* window);

// Window dimensions
const GLuint WIDTH = 800, HEIGHT = 600;
int SCREEN_WIDTH, SCREEN_HEIGHT;

// Camera
Camera  camera(glm::vec3(10.0f, 25.0f, 250.0f));
GLfloat lastX = WIDTH / 2.0;
GLfloat lastY = HEIGHT / 2.0;
bool keys[1024];
bool firstMouse = true;
float range = 0.0f;
float rot = 0.0f;


// Light attributes
glm::vec3 lightPos(0.0f, 0.0f, 0.0f);
glm::vec3 PosIni(-95.0f, 1.0f, -45.0f);
bool active, active2;


// Deltatime
GLfloat deltaTime = 0.0f;	// Time between current frame and last frame
GLfloat lastFrame = 0.0f;  	// Time of last frame

//Animacion pikachu
float movKitX = 0.0;
float movKitY = 0.0;
float rotKit = 0.0;
bool circuito = true;
bool recorrido1 = true;
bool recorrido2 = false;
bool recorrido3 = false;

// Keyframes
float posX = PosIni.x, posY = PosIni.y, posZ = PosIni.z, rotRodIzq = 0, rotRodDer, rotBIzq, rotBDer, rotSilla, rotPikachu;
float movSilla, movMueble, movPikachu;
float rotCompu;


float  rotMascara = 0;
float MposX = 0, MposY = 0, MposZ = 0;

float rotCoraje = 0;
float CposX = 0, CposY = 0, CposZ = 0;

float rotDoor = 0;
float rotMec = 0;
float movPan = 0;

#define MAX_FRAMES 9
int i_max_steps = 100;
int i_curr_steps = 0;
int i_curr_steps2 = 0;
int i_curr_steps3 = 0;
//Animacion 1
typedef struct _frame
{
	//Variables para GUARDAR Key Frames
	float posX;		//Variable para PosicionX
	float posY;		//Variable para PosicionY
	float posZ;		//Variable para PosicionZ
	float incX;		//Variable para IncrementoX
	float incY;		//Variable para IncrementoY
	float incZ;		//Variable para IncrementoZ
	float rotRodIzq;
	float rotRodDer;
	float rotInc;
	float rotInc2;
	float rotBIzq;
	float rotBDer;
	float rotInc3;
	float rotInc4;
	
	float rotMec;
	float rotInc5;

	float rotSilla;
	float inc1;
	float movSilla;
	float inc2;

	float rotPikachu;
	float inc3;
	float movPikachu;
	float inc4;

}FRAME;


//Animacion 2 Mascara
typedef struct _frame2
{
	//Variables para GUARDAR Key Frames
	float posX;		//Variable para PosicionX
	float posY;		//Variable para PosicionY
	float posZ;		//Variable para PosicionZ
	float incX;		//Variable para IncrementoX
	float incY;		//Variable para IncrementoY
	float incZ;		//Variable para IncrementoZ

	float rotInc6, rotMascara;

}FRAME2;

//Animacion 3 Coraje
typedef struct _frame3
{
	//Variables para GUARDAR Key Frames
	float posX;		//Variable para PosicionX
	float posY;		//Variable para PosicionY
	float posZ;		//Variable para PosicionZ
	float incX;		//Variable para IncrementoX
	float incY;		//Variable para IncrementoY
	float incZ;		//Variable para IncrementoZ

	float rotInc7, rotCoraje;

}FRAME3;

FRAME KeyFrame[MAX_FRAMES];
FRAME2 KeyFrame2[MAX_FRAMES];
FRAME3 KeyFrame3[MAX_FRAMES];

int FrameIndex = 7;			//introducir datos
bool play = false;
bool play2 = false; //Animación 2
bool play3 = false;
bool play4 = false; //Puerta
bool play5 = false; //PAntalla

bool play6 = false;
bool play7 = false;
bool play8 = false;
bool play8_1 = false;
bool play9 = false;
bool play9_1 = false;

bool play10 = false;
bool play10_1 = false;

int playIndex = 0;
int playIndex2 = 0;
int playIndex3 = 0;

// Positions of the point lights
glm::vec3 pointLightPositions[] = {
	glm::vec3(25.0,90.0f,-80.0f),
	glm::vec3(1000,1000,1000),
	glm::vec3(1000,1000,1000),
	glm::vec3(1000,1000,1000),
	glm::vec3(-27.0,25.0f,15.0f)//y=15 x=30
//	glm::vec3(35,90.0f,-70.0f)
};

glm::vec3 LightP1;
//Luz para simular encendido de TV
glm::vec3 LightP2;


void resetElements(void)
{
	posX = KeyFrame[0].posX;
	posY = KeyFrame[0].posY;
	posZ = KeyFrame[0].posZ;

	rotRodIzq = KeyFrame[0].rotRodIzq;
	rotRodDer = KeyFrame[0].rotRodDer;

	rotRodIzq = KeyFrame[0].rotBIzq;
	rotRodDer = KeyFrame[0].rotBDer;

	rotMec = KeyFrame[0].rotMec;

	rotSilla = KeyFrame[0].rotSilla;
	movSilla = KeyFrame[0].movSilla;

	rotPikachu = KeyFrame[0].rotPikachu;
	movPikachu = KeyFrame[0].movPikachu;

}

void resetElements2(void)
{
	MposX = KeyFrame2[0].posX;
	MposY = KeyFrame2[0].posY;
	MposZ = KeyFrame2[0].posZ;

	rotMascara = KeyFrame2[0].rotMascara;
}

void resetElements3(void)
{

	rotCoraje = KeyFrame3[0].rotCoraje;
}

void interpolation(void)
{

	KeyFrame[playIndex].incX = (KeyFrame[playIndex + 1].posX - KeyFrame[playIndex].posX) / i_max_steps;
	KeyFrame[playIndex].incY = (KeyFrame[playIndex + 1].posY - KeyFrame[playIndex].posY) / i_max_steps;
	KeyFrame[playIndex].incZ = (KeyFrame[playIndex + 1].posZ - KeyFrame[playIndex].posZ) / i_max_steps;

	KeyFrame[playIndex].rotInc = (KeyFrame[playIndex + 1].rotRodIzq - KeyFrame[playIndex].rotRodIzq) / i_max_steps;
	KeyFrame[playIndex].rotInc2 = (KeyFrame[playIndex + 1].rotRodDer - KeyFrame[playIndex].rotRodDer) / i_max_steps;

	KeyFrame[playIndex].rotInc3 = (KeyFrame[playIndex + 1].rotBIzq - KeyFrame[playIndex].rotBIzq) / i_max_steps;
	KeyFrame[playIndex].rotInc4 = (KeyFrame[playIndex + 1].rotBDer - KeyFrame[playIndex].rotBDer) / i_max_steps;

	//KeyFrame[playIndex].rotInc5 = (KeyFrame[playIndex + 1].rotMec - KeyFrame[playIndex].rotMec) / i_max_steps;
	KeyFrame[playIndex].inc1 = (KeyFrame[playIndex + 1].rotSilla - KeyFrame[playIndex].rotSilla) / i_max_steps;
	KeyFrame[playIndex].inc2 = (KeyFrame[playIndex + 1].movSilla - KeyFrame[playIndex].movSilla) / i_max_steps;
	KeyFrame[playIndex].inc3 = (KeyFrame[playIndex + 1].rotPikachu - KeyFrame[playIndex].rotPikachu) / i_max_steps;
	KeyFrame[playIndex].inc4 = (KeyFrame[playIndex + 1].movPikachu - KeyFrame[playIndex].movPikachu) / i_max_steps;

}


void interpolation2(void)
{

	KeyFrame2[playIndex2].incX = (KeyFrame2[playIndex2 + 1].posX - KeyFrame2[playIndex2].posX) / i_max_steps;
	KeyFrame2[playIndex2].incY = (KeyFrame2[playIndex2 + 1].posY - KeyFrame2[playIndex2].posY) / i_max_steps;
	KeyFrame2[playIndex2].incZ = (KeyFrame2[playIndex2 + 1].posZ - KeyFrame2[playIndex2].posZ) / i_max_steps;

	KeyFrame2[playIndex2].rotInc6 = (KeyFrame2[playIndex2 + 1].rotMascara - KeyFrame2[playIndex2].rotMascara) / i_max_steps;



}

void interpolation3(void)
{

	KeyFrame3[playIndex3].incX = (KeyFrame3[playIndex3 + 1].posX - KeyFrame3[playIndex3].posX) / i_max_steps;
	KeyFrame3[playIndex3].incY = (KeyFrame3[playIndex3 + 1].posY - KeyFrame3[playIndex3].posY) / i_max_steps;
	KeyFrame3[playIndex3].incZ = (KeyFrame3[playIndex3 + 1].posZ - KeyFrame3[playIndex3].posZ) / i_max_steps;

	KeyFrame3[playIndex3].rotInc7 = (KeyFrame3[playIndex3 + 1].rotCoraje - KeyFrame3[playIndex3].rotCoraje) / i_max_steps;
}


int main()
{
	// Init GLFW
	glfwInit();
	// Set all the required options for GLFW
	/*(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
	glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
	glfwWindowHint(GLFW_RESIZABLE, GL_FALSE);*/

	// Create a GLFWwindow object that we can use for GLFW's functions
	GLFWwindow* window = glfwCreateWindow(WIDTH, HEIGHT, "Casa de Coraje el Perro Cobarde", nullptr, nullptr);

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

	Shader lightingShader("Shaders/lighting.vs", "Shaders/lighting.frag");
	Shader lampShader("Shaders/lamp.vs", "Shaders/lamp.frag");
	Shader SkyBoxshader("Shaders/SkyBox.vs", "Shaders/SkyBox.frag");

	Model Casa((char*)"Models/Muebles/casaFinal.obj");
	Model Puerta((char*)"Models/Muebles/puerta.obj");
	Model Mascara((char*)"Models/Muebles/mascara.obj");
	Model Mecedora((char*)"Models/Muebles/mecedora.obj");
	Model Coraje((char*)"Models/Muebles/coraje.obj");
	Model Pantalla((char*)"Models/Muebles/pantalla.obj");

	//Modelos derek
	//Modelos de objetos
	Model Computadora1((char*)"Models/ModelosPokemon/Computadora.obj");
	Model Computadora2((char*)"Models/ModelosPokemon/Computadora1.obj");
	Model Libro((char*)"Models/ModelosPokemon/Libro.obj");
	//Model Mueble1((char*)"Models/ModelosPokemon/MuebleTv.obj");
	//Model Mueble2((char*)"Models/ModelosPokemon/muebleTV1.obj");
	//Model Mueble3((char*)"Models/ModelosPokemon/MuebleTV2.obj");
	Model Pikachu((char*)"Models/ModelosPokemon/Pikachu.obj");
	Model Reloj1((char*)"Models/ModelosPokemon/Reloj.obj");
	Model Reloj2((char*)"Models/ModelosPokemon/Reloj1.obj");
	Model Reloj3((char*)"Models/ModelosPokemon/Reloj2.obj");
	Model Silla1((char*)"Models/ModelosPokemon/Silla.obj");
	Model Silla2((char*)"Models/ModelosPokemon/Silla1.obj");
	Model Switch((char*)"Models/ModelosPokemon/Switch.obj");
	Model Television((char*)"Models/ModelosPokemon/Television.obj");
	Model Cuarto((char*)"Models/ModelosPokemon/Cuarto.obj");

	// Build and compile our shader program

	//Inicialización de KeyFrames

	for (int i = 0; i < MAX_FRAMES; i++)
	{
		KeyFrame[i].posX = 0;
		KeyFrame[i].incX = 0;
		KeyFrame[i].incY = 0;
		KeyFrame[i].incZ = 0;
		KeyFrame[i].rotRodIzq = 0;
		KeyFrame[i].rotRodDer = 0;
		KeyFrame[i].rotInc = 0;
		KeyFrame[i].rotInc2 = 0;
		KeyFrame[i].rotBIzq = 0;
		KeyFrame[i].rotBDer = 0;
		KeyFrame[i].rotInc3 = 0;
		KeyFrame[i].rotInc4 = 0;
		
		KeyFrame[i].rotMec = 0;
		KeyFrame[i].rotInc5 = 0;

		KeyFrame2[i].rotMascara = 0;
		KeyFrame2[i].rotInc6 = 0;

		KeyFrame3[i].rotCoraje = 0;
		KeyFrame3[i].rotInc7 = 0;

		KeyFrame[i].rotSilla = 0;
		KeyFrame[i].inc1 = 0;
		KeyFrame[i].movSilla = 0;
		KeyFrame[i].inc2 = 0;

		KeyFrame[i].rotPikachu = 0;
		KeyFrame[i].inc3 = 0;

	}

	//KeyFrame[0].rotMec = 0;
	//KeyFrame[1].rotMec = 5;
	//KeyFrame[2].rotMec = -5;
	//KeyFrame[3].rotMec = 5;
	//KeyFrame[4].rotMec = -5;

	//Mascara
	KeyFrame2[0].posX = 0;
	KeyFrame2[0].posY = 0;
	KeyFrame2[0].posZ = 0;
	KeyFrame2[0].rotMascara = 0;

	KeyFrame2[1].posX = 2.0;
	KeyFrame2[1].posY = 0;
	KeyFrame2[1].posZ = 0.0;
	KeyFrame2[1].rotMascara = 0;

	KeyFrame2[2].posX = 2.0;
	KeyFrame2[2].posY = 0.0;
	KeyFrame2[2].posZ = 0.0;
	KeyFrame2[2].rotMascara = -90;

	KeyFrame2[3].posX = 2.0;
	KeyFrame2[3].posY = 0.0;
	KeyFrame2[3].posZ = -3.0;
	KeyFrame2[3].rotMascara = -90;

	KeyFrame2[4].posX = 2.0;
	KeyFrame2[4].posY = 1.0;
	KeyFrame2[4].posZ = -3.0;
	KeyFrame2[4].rotMascara = -90;

	KeyFrame2[5].posX = 2.0;
	KeyFrame2[5].posY = 1.0;
	KeyFrame2[5].posZ = -3.0;
	KeyFrame2[5].rotMascara = -180;

	KeyFrame2[6].posX = -0.5;
	KeyFrame2[6].posY = 1.0;
	KeyFrame2[6].posZ = -3.0;
	KeyFrame2[6].rotMascara = 0;

	KeyFrame2[7].posX = 0;
	KeyFrame2[7].posY = 1.0;
	KeyFrame2[7].posZ = 0;
	KeyFrame2[7].rotMascara = 180;

	////Coraje

	KeyFrame3[0].posX = 0;
	KeyFrame3[0].posY = 0;
	KeyFrame3[0].posZ = 0;
	KeyFrame3[0].rotCoraje = 0;

	KeyFrame3[1].posX = 5.0;
	KeyFrame3[1].posY = 0;
	KeyFrame3[1].posZ = 0.0;
	KeyFrame3[1].rotCoraje = 0;

	KeyFrame3[2].posX = 5.0;
	KeyFrame3[2].posY = 0.0;
	KeyFrame3[2].posZ = 0.0;
	KeyFrame3[2].rotCoraje = -90;

	KeyFrame3[3].posX = 5.0;
	KeyFrame3[3].posY = 0.0;
	KeyFrame3[3].posZ = -6.0;
	KeyFrame3[3].rotCoraje = -90;

	KeyFrame3[4].posX = 26.0;
	KeyFrame3[4].posY = 0.0;
	KeyFrame3[4].posZ = -6.0;
	KeyFrame3[4].rotCoraje = -90;

	KeyFrame3[5].posX = 26.0;
	KeyFrame3[5].posY = 0.0;
	KeyFrame3[5].posZ = -6.0;
	KeyFrame3[5].rotCoraje = 45;

	KeyFrame3[6].posX = 26.0;
	KeyFrame3[6].posY = 0.0;
	KeyFrame3[6].posZ = 6.0;
	KeyFrame3[6].rotCoraje = 45;

	//Silla
	KeyFrame[0].rotSilla = 0;
	KeyFrame[1].rotSilla = 360;
	KeyFrame[0].movSilla = 0;
	KeyFrame[1].movSilla = 3.5;
	//Pikachu
	KeyFrame[0].rotPikachu = 0;
	KeyFrame[1].rotPikachu = 360;

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
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(GLfloat), (GLvoid*)0);
	glEnableVertexAttribArray(0);
	// Normals attribute
	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(GLfloat), (GLvoid*)(3 * sizeof(GLfloat)));
	glEnableVertexAttribArray(1);
	// Texture Coordinate attribute
	glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, 8 * sizeof(GLfloat), (GLvoid*)(6 * sizeof(GLfloat)));
	glEnableVertexAttribArray(2);
	glBindVertexArray(0);

	// Then, we set the light's VAO (VBO stays the same. After all, the vertices are the same for the light object (also a 3D cube))
	GLuint lightVAO;
	glGenVertexArrays(1, &lightVAO);
	glBindVertexArray(lightVAO);
	// We only need to bind to the VBO (to link it with glVertexAttribPointer), no need to fill it; the VBO's data already contains all we need.
	glBindBuffer(GL_ARRAY_BUFFER, VBO);
	// Set the vertex attributes (only position data for the lamp))
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(GLfloat), (GLvoid*)0); // Note that we skip over the other data in our buffer object (we don't need the normals/textures, only positions).
	glEnableVertexAttribArray(0);
	glBindVertexArray(0);


	//SkyBox
	GLuint skyboxVBO, skyboxVAO;
	glGenVertexArrays(1, &skyboxVAO);
	glGenBuffers(1, &skyboxVBO);
	glBindVertexArray(skyboxVAO);
	glBindBuffer(GL_ARRAY_BUFFER, skyboxVBO);
	glBufferData(GL_ARRAY_BUFFER, sizeof(skyboxVertices), &skyboxVertices, GL_STATIC_DRAW);
	glEnableVertexAttribArray(0);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(GLfloat), (GLvoid*)0);

	// Load textures
	vector<const GLchar*> faces;
	faces.push_back("SkyBox/right.tga");
	faces.push_back("SkyBox/left.tga");
	faces.push_back("SkyBox/top.tga");
	faces.push_back("SkyBox/bottom.tga");
	faces.push_back("SkyBox/back.tga");
	faces.push_back("SkyBox/front.tga");

	GLuint cubemapTexture = TextureLoading::LoadCubemap(faces);

	GLuint texture3, texture4;
	glGenTextures(1, &texture3);
	glGenTextures(1, &texture4);

	int textureWidth2, textureHeight2, nrChannels2;
	stbi_set_flip_vertically_on_load(true);
	unsigned char* image2;
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST_MIPMAP_NEAREST);
	// Diffuse map
	image2 = stbi_load("images/madera.jpg", &textureWidth2, &textureHeight2, &nrChannels2, 0);
	glBindTexture(GL_TEXTURE_2D, texture3);
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, textureWidth2, textureHeight2, 0, GL_RGB, GL_UNSIGNED_BYTE, image2);
	glGenerateMipmap(GL_TEXTURE_2D);
	if (image2)
	{
		glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, textureWidth2, textureHeight2, 0, GL_RGB, GL_UNSIGNED_BYTE, image2);
		glGenerateMipmap(GL_TEXTURE_2D);
	}
	else
	{
		std::cout << "Failed to load texture" << std::endl;
	}
	stbi_image_free(image2);

	// Specular map
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST_MIPMAP_NEAREST);
	image2 = stbi_load("images/madera.jpg", &textureWidth2, &textureHeight2, &nrChannels2, 0);
	glBindTexture(GL_TEXTURE_2D, texture4);
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, textureWidth2, textureHeight2, 0, GL_RGB, GL_UNSIGNED_BYTE, image2);
	glGenerateMipmap(GL_TEXTURE_2D);
	if (image2)
	{
		glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, textureWidth2, textureHeight2, 0, GL_RGB, GL_UNSIGNED_BYTE, image2);
		glGenerateMipmap(GL_TEXTURE_2D);
	}
	else
	{
		std::cout << "Failed to load texture" << std::endl;
	}
	stbi_image_free(image2);

	glBindTexture(GL_TEXTURE_2D, 0);

	//Set textures units
	lightingShader.Use();
	glUniform1i(glGetUniformLocation(lightingShader.Program, "text3"),2);
	glUniform1i(glGetUniformLocation(lightingShader.Program, "text4"), 3);


	////--------------------------------------
	glm::mat4 projection = glm::perspective(camera.GetZoom(), (GLfloat)SCREEN_WIDTH / (GLfloat)SCREEN_HEIGHT, 0.1f, 10000.0f);

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
		// == ==========================
		// Here we set all the uniforms for the 5/6 types of lights we have. We have to set them manually and index
		// the proper PointLight struct in the array to set each uniform variable. This can be done more code-friendly
		// by defining light types as classes and set their values in there, or by using a more efficient uniform approach
		// by using 'Uniform buffer objects', but that is something we discuss in the 'Advanced GLSL' tutorial.
		// == ==========================
		// Directional light
		glUniform3f(glGetUniformLocation(lightingShader.Program, "dirLight.direction"), -0.2f, -1.0f, -0.3f);
		glUniform3f(glGetUniformLocation(lightingShader.Program, "dirLight.ambient"), 0.913f, 0.733f, 0.486f); //0.878f, 0.549f, 0.101f
		glUniform3f(glGetUniformLocation(lightingShader.Program, "dirLight.diffuse"), 0.4f, 0.4f, 0.4f);
		glUniform3f(glGetUniformLocation(lightingShader.Program, "dirLight.specular"), 0.5f, 0.5f, 0.5f);


		// Point light 1
		glUniform3f(glGetUniformLocation(lightingShader.Program, "pointLights[0].position"), pointLightPositions[0].x, pointLightPositions[0].y, pointLightPositions[0].z);
		glUniform3f(glGetUniformLocation(lightingShader.Program, "pointLights[0].ambient"), 0.05f, 0.05f, 0.05f);
		glUniform3f(glGetUniformLocation(lightingShader.Program, "pointLights[0].diffuse"), LightP1.x, LightP1.y, LightP1.z);
		glUniform3f(glGetUniformLocation(lightingShader.Program, "pointLights[0].specular"), LightP1.x, LightP1.y, LightP1.z);
		glUniform1f(glGetUniformLocation(lightingShader.Program, "pointLights[0].constant"), 1.0f);
		glUniform1f(glGetUniformLocation(lightingShader.Program, "pointLights[0].linear"), 0.09f);
		glUniform1f(glGetUniformLocation(lightingShader.Program, "pointLights[0].quadratic"), 0.032f);

		// Point light 2
		glUniform3f(glGetUniformLocation(lightingShader.Program, "pointLights[1].position"), pointLightPositions[1].x, pointLightPositions[1].y, pointLightPositions[1].z);
		glUniform3f(glGetUniformLocation(lightingShader.Program, "pointLights[1].ambient"), 0.05f, 0.05f, 0.05f);
		glUniform3f(glGetUniformLocation(lightingShader.Program, "pointLights[1].diffuse"), 1.0f, 1.0f, 0.0f);
		glUniform3f(glGetUniformLocation(lightingShader.Program, "pointLights[1].specular"), 1.0f, 1.0f, 0.0f);
		glUniform1f(glGetUniformLocation(lightingShader.Program, "pointLights[1].constant"), 1.0f);
		glUniform1f(glGetUniformLocation(lightingShader.Program, "pointLights[1].linear"), 0.09f);
		glUniform1f(glGetUniformLocation(lightingShader.Program, "pointLights[1].quadratic"), 0.032f);

		// Point light 3
		glUniform3f(glGetUniformLocation(lightingShader.Program, "pointLights[2].position"), pointLightPositions[2].x, pointLightPositions[2].y, pointLightPositions[2].z);
		glUniform3f(glGetUniformLocation(lightingShader.Program, "pointLights[2].ambient"), 0.05f, 0.05f, 0.05f);
		glUniform3f(glGetUniformLocation(lightingShader.Program, "pointLights[2].diffuse"), 0.0f, 1.0f, 1.0f);
		glUniform3f(glGetUniformLocation(lightingShader.Program, "pointLights[2].specular"), 0.0f, 1.0f, 1.0f);
		glUniform1f(glGetUniformLocation(lightingShader.Program, "pointLights[2].constant"), 1.0f);
		glUniform1f(glGetUniformLocation(lightingShader.Program, "pointLights[2].linear"), 0.09f);
		glUniform1f(glGetUniformLocation(lightingShader.Program, "pointLights[2].quadratic"), 0.032f);

		// Point light 4
		glUniform3f(glGetUniformLocation(lightingShader.Program, "pointLights[3].position"), pointLightPositions[3].x, pointLightPositions[3].y, pointLightPositions[3].z);
		glUniform3f(glGetUniformLocation(lightingShader.Program, "pointLights[3].ambient"), 0.05f, 0.05f, 0.05f);
		glUniform3f(glGetUniformLocation(lightingShader.Program, "pointLights[3].diffuse"), 1.0f, 0.0f, 1.0f);
		glUniform3f(glGetUniformLocation(lightingShader.Program, "pointLights[3].specular"), 1.0f, 0.0f, 1.0f);
		glUniform1f(glGetUniformLocation(lightingShader.Program, "pointLights[3].constant"), 1.0f);
		glUniform1f(glGetUniformLocation(lightingShader.Program, "pointLights[3].linear"), 0.09f);
		glUniform1f(glGetUniformLocation(lightingShader.Program, "pointLights[3].quadratic"), 0.032f);

		// SpotLight
		glUniform3f(glGetUniformLocation(lightingShader.Program, "spotLight.position"), pointLightPositions[4].x, pointLightPositions[4].y, pointLightPositions[4].z);
		//glUniform3f(glGetUniformLocation(lightingShader.Program, "spotLight.direction"), camera.GetFront().x, camera.GetFront().y, camera.GetFront().z);
		glUniform3f(glGetUniformLocation(lightingShader.Program, "spotLight.direction"), 100.0, 8.0f, 0.0f); //-100 en x
		glUniform3f(glGetUniformLocation(lightingShader.Program, "spotLight.ambient"), 0.0f, 1.0f, 0.0f);
		glUniform3f(glGetUniformLocation(lightingShader.Program, "spotLight.diffuse"), LightP2.x, LightP2.y, LightP2.z);
		glUniform3f(glGetUniformLocation(lightingShader.Program, "spotLight.specular"), LightP2.x, LightP2.y, LightP2.z);
		glUniform1f(glGetUniformLocation(lightingShader.Program, "spotLight.constant"), 1.0f);
		glUniform1f(glGetUniformLocation(lightingShader.Program, "spotLight.linear"), 0.01f);
		glUniform1f(glGetUniformLocation(lightingShader.Program, "spotLight.quadratic"), 0.35);
		glUniform1f(glGetUniformLocation(lightingShader.Program, "spotLight.cutOff"), glm::cos(glm::radians(2.0f)));
		//glUniform1f(glGetUniformLocation(lightingShader.Program, "spotLight.outerCutOff"), glm::cos(glm::radians(12.0f)));

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

		 //Bind diffuse map
		glBindTexture(GL_TEXTURE_2D, texture3);

		 //Bind specular map
		glActiveTexture(GL_TEXTURE0);
		glBindTexture(GL_TEXTURE_2D, texture4);


		glBindVertexArray(VAO);
		glm::mat4 tmp = glm::mat4(1.0f); //Temp
		glm::mat4 model(1);
		
		//_______________________________________________________
		//Cuerpo del mazo
		model = glm::mat4(1.0f);
		model = glm::scale(model, glm::vec3(8.0f, 5.0, 6.0));
		model = glm::translate(model, glm::vec3(7.5f, 4.0, 0.0f));
		glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model));
		glDrawArrays(GL_TRIANGLES, 0, 36);

		//Mango del mazo
		model = glm::mat4(1.0f);
		model = glm::scale(model, glm::vec3(2.0f, 2.0, 8.0));
		model = glm::translate(model, glm::vec3(30.0f, 10.0, 0.8f));
		model = glm::rotate(model, glm::radians(180.0f), glm::vec3(0.0f, 1.0f, 0.0f));
		glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model));
		glDrawArrays(GL_TRIANGLES, 0, 36);

		//Bind difuuse map
		glBindTexture(GL_TEXTURE_2D, texture3);

		//Bind specular map
		glActiveTexture(GL_TEXTURE0);
		glBindTexture(GL_TEXTURE_2D, texture4);

		glBindVertexArray(VAO);

		glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model));
		glDrawArrays(GL_TRIANGLES, 0, 6);

		//______________________________________

		//Casa
		view = camera.GetViewMatrix();
		model = glm::mat4(1);
		model = glm::scale(model, glm::vec3(20.0f, 20.0f, 20.0f));
		/*model = glm::translate(model, glm::vec3(posX, posY, posZ));
		model = glm::rotate(model, glm::radians(rot), glm::vec3(0.0f, 1.0f, 0.0));*/
		model = glm::translate(model, glm::vec3(0.0f, 0.0f, 0.0f));
		glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model));
		Casa.Draw(lightingShader);

		//Pantalla
		view = camera.GetViewMatrix();
		model = glm::mat4(1);
		model = glm::scale(model, glm::vec3(20.0f, 20.0f, 20.0f));
		/*model = glm::translate(model, glm::vec3(posX, posY, posZ));
		model = glm::rotate(model, glm::radians(rot), glm::vec3(0.0f, 1.0f, 0.0));*/
		model = glm::translate(model, glm::vec3(0.0f, 0.0f, 0.0f));
		model = glm::translate(model, glm::vec3(movPan, 0.0f, 0.0f));
		glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model));
		Pantalla.Draw(lightingShader);

		//Puerta
		view = camera.GetViewMatrix();
		model = glm::mat4(1);
		model = glm::scale(model, glm::vec3(20.0f, 20.0f, 20.0f));
		/*model = glm::translate(model, glm::vec3(posX, posY, posZ));
		model = glm::rotate(model, glm::radians(rot), glm::vec3(0.0f, 1.0f, 0.0));*/
		model = glm::translate(model, glm::vec3(0.9f, 0.0f, 3.25f));
		model = glm::rotate(model, glm::radians(rotDoor), glm::vec3(0.0f, 1.0f, 0.0f));
		glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model));
		Puerta.Draw(lightingShader);

		//Mecedora
		view = camera.GetViewMatrix();
		model = glm::mat4(1);
		model = glm::scale(model, glm::vec3(20.0f, 20.0f, 20.0f));
		//model = glm::scale(model, glm::vec3(0.1f, 0.1f, 0.1f));
		model = glm::translate(model, glm::vec3(1.2f, 0.01f, -0.5f));
		model = glm::rotate(model, glm::radians(5.0f), glm::vec3(0.0f, 0.0f, 1.0f));
		//model = glm::rotate(model, glm::radians(10.0f), glm::vec3(0.0f, 1.0f, 0.0));
		model = glm::rotate(model, glm::radians(rotMec), glm::vec3(0.0f, 0.0f, 1.0f));
		glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model));
		Mecedora.Draw(lightingShader);

		//Máscara
		view = camera.GetViewMatrix();
		model = glm::mat4(1);
		tmp = model = glm::scale(model, glm::vec3(12.0f, 12.0f, 12.0f));
		model = glm::translate(model, glm::vec3(-1.8, 2, 3));
		model = glm::translate(model, glm::vec3(MposX, MposY, MposZ));

		model = glm::rotate(model, glm::radians(-rotMascara), glm::vec3(0.0f, 1.0f, 0.0f));

		glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model));
		Mascara.Draw(lightingShader);

		//Coraje
		view = camera.GetViewMatrix();
		model = glm::mat4(1);
		model = glm::scale(model, glm::vec3(2.0f, 2.0f, 2.0f));
		model = glm::translate(model, glm::vec3(-3.0f, 12.0f, -9.0f));
		
		model = glm::translate(model, glm::vec3(CposX, CposY, CposZ));
		model = glm::rotate(model, glm::radians(-rotCoraje), glm::vec3(0.0f, 1.0f, 0.0f));

		glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model));
		Coraje.Draw(lightingShader);
		
		// MODELOS DEREK

		//Television
		view = camera.GetViewMatrix();
		model = glm::mat4(1);
		model = glm::scale(model, glm::vec3(5.0f, 5.0f, 5.0f));
		model = glm::translate(model, glm::vec3(-5.54f, 16.0f, -8.30f));
		model = glm::scale(model, glm::vec3(1.0f, 1.83f, 1.57f));
		glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model));
		Television.Draw(lightingShader);
		//Libro
		view = camera.GetViewMatrix();
		model = glm::mat4(1);
		model = glm::scale(model, glm::vec3(5.0f, 5.0f, 5.0f));
		//tmp = model = glm::translate(model, glm::vec3(0, 1, 0));
		model = glm::translate(model, glm::vec3(2.0f, 15.8f, 8.0f));
		glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model));
		Libro.Draw(lightingShader);
		//Computadora (1)
		view = camera.GetViewMatrix();
		model = glm::mat4(1);
		model = glm::scale(model, glm::vec3(5.0f, 5.0f, 5.0f));
		//tmp = model = glm::translate(model, glm::vec3(0, 1, 0));
		model = glm::translate(model, glm::vec3(-0.0f, 17.8f, 10.0f));
		model = glm::rotate(model, glm::radians(155.0f), glm::vec3(0.0f, 1.0f, 0.0f));
		glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model));
		Computadora1.Draw(lightingShader);
		//Computadora (2)
		view = camera.GetViewMatrix();
		model = glm::translate(model, glm::vec3(-0.0f, 0.0f, -0.3f));
		model = glm::rotate(model, glm::radians(rotCompu), glm::vec3(1.0f, 0.0f, 0.0f));
		glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model));
		Computadora2.Draw(lightingShader);
		//Pikachu
		view = camera.GetViewMatrix();
		model = glm::mat4(1);
		model = glm::scale(model, glm::vec3(5.0f, 5.0f, 5.0f));
		//tmp = model = glm::translate(model, glm::vec3(0, 1, 0));
		model = glm::translate(model, glm::vec3(movKitX, movKitY, 0));
		model = glm::translate(model, glm::vec3(-5.5f, 17.0f, 1.7f));
		model = glm::rotate(model, glm::radians(rotPikachu), glm::vec3(0.0f, 0.0f, 1.0f));
		model = glm::translate(model, glm::vec3(0, 0, -movPikachu));
		glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model));
		Pikachu.Draw(lightingShader);
		//Switch
		view = camera.GetViewMatrix();
		model = glm::mat4(1);
		model = glm::scale(model, glm::vec3(5.0f, 5.0f, 5.0f));
		//tmp = model = glm::translate(model, glm::vec3(0, 1, 0));
		model = glm::translate(model, glm::vec3(-5.51f, 16.5f, -2.7f));
		glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model));
		Switch.Draw(lightingShader);
		//Silla (1)
		view = camera.GetViewMatrix();
		model = glm::mat4(1);
		model = glm::scale(model, glm::vec3(5.0f, 5.0f, 5.0f));
		model = glm::translate(model, glm::vec3(-0.322f, 16.0f, 8.55f));
		model = glm::translate(model, glm::vec3(movSilla, 0, 0));
		model = glm::rotate(model, glm::radians(-rotSilla), glm::vec3(0.0f, 1.0f, 0.0f));
		model = glm::scale(model, glm::vec3(1.5f, 2.5f, 1.5f));
		glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model));
		Silla1.Draw(lightingShader);
		//Silla (2)
		view = camera.GetViewMatrix();
		model = glm::mat4(1);
		model = glm::scale(model, glm::vec3(5.0f, 5.0f, 5.0f));
		//tmp = model = glm::translate(model, glm::vec3(0, 1, 0));
		model = glm::translate(model, glm::vec3(-0.322f, 16.0f, 8.55f));
		model = glm::translate(model, glm::vec3(movSilla, 0, 0));
		model = glm::scale(model, glm::vec3(1.5f, 2.5f, 1.5f));
		glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model));
		Silla2.Draw(lightingShader);
		//Reloj (1)
		view = camera.GetViewMatrix();
		model = glm::mat4(1);
		model = glm::scale(model, glm::vec3(5.0f, 5.0f, 5.0f));
		//tmp = model = glm::translate(model, glm::vec3(0, 1, 0));
		model = glm::translate(model, glm::vec3(2.0f, 23.4f, 3.47f));
		model = glm::rotate(model, glm::radians(90.0f), glm::vec3(0.0f, 0.0f, -1.0f));
		model = glm::translate(model, glm::vec3(0.0f, 0.0f, 7.8f));
		model = glm::rotate(model, glm::radians(90.0f), glm::vec3(-1.0f, 0.0f, 0.0f));
		glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model));
		Reloj1.Draw(lightingShader);
		//Reloj (2)
		view = camera.GetViewMatrix();
		//tmp = model = glm::translate(model, glm::vec3(0, 1, 0));
		model = glm::rotate(model, -(float)glfwGetTime(), glm::vec3(0.0f, 1.0f, 0.0f));
		glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model));
		Reloj3.Draw(lightingShader);
		//Reloj (3)
		view = camera.GetViewMatrix();
		//tmp = model = glm::translate(model, glm::vec3(0, 1, 0));
		model = glm::rotate(model, -(float)glfwGetTime() / 50, glm::vec3(0.0f, 1.0f, 0.0f));
		glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model));
		Reloj2.Draw(lightingShader);
		//Resto del cuarto
		view = camera.GetViewMatrix();
		model = glm::mat4(1);
		model = glm::scale(model, glm::vec3(5.0f, 5.0f, 5.0f));
		//tmp = model = glm::translate(model, glm::vec3(0, 1, 0));
		model = glm::translate(model, glm::vec3(0.0f,16.0f,0.0f));
		glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model));
		Cuarto.Draw(lightingShader);

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
		//model = glm::scale(model, glm::vec3(20.0f)); // Make it a smaller cube
		glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model));
		// Draw the light object (using light's vertex attributes)
		glBindVertexArray(lightVAO);
		for (GLuint i = 0; i < 4; i++)
		{
			model = glm::mat4(1);
			model = glm::translate(model, pointLightPositions[i]);
			model = glm::scale(model, glm::vec3(2.0f));
			model = glm::translate(model, glm::vec3(12.5f,35.5f,-43.0f));
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
	if (play6)
	{
		if (i_curr_steps >= i_max_steps) //end of animation between frames?
		{
			playIndex++;
			if (playIndex > FrameIndex - 2)	//end of total animation?
			{
				playIndex = 0;
				play6 = false;
			}
			else //Next frame interpolations
			{
				i_curr_steps = 0; //Reset counter
								  //Interpolation
				interpolation();
			}
		}
		else
		{
			//Draw animation
			posX += KeyFrame[playIndex].incX;
			posY += KeyFrame[playIndex].incY;
			posZ += KeyFrame[playIndex].incZ;

			rotSilla += KeyFrame[playIndex].inc1;
			movSilla += KeyFrame[playIndex].inc2;
			i_curr_steps++;
		}

	}
	if (play7)
	{
		if (i_curr_steps >= i_max_steps) //end of animation between frames?
		{
			playIndex++;
			if (playIndex > FrameIndex - 2)	//end of total animation?
			{
				playIndex = 0;
				play7 = false;
			}
			else //Next frame interpolations
			{
				i_curr_steps = 0; //Reset counter
								  //Interpolation
				interpolation2();
			}
		}
		else
		{
			//Draw animation
			posX += KeyFrame[playIndex].incX;
			posY += KeyFrame[playIndex].incY;
			posZ += KeyFrame[playIndex].incZ;
			rotPikachu += KeyFrame[playIndex].inc3;
			movPikachu += KeyFrame[playIndex].inc4;
			i_curr_steps++;
		}
	}
	else if (play9) {
		if (rotCompu > 45.0) {
			play9 = false;
		}
		else {
			rotCompu += 0.45f;
		}
	}
	else if (play9_1) {
		if (rotCompu < 0.0) {
			play9_1 = false;
		}
		else {
			rotCompu -= 0.45f;
		}
	}
	if (circuito)
	{
		if (recorrido1)
		{
			movKitY += 0.03f;
			if (movKitY > 2.5)
			{
				recorrido1 = false;
				recorrido2 = true;
			}
		}
		if (recorrido2)
		{
			rotKit = 0;
			movKitY -= 0.015f;
			if (movKitY < 0)
			{
				recorrido2 = false;
				recorrido3 = true;

			}
		}
		if (recorrido3)
		{
			rotKit = 0;
			movKitY += 0.03f;
			if (movKitY > 2.5)
			{
				recorrido3 = false;
				recorrido1 = true;
			}
		}
	}
	if (play4)
	{
		if (rotDoor > -90.0f) {
			rotDoor -= 1.0f;
		}
		
		else {
			if (rotDoor <= 90.0f) {
				rotDoor += 1.0f;
			}
			play4 = false;
		}
	}
	//Movimiento de la mecedora
	if (play)
	{
		if (rotMec > -10.0f) {
			rotMec -= 0.1f;
		}
		else {
			play = false;
		}
		
	}
	//Pantalla
	/*if (play5)
	{
		if (movPan < 0.07f) {
			movPan += 0.01f;
		}
		else {
			play5 = false;
		}

	}*/


	else if (play10) {
		if (movPan > 0.07f) {
			play10 = false;
		}
		else {
			movPan += 0.01f;
		}
	}
	else if (play10_1) {
		if (movPan < 0.0f) {
			play10_1 = false;
		}
		else {
			movPan -= 0.01f;
		}
	}


	if (play2)
	{
		if (i_curr_steps2 >= i_max_steps) //end of animation between frames?
		{
			playIndex2++;
			if (playIndex2 > FrameIndex - 2)	//end of total animation?
			{
				printf("Animacion de la mascara\n");
				playIndex2 = 0;
				play2 = false;
			}
			else //Next frame interpolations
			{
				i_curr_steps2 = 0; //Reset counter
								  //Interpolation
				interpolation2();
			}
		}
		else
		{
			//Draw animation
			MposX += KeyFrame2[playIndex2].incX;
			MposY += KeyFrame2[playIndex2].incY;
			MposZ += KeyFrame2[playIndex2].incZ;

			rotMascara += KeyFrame2[playIndex2].rotInc6;

			i_curr_steps2++;
		}

	}


	if (play3)
	{
		if (i_curr_steps3 >= i_max_steps) //end of animation between frames?
		{
			playIndex3++;
			if (playIndex3 > FrameIndex - 2)	//end of total animation?
			{
				printf("Animacion de Coraje\n");
				playIndex3 = 0;
				play3 = false;
			}
			else //Next frame interpolations
			{
				i_curr_steps3 = 0; //Reset counter
								  //Interpolation
				interpolation3();
			}
		}
		else
		{
			//Draw animation
			CposX += KeyFrame3[playIndex3].incX;
			CposY += KeyFrame3[playIndex3].incY;
			CposZ += KeyFrame3[playIndex3].incZ;

			rotCoraje += KeyFrame3[playIndex3].rotInc7;

			i_curr_steps3++;
		}


	}
}

// Is called whenever a key is pressed/released via GLFW
void KeyCallback(GLFWwindow* window, int key, int scancode, int action, int mode)
{

	if (keys[GLFW_KEY_1])
	{
		if (play4 == false)
		{
			rotDoor = 0.0f;
			play4 = true;
		}

	}

	if (keys[GLFW_KEY_2] && (FrameIndex > 1))
	{
		if (play2 == false )
		{
			MposX = 0;
			MposY = 0;
			MposZ = 0;
			rotMascara = 0;

			resetElements2();
			//First Interpolation				
			interpolation2();

			play2 = true;
			playIndex2 = 0;
			i_curr_steps2 = 0;
		}
		else
		{
			play2 = false;
		}
	}


	if (keys[GLFW_KEY_4])
	{
		if (play == false)
		{
			rotMec = 0.0f;
			play = true;
		}

	}


	if (keys[GLFW_KEY_3] && (FrameIndex > 1))
	{
		if (play3 == false)
		{
			CposX = 0;
			CposY = 0;
			CposZ = 0;
			rotCoraje = 0;

			resetElements3();
			//First Interpolation				
			interpolation3();

			play3 = true;
			playIndex3 = 0;
			i_curr_steps3 = 0;
		}
		else
		{
			play3 = false;
		}
	}

	/*if (keys[GLFW_KEY_5])
	{
		if (play5 == false)
		{
			movPan = 0.0f;
			play5 = true;
		}

	}*/

	/*if (keys[GLFW_KEY_5])
	{
		if (play10 == false)
		{
			movPan = 0.0f;
			play10 = true;
		}

	}*/

	if (keys[GLFW_KEY_L])
	{
		if (play6 == false)
		{

			resetElements();
			//First Interpolation				
			interpolation();

			play6 = true;
			playIndex = 0;
			i_curr_steps = 0;
		}
		else
		{
			play6 = false;
		}
	}
	if (keys[GLFW_KEY_K])
	{
		if (play7 == false)
		{
			resetElements();
			//First Interpolation				
			interpolation2();
			play7 = true;
			playIndex = 0;
			i_curr_steps = 0;
		}
		else
		{
			play7 = false;
		}

	}

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

	if (keys[GLFW_KEY_SPACE])
	{
		active = !active;
		if (active)
			LightP1 = glm::vec3(25.0f, 25.0f, 15.0f);
		else
			LightP1 = glm::vec3(0.0f, 0.0f, 0.0f);
	}

	//if (keys[GLFW_KEY_M])
	//{
	//	active2 = !active2;
	//	if (active2)
	//		LightP2 = glm::vec3(25.0f, 59.0f, 215.0f);
	//	else
	//		LightP2 = glm::vec3(0.0f, 0.0f, 0.0f);
	//}
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

	if (keys[GLFW_KEY_8] == GLFW_PRESS)
	{
		camera.position.x = 10.0f;
		camera.position.y = 100.0f;
		camera.position.z = 50.0f;
	}

	if (keys[GLFW_KEY_9] == GLFW_PRESS)
	{
		camera.position.x = 10.0f;
		camera.position.y = 40.0f;
		camera.position.z = 50.0f;
	}

	//if (glfwGetKey(window, GLFW_KEY_8) == GLFW_PRESS) {
	//	camera.position.x = 10.0f;
	//	camera.position.y = 25.0f;
	//	camera.position.z = 250.0f;

	//}
}

// Moves/alters the camera positions based on user input
void DoMovement()
{

	if (keys[GLFW_KEY_I])
	{
		circuito = true;
	}

	if (keys[GLFW_KEY_O])
	{
		movKitY = 0;
		circuito = false;
	}
	if (keys[GLFW_KEY_C])
	{
		play9 = !play9;

	}
	if (keys[GLFW_KEY_V])
	{
		play9_1 = !play9_1;

	}
	//TV encendido y apagado-------------------------
	if (keys[GLFW_KEY_N])
	{
		play10 = !play10;
		active2 = !active2;
		if (active2)
			LightP2 = glm::vec3(25.0f, 59.0f, 215.0f);

	}
	if (keys[GLFW_KEY_M])
	{
		play10_1 = !play10_1;
		active2 = !active2;
		if (active2)
			LightP2 = glm::vec3(0.0f, 0.0f, 0.0f);

	}
	//---------------------------------------------
	//Mov Personaje
	if (keys[GLFW_KEY_H]){
		posZ += 1;
	}

	if (keys[GLFW_KEY_Y]){
		posZ -= 1;
	}

	if (keys[GLFW_KEY_G]){
		posX -= 1;
	}

	if (keys[GLFW_KEY_J]){
		posX += 1;
	}

	// Camera controls
	if (keys[GLFW_KEY_W] || keys[GLFW_KEY_UP])
	{
		camera.ProcessKeyboard(FORWARD, deltaTime + 0.5f);
	}

	if (keys[GLFW_KEY_S] || keys[GLFW_KEY_DOWN])
	{
		camera.ProcessKeyboard(BACKWARD, deltaTime + 0.5f);
	}

	if (keys[GLFW_KEY_A] || keys[GLFW_KEY_LEFT])
	{
		camera.ProcessKeyboard(LEFT, deltaTime + 0.5f);
	}

	if (keys[GLFW_KEY_D] || keys[GLFW_KEY_RIGHT])
	{
		camera.ProcessKeyboard(RIGHT, deltaTime + 0.5f);
	}


}

//void my_input(GLFWwindow* window)
//{
//	/*if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
//		glfwSetWindowShouldClose(window, true);*/
//
//	
//	if (glfwGetKey(window, GLFW_KEY_8) == GLFW_PRESS) {
//		camera.position.x = 10.0f;
//		camera.position.y = 25.0f;
//		camera.position.z = 250.0f;
//
//	}
//
//
//}