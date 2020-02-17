#include <Game.h>

static bool flip;

Game::Game() : window(sf::VideoMode(800, 600), "OpenGL Cube Texturing")
{
}

Game::~Game() {}

void Game::run()
{

	initialize();

	sf::Event event;

	while (isRunning) {

#if (DEBUG >= 2)
		DEBUG_MSG("Game running...");
#endif

		while (window.pollEvent(event))
		{
			if (event.type == sf::Event::Closed)
			{
				isRunning = false;
			}
		}
		update();
		render();
	}

}





typedef struct
{
	float coordinate[3];
	float color[4];
	float texel[24];
} Vertex;

Vertex vertex[24];
GLubyte triangles[36];

float vertices[] = { -0.5f, -0.5f, 0.5f,
						0.5f, -0.5f, 0.5f,
						0.5f, 0.5f, 0.5f,
						-0.5f, 0.5f, 0.5f,
						-0.5f, -0.5f, -0.5f,
						0.5f, -0.5f, -0.5f,
						0.5f, 0.5f, -0.5f,
						-0.5f, 0.5f, -0.5f };

Vector3f m_points[] = { {vertices[0],vertices[1],vertices[2] },
						{vertices[3],vertices[4],vertices[5] },
						{vertices[6],vertices[7],vertices[8] },
						{vertices[9],vertices[10],vertices[11] },
						{vertices[12],vertices[13],vertices[14] },
						{vertices[15],vertices[16],vertices[17] },
						{vertices[18],vertices[19],vertices[20] },
							{vertices[21],vertices[22],vertices[23] }
};



/* Variable to hold the VBO identifier and shader data */
GLuint	index,		//Index to draw
		vsid,		//Vertex Shader ID
		fsid,		//Fragment Shader ID
		progID,		//Program ID
		vao = 0,	//Vertex Array ID
		vbo = 1,		// Vertex Buffer ID
		positionID, //Position ID
		colorID,	// Color ID
		to,			// Texture ID 1 to 32
		textureID,	//Texture ID
		texelID;	// Texel ID

//const string filename = "texture.tga";
//const string filename = "cube.tga";

const std::string filename = "cube.tga";

int width; //width of texture
int height; //height of texture
int comp_count; //Component of texture
const int number = 4; //4 = RGBA

unsigned char* img_data;

