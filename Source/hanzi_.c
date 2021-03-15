#include<stdio.h>
#include"hanzi_.h"
#include<graphics.h>
#include<fcntl.h>
#include<io.h>
#include<conio.h>
#include<stdlib.h>
#include<dos.h>

void hanzi_s(int x,int y,char *s,int color)  /*16���庺�����*/
{
	FILE *fp;
    char buffer[32];    /* 32�ֽڵ���ģ������ */
    int i,j,k;
    unsigned char qh,wh;
    unsigned long location;
	if((fp=fopen("hzk\\hzk16s","rb"))==NULL)
    {
    	printf("Can't open hzk16!");
		getchar();
        exit(1);
    }
    while(*s)
    {
     	qh=*s-0xa0;
        wh=*(s+1)-0xa0;
        location=(94*(qh-1)+(wh-1))*32L; /* ���㺺����ģ���ļ��е�λ�� */
        fseek(fp,location,SEEK_SET);
        fread(buffer,32,1,fp);
        for(i=0;i<16;i++)
         for(j=0;j<2;j++)
          for(k=0;k<8;k++)
           if(((buffer[i*2+j]>>(7-k))&0x1)!=NULL)
              putpixel(x+8*j+k,y+i,color);
        s+=2;
        x+=16; /* ���ּ�� */
    }
    fclose(fp);
}

int ChineseStrlen(char *s) /*���㺺�ָ���*/
{
	int i,n = 0;
	
	for(i = 0;s[i];i ++)
	  if(s[i] < 0)  n ++;
	
	return (n/2);
}

void yingwen(char *s,int x,int y,int dx,int dy,short color) 
{
	char *s1;
	unsigned long offset;
	FILE *fp;
	char buffer[16]; //buffer�����洢һ���ַ�
	int m,n,i,j;
	if ((fp=fopen("hzk\\ASC16","rb"))==NULL)
	{
		printf("Can't open asc16,Please add it");
		exit(1);
	}
	s1=s;
	while(*s)
	{
		offset=(*s)*16+1; //������ַ����ֿ���ƫ����
		fseek(fp,offset,SEEK_SET);
		fread(buffer,16,1,fp); //ȡ���ַ�16�ֽڵĵ�����ģ����buffer��

		for(n=0;n<dx;n++) //��16λ�ֽڵĵ���λ����Ļ�ϴ�ӡ����(1:��ӡ,0:����ӡ),��ʾ�ַ�
		{
			for(i=0;i<16;i++)
			{
						for(j=0;j<8;j++)
						{
							for(m=0;m<dy;m++)
							{
								if(((buffer[i]>>(7-j))&0x1)!=NULL)
								{
									putpixel(x+j+n,y+i+m,color);
								}
							}
						}

			}
		}
		s++; //һ���ַ�����ռ��һ���ֽ�
		x+=8*dx;//�ַ�����
	}
	s=s1;
	fclose(fp);

}

void hanzi48(int x0,int y0,char *s,int color)
{
  FILE *fp;
  unsigned char qh,wh;
  unsigned long offset;
  unsigned char mask[]={0x80,0x40,0x20,0x10,0x08,0x04,0x02,0x01};
  int i,j;
  int x,y;
  char a[288];
  int pos;
  y=y0;
  if(*s=='\0')
  {
	*(s+2)=NULL;
  }
  qh=*s-0xa0;
  wh=*(s+1)-0xa0;
  if((fp=fopen("hzk\\48.dzk","rb+"))==NULL)
  {
	printf("\n can't open file");
	exit(1);
  }
  rewind(fp);
  offset=(94*(qh-1)+(wh-1))*288L;
  fseek(fp,offset,0);
  fread(a,288,1,fp);
  fclose(fp);
  for(i=0;i<48;i++)
  {
	x=x0;
	pos=6*i;
	for(j=0;j<48;j++)
	{
	  if((mask[j%8]&a[pos+j/8])!=NULL)
	  {
		putpixel(x,y,color);
	  }
	  x++;
	}
	y++;
  }
}

