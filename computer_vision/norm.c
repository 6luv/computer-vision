#include <stdio.h>
int main(int argc, char *argv[])
{
 FILE *file1, *file2;
 int image1[800][1100];
 int image2[800][1100];
 char M;
 char N;
 int yy, xx;
 int XX, YY, MAX;
 int x, y;

 file1=fopen(argv[1], "r");
 fscanf(file1, "%c%c", &M, &N);
 fscanf(file1, "%d%d", &XX, &YY);
 fscanf(file1, "%d", &MAX);
 for(y=0;y<YY;y++){
  for(x=0;x<XX;x++)
   fscanf(file1, "%d", &image1[y][x]);
  }

 //크기 정규화
 for(y=0;y<YY;y++)
  for(x=0;x<XX;x++)
  {
   xx = x * 200 / XX;
   yy = y * 100 / YY;
   image2[yy][xx] = image1[y][x];
  }

 XX = XX * 200 / XX;  //상수를 곱해야 됨
 YY = YY * 100 / YY;  //출력 영상도 반으로 줄어야 됨

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
