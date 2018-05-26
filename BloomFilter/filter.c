#include <stdio.h>
#include <string.h>

#define BITSPERWORD 32  
#define SHIFT 5  
#define MASK 0x1F  
#define N 1024*1024*64  //64M bits if we have 16M item, than bits-per-key = 4;
int bitmap[1 + N/BITSPERWORD]={0};

//set the ith bit to 1
static void set_bitmap(int i,int a[]) 
{        
	a[i>>SHIFT] |= (1<<(i & MASK)); 
}   

//if the ith bit equals to 1, return 1; otherwise return 0;
static int  test_bitmap(int i,int a[])
{ 
	return (a[i>>SHIFT] & (1<<(i & MASK))) > 0; 
}  

static void reset_bitmap(void)
{
	memset(bitmap,0,(1 + N/BITSPERWORD)*sizeof(int));
}


unsigned long long hash(char *str)
{
    unsigned long long ret = 5381;
    int c;

    while ((c = *str++))
        ret = ((ret << 5) + ret) + c; 

    return ret;
}

void insert_bloom(char *str)
{
	unsigned long long checksum;
	checksum = hash(str);
	set_bitmap(checksum & 0x03FFFFFF, bitmap);
	set_bitmap(checksum>>3 & 0x03FFFFFF, bitmap);
	set_bitmap(checksum>>6 & 0x03FFFFFF, bitmap);

}

int search_bloom(char *str)
{
	unsigned long long checksum;
	checksum = hash(str);

	int ret = 1;

	if(!test_bitmap(checksum & 0x03FFFFFF, bitmap))
		ret = 0;
	if(!test_bitmap(checksum>>3 & 0x03FFFFFF, bitmap))
		ret = 0;
	if(!test_bitmap(checksum>>6 & 0x03FFFFFF, bitmap))
		ret = 0;

	return ret;
}



int main()
{
    char *name[10] = {"aaa", "bbb", "ccc", "ddd", "eee", "fff", "ggg", "hhh", "iii", "jjj"};
    int i;

    reset_bitmap();

    for(i=0; i<10; i++)
   		insert_bloom(name[i]);

   	printf("aaa is exist:%d\n", search_bloom("aaa"));
   	printf("abc is exist:%d\n", search_bloom("abc"));
   	printf("bbb is exist:%d\n", search_bloom("bbb"));
   	printf("bcde is exist:%d\n", search_bloom("bcde"));

    return 0;
}
