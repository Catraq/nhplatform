#include <GL/glew.h>
#include <GLFW/glfw3.h>

#define GLFW_EXPOSE_NATIVE_EGL
#include <GLFW/glfw3native.h>

#include <stdio.h>

#include "nh_platform.h"



int nh_platform_initialize(
		struct nh_platform *platform,
		const char *window_title, 
		uint32_t window_width,
		uint32_t window_height
)
{
	/* Initialize openGL */	
	if (!glfwInit())
		return -1;

	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 4);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
	glfwWindowHint(GLFW_SAMPLES, 16);

	platform->window = glfwCreateWindow(window_width, window_height, window_title, NULL, NULL);
	if(!platform->window)
	{
		glfwTerminate();
		return -1;
	}

	glfwMakeContextCurrent(platform->window);
	
	/* Disable vertical sync */
	glfwSwapInterval(0);

  	
       	/* Enable Version 3.3 */
	glewExperimental = 1;
	if (glewInit() != GLEW_OK)
	{
		fprintf(stderr,"Failed to init Glew \n");
		glfwTerminate();
		return -1;
	}


	/* Clear any errors */
	while( glGetError() != GL_NONE)
	{
		glGetError();
	}
	
	glfwSwapBuffers(platform->window);
	glfwPollEvents();

	return 0;
}

void nh_platform_deinitialize(
		struct nh_platform *platform
)
{
    glfwDestroyWindow(platform->window);
    glfwTerminate();
}

int nh_platform_update(
		struct nh_platform *platform,
		struct nh_platform_update *update 
)
{
	int width_mm, height_mm;
	glfwGetMonitorPhysicalSize(glfwGetPrimaryMonitor(), &width_mm, &height_mm);
	update->screen_width_mm = width_mm;
	update->screen_height_mm = height_mm;

	const GLFWvidmode *mode = glfwGetVideoMode(glfwGetPrimaryMonitor());
	update->screen_resolution_x_pixel = mode->width;
	update->screen_resolution_y_pixel = mode->height;
	
	{
		int x,y;
		glfwGetFramebufferSize(platform->window, &x, &y);
		update->window_resolution_x_pixel = (uint32_t)x;
		update->window_resolution_y_pixel = (uint32_t)y;
	}
	
	{	
		double x,y;
		glfwGetCursorPos(platform->window, &x, &y);
		y = (int)update->window_resolution_y_pixel - (int)y;

		if(x < 0)
		{
			update->mouse_x_pixel = 0;
		}
		else if(x > update->window_resolution_x_pixel)
		{
			update->mouse_x_pixel = update->window_resolution_x_pixel;
		}
		else
		{
			update->mouse_x_pixel = (uint32_t)x;	
		}


		if(y < 0)
		{
			update->mouse_y_pixel = 0;
		}
		else if(y > update->window_resolution_y_pixel)
		{
			update->mouse_y_pixel = update->window_resolution_y_pixel;
		}
		else
		{
			update->mouse_y_pixel = (uint32_t)y;	
		}

	}


	int mouse_button_left = glfwGetMouseButton(platform->window, GLFW_MOUSE_BUTTON_LEFT);
	uint32_t mouse_button_left_state = mouse_button_left == GLFW_RELEASE ?  update->mouse_button_left_state != mouse_button_left ? 1 : 0 : 0;
	update->mouse_button_left_state = mouse_button_left;
	update->mouse_button_left_pressed = mouse_button_left == GLFW_PRESS;
	update->mouse_button_left_clicked = mouse_button_left_state;
	
	int mouse_button_right = glfwGetMouseButton(platform->window, GLFW_MOUSE_BUTTON_RIGHT);
	uint32_t mouse_button_right_state = mouse_button_right == GLFW_RELEASE ?  update->mouse_button_right_state != mouse_button_right ? 1 : 0 : 0;
	update->mouse_button_right_state = mouse_button_right;
	update->mouse_button_right_pressed = mouse_button_right == GLFW_PRESS;
	update->mouse_button_right_clicked = mouse_button_right_state;
	

	glfwSwapBuffers(platform->window);
	glfwPollEvents();

	return glfwWindowShouldClose(platform->window) == 0 ? 1 : 0;
}



int32_t nh_platform_key(
		struct nh_platform *platform,
		uint8_t key
)
{
	return (int32_t)glfwGetKey(platform->window, ( int )key );
}



