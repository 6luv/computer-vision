#include <stdio.h>
#include <stdlib.h>
int main(int argc, char *argv[])
{
 FILE *file1, *file2;
 int image1[1100][1100];
 int image2[1100][1000];
 char M;
 char N;
 int XX, YY, MAX;
 int x, y;

 int r, c;   //mask에서 col, row 
 int max; //maximum

 file1=fopen(argv[1], "r");
 fscanf(file1, "%c%c", &M, &N);
 fscanf(file1, "%d%d", &XX, &YY);
 fscanf(file1, "%d", &MAX);
 for(y=0;y<YY;y++){
  for(x=0;x<XX;x++)
   fscanf(file1, "%d", &image1[y][x]);
  }
 
 for(y=0; y<YY-2; y++) 
  for(x=0; x<XX-2; x++) {
   max = 0;
   for(r=0; r<3; r++) {
    for(c=0; c<3; c++) {
     if(image1[y+r][x+c] > max)
      max = image1[y+r][x+c];
   }
  }

  image2[y+1][x+1] = max;
 }

 file2=fopen(argv[2], "w");
 fprintf(file2, "%c%c\n", M, N);
 fprintf(file2, "%d %d\n", XX, YY);
 fprintf(file2, "%d\n", MAX);
 for(y=0;y<YY;y++){
  for(x=0;x<XX;x++)
   fprintf(file2, "%4d", image2[y][x]);
  fprintf(file2, "\n");
 }

return 0;
}
