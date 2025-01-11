#include "../common.h"

#include "util.h"

unsigned long hashcode(const char *str)
{
	unsigned long hash = 5381;
	int c;

	c = *str;

	while (c)
	{
		hash = ((hash << 5) + hash) + c; /* hash * 33 + c */

		c = *str++;
	}

	hash = ((hash << 5) + hash);

	return hash;
}

char *readFile(char *filename)
{
	FILE *file = fopen(filename, "rb");
	if(!file) {
		SDL_Log("Error: Unable to open file: %s", filename);
		return NULL;
	}

	fseek(file, 0, SEEK_END);
	long length = ftell(file);
	if (length <= 0)
	{
		SDL_Log("Error: File is empty or invalid: %s", filename);
		fclose(file);
		return NULL;
	}
	rewind(file); // Ставим указатель на начало файла

	char *buffer = malloc(length + 1); // +1 для завершающего \0
	if (!buffer)
	{
		SDL_Log("Error: Failed to allocate memory for file: %s", filename);
		fclose(file);
		return NULL;
	}

	fread(buffer, 1, length, file);
	buffer[length] = '\0'; // Завершаем строку

	fclose(file);
	return buffer;
}
