#include <stdio.h>
#include <nh_platform.h>


int main(int args, char *argv[])
{
	int result = 0;	
	struct nh_platform platform;
	
	result = nh_platform_initialize(&platform, "Test", 640, 480);
	if(result < 0)
	{
		fprintf(stderr, "nh_platform_initialize() failed. \n");
		return -1;	
	}
	
	struct nh_platform_update platform_update;	
	while(nh_platform_update(&platform, &platform_update) > 0)
	{
		printf("window resolution(pixel): %u %u \n", platform_update.window_resolution_x_pixel, platform_update.window_resolution_y_pixel);
		printf("screen size(mm): %u %u \n", platform_update.screen_width_mm, platform_update.screen_height_mm);
		printf("screen resolution(pixel): %u %u \n", platform_update.screen_resolution_x_pixel, platform_update.screen_resolution_y_pixel);
		printf("mouse (pixel): %i %i \n", platform_update.mouse_x_pixel, platform_update.mouse_y_pixel);
		printf("mouse button pressed: %u %u \n", platform_update.mouse_button_left_pressed, platform_update.mouse_button_right_pressed);
		printf("mouse button clicked: %u %u \n", platform_update.mouse_button_left_clicked, platform_update.mouse_button_right_clicked);
	}

	nh_platform_deinitialize(&platform);
	return 0;
}
