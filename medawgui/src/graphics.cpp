#include "graphics.hpp"

using namespace gui;

GLFWwindow *Graphics::window;
unsigned int Graphics::width;
unsigned int Graphics::height;
bool Graphics::forceClose;

Shader *Graphics::currentShader;
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
	glewInit();

	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
	glDisable(GL_DEPTH_TEST);
	glDisable(GL_CULL_FACE);
	glDisable(GL_STENCIL_TEST);
	glDepthMask(GL_FALSE);
    glfwSwapInterval(1);
	glActiveTexture(GL_TEXTURE0);

	Graphics::clearScreen({255, 255, 255});

	Graphics::currentShader  = nullptr;
	Graphics::currentVAO     = 0;
	Graphics::currentTexture = 0;
	Graphics::defaultCamera  = new Camera(Graphics::width, Graphics::height);
	Graphics::currentCamera  = Graphics::defaultCamera;

	Graphics::fps   = 0.0f;
	Graphics::delta = 0.0f;

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

void Graphics::clearScreen(const Color &color)
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

void Graphics::endFrame()
{
	glfwSwapBuffers(Graphics::window);
	glfwPollEvents();
	Graphics::updateTime();
}

void Graphics::updateTime()
{

}

