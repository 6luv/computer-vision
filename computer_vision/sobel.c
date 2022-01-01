#include <stdio.h>
#include <stdlib.h>
int main(int argc, char *argv[])
{
 FILE *file1, *file2;
 int image1[768][1100];
 int image2[768][1000];
 char M;
 char N;
 int XX, YY, MAX;
 int x, y;

 int sum=0, sumX=0, sumY=0, r, c;   //mask에서 col, row
 int maskX[3][3] = {{-1, 0, 1},
                    {-2, 0, 2},
		    {-1, 0, 1}};          //sobel mask

 int maskY[3][3] = {{-1, -2, -1},
                    { 0,  0,  0},
                    { 1,  2,  1}};

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
   for(r=0; r<3; r++) {
    for(c=0; c<3; c++) {
     sumX += image1[y+r][x+c] * maskX[r][c];  //convolution
     sumY += image1[y+r][x+c] * maskY[r][c];
   }
  }

  sum = abs(sumX) + abs(sumY); //convolution 결과에 절댓값

  if(sum > 255)     //clamping
   sum = 255;
  else if (sum < 0)
   sum = 0;

  image2[y+1][x+1] = sum;

  sumX = 0;                  //초기화
  sumY = 0;
  
 }

 for(y=0; y<YY; y++)   //반전
  for(x=0; x<XX; x++)
   image2[y][x] = 255 - image2[y][x];

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
