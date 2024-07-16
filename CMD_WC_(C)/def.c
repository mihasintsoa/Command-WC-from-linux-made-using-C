#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "wc.h"

int countLine(FILE *f)
{
	int count = 0;
	char word[100];
	while ( (fgets(word,100,f) != 0) )
	{
		count++;
	}
	rewind(f);
	return (count);
}
int countCharact(FILE* f)
{
	int count = 0;
	char a;
	while ( !(feof(f)) )
	{
		a = fgetc(f);
		if ( (a & 0xC0) != 0x80) //also count the meta character one meta charactere is count as 2
			count++;
	}
	rewind(f);
	//-1 'cause EOF is a character
	return (count - 1);
}
int countWord(FILE* f)
{
	char  a[1000];
	int wordCount = 1;
	while (  !(feof(f))  )
	{
		fscanf(f,"%s",a);
		if (feof(f)) break;
		wordCount++;
	}
	rewind(f);
	return (wordCount - 1);
}
int maxWidth(FILE* f)
{
	int max = 0,
		count = 0;
	char a[1000];
	while ( !(feof(f)) )
	{
		fgets(a,1000,f);
		count = (int)strlen(a);
		
		if (max < count) max = count;
	}
	return (max);
}

void defaultDisplay(int line, int word, int chara )
{
	printf("word: %d \nline: %d \nchara: %d \n",word,line,chara);
}

void displayHelp()
{
	printf("WARNING: can only use on only \"ONE\" file\n");
	printf("--files0-from:\n");
	printf("           show the special charactere\n");
	printf("           (if there is tabulation or new line : show \\n for new line\n");
	printf("                                                      \\t for tabulation\n");
	printf("-c, --bytes");
    printf("          print the byte counts\n\n");

    printf("   -m, --chars\n");
    printf("          print the character counts\n\n");

    printf("   -l, --lines\n");
    printf("          print the newline counts\n\n");


    printf("   -L, --max-line-length\n");
    printf("          print the maximum display width\n\n");

    printf("   -w, --words\n");
    printf("          print the word counts\n\n");

    printf("   --help display this help and exit\n");

    printf("   --version\n");
    printf("          output version information and exit\n");
}

void option(int arg,char* argv[])
{
	int lineCount, wordCount, charaCount,
		i;
		char a;
	FILE* f = fopen(argv[arg - 1],"r");
	if ( f == NULL)
	{
		printf("ERROR WHEN LOADING THE FILE\n");
		exit(1);
	}
	else
	{
		if (arg == 2)
		{
			lineCount = countLine(f);
			wordCount = countWord(f);
			charaCount = countCharact(f);
			defaultDisplay(lineCount,wordCount,charaCount);
		}
		else if (arg == 1)
		{
			displayHelp();
		}
		for ( i = 1; i < arg - 1; i++)
		{
			if (strcmp(argv[i],"-c") == 0 || strcmp(argv[i],"--byte") == 0 || strcmp(argv[i],"-m") == 0 || (strcmp(argv[i],"-chars")) == 0)
			{
				printf("Number of character/byte:%d\n",countCharact(f));
			}
			if (strcmp(argv[i],"-l") == 0 || (strcmp(argv[i],"--lines")) == 0)
			{
				printf("Number of line:%d\n",countLine(f));
			}
			if(strcmp(argv[i],"-w") == 0 || (strcmp(argv[i],"--words"))== 0 )
			{
				printf("Number of words:%d\n",countWord(f));
			}
			if(strcmp(argv[i],"-L") == 0 || (strcmp(argv[i],"--max-line-length")) == 0)
			{
				printf("max Width:%d\n",maxWidth(f));
			}
			if(strcmp(argv[i],"--files0-from") == 0)
			{
				while (1)
				{
					a = fgetc(f);
					//printf("%c",a);
					if ( feof(f) ) break;
					switch (a)
					{
						default :printf("%c",a);
						break;

						case '\n':printf("\\n");
						break;

						case '\t': printf("\\t");
						break;

						case '\v' : printf("\\v");
						break;

						case '\r' : printf("\\r");
						break;

						case '\b' : printf("\\b");
						break;
					}
				}
			}
			if(strcmp(argv[i],"--version") == 0 || strcmp (argv[i],"-v"))
			{
				printf("Version: 1.0.0 \n");
			}
			if(strcmp(argv[i],"--help") == 0)
			{
				displayHelp();
			}
		}
	}
}
