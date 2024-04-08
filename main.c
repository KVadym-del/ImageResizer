#include <stdio.h>
#include <stdint.h>

#define STB_IMAGE_IMPLEMENTATION
#include <stb_image.h>

#define STB_IMAGE_WRITE_IMPLEMENTATION
#include <stb_image_write.h>

void print_welcome(void);
void shrink_image(uint32_t* input, const int width, const int height, uint32_t* output, const int newWidth, const int newHeight);

int main(int argc, char** argv)
{
	if (argc != 5)
	{
		print_welcome();
		return 0;
	}
	const char* in_file = argv[1];
	const int32_t new_width = (int32_t)strtoul(argv[2], (char **)NULL, 10);
	if (new_width <= 0)
	{
		fprintf(stderr, "ERROR: invalid width!");
		return 1;
	}
	const int32_t new_height = (int32_t)strtoul(argv[3], (char **)NULL, 10);
	if (new_height <= 0)
	{
		fprintf(stderr, "ERROR: invalid height!");
		return 1;
	}
	char* out_file = argv[4];

	int32_t width, height;
	uint32_t* data = (uint32_t*)stbi_load(in_file, &width, &height, NULL, 4);
	if (data == NULL)
	{
		fprintf(stderr, "ERROR: could not load file %s!", in_file);
		return 1;
	}

	printf("Resizing image from %dx%d to %dx%d\n", width, height, new_width, new_height);

	uint32_t* new_data = malloc(new_width * new_height * 4);
	shrink_image(data, width, height, new_data, new_width, new_height);

	if(!stbi_write_jpg(out_file, new_width, new_height, 4, new_data, new_width * sizeof(*new_data)))
	{
		free(new_data);
		fprintf(stderr, "ERROR: could not save file %s!", out_file);
		return 1;
	}

	free(new_data);
	return 0;
}

void print_welcome(void)
{
	printf("Image resizer!\n");
	printf("(Input path) ");
	printf("(Width) ");
	printf("(Height) ");
	printf("(Output path)");
}

void shrink_image(uint32_t* input, const int width, const int height, uint32_t* output, const int newWidth, const int newHeight) {
	const double x_ratio = width/(double)newWidth;
	const double y_ratio = height/(double)newHeight;
	double px, py;
	for (uint32_t i = 0; i < newHeight; i++) {
		for (uint32_t j = 0; j < newWidth; j++) {
			px = floor(j * x_ratio);
			py = floor(i * y_ratio);
			output[(i * newWidth) + j] = input[(int32_t)((py * width) + px)];
		}
	}
}