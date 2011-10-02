#include<iostream>
#include "Parser.h"
#include "Scanner.h"

int main(int argc, char* argv[])
{
	if(argc == 2)
	{
		wchar_t *fileName = coco_string_create(argv[1]);
		Scanner *scanner = new Scanner(fileName);
		Parser *parser = new Parser(scanner);
		parser->Parse();
		printf("%d errors detected:",parser->errors->count);
	}
	else
	{
		printf("file not specified");
	}


	return 0;
}