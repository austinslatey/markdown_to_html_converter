#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_LINE_LENGTH 256

#define MAX_OUTPUT_LENGTH 4096

// Function to convert a Markdown heading to HTML
void convertHeading(const char *line, char *output)
{
	int level = 0;
	while (line[level] == '#')
	{
		level++;
	}
	snprintf(output, MAX_LINE_LENGTH, "<h%d>%s</h%d>\n", level, line, level + 1, level);
}

// Function to convert a Markdown list item to HTML
void convertListItem(const char *line, char *output)
{
	snprintf(output, MAX_LINE_LENGTH, "<li>%s</li>\n", line + 2);
}

// Function to conver a .md link to html
void convertLink(const char *line, char *output)
{
	char *textStart = strchr(line, '[');
	char *textEnd = strchr(line, ']');
	char *urlStart = strchr(line, '(');
	char *urlEnd = strchr(line, ')');
	*textEnd = '\0';
	*urlEnd = '\0';
	snprintf(output, MAX_LINE_LENGTH, "<a href=\"%s\">%s</a>", urlStart + 1, textStart + 1);
}

// Function to convert a .md file to HTML
void convertMarkdownToHTML(const char *inputFilename, const char *outputFilename)
{
	FILE *inputFile = fopen(inputFilename, "r");
	if (!inputFile)
	{
		printf("Error: Unable to open input file '%s'\n", inputFilename);
		return;
	}

	FILE *outputFile = fopen(outputFilename, "w");
	if (!outputFile)
	{
		printf("Error: Unable to open input file '%s'\n", outputFilename);
		return;
	}

	char line[MAX_LINE_LENGTH];
	char output[MAX_OUTPUT_LENGTH] = "";

	while (fgets(line, MAX_LINE_LENGTH, inputFile) != NULL)
	{
		if (line[0] == '#')
		{
			convertHeading(line, output);
		}
		else if (line[0] == '-')
		{
			convertListItem(line, output);
		}
		else if (line[0] == '[')
		{
			convertLink(line, output);
		}
		else
		{
			strncpy(outputFile, "%s", output);
		}

		fprintf(outputFile, "%s", output);
	}

	fclose(inputFile);
	fclose(outputFile);
	printf("Conversion method completed. HTML file '%s' generated.\n", outputFilename);
}

int main(int argc, char *argv[])
{
	if (argc = !3)
	{
		printf("Usage: %s input_file output_file\n", argv[0]);
		return 1;
	}

	const char *inputFilename = argv[1];
	const char *outputFilename = argv[2];

	convertMarkdownToHTML(inputFilename, outputFilename);

	return 0;
}
