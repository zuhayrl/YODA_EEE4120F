__kernel void LSB_Encoding(__global char* line, const int argLength) {

	//work item and work groups numbers
	int workItemNum = get_global_id(0); //Work item ID
	int workGroupNum = get_group_id(0); //Work group ID
	int localGroupID = get_local_id(0); //Work items ID within each work group

	if (workItemNum == 12286){
		printf("Completed");
	}
}