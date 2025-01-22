#include <stdio.h>
#include <stdlib.h>

void readMatrix(float **matrix, int n, const char *filename) 
{
FILE *file = fopen(filename, "r");
if (file == NULL) 
{
printf("Error opening matrix file: %s\n", filename);
exit(1);
}

for (int i = 0; i < n; i++) 
{
for (int j = 0; j < n; j++) 
{
fscanf(file, "%f", &matrix[i][j]);
}
}

fclose(file);
}

void readVector(float *vector, int n, const char *filename) 
{
FILE *file = fopen(filename, "r");
if (file == NULL) 
{
printf("Error opening vector file: %s\n", filename);
exit(1);
}

    
for (int i = 0; i < n; i++) 
{
fscanf(file, "%f", &vector[i]);
}

fclose(file);
}

void matrixVectorMultiplication(float **matrix, float *vector, float *result, int n) 
{
for (int i = 0; i < n; i++) 
{
result[i] = 0;
for (int j = 0; j < n; j++) 
{
result[i] += matrix[i][j] * vector[j];
}
}
}

int checkEigenvector(float *result, float *vector, int n, float *eigenvalue) 
{
*eigenvalue = result[0] / vector[0];  

for (int i = 1; i < n; i++) 
{
if (result[i] / vector[i] != *eigenvalue) 
{  
return 0;  
}
}

return 1;  
}

void appendEigenvalueToFile(const char *filename, float eigenvalue) 
{
FILE *file = fopen(filename, "a");
if (file == NULL) 
{
printf("Error opening vector file for appending: %s\n", filename);
exit(1);
}

    
fprintf(file, " %.6f", eigenvalue);
fclose(file);
}

int main()
{
int n;
FILE *file;

    
file = fopen("input.in", "r");
if (file == NULL) 
{
printf("Error opening input.in\n");
return 1;
}
fscanf(file, "%d", &n);
fclose(file);

    
float **matrix = (float **)malloc(n * sizeof(float *));
for (int i = 0; i < n; i++) 
{
matrix[i] = (float *)malloc(n * sizeof(float));
}
float *vector = (float *)malloc(n * sizeof(float));
float *result_vector = (float *)malloc(n * sizeof(float));

    
char matrix_filename[100];
sprintf(matrix_filename, "inputfiles/mat_%06d.in", n);  
readMatrix(matrix, n, matrix_filename);

    
int vec_num = 1;
while (1) 
{
        
char vector_filename[100];
sprintf(vector_filename, "inputfiles/vec_%06d_%06d.in", n, vec_num);
file = fopen(vector_filename, "r");
if (file == NULL) 
{
break;  
}
fclose(file);

readVector(vector, n, vector_filename);
matrixVectorMultiplication(matrix, vector, result_vector, n);

float eigenvalue;
if (checkEigenvector(result_vector, vector, n, &eigenvalue)) 
{
printf("vec_%06d_%06d.in : Yes : %.6f\n", n, vec_num, eigenvalue);  
appendEigenvalueToFile(vector_filename, eigenvalue);  
} 
else 
{
printf("vec_%06d_%06d.in : Not an eigenvector\n", n, vec_num);  
}

vec_num++;  
}
   
for (int i = 0; i < n; i++) 
{
free(matrix[i]);
}
free(matrix);
free(vector);
free(result_vector);

return 0;
}

