#include<iostream>
#include<cstdlib>
#include<algorithm>
using namespace std;
int gcd(int a,int b)
{
    while(b != 0)
    {
        int r = b;
        b = a%b;
        a = r;
    }
    return a;
} 
int math(int a)
{
	if(a<0)
	{
		for(int i=1;;i++)
		{
			a=a+26;
			if(a>=0&&a<26)
				break;
		}
	}
	else
		for(int i=0;;i++)
		{
			if(a>=0&&a<26)
				break;
				a=a-26;
		}

		return a;
}
int main()
{
	int matrix[2][2];//matrix[2][2]为加密矩阵
	int dt,p,len;//dt为行列式的值，flag是明（文）长度的奇偶标志，0为偶数，1为奇数
	cout<<"请输入明文长度:";
	cin>>len;
	cout<<'\n'<<"请输入明文:";
	char *pla=new char[len];//plaz指向用户输入的明文（26个字母组成)
	int *tran1=new int[len];//tran1指向明文对应的数字组成的数组
	char *ciph=new char[len];//ciph指向密文
	int *s=new int[len];//s指向密文数字数组
	for(int i=0;i<len;i++)
		cin>>pla[i];
	//随机生成一个对模为26可逆的二阶矩阵
	do
	{
		matrix[0][0]=rand()%26;
		matrix[0][1]=rand()%26;
		matrix[1][0]=rand()%26;
		matrix[1][1]=rand()%26;
		dt = -1;
		for(p=1; dt < 0; p++)
		{
			dt = ((matrix[0][0] * matrix[1][1] - matrix[0][1] * matrix[1][0]) + 26 * p)%26; //行列式的值 
		}
	}while(dt%2==0||dt%13==0);
	cout<<'\n'<<"加密矩阵为："<<'\n'<<matrix[0][0]<<'\t'<<matrix[0][1]<<'\n'<<matrix[1][0]<<'\t'<<matrix[1][1]<<'\n';
	//判断输入明文的长度是否为偶数
	if(len % 2 == 1) 
	 {
		pla[len] = 'a';
		len = len+1;
	 }
	//将明文里的字母转化为对应的数字（要区分大小写,大写字母要先转换为小写字母)
	for(i=0; i<len; i++)
	{
		if(pla[i] >= 'A' && pla[i] <= 'Z')
		{
			pla[i] = pla[i] + 32;
		}
		if(pla[i] >= 'a' && pla[i] <'z')
			tran1[i]=pla[i]-'a'+1;
		else
			tran1[i]=0;
	}
	//以两个为一组，一次加密
	for(i=0; i<len; i=i+2)
	{
		s[i]=(tran1[i]*matrix[0][0]+tran1[i + 1]*matrix[0][1])%26;
		s[i + 1] = (tran1[i] *matrix[1][0] + tran1[i + 1] * matrix[1][1]) % 26;
    }
	//把加密后的数字数组转化为字母（不区分大小写）
	cout<<"密文:"<<'\n';
	for(i=0; i<len; i++)
	{
		if(s[i]!=0)
			ciph[i] = s[i] + 'a'-1;
		else ciph[i]='z';
		cout<<(char)ciph[i]<<'\t';
	}

	//求矩阵的逆
	int det = -1,invdet;//invdet为加密矩阵模的倒数
	int matrix2[2][2];//matrix2[2,2]为解密矩阵
	int *mes=new int[len];//mes指向解密后的明文对应的数字数组
	char *ciph2=new char[len];//ciph2指向解密后的明文
    /*for(i=0; det < 0; i++)
	{
		det = ((matrix[0][0] * matrix[1][1] - matrix[0][1] * matrix[1][0])+i*26)%26;
	}
	i=1;*/
	while(i++)
	{
		if((dt*i)%26==1)
		{
			invdet=i;	
			break;
		}
	}
    /*i = 1;
    while(1)
	{
		if((det * i) % 26 == 1)
		{
			invdet=i;
			break;
        }
		else
			i++;
	}*/
	//逆矩阵
    int temp=(matrix[1][1]*invdet);
	matrix2[0][1]=(-1 * matrix[0][1]) * invdet;
    matrix2[1][0]=(-1 * matrix[1][0]) * invdet;
    matrix2[1][1]=(matrix[0][0]*invdet);
	matrix2[0][0]=temp;
	matrix2[0][0]=math(matrix2[0][0]);
	matrix2[0][1]=math(matrix2[0][1]);
	matrix2[1][0]=math(matrix2[1][0]);
	matrix2[1][1]=math(matrix2[1][1]);
    // 得到解密后结果
	cout<<'\n'<<"解密矩阵:"<<'\n'<<matrix2[0][0]<<'\t'<<matrix2[0][1]<<'\n'<<matrix2[1][0]<<'\t'<<matrix2[1][1]<<'\n';
    for(i=0; i<len; i+=2)
	{
		mes[i] = (s[i] * matrix2[0][0] + s[i + 1] * matrix2[0][1]) % 26;
		mes[i + 1] = (s[i] * matrix2[1][0] + s[i + 1] * matrix2[1][1]) % 26;
	}
	cout<<"明文为:"<<'\n';
	for(i=0; i<len; i++)
	{
		if(mes[i]!=0)
			ciph2[i] =mes[i] + 'a'-1;
		else ciph2[i]='z';
		cout<<(char)ciph2[i]<<'\t';
	}
	return 0;
}
//
