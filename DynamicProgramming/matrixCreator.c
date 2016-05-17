#include <stdio.h>
#include <stdlib.h>

int main()
{
	FILE* data = fopen("matrixData.txt","w");
	FILE* dims = fopen("MatrixDimensions.txt","r");
	
	int nMats;
	fscanf(dims,"%d\n",&nMats);
	
	int matDims[nMats+1];
	
	int x;
	for(x = 0; x < nMats+1; x++)
		fscanf(dims,"%d\n",&matDims[x]);
	
	int y,z;
	for(x = 0; x < nMats; x++)
	{
		int count = 0;
		for(y = 0; y < matDims[x];y++)
		{
			for(z = 0; z < matDims[x+1]; z++)
			{
				fprintf(data,"%d ",count++);
			}
			fprintf(data,"\n");
		}
	}
	
}