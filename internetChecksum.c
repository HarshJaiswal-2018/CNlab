#include<stdio.h>
#include<string.h>
//for encoding
int checksum1(int fl)
{
	char in[100];
	int buf[25];
	int i,sum1=0,n,temp;
	scanf("%s",in);
	
	//number of pairs for addition
	if(strlen(in)%2!=0)
        	n=(strlen(in)+1)/2;
	else
        	n=(strlen(in))/2;

	//getting hexadecimal values of the string. Appends 2 characters' hexa values
	for(i=0;i<n;i++)
    	{
		temp=in[i*2];
		//11printf("temp1:%x, %x\n",temp, (temp*256));  //%x directly converts it to hex.
		
		temp=(temp*256)+in[(i*2)+1]; //temp*256 converts 2 digit hex number to 4 digit number with 00 at LSB.
		//11printf("temp 2:%x\n",temp);
		
		sum1=sum1+temp; //sum with carry
		//11printf("sum1 before: %x\n",sum1);
    	}

	if(sum1%65536!=0)
   	{
        	n=sum1%65536;
        	//11printf("n=%x\n",n);  //n is the sum of hexadecimal numbers in the string without carry
        	
		sum1=(sum1/65536) + n; //sum/65536 gives carry. sum1%65536=n gives sum without carry
		//55printf("sum1=%x\n",sum1);  //sum1 is n+carry
    	}
	sum1=65535-sum1; //complimenting
	//66printf("%x\n",sum1);
	return sum1;
}

//for decoding
int checksum2(int fl)
{
	char in[100];
	int buf[25];
	int i,sum2=0,n,temp;
	scanf("%s",in);
	
	if(strlen(in)%2!=0)
        	n=(strlen(in)+1)/2;
	else
        	n=n=(strlen(in))/2;
	
	for(i=0;i<n;i++)
    	{
		temp=in[i*2];
		temp=(temp*256)+in[(i*2)+1];
		sum2=sum2+temp;
    	}

	if(sum2%65536!=0)
    	{
        	n=sum2%65536;
		sum2=(sum2/65536) + n;
    	}
	sum2=65535-sum2;
	//printf("Syndrome bit is: %x\n",sum2);
	return sum2;
}


void main()
{
	int ch,sum1,sum2;
	do
	{
		printf("1.Encode \n2.Decode \n3.Exit \n");
		scanf("%d",&ch);
		switch(ch)
        	{

			case 1: printf("Enter the string \n");
				sum1=checksum1(0);
				printf("Checksum to append is:%x \n",sum1);
				break;
			case 2: printf("Enter the string \n");
				sum2=checksum2(1);
    				if(sum1!=sum2)
				{
        				printf("The data has been tampered with or invalid checksum\n");
        				printf("The syndrome bit is %x\n",sum2);   
    				}
    				else
        				printf("The checksum is valid %x \n",sum2);
				break;
			case 3: break;
			default: printf("Invalid option, try again \n");
        	}
    	}
	while(ch!=3);
}
