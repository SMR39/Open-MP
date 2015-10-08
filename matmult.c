#include <omp.h>
#include <stdio.h>

int main()
    {    
        int mat1[3][3];
        int mat2[3][3];
        int mat3[3][3] = {0,0,0,0,0,0,0,0,0};
        int nb=4,me;
        int i, j, k;
        for (i=0; i<3; i++)
        {
            for (j=0; j<3; j++)
                {
                    mat1[i][j] = i+j+1;
                    mat2[i][j] = i+j+2;    
                }
        }
        printf("printing first matrix\n");
        for (i=0; i<3; i++)
        {
            for (j=0; j<3; j++)
                {
                    printf("\t %d",mat1[i][j]);    
                }
            printf("\n");
        }
        printf("printing second matrix\n");
        for (i=0; i<3; i++)
        {
            for (j=0; j<3; j++)
                {
                    printf("\t %d",mat2[i][j]);    
                }
            printf("\n");
        }

        omp_set_num_threads(4);

        

        #pragma omp parallel shared(mat1,mat2,mat3) private(i,j,k)
        {
        me = omp_get_thread_num();
        nb = omp_get_num_threads();
        if(me == 0)
        {
            nb = omp_get_num_threads();
            printf("There are %d threads assigned for the matrix multiplication\n",nb);
        }
        
                
        #pragma omp for schedule(dynamic)        
        for (i=0; i<3; i++)
        {
            for (j=0; j<3; j++)
                {
                    for (k=0; k<3; k++)
                    {
                        mat3[i][j] += mat1[i][k] * mat2[k][j];
                    }
                }
        }
        
        }
        printf("printing the third matrix with multipication \n");
        for (i=0; i<3; i++)
        {
            for (j=0; j<3; j++)
                {
                    printf("\t %d",mat3[i][j]);    
                }
            printf("\n");
        }
        return 0;
}