void Game::initialize()
{
	isRunning = true;
	for (int i = 0; i < 8; i++)
	{
		m_points[i] = Matrix3f::scale3D(50) * m_points[i];
	}
	glTranslated(0.0f, 0.0f, -8.0f);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	gluPerspective(45.0, window.getSize().x / window.getSize().y, 1.0, 500.0);
	glMatrixMode(GL_MODELVIEW);
	glEnable(GL_CULL_FACE);
	GLint isCompiled = 0;
	GLint isLinked = 0;

	glewInit();

	DEBUG_MSG(glGetString(GL_VENDOR));
	DEBUG_MSG(glGetString(GL_RENDERER));
	DEBUG_MSG(glGetString(GL_VERSION));



	//vertex[0].coordinate[0] = vertices[0];
	//vertex[0].coordinate[1] = vertices[1];
	//vertex[0].coordinate[2] = vertices[2];

	//vertex[1].coordinate[0] = vertices[3];
	//vertex[1].coordinate[1] = vertices[4];
	//vertex[1].coordinate[2] = vertices[5];

	//vertex[2].coordinate[0] = vertices[6];
	//vertex[2].coordinate[1] = vertices[7];
	//vertex[2].coordinate[2] = vertices[8];

	//vertex[3].coordinate[0] = vertices[9];
	//vertex[3].coordinate[1] = vertices[10];
	//vertex[3].coordinate[2] = vertices[11];

	//vertex[4].coordinate[0] = vertices[12];
	//vertex[4].coordinate[1] = vertices[13];
	//vertex[4].coordinate[2] = vertices[14];

	//vertex[5].coordinate[0] = vertices[15];
	//vertex[5].coordinate[1] = vertices[16];
	//vertex[5].coordinate[2] = vertices[17];

	//vertex[6].coordinate[0] = vertices[18];
	//vertex[6].coordinate[1] = vertices[19];
	//vertex[6].coordinate[2] = vertices[20];

	//vertex[7].coordinate[0] = vertices[21];
	//vertex[7].coordinate[1] = vertices[22];
	//vertex[7].coordinate[2] = vertices[23];






	//front

	vertex[0].texel[0] = 0.25f;
	vertex[0].texel[1] = 0.25f;

	vertex[1].texel[0] = 0.5f;
	vertex[1].texel[1] = 0.25f;

	vertex[2].texel[0] = 0.5f;
	vertex[2].texel[1] = 0.5f;

	vertex[3].texel[0] = 0.25f;
	vertex[3].texel[1] = 0.5f;

	//back

	vertex[4].texel[0] = 0.75f;
	vertex[4].texel[1] = 0.25f;

	vertex[5].texel[0] = 1.0f;
	vertex[5].texel[1] = 0.25f;


	vertex[6].texel[0] = 1.0f;
	vertex[6].texel[1] = 0.5f;

	vertex[7].texel[0] = 0.75f;
	vertex[7].texel[1] = 0.5f;

	// 

	vertex[8].texel[0] = 0.25f;
	vertex[8].texel[1] = 0.75f;

	vertex[9].texel[0] = 1.0f;
	vertex[9].texel[1] = 0.25f;

	vertex[10].texel[0] = 1.0f;
	vertex[10].texel[1] = 0.5f;

	vertex[11].texel[0] = 0.75f;
	vertex[11].texel[1] = 0.5f;

	////
	//vertex[12].texel[0] = 0.25f;
	//vertex[12].texel[1] = 0.75f;

	//vertex[13].texel[0] = 1.0f;
	//vertex[13].texel[1] = 0.25f;

	//vertex[14].texel[0] = 1.0f;
	//vertex[14].texel[1] = 0.5f;

	//vertex[15].texel[0] = 0.75f;
	//vertex[15].texel[1] = 0.5f;

	////
	//vertex[16].texel[0] = 0.75f;
	//vertex[16].texel[1] = 0.75f;

	//vertex[17].texel[0] = 0.75f;
	//vertex[17].texel[1] = 0.75f;

	//vertex[18].texel[0] = 0.75f;
	//vertex[18].texel[1] = 0.75f;

	//vertex[19].texel[0] = 0.75f;
	//vertex[19].texel[1] = 0.75f;

	////
	//vertex[20].texel[0] = 0.75f;
	//vertex[20].texel[1] = 0.75f;

	//vertex[21].texel[0] = 0.75f;
	//vertex[21].texel[1] = 0.75f;
	//
	//vertex[22].texel[0] = 0.75f;
	//vertex[22].texel[1] = 0.75f;

	//vertex[23].texel[0] = 0.75f;
	//vertex[23].texel[1] = 0.75f;

	
	/*Index of Poly / Triangle to Draw */

	// front
	triangles[0] = 0;   triangles[1] = 1;   triangles[2] = 2; // 1
	triangles[3] = 2;   triangles[4] = 3;   triangles[5] = 0; // 2

	//
	triangles[6] = 2;   triangles[7] = 6;   triangles[8] = 3; // 3
	triangles[9] = 6;   triangles[10] = 7;   triangles[11] = 3; // 4

	//
	triangles[12] = 7;   triangles[13] = 6;   triangles[14] = 5;
	triangles[15] = 5;   triangles[16] = 4;   triangles[17] = 7;
	
	//
	triangles[18] = 5;   triangles[19] = 0;   triangles[20] = 4;
	triangles[21] = 5;   triangles[22] = 1;   triangles[23] = 0;
	
	//
	triangles[24] = 1;   triangles[25] = 5;   triangles[26] = 6;
	triangles[27] = 6;   triangles[28] = 2;   triangles[29] = 1;

	//
	triangles[30] = 4;   triangles[31] = 0;   triangles[32] = 3;
	triangles[33] = 3;   triangles[34] = 7;   triangles[35] = 4;


	/* Create a new VBO using VBO id */
	glGenBuffers(1, &vbo);

	/* Bind the VBO */
	glBindBuffer(GL_ARRAY_BUFFER, vbo);

	/* Upload vertex data to GPU */
	glBufferData(GL_ARRAY_BUFFER, sizeof(Vertex) * 24, vertex, GL_STATIC_DRAW);
	glBindBuffer(GL_ARRAY_BUFFER, 0);

	glGenBuffers(1, &index);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, index);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(GLubyte) * 36, triangles, GL_STATIC_DRAW);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);

	/* Vertex Shader which would normally be loaded from an external file */
	const char* vs_src = "#version 400\n\r"
		"in vec4 sv_position;"
		"in vec4 sv_color;"
		"in vec2 sv_texel;"
		"out vec4 color;"
		"out vec2 texel;"
		"void main() {"
		"	color = sv_color;"
		"	texel = sv_texel;"
		"	gl_Position = sv_position;"
		"}"; //Vertex Shader Src

	DEBUG_MSG("Setting Up Vertex Shader");

	vsid = glCreateShader(GL_VERTEX_SHADER); //Create Shader and set ID
	glShaderSource(vsid, 1, (const GLchar**)&vs_src, NULL); // Set the shaders source
	glCompileShader(vsid); //Check that the shader compiles

	//Check is Shader Compiled
	glGetShaderiv(vsid, GL_COMPILE_STATUS, &isCompiled);

	if (isCompiled == GL_TRUE) {
		DEBUG_MSG("Vertex Shader Compiled");
		isCompiled = GL_FALSE;
	}
	else
	{
		DEBUG_MSG("ERROR: Vertex Shader Compilation Error");
	}

	/* Fragment Shader which would normally be loaded from an external file */
	const char* fs_src = "#version 400\n\r"
		"uniform sampler2D f_texture;"
		"in vec4 color;"
		"in vec2 texel;"
		"out vec4 fColor;"
		"void main() {"
		//"	fColor = vec4(0.0f, 1.0f, 0.0f, 1.0f);"
		"	fColor = texture(f_texture, texel.st);"
		"}"; //Fragment Shader Src

	DEBUG_MSG("Setting Up Fragment Shader");

	fsid = glCreateShader(GL_FRAGMENT_SHADER);
	glShaderSource(fsid, 1, (const GLchar**)&fs_src, NULL);
	glCompileShader(fsid);
	//Check is Shader Compiled
	glGetShaderiv(fsid, GL_COMPILE_STATUS, &isCompiled);

	if (isCompiled == GL_TRUE) {
		DEBUG_MSG("Fragment Shader Compiled");
		isCompiled = GL_FALSE;
	}
	else
	{
		DEBUG_MSG("ERROR: Fragment Shader Compilation Error");
	}

	DEBUG_MSG("Setting Up and Linking Shader");
	progID = glCreateProgram();	//Create program in GPU
	glAttachShader(progID, vsid); //Attach Vertex Shader to Program
	glAttachShader(progID, fsid); //Attach Fragment Shader to Program
	glLinkProgram(progID);

	//Check is Shader Linked
	glGetProgramiv(progID, GL_LINK_STATUS, &isLinked);

	if (isLinked == 1) {
		DEBUG_MSG("Shader Linked");
	}
	else
	{
		DEBUG_MSG("ERROR: Shader Link Error");
	}

	// Use Progam on GPU
	// https://www.opengl.org/sdk/docs/man/html/glUseProgram.xhtml
	glUseProgram(progID);

	img_data = stbi_load(filename.c_str(), &width, &height, &comp_count, 4);

	if (img_data == NULL)
	{
		DEBUG_MSG("ERROR: Texture not loaded");
	}

	glEnable(GL_TEXTURE_2D);
	glGenTextures(1, &to);
	glBindTexture(GL_TEXTURE_2D, to);

	//Wrap around
	//https://www.khronos.org/opengles/sdk/docs/man/xhtml/glTexParameter.xml
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);

	//Filtering
	//https://www.khronos.org/opengles/sdk/docs/man/xhtml/glTexParameter.xml
	glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
	glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);

	//Bind to OpenGL
	//https://www.khronos.org/opengles/sdk/docs/man/xhtml/glTexImage2D.xml
	glTexImage2D(GL_TEXTURE_2D, //2D Texture Image
		0, //Mipmapping Level 
		GL_RGBA, //GL_RED, GL_GREEN, GL_BLUE, GL_ALPHA, GL_RGB, GL_BGR, GL_RGBA 
		width, //Width
		height, //Height
		0, //Border
		GL_RGBA, //Bitmap
		GL_UNSIGNED_BYTE, img_data);

	// Find variables in the shader
	//https://www.khronos.org/opengles/sdk/docs/man/xhtml/glGetAttribLocation.xml
	positionID = glGetAttribLocation(progID, "sv_position");
	colorID = glGetAttribLocation(progID, "sv_color");
	texelID = glGetAttribLocation(progID, "sv_texel");
	textureID = glGetUniformLocation(progID, "f_texture");
}

