#include<iostream>
#include<cstdlib>
#include<algorithm>
using namespace std;
#define N 4//默认已知四个明文字母及其对应的暗文字母（至少四个，可以更多，然后每四个为一组）
int math(int a)//该函数用于将一个整数化为模为26时对应的数
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
	int invdet,det,det1,invdet1;//det和invdet分别是明文矩阵的行列式的值及该值在模26下的倒数，det1和invdet1是加密矩阵的行列式的值及该值在模26下的倒数
	int matrix[2][2];//matrix[2][2]为加密矩阵
	int matrix2[2][2];//matrix2[2,2]为解密矩阵
	char *m=new char[N];//m指向已知的明文
	char *n=new char[N];//n指向对应的暗文
	int *mm=new int[N];//m指向明文对应的数字数组
	int *nn=new int[N];//n指向明文对应的数字数组
	cout<<"请用户输入已知的明文和对应的暗文"<<endl;
	cout<<"明文:"<<endl;
	cin>>m;
	cout<<"暗文:"<<endl;
	cin>>n;
	//把明文和暗文化成对应的数字数组，分别存储到mm和nn指向的空间
	for(int i=0; i<N; i++)
	{
		if(m[i] >= 'A' && m[i] <= 'Z')
		{
			m[i] = m[i] + 32;
		}
		if(m[i] >= 'a' && m[i] <'z')
			mm[i]=m[i]-'a'+1;
		else
			mm[i]=0;
	}
	for(i=0; i<N; i++)
	{
		if(n[i] >= 'A' && n[i] <= 'Z')
		{
			n[i] = n[i] + 32;
		}
		if(n[i] >= 'a' && n[i] <'z')
			nn[i]=n[i]-'a'+1;
		else
			nn[i]=0;
	}
	int a=mm[0],b=mm[1],c=mm[2],d=mm[3];
	det=(a*d-b*c);
	for( i=0;det<0||det>=26;i++)
	{
		det=(det+i*26)%26;
	}
	if(det%2==0||det%13==0)
	{
		cout<<"无法破译";//给的明文向量线性相关，无法破译
		exit(0);
	}
	i=1;
	while(i++)
	{
		if((det*i)%26==1)
		{
			invdet=i;	
			break;
		}
	}
	//求加密矩阵
	int temp=mm[3]*invdet;
	mm[1]=(-1*mm[1])*invdet;
	mm[2]=(-1*mm[2])*invdet;
	mm[3]=mm[0]*invdet;
	mm[0]=temp;
	mm[0]=math(mm[0]);
	mm[1]=math(mm[1]);
	mm[2]=math(mm[2]);
	mm[3]=math(mm[3]);
	matrix[0][0]=nn[0]*mm[0]+nn[2]*mm[1];
	matrix[0][1]=nn[0]*mm[2]+nn[2]*mm[3];
	matrix[1][0]=nn[1]*mm[0]+nn[3]*mm[1];
	matrix[1][1]=nn[1]*mm[2]+nn[3]*mm[3];
	matrix[0][0]=math(matrix[0][0]);
	matrix[0][1]=math(matrix[0][1]);
	matrix[1][0]=math(matrix[1][0]);
	matrix[1][1]=math(matrix[1][1]);
	cout<<'\n'<<"加密矩阵为："<<'\n'<<matrix[0][0]<<'\t'<<matrix[0][1]<<'\n'<<matrix[1][0]<<'\t'<<matrix[1][1]<<'\n';
	//求解密矩阵
	for(i=0; det1 < 0; i++)
	{
		det1 = ((matrix[0][0] * matrix[1][1] - matrix[0][1] * matrix[1][0])+i*26)%26;
	}
	i=1;
	while(i++)
	{
		if((det1*i)%26==1)
		{
			invdet1=i;	
			break;
		}
	}
	int temp1=(matrix[1][1]*invdet1);
	matrix2[0][1]=(-1 * matrix[0][1]) * invdet1;
    matrix2[1][0]=(-1 * matrix[1][0]) * invdet1;
    matrix2[1][1]=(matrix[0][0]*invdet1);
	matrix2[0][0]=temp1;
	matrix2[0][0]=math(matrix2[0][0]);
	matrix2[0][1]=math(matrix2[0][1]);
	matrix2[1][0]=math(matrix2[1][0]);
	matrix2[1][1]=math(matrix2[1][1]);
	 // 得到解密后结果
	cout<<'\n'<<"解密矩阵:"<<'\n'<<matrix2[0][0]<<'\t'<<matrix2[0][1]<<'\n'<<matrix2[1][0]<<'\t'<<matrix2[1][1]<<'\n';
	cout<<"请输入已知密文序列长度及内容:"<<endl;
	int len;
	cout<<"长度:";
	cin>>len;
	char *cip=new char[len];//cip指向密文
	cout<<"内容:";
	cin>>cip;
	int *s=new int[len];//s指向密文数字数组
	int *mes=new int[len];//mes指向解密后的明文对应的数字数组
	char *ciph2=new char[len];//ciph2指向解密后的明文
	for(i=0; i<len; i++)
	{
		if(cip[i] >= 'A' && cip[i] <= 'Z')
		{
			cip[i] = cip[i] + 32;
		}
		if(cip[i] >= 'a' && cip[i] <'z')
			s[i]=cip[i]-'a'+1;
		else
			s[i]=0;
	}
	if(len % 2 == 1) 
	 {
		s[len] = 'a';
		len = len+1;
	 }
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


//
