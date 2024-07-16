#include <stdio.h>

void option (int arg, char* argv[]);

int countLine(FILE *f);
int countCharact(FILE* f);
int countWord(FILE *f);
int maxWidth(FILE* f);
void defaultDisplay(int line, int word, int chara);
void displayHelp();
