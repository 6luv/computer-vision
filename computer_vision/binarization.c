#include <stdio.h>
int main(int argc, char *argv[])
{
 FILE *file1, *file2;
 int image[1100][1100];
 char M;
 char N;
 int XX, YY, MAX;
 int x, y;

 file1=fopen(argv[1], "r");
 fscanf(file1, "%c%c", &M, &N);
 fscanf(file1, "%d%d", &XX, &YY);
 fscanf(file1, "%d", &MAX);
 for(y=0;y<YY;y++){
  for(x=0;x<XX;x++)
   fscanf(file1, "%d", &image[y][x]);
  }

 for(y=0;y<YY;y++)
  for(x=0;x<XX;x++)
   if (image[y][x] <= 50)
	image[y][x] = 0;
   else
	image[y][x] = 255;

 file2=fopen(argv[2], "w");
 fprintf(file2, "%c%c\n", M, N);
 fprintf(file2, "%d %d\n", XX, YY);
 fprintf(file2, "%d\n", MAX);
 for(y=0;y<YY;y++){
  for(x=0;x<XX;x++)
   fprintf(file2, "%4d", image[y][x]);
  fprintf(file2, "\n");
 }

return 0;
}