void Game::update()
{
	elapsed = clock.getElapsedTime();

	if (elapsed.asSeconds() >= 1.0f)
	{
		clock.restart();

		if (!flip)
		{
			flip = true;
		}
		else
			flip = false;
	}

	if (flip)
	{
		//rotationAngle += 0.005f;

		if (rotationAngle > 360.0f)
		{
			rotationAngle -= 360.0f;
		}
	}


	cubeRotation();
	//unload();

	//Change vertex data
	//vertex[0].coordinate[0] += -0.0001f;
	//vertex[0].coordinate[1] += -0.0001f;
	//vertex[0].coordinate[2] += -0.0001f;

	//vertex[1].coordinate[0] += -0.0001f;
	//vertex[1].coordinate[1] += -0.0001f;
	//vertex[1].coordinate[2] += -0.0001f;

	//vertex[2].coordinate[0] += -0.0001f;
	//vertex[2].coordinate[1] += -0.0001f;
	//vertex[2].coordinate[2] += -0.0001f;

#if (DEBUG >= 2)
	DEBUG_MSG("Update up...");
#endif

}

void Game::render()
{

#if (DEBUG >= 2)
	DEBUG_MSG("Drawing...");
#endif

	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	glClearColor(0.0f, 0.0f, 0.0f, 0.0f);

	glBindBuffer(GL_ARRAY_BUFFER, vbo);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, index);

	/*	As the data positions will be updated by the this program on the
		CPU bind the updated data to the GPU for drawing	*/
	glBufferData(GL_ARRAY_BUFFER, sizeof(Vertex) * 36, vertex, GL_STATIC_DRAW);

	/*	Draw Triangle from VBO	(set where to start from as VBO can contain
		model components that 'are' and 'are not' to be drawn )	*/

	//Set Active Texture .... 32
	glActiveTexture(GL_TEXTURE0);
	glUniform1i(textureID, 0);

	// Set pointers for each parameter
	// https://www.opengl.org/sdk/docs/man4/html/glVertexAttribPointer.xhtml
	glVertexAttribPointer(positionID, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), 0);
	glVertexAttribPointer(colorID, 4, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)(3 * sizeof(float)));
	glVertexAttribPointer(texelID, 2, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)(7 * sizeof(float)));

	//Enable Arrays
	glEnableVertexAttribArray(positionID);
	glEnableVertexAttribArray(colorID);
	glEnableVertexAttribArray(texelID);

	glDrawElements(GL_TRIANGLES, 36, GL_UNSIGNED_BYTE, (char*)NULL + 0);

	window.display();

}

