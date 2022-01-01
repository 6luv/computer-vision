#include <stdio.h>
//매크로 함수
#define MAX(x, y) (((x) > (y)) ? (x) : (y))
#define MIN(x, y) (((x) < (y)) ? (x) : (y))

int main(int argc, char *argv[])
{
 FILE *file1, *file2;
 int image[800][1100];
 char M;
 char N;
 int XX, YY, MAX;
 int x, y, i;

 int label = 0;
 int max, min, Tmin; //label 위, 왼쪽 저장, 등가 테이블 값
 int t[500][2]; //등가 테이블

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

 //두번째 스캔
 for(y=1; y<YY; y++)
  for(x=1; x<XX; x++)
   if(image[y][x] != 0) //검은색이 아니라면 (레이블이 있다면)
    image[y][x] = t[image[y][x]][1]; //이미지의 두번째 값

 //영상 추출하기
 for(y=1; y<YY; y++)
  for(x=1; x<XX; x++) {
   if(image[y][x] == 3) //1인 부분
    image[y][x] = 255;
   else
    image[y][x] = 0;
  }
 
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
