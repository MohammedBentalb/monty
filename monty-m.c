#include "main.h"

/**
 * main - Entry function
 * @argc: args count
 * @argv: args array
 * Return: 0
 */

int main(int argc, char *argv[])
{
	stack_t *stack = NULL;
	int i, opcode_found = 0;
	FILE *file;
	char line[MAX_LINE_LENGTH];
	unsigned int line_number = 0;
	instruction_t instructions[] = {{"push", push}, {"pall", pall},
		{"pint", pint}, {"pop", pop}, {"swap", swap}, {"add", add},
		{"nop", nop}, {"div", divv}, {"mod", mod}, {"sub", sub}, {NULL, NULL}};

	if (argc != 2)
	{	fprintf(stderr, "USAGE: monty file\n");
		exit(EXIT_FAILURE);
	}
	file = fopen(argv[1], "r");
	if (file == NULL)
	{	fprintf(stderr, "Error: Can't open file %s\n", argv[1]);
		exit(EXIT_FAILURE);
	}
	while (fgets(line, MAX_LINE_LENGTH, file) != NULL)
	{	char *opcode = strtok(line, " \t\n");

		line_number++;
		if (opcode == NULL || opcode[0] == '#')
			continue;
		for (i = 0; instructions[i].opcode != NULL; i++)
		{
			if (strcmp(opcode, instructions[i].opcode) == 0)
			{	opcode_found = 1;
				instructions[i].f(&stack, line_number);
				break;
			}
		}
		if (opcode_found == 0)
		{	fprintf(stderr, "L%u: unknown instruction %s\n", line_number, opcode);
			fclose(file);
			exit(EXIT_FAILURE);
		}
	}
	fclose(file);
	return (EXIT_SUCCESS);
}
