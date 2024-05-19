//Open Cl Kernal for LSB LSB_Decoding

__kernel void matrixMultiplication(__global int* inputMatrixA, __global int* inputMatrixB, __global int* output, const int argSize) {

	//work item and work groups numbers
	int workItemNum = get_global_id(0); //Work item ID
	int workGroupNum = get_group_id(0); //Work group ID
	int localGroupID = get_local_id(0); //Work items ID within each work group

	int i = workGroupNum;  //row 
    int j = localGroupID;  //column                               
    int dotProduct = 0;    //placeholder for item in output array					

    //Dot Multiplication
    for (int k = 0; k < argSize; k++) 
	{
    	dotProduct += inputMatrixA[i * argSize + k] * inputMatrixB[k * argSize + j];
		//printf("i: %d    j: %d    k: %d \n")
    }

	output[workItemNum] = dotProduct;
}






