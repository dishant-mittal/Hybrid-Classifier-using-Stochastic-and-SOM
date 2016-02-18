
#include <stdio.h>
#include <stdlib.h>
#include <conio.h>
#define ARRAYSIZE(x)  (sizeof(x)/sizeof(*(x)))
#include <math.h>
#include<string.h>


//declarations
 int p,i,j,n,k,c,s,r,in,ou;
 float b;
 int array[700][9];
    float z;
    float d[9];
    float weight[9][4]={{0.23,0.54,0.77,0.89},{0.16,0.65,0.80,0.55},{0.77,0.543,0.7,0.89},{0.11,0.32,0.74,0.9},{0.12,0.34,0.5,0.43},{0.65,0.78,0.98,0.12},{0.23,0.56,0.87,0.10},{0.87,0.90,0.21,0.54},{0.45,0.21,0.78,0.01}};
//weight update function
     void update(int c)
     {
     for (k=0; k<ARRAYSIZE(*array); k++)
     {
           weight[k][c]+= z * (array[j][k] - weight[k][c]);

     }
     }

//main
int main(void)
{
   const char filename[] = "original.csv";

   FILE *file = fopen(filename, "r");
   if ( file )
   {

      size_t i, j, k;
      char buffer[BUFSIZ], *ptr;

      for ( i = 0; fgets(buffer, sizeof buffer, file); ++i )
      {

         for ( j = 0, ptr = buffer; j < ARRAYSIZE(*array); ++j, ++ptr )
         {
            array[i][j] = (int)strtol(ptr, &ptr, 10);
         }

      }

      fclose(file);

      for ( j = 0; j < i; ++j )
      {
         printf("array[%lu]: ", (long unsigned)j);
         for ( k = 0; k < ARRAYSIZE(*array); ++k )
         {
            printf("%4d ", array[j][k]);
         }

         putchar('\n');
         in=i;
      }

   }
   else
   {
      perror(filename);
   }


  /////////////////////////////////


    printf("Kohenen's Self Organising Map..\n");
    printf("\Weight matrix generated\n");
    printf("enter the number of outputs..\n");
    scanf("%d",&ou);
    //printf("enter %d",ARRAYSIZE(*array));


   /* for(i=0; i<ARRAYSIZE(*array); i++)
    {
          printf("Entering row %d\n",(i+1));
          for(j=0; j<ou; j++)
          {
              scanf("%f",&weight[i][j]);
          }
    }*/


    printf("Enter the value of alpha.. \n");
    scanf("%f",&z);



    while(z>0.00001)
    {

    for(j=0; j<in; j++)
    {
             d[0]=0;
             d[1]=0;
             d[2]=0;
             d[3]=0;

          for(i=0; i<ou; i++)
          {
                for(n=0; n<ARRAYSIZE(*array); n++)
                {
                        d[i]+= pow((array[j][n]-weight[n][i]),2);

                }

          }

     int min=0;

      for (c = 1 ; c < ou ; c++ )
    {
        if ( d[c] < d[min] )
        {
           min = c;
        }
    }


   printf("\nwinning is %d",min);
                      update(min);

     }

     z/=2;
     printf("Now alpha=%f",z);
     printf("\n");

     }

//displaying updated weights

     printf("\nUpdated weights at the end:\n");
     for(i=0; i<ARRAYSIZE(*array); i++)
     {
              for(s=0; s<ou; s++)
              {
                       printf("%0.3f",weight[i][s]);
                       printf("\t");
              }
              printf("\n");
     }

     //////////////////predicting:::lastly
FILE *fs = fopen("C:\\Users\\dishant mittal\\Desktop\\oa.csv", "w+");
if(fs == NULL){
    printf("Couldn't open file\n");
    return -1;
    }
     float predictions[in][4];
     for(int a=0;a<in;a++)
     {
             predictions[a][0]=0;
             predictions[a][1]=0;
             predictions[a][2]=0;
             predictions[a][3]=0;
             for(int i=0;i<ou;i++)
             {

                     for(int j=0;j<ARRAYSIZE(*array);j++)
                     {
                             predictions[a][i]+= pow((array[a][j]-weight[j][i]),2);
                             }
                             }
      int minimum=0;

      for (int c = 1 ; c < ou ; c++ )
    {
        if ( predictions[a][c] < predictions[a][minimum] )
        {
           minimum = c;
        }
    }

               printf("minimum is %d\n",minimum);



             fprintf(fs,"%f,%f,%f,%f,%d\n",predictions[a][0],predictions[a][1],predictions[a][2],predictions[a][3],minimum+1);

                             }
                             fclose(fs);




     getch();
     return 0;

}