void Game::unload()
{
#if (DEBUG >= 2)
	DEBUG_MSG("Cleaning up...");
#endif
	glDeleteProgram(progID);
	glDeleteBuffers(1, &vbo);
	stbi_image_free(img_data); //Free image
}

void Game::cubeRotation()
{

	if (sf::Keyboard::isKeyPressed(sf::Keyboard::W))
	{
		for (int i = 0; i < 8; i++)
		{
			m_points[i] = Matrix3f::rotationX(rotationAngle) * m_points[i];
		}
	}

	if (sf::Keyboard::isKeyPressed(sf::Keyboard::S))
	{
		for (int i = 0; i < 8; i++)
		{
			m_points[i] = Matrix3f::rotationX(-rotationAngle) * m_points[i];
		}
	}


	if (sf::Keyboard::isKeyPressed(sf::Keyboard::A))
	{
		for (int i = 0; i < 8; i++)
		{
			m_points[i] = Matrix3f::rotationY(-rotationAngle) * m_points[i];
		}
	}


	if (sf::Keyboard::isKeyPressed(sf::Keyboard::D))
	{
		for (int i = 0; i < 8; i++)
		{
			m_points[i] = Matrix3f::rotationY(rotationAngle) * m_points[i];
		}
	}


	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Q))
	{
		for (int i = 0; i < 8; i++)
		{
			m_points[i] = Matrix3f::rotationZ(rotationAngle) * m_points[i];
		}
	}


	if (sf::Keyboard::isKeyPressed(sf::Keyboard::E))
	{
		for (int i = 0; i < 8; i++)
		{
			m_points[i] = Matrix3f::rotationZ(-rotationAngle) * m_points[i];
		}
	}




	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Z))
	{
		for (int i = 0; i < 8; i++)
		{
			m_points[i] = Matrix3f::scale3D(100.05) * m_points[i];
		}
	}



	if (sf::Keyboard::isKeyPressed(sf::Keyboard::X))
	{
		for (int i = 0; i < 8; i++)
		{
			m_points[i] = Matrix3f::scale3D(99.95) * m_points[i];
		}
	}


	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right))
	{
		for (int i = 0; i < 8; i++)
		{
			float temp = m_points[i].m_z;
			m_points[i].m_z = 1;
			m_points[i] = Matrix3f::translation(0.001f, 0.0f) * m_points[i];
			m_points[i].m_z = temp;
		}
	}

	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left))
	{
		for (int i = 0; i < 8; i++)
		{
			float temp = m_points[i].m_z;
			m_points[i].m_z = 1;
			m_points[i] = Matrix3f::translation(-0.001f, 0.0f) * m_points[i];
			m_points[i].m_z = temp;
		}
	}

	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up))
	{
		for (int i = 0; i < 8; i++)
		{
			float temp = m_points[i].m_z;
			m_points[i].m_z = 1;
			m_points[i] = Matrix3f::translation(0.0f, 0.001f) * m_points[i];
			m_points[i].m_z = temp;
		}
	}

	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Down))
	{
		for (int i = 0; i < 8; i++)
		{
			float temp = m_points[i].m_z;
			m_points[i].m_z = 1;
			m_points[i] = Matrix3f::translation(0.0f, -0.001f) * m_points[i];
			m_points[i].m_z = temp;
		}
	}




	for (int i = 0, j = 0; i < 8, j < 24; i++)
	{
		vertex[i].coordinate[0] = m_points[i].m_x;
		j++;
		vertex[i].coordinate[1] = m_points[i].m_y;
		j++;
		vertex[i].coordinate[2] = m_points[i].m_z;
		j++;
	}




}