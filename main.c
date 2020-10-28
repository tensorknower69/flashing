#include <GL/gl.h>
#include <GLFW/glfw3.h>
#include <errno.h>
#include <getopt.h>
#include <limits.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

#define NO_VALUE -1
#define PROG "flashing"

const char* usage =
	"usage: " PROG " [-f] [-x width] [-y height] [-t title], to run fullscreen (use -f) or windowed\n"
	"       " PROG " -h, for help\n"
	;

float rand_rgb_float() {
	return rand() % 255 / 255.0;
}

/*
 * read optarg as a positive number or die
 */
int optarg_pnum_or_die(char name) {
	char* dummy = optarg;
	long int value = strtol(optarg, &dummy, 10);
	if (errno != 0) {
		fprintf(stderr, PROG ": -%c: strtol failed, unable to parse value", name);
		exit(1);
	}
	if (!(value > 0 && value <= INT_MAX)) {
		fprintf(stderr, PROG ": -%c: (value > 0 && value <= INT_MAX) is false", name);
		exit(1);
	}
	return (int) value;
}

int main(int argc, char **argv) {
	bool flag_fullscreen = false;
	bool flag_help = false;
	const char* title = NULL;
	int width = NO_VALUE, height = NO_VALUE;

	char c;
	while((c = getopt(argc, argv, "hfx:y:t:")) != -1) {
		switch (c) {
			case 'h':
				flag_help = true;
				break;
			case 'f':
				flag_fullscreen = true;
				break;
			case 'x':
				width = optarg_pnum_or_die(c);
				break;
			case 'y':
				height = optarg_pnum_or_die(c);
				break;
			case 't':
				title = strdup(optarg);
				break;
			case '?':
			default:
				fprintf(stderr, usage);
				exit(1);
				break;
		}
	}

	if (flag_help) {
		fprintf(stdout, usage);
		exit(0);
	}

	glfwInit();

	GLFWmonitor* mon;
	if (flag_fullscreen) {
		mon = glfwGetPrimaryMonitor();
		const GLFWvidmode* mode = glfwGetVideoMode(mon);
		width = mode->width;
		height = mode->height;
	} else {
		if (width == NO_VALUE || height == NO_VALUE) {
			fprintf(stderr, "width or/and height aren't specified, or just use -f for fullscreen mode\n");
			exit(1);
		}
		mon = NULL;
	}

	if (title == NULL)
		title = PROG;

	GLFWwindow* win = glfwCreateWindow(width, height, title, mon, NULL);
	glfwMakeContextCurrent(win);

	fprintf(stdout, "Window info: title='%s' fullscreen=%d, size=%dx%d\n", title, flag_fullscreen, width, height);
	fprintf(stdout, "Press 'q' to close\n");

	srand(time(NULL));
	float r, g, b;
	while (!glfwWindowShouldClose(win)) {
		r = rand_rgb_float();
		g = rand_rgb_float();
		b = rand_rgb_float();

		glClearColor(r, g, b, 1);
		glClear(GL_COLOR_BUFFER_BIT);

		glfwSwapBuffers(win);
		glfwPollEvents();
		if (glfwGetKey(win, GLFW_KEY_Q) == GLFW_PRESS) {
			glfwSetWindowShouldClose(win, true);
		}
	}
	glfwDestroyWindow(win);
	glfwTerminate();
	return 0;
}
