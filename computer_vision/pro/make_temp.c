#include <stdio.h>
int main(int argc, char *argv[])
{
 FILE *file;
 int image[100][100];
 char M;
 char N;
 int XX, YY, MAX;
 int x, y;

 file=fopen(argv[1], "r");
 fscanf(file, "%c%c", &M, &N);
 fscanf(file, "%d%d", &XX, &YY);
 fscanf(file, "%d", &MAX);
 for(y=0;y<YY;y++){
  for(x=0;x<XX;x++)
   fscanf(file, "%d", &image[y][x]);
  }

 printf("int [15][10]={\n");

 for(y=0;y<YY;y++) {
  for(x=0;x<XX;x++) {
   printf("%4d,", image[y][x]);
  }
  printf("\n");
 }
 
 printf("};\n");
return 0;
}
