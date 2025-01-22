#include <stdio.h>
#include <stdlib.h>

void print_to_file(int n, double **A, int format_flag) 
{
char filename[50];
FILE *file;

    
sprintf(filename, "array_%06d_%s.out", n, (format_flag == 0) ? "asc" : "bin");


if (format_flag == 0) 
{
  
file = fopen(filename, "w");
} 
else 
{
file = fopen(filename, "wb");
}

if (file == NULL) 
{
perror("Error opening file");
return;
}

if (format_flag == 0) 
{
for (int i = 0; i < n; i++) {
for (int j = 0; j < n; j++) {
fprintf(file, "%.15f ", A[i][j]);
}
fprintf(file, "\n");
}
} 
else 
{
fwrite(&A[0][0], sizeof(double), n * n, file);
}

fclose(file); 
}

int main() 
{
int n;
FILE *input = fopen("inputq06_01.in", "r");  
    
if (input == NULL) 
{
perror("Error opening input file");
return 1;
}

fscanf(input, "%d", &n);  
fclose(input);  

double **A = (double**)malloc(n * sizeof(double *));
if (A == NULL) 
{
perror("Error allocating memory for rows");
return 1;
}

for (int i = 0; i < n; i++) 
{
A[i] =(double*) malloc(n * sizeof(double));
if (A[i] == NULL)
{
perror("Error allocating memory for columns");
return 1;
}
}

for (int i = 0; i < n; i++)
{
for (int j = 0; j < n; j++)
{
A[i][j] = i + j;
}
}

    
print_to_file(n, A, 0);  
print_to_file(n, A, 1);  

    
long memory_size = 8 * n * n;  
printf("Estimated memory size of the array: %.2f MB\n", memory_size / (1024.0 * 1024.0));

    
for (int i = 0; i < n; i++) 
{
free(A[i]);
}
free(A);

return 0;
}

