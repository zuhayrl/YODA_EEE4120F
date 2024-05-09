#include <cstdlib>
using namespace std;

__kernel void createImageData(__global char (*imageData)[20], const int argLength) {

	//work item and work groups numbers
	int workItemNum = get_global_id(0); //Work item ID
	int workGroupNum = get_group_id(0); //Work group ID (i)
	int localGroupID = get_local_id(0); //Work items ID within each work group (j)

	int random_r = rand() % 256;
    int random_g = rand() % 256;
    int random_b = rand() % 256;
    char pixel[20];
    sprintf(pixel, "%d\n%d\n%d\n", random_r, random_g, random_b);
    strcpy(imageData[workGroupNum*argLength+localGroupID], pixel);
}