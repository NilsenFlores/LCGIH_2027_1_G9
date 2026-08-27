#include<iostream>

//#define GLEW_STATIC

#include <GL/glew.h> 

#include <GLFW/glfw3.h>

// Shaders
#include "Shader.h" //ahora ya tiene el shader 

void resize(GLFWwindow* window, int width, int height);

const GLint WIDTH = 800, HEIGHT = 600;


int main() {
	glfwInit();
	//Verificaci�n de compatibilidad 
	/*glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_COMPAT_PROFILE);
	glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
	glfwWindowHint(GLFW_RESIZABLE, GL_FALSE);*/

	GLFWwindow *window = glfwCreateWindow(WIDTH, HEIGHT, "Dibujo de Primitivas en 2D", NULL, NULL); //generacion de la ventana
	glfwSetFramebufferSizeCallback(window, resize);
	
	//Verificaci�n de errores de creacion  ventana
	if (window== NULL) 
	{
		std::cout << "Failed to create GLFW window" << std::endl;
		glfwTerminate();

		return EXIT_FAILURE;
	}

	glfwMakeContextCurrent(window);
	glewExperimental = GL_TRUE;

	//Verificaci�n de errores de inicializaci�n de glew

	if (GLEW_OK != glewInit()) {
		std::cout << "Failed to initialise GLEW" << std::endl;
		return EXIT_FAILURE;
	}

	// Imprimimos informacin de OpenGL del sistema
	std::cout << "> Version: " << glGetString(GL_VERSION) << std::endl;
	std::cout << "> Vendor: " << glGetString(GL_VENDOR) << std::endl;
	std::cout << "> Renderer: " << glGetString(GL_RENDERER) << std::endl;
	std::cout << "> SL Version: " << glGetString(GL_SHADING_LANGUAGE_VERSION) << std::endl;


	// Define las dimensiones del viewport
	//glViewport(0, 0, screenWidth, screenHeight);

    Shader ourShader("Shader/core.vs", "Shader/core.frag"); //aqui se llaman los shader de los archivo frag y vs

	// Set up vertex data (and buffer(s)) and attribute pointers
	float vertices[] = { //puntos donde se van colocando (6 elemtnos cada vertice (3 de posicion y 3 de color definidos en core.vs)
		0.5f,  0.5f, 0.0f,    1.0f,0.0f,0.0f,  // top right
		0.5f, -0.5f, 0.0f,    1.0f,1.0f,0.0f,  // bottom right
		-0.5f, -0.5f, 0.0f,   1.0f,0.0f,1.0f,  // bottom left
		-0.5f,  0.5f, 0.0f,   1.0f,1.0f,0.0f, // top left 
	};
	unsigned int indices[] = {  // note that we start from 0!  //orden en el que se va a dibujar un triangulo
		3,0,1, //primer triangulo
		3,0,2, //segundo triangulo mio xd
		2,1,0, //complemento del cuaddrado con el anterior
		3,2,1,// second Triangle
		0,1,3,
		
	};



	GLuint VBO, VAO,EBO;
	glGenVertexArrays(1, &VAO);
	glGenBuffers(1, &VBO);
	glGenBuffers(1, &EBO);

	// Enlazar  Vertex Array Object
	glBindVertexArray(VAO);

	//2.- Copiamos nuestros arreglo de vertices en un buffer de vertices para que OpenGL lo use
	glBindBuffer(GL_ARRAY_BUFFER, VBO);
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);
	// 3.Copiamos nuestro arreglo de indices en  un elemento del buffer para que OpenGL lo use
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);

	// 4. Despues colocamos las caracteristicas de los vertices

	//Posicion
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(GLfloat), (GLvoid *)0);
	glEnableVertexAttribArray(0);

	//Color
	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(GLfloat), (GLvoid *)(3*sizeof(GLfloat)));
	glEnableVertexAttribArray(1);

	glBindBuffer(GL_ARRAY_BUFFER, 0);


	glBindVertexArray(0); // Unbind VAO (it's always a good thing to unbind any buffer/array to prevent strange bugs)


	
	while (!glfwWindowShouldClose(window)) //bucle de renderizado (visualmente solo vemos una imagen, pero opengl dibuja todo el tiempo lo que se indica
	{
		// Check if any events have been activiated (key pressed, mouse moved etc.) and call corresponding response functions
		glfwPollEvents();

		// Render
		// Clear the colorbuffer
		glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT);


		// Draw our first triangle
        ourShader.Use();
        glBindVertexArray(VAO);

		//ctrl k c comenta /// ctrl k u desocmenta
        //glpointsize(10); //define el tamaño del punto nn
        //gldrawarrays(gl_points,0,1); //se indica que va adibujar un punto de laposicion 0 a la posición 1
        //
		
        //glDrawArrays(GL_LINES,0,2); //incluyendo el vert. 0 toma dos puntos y haz una linea
        //glDrawArrays(GL_LINE_LOOP,0,4);  //a partir del 0 toma 4 - con loop los cierra
        
       // glDrawArrays(GL_TRIANGLES,0,3); //a partir del v0 toma 3 putnos y dibuja como un triangulo
        //glDrawElements(GL_TRIANGLES, 3,GL_UNSIGNED_INT,0); //dibuja con base al orden de los indices, auqnue en este caso solo 3 valores

        
        //ejercicios-----------
		//01 listo
		//glPointSize(10); //define el tamaño del punto nn
		//glDrawArrays(GL_POINTS, 0, 4); //se indica que va adibujar un punto de laposicion 0 a la posición 1

		//02 listo
		//glDrawArrays(GL_LINES, 0, 4);


		//03
		//glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);

		//04
		glDrawElements(GL_TRIANGLES, 3, GL_UNSIGNED_INT, 0);

        glBindVertexArray(0);
    
		// Swap the screen buffers
		glfwSwapBuffers(window);
	}



	glfwTerminate();
	return EXIT_SUCCESS;
}

void resize(GLFWwindow* window, int width, int height)
{
	// Set the Viewport to the size of the created window
	glViewport(0, 0, width, height);
	//glViewport(0, 0, screenWidth, screenHeight);
}