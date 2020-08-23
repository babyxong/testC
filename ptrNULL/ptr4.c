#include<stdio.h>
#include<string.h>
#include<stdlib.h>
#define PASSWORD "1234567"  //写入静态密码

int verify_password(char *password)//确认密码是否输入正确
{
	int authenticated;
	char buffer[8];
	authenticated=strcmp(password,PASSWORD);  
	strcpy(buffer,password);  //存在栈溢出的函数
	return authenticated;
}

void main()
{
	int valid_flag=0;
	char password[1024];
	scanf("%s",password); //输入密码
	valid_flag=verify_password(password);
	if(valid_flag) //返回0代表正确，返回1代表错误
	{
		printf("incorrect password!\n");
	}
	else
	{
		printf("success\n");
	}
	getchar();//暂停一下
}