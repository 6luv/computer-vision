#include <stdio.h>
#include <math.h>
int main(int argc, char *argv[])
{
 FILE *file1, *file2;
 int image1[800][1100];
 int image2[800][1100];
 char M;
 char N;
 int XX, YY, MAX;
 int x, y;
 int x1, y1;
 double x2, y2;
 double pi=3.14159, t=-pi/6; //30도
 int left, right;

 file1=fopen(argv[1], "r");
 fscanf(file1, "%c%c", &M, &N);
 fscanf(file1, "%d%d", &XX, &YY);
 fscanf(file1, "%d", &MAX);
 for(y=0;y<YY;y++){
  for(x=0;x<XX;x++)
   fscanf(file1, "%d", &image1[y][x]);
  }

 for(y1=0;y1<YY;y1++)
  for(x1=0;x1<XX;x1++) {
   x2 = (x1 - XX/2) * cos(t) - (y1 - YY/2) * sin(t) + XX/2; //y0 -> 영상의 중심
   y2 = (x1 - XX/2) * sin(t) + (y1 - YY/2) * cos(t) + YY/2;
   if (x2 > XX-1)
    x2 = XX-1;
   if (x2 < 0)
    x2 = 0;
   if (y2 > YY-1)
    y2 = YY-1;
   if (y2 < 0)
    y2 = 0;
   image2[(int)y2][(int)x2] = image1[y1][x1];
  }

 for(y=0; y<YY; y++) {
  for(x=1; x<XX-1; x++) {
   left = image2[y][x-1];
   right = image2[y][x+1];
   if (left != 0 && right != 0 && image2[y][x] == 0)
    image2[y][x] = (left + right) / 2;
  }
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
