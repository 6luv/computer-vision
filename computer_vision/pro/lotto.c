#include <stdio.h>
#include <stdlib.h> //atoi
#include "template.h"
#define MAX(x, y) (((x) > (y)) ? (x) : (y))
#define MIN(x, y) (((x) < (y)) ? (x) : (y))

int main(int argc, char *argv[])
{
 FILE *file1, *file2;
 int image[800][1100];
 int image2[800][1100];
 int image3[800][1100];
 char M;
 char N;
 int XX, YY, MAX;
 int x, y, i, j, a = 0, b = 0;
 int xsize, ysize;
 int xx, yy;
 int xsize_min, ysize_min;

 int label = 0;
 int max, min, Tmin; //label 위, 왼쪽 저장, 등가 테이블 값
 int t[500][2]; //등가 테이블
 int hash[500]={0}; 
 int cnt, key[1][1];
 int arr[13][3] = {0};
 int distance[10] = {0};
 int class, Dmin = 150;
 int sum[6] = {0};
 int lotto_num[6] = {9, 13, 28, 31, 39, 41};
 int flag = 0;

 file1=fopen(argv[1], "r");
 fscanf(file1, "%c%c", &M, &N);
 fscanf(file1, "%d%d", &XX, &YY);
 fscanf(file1, "%d", &MAX);
 for(y=0;y<YY;y++){
  for(x=0;x<XX;x++)
   fscanf(file1, "%d", &image[y][x]);
  }

 //첫 번재 스캔
 for(y=1;y<YY;y++)
  for(x=1;x<XX;x++)
   if(image[y][x] == 255) //1
    if((image[y-1][x] == 0) && (image[y][x-1] == 0)) //첫 번째 조건 위, 왼쪽 배경
     {
      label++;
      image[y][x] = label;
      t[label][0] = label;
      t[label][1] = label;
     }
    else if((image[y-1][x] != 0) && (image[y][x-1] == 0)) //2
     image[y][x] = image[y-1][x];
    else if((image[y-1][x] == 0) && (image[y][x-1] != 0)) //2
     image[y][x] = image[y][x-1];
    else if(image[y-1][x] == image[y][x-1]) //3
     image[y][x] = image[y-1][x];
    else                       //4 작은 수 찾아서 레이블 넣음
    {
     max = MAX(image[y-1][x], image[y][x-1]);
     min = MIN(image[y-1][x], image[y][x-1]);
     image[y][x] = min;
     
     Tmin = MIN(t[max][1], t[min][1]);  //등가테이블 두번째 컬럼에서 작은 값
     t[max][1] = Tmin;                  //작은 값 넣음
     t[min][1] = Tmin;
    }

 //등가 테이블 출력
 for(i=1; i<=label; i++)
  printf("t[%d][0] = %d t[%d][1] = %d\n", i, t[i][0], i, t[i][1]);

 printf("\n");

 //모든 등가테이블 정리
 for(i=1; i<=label; i++)
  t[i][1] = t[t[i][1]][1]; //두번째항이 가리키는 값의 두번째항

 for(i=1; i<=label; i++)
  printf("t[%d][0] = %d t[%d][1] = %d\n", i, t[i][0], i, t[i][1]);

 for(i=0; i<=label; i++)
  hash[t[i][1]] = t[i][1];

 cnt = 1;
 for(i=0; i<=label; i++)
  if(hash[i] != 0)
   hash[i] = cnt++;

 for(i=0; i<=label; i++)
  t[i][1] = hash[t[i][1]];

 printf("\n");

 for(i=1; i<=label; i++)
  printf("t[%d][0] = %d t[%d][1] = %d\n", i, t[i][0], i, t[i][1]);

 //두번째 스캔
 for(y=1; y<YY; y++)
  for(x=1; x<XX; x++)
   if(image[y][x] != 0) //검은색이 아니라면 (레이블이 있다면)
    image[y][x] = t[image[y][x]][1]; //이미지의 두번째 값
 

 //영상 추출하기
 for(label=1; label<cnt; label++) { //자동으로 정보주기
  printf("label = %d\n", label);
  ysize_min = 799;
  xsize_min = 1099;
  xsize = 0;
  ysize = 0;
  for(y=1; y<YY; y++)
   for(x=1; x<XX; x++)
    if(image[y][x] == label) //1인 부분
     image2[y][x] = 255;
    else
     image2[y][x] = 0;

  for(y=1; y<YY; y++) {
   for(x=1; x<XX; x++)
    if(image[y][x] == label) {
     if(ysize_min > y)
      ysize_min = y;
     ysize++;
     break;
    }
  }

  for(x=1; x<XX; x++) {
   for(y=1; y<YY; y++)
    if(image[y][x] == label) {
     if(xsize_min > x)
     {
      xsize_min = x;
      arr[label][0] = label;
      arr[label][1] = xsize_min;
     }
     xsize++;
     break;
    }
  }
  
  for(y=ysize_min; y<ysize_min + ysize; y++){
   for(x=xsize_min; x<xsize_min + xsize; x++) {
    image3[b][a] = image2[y][x];
    a++;
   }
   b++;
   a = 0;
  }
  b = 0;

  for(y=0; y<ysize; y++) {
   for(x=0; x<xsize; x++) {
    xx = x * 10 / xsize;
    yy = y * 15 / ysize;
    image2[yy][xx] = image3[y][x];
   }
  }

  xsize = xsize * 10 / xsize;
  ysize = ysize * 15 / ysize;
/*
  file2=fopen("label.pgm", "w");
  fprintf(file2, "%c%c\n", M, N);
  fprintf(file2, "%d %d\n", xsize, ysize);
  fprintf(file2, "%d\n", MAX);
  for(y=0; y<ysize; y++) {
   for(x=0; x<xsize; x++)
    fprintf(file2, "%4d", image2[y][x]);
   fprintf(file2, "\n");
  }
  fclose(file2);
  system("xv label.pgm");
 */
  for(y=0; y<ysize; y++){
   for(x=0; x<xsize; x++) {
    if(abs(image2[y][x] - zero[y][x]) == 255)
     distance[0]++;

    if(abs(image2[y][x] - one[y][x]) == 255)
     distance[1]++;

    if(abs(image2[y][x] - two[y][x]) == 255)
     distance[2]++;

    if(abs(image2[y][x] - three[y][x]) == 255)
     distance[3]++;

    if(abs(image2[y][x] - four[y][x]) == 255)
     distance[4]++;

    if(abs(image2[y][x] - five[y][x]) == 255)
     distance[5]++;

    if(abs(image2[y][x] - six[y][x]) == 255)
     distance[6]++;

    if(abs(image2[y][x] - seven[y][x]) == 255)
     distance[7]++;

    if(abs(image2[y][x] - eight[y][x]) == 255)
     distance[8]++;

    if(abs(image2[y][x] - nine[y][x]) == 255)
     distance[9]++;
   }
  }

  for(i=0; i<10; i++)
   printf("distance[%d] = %d\n", i, distance[i]);

  for(i=0; i<10; i++) {
   if(distance[i] < Dmin) {
    Dmin = distance[i];
    class = i;
    arr[label][2] = class;
   }
  }

  for(i=0; i<10; i++){
   distance[i] = 0;
   Dmin = 150;
  }
  printf("The input character is %d\n\n", class); 

  printf("label  x  class\n");
  for(i = 1; i <= label; i ++)
   printf("%3d  %3d  %3d\n", arr[i][0], arr[i][1], arr[i][2]);
  printf("\n");
  //label 정리
  if(label == cnt - 1) {
   for(i = 2; i < cnt; i++) {
    key[i][1] = arr[i][1];
    key[i][2] = arr[i][2];
    for(j = i - 1; j>0 && arr[j][1] > key[i][1]; j--) {
     arr[j+1][1] = arr[j][1];
     arr[j+1][2] = arr[j][2];
    }
    arr[j+1][1] = key[i][1];
    arr[j+1][2] = key[i][2]; 
   }
   printf("label  x  class\n");
   for(i = 1; i <= label; i++)
    printf("%3d  %3d  %3d\n", arr[i][0], arr[i][1], arr[i][2]);
  }
 }
 
 // label 홀수는 *10 + 짝수 label 더하기, 번호 출력
 printf("\n내 번호   : ");
 for(i = 1; i < label; i+=2)
 {
  sum[i - (i+1)/2] = arr[i][2] * 10 + arr[i+1][2];
  printf("%2d ", sum[i-(i+1)/2]);
 }
 printf("\n");
 
 printf("당첨 번호 : ");
 for(i = 0; i < 6; i ++) {
  printf("%2d ", lotto_num[i]);
 }
 printf("\n");
 
 // 몇개 맞았는지 판단
 for(i = 0; i < 6; i ++) 
  for(j = 0; j < 6; j ++) 
   if(lotto_num[i] == sum[j]) 
    flag++;

 printf("결과      : ");
 switch(flag) {
  case 0:
	  printf("꽝입니다.\n");
	  break;
  case 1:
	  printf(" 1개 일치합니다.\n");
	  break;
  case 2:
	  printf(" 2개 일치합니다.\n");
	  break;
  case 3:
	  printf(" 3개 일치합니다.\n");
	  break;
  case 4:
	  printf(" 4개 일치합니다.\n");
	  break;
  case 5:
	  printf(" 5개 일치합니다.\n");
	  break;
  case 6:
	  printf(" 당첨입니다.\n");
	  break;
 }

 return 0;
}