void hz48(int a,int b,int c,int d,char *s1,int color)
{
    char ch; //�洢����ַ����һ�����ֵ�qh
	int i;   //ѭ������ 
	char*s=s1;
  int x=a,y=b;

  if(a>=c||b>d)
  {
	hanzi_s(200,250,"�ı������ô���",-6045);
	exit(1);
  }
  while(*s!=NULL)
  {
	while((x<c)&&(*s!=NULL))
	{ 
	  if(*s>=20&&*s<=126)
  { 
     for(i=0;*(s+i)>=20&&*(s+i)<=126;i++) //�ҵ��ַ���֮������ĺ��� 
	 { 	
	 }     
	 ch=*(s+i);
	 *(s+i)='\0'; 
  	//Outtextxy48(s,x,y,color);
  	*(s+i)=ch;
  	s=s+i;
  	x=x+42*i;
  }
  else 
  {
	  hanzi48(x,y,s,color);
	  x=x+42;
	  s=s+2;
   }
	}
	x=a;
	y=y+42;
	if(y-42>d)
	{
	  hanzi_s(200,200,"�ı������ù�С",-6045);
	}
  }
}

void hz24kaiti(int a,int b,int c,int d,char *s1,int color)
{
    char ch; //�洢����ַ����һ�����ֵ�qh
	int i;   //ѭ������ 
	char*s=s1;
  int x=a,y=b;

  if(a>=c||b>d)
  {
	exit(1);
  }
  while(*s!=NULL)
  {
	while((x<c)&&(*s!=NULL))
	{ 
	  if(*s>=20&&*s<=126)
  { 
     for(i=0;*(s+i)>=20&&*(s+i)<=126;i++) //�ҵ��ַ���֮������ĺ��� 
	 { 	
	 }  
	 x=x-10;   
	 ch=*(s+i);
	 *(s+i)='\0'; 
  	*(s+i)=ch;
  	s=s+i;
  	x=x+20*i;
  }
  else 
  {
	  hanzi24kaiti(x,y,s,color);
	  x=x+28;
	  s=s+2;
   }
	}
	x=a;
	y=y+28;
	if(y-28>d)
	{
	  ; 
	}
  }
}

void hanzi24kaiti(int x0,int y0,char *s,int color)
{
  FILE *fp;
  unsigned char qh,wh;
  unsigned long offset;
  unsigned char mask[]={0x80,0x40,0x20,0x10,0x08,0x04,0x02,0x01};
  int i,j;
  int x,y;
  char a[72];
  int pos;
  y=y0;
  if(*s=='\0')
  {
	*(s+2)=NULL;
  }
  qh=*s-0xa0;
  wh=*(s+1)-0xa0;
  if((fp=fopen("hzk\\24kaiti.dzk","rb+"))==NULL)
  {
	printf("\n can't open file");
	exit(1);
  }
  rewind(fp);
  offset=(94*(qh-1)+(wh-1))*72L;
  fseek(fp,offset,0);
  fread(a,72,1,fp);
  fclose(fp);
  for(i=0;i<24;i++)
  {
	x=x0;
	pos=3*i;
	for(j=0;j<24;j++)
	{
	  if((mask[j%8]&a[pos+j/8])!=NULL)
	  {
		putpixel(x,y,color);
	  }
	  x++;
	}
	y++;
  }
}

 void hanzi(int x0,int y0,char *s,int color)
{
  FILE *fp;
  unsigned char qh,wh;
  unsigned long offset;
  unsigned char mask[]={0x80,0x40,0x20,0x10,0x08,0x04,0x02,0x01};
  int i,j;
  int x,y;
  char a[32];
  int pos;
  y=y0;
  if(*s=='\0')
  {
	*(s+2)=NULL;
  }
  qh=*s-0xa0;
  wh=*(s+1)-0xa0;
  if((fp=fopen("HZK\\HZK16S","rb+"))==NULL)
  {
	printf("\n can't open file");
	exit(1);
  }
  rewind(fp);
  offset=(94*(qh-1)+(wh-1))*32L;
  fseek(fp,offset,0);
  fread(a,32,1,fp);
  fclose(fp);
  for(i=0;i<16;i++)
  {
	x=x0;
	pos=2*i;
	for(j=0;j<16;j++)
	{
	  if((mask[j%8]&a[pos+j/8])!=NULL)
	  {
		putpixel(x,y,color);
	  }
	  x++;
	}
	y++;
  }
  }