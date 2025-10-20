#include "core/graphics.hpp"

using namespace gui;

GLFWwindow *Graphics::window;
unsigned int Graphics::width;
unsigned int Graphics::height;
bool Graphics::forceClose;

GLuint Graphics::currentVAO;
GLuint Graphics::currentTexture;
Camera *Graphics::currentCamera;
Camera *Graphics::defaultCamera;

float Graphics::fps;
float Graphics::delta;

void Graphics::initialize(int width, int height, const char *title)
{
	Graphics::width  = width;
	Graphics::height = height;
	
	glfwInit();
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 6);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
	glfwWindowHint(GLFW_RESIZABLE, GLFW_TRUE);
	glfwWindowHint(GLFW_VISIBLE, GLFW_TRUE);
	glfwWindowHint(GLFW_DOUBLEBUFFER, GLFW_TRUE);
	glfwWindowHint(GLFW_OPENGL_DEBUG_CONTEXT, GLFW_TRUE);

	Graphics::window = glfwCreateWindow(width, height, title, nullptr, nullptr);
	glfwMakeContextCurrent(Graphics::window);
	glfwSetWindowSizeLimits(Graphics::window, 800, 600, GLFW_DONT_CARE, GLFW_DONT_CARE);
	glewInit();

	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
	glDisable(GL_DEPTH_TEST);
	glDisable(GL_CULL_FACE);
	glDisable(GL_STENCIL_TEST);
	glDepthMask(GL_FALSE);
  glfwSwapInterval(1);
	glActiveTexture(GL_TEXTURE0);

	Graphics::clearScreen({255, 255, 255, 255});

	Shader::current  = nullptr;
	Graphics::currentVAO     = 0;
	Graphics::currentTexture = 0;
	Graphics::defaultCamera  = new Camera(Graphics::width, Graphics::height);
	Graphics::currentCamera  = Graphics::defaultCamera;

	Graphics::fps   = 0.0f;
	Graphics::delta = 0.0f;

	// Set callbacks
	glfwSetKeyCallback(Graphics::window, &Event::keyboardCallback);
	glfwSetMouseButtonCallback(Graphics::window, &Event::mouseCallback);
	glfwSetCursorPosCallback(Graphics::window, &Event::cursorCallback);
	glfwSetFramebufferSizeCallback(Graphics::window, &Event::resizedCallback);

	// Components
	Texture::initialize();
}

void Graphics::finalize()
{
	Texture::finalize();
	glfwTerminate();
}

bool Graphics::shouldClose()
{
	if (Graphics::forceClose)
		glfwSetWindowShouldClose(Graphics::window, GLFW_TRUE);

	return glfwWindowShouldClose(Graphics::window);
}

void Graphics::clearScreen(const glm::uvec4 &color)
{
	glClearColor(color.r / 255.0f, color.g / 255.0f, color.b / 255.0f, color.a / 255.0f);
	glClear(GL_COLOR_BUFFER_BIT);
}

void Graphics::setRenderTexture(RenderTexture *renderTexture)
{
	if (renderTexture)
	{
		glBindFramebuffer(GL_FRAMEBUFFER, renderTexture->FBO);
		glViewport(0, 0, renderTexture->texture->width, renderTexture->texture->height);
		Graphics::currentCamera = renderTexture->camera;
	}
	else
	{
		glBindFramebuffer(GL_FRAMEBUFFER, 0);
		glViewport(0, 0, Graphics::width, Graphics::height);
		Graphics::currentCamera = Graphics::defaultCamera;
	}

	Graphics::currentCamera->updateViewProjectionMatrix();

	//? Submit camera data to GPU (UBO_Shared)
	glNamedBufferSubData(Texture::UBO_Shared, 0, sizeof(glm::mat4), &Graphics::currentCamera->viewProjection);
}

void Graphics::setVAO(GLuint VAO)
{
	if (VAO != Graphics::currentVAO) {

		Graphics::currentVAO = VAO;
		glBindVertexArray(VAO);
	}
}

void Graphics::setTexture(GLuint texture)
{
	if (texture != Graphics::currentTexture) {

		Graphics::currentTexture = texture;
		glBindTexture(GL_TEXTURE_2D, texture);
	}
}

void Graphics::drawBuffer()
{
	glfwSwapBuffers(Graphics::window);
}

void Graphics::pollEvents()
{
	glfwPollEvents();
}

