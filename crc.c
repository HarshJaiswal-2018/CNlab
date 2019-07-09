#include<stdio.h>
#include<string.h>
#define N strlen(g)

char t[28];
char cs[28];
char g[] = "10001000000100001";
int a,e,c;

void xor()
{
	for(c=1;c<N;c++)
		cs[c] = ((cs[c]==g[c])?'0':'1');
}
void crc()
{
	for(e=0;e<N;e++)
		cs[e]=t[e];

	do
	{
		if(cs[0]=='1')
		xor();

		for(c=0;c<N-1;c++)
			cs[c]=cs[c+1];
	
		cs[c]=t[e++];
	}
	while(e<=a+N-1);
}

int main()
{
	printf("Enter data : ");
	scanf("%s",t);
	
	printf("Generating Polynomial is : %s\n",g);
	a=strlen(t);

	for(e=a;e<a+N-1;e++)
		t[e]='0';
	printf("Padded data is : %s\n",t);
	crc();

	printf("Checksum is : %s\n",cs);
	for(e=a;e<a+N-1;e++)
		t[e]=cs[e-a];

	printf("Final Codeword is : %s\n",t);
	printf("Test Error Detection 0[yes] 1[no] : ");
	scanf("%d",&e);

	if(e==0)
	{
		do
		{
			printf("position to insert error : ");
			scanf("%d",&e);
		}
		while(e==0||e>a+N-1);
		
		t[e-1]=(t[e-1]=='0')?'1':'0';
		printf("Errorneous Data : %s	\n",t);
	}
	crc();
	for(e=0;(e<N-1)&&(cs[e]!='1');e++) {}
		if(e<N-1)
			printf("Error detected\n");
		else
			printf("No error detected\n");
	return 0;
}
