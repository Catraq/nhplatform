#ifndef NH_PLATFORM_H
#define NH_PLATFORM_H

#include <GL/glew.h>
#include <GLFW/glfw3.h>


struct nh_platform 
{
	GLFWwindow* window;

};

struct nh_platform_update 
{

	uint32_t window_resolution_x_pixel;
	uint32_t window_resolution_y_pixel;

	uint32_t screen_width_mm;
	uint32_t screen_height_mm;

	uint32_t screen_resolution_x_pixel;
	uint32_t screen_resolution_y_pixel;

	uint32_t mouse_x_pixel;
	uint32_t mouse_y_pixel;

	uint32_t mouse_button_left_pressed;
	uint32_t mouse_button_right_pressed;

	uint32_t mouse_button_left_clicked;
	uint32_t mouse_button_right_clicked;

	uint32_t mouse_button_left_state;
	uint32_t mouse_button_right_state;	
};



int nh_platform_initialize(
	struct nh_platform *platform,
	const char *window_title, 
	uint32_t window_width,
	uint32_t window_height
);

void nh_platform_deinitialize(
	struct nh_platform *platform
);


int nh_platform_update(
	struct nh_platform *platform,
	struct nh_platform_update *update 
);

int32_t nh_platform_key(
		struct nh_platform *platform,
		uint8_t key
);

#endif //NH_PLATFORM_H
