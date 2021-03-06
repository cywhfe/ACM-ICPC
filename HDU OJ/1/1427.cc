//Result:2013-01-19 11:31:03	Accepted	1427	625MS	304K	3218 B	G++	Wizmann
#include <iostream>
#include <cstdio>
#include <cstring>
#include <cstdlib>
#include <algorithm>
#include <string>

using namespace std;

#define print(x) cout<<x<<endl
#define input(x) cin>>x
#define INF 1<<28

char chopr[]={'+','-','*','/'};

inline int calc(int a,int b,int opr)
{
	if(opr==0) return a+b;
	else if(opr==1) return a-b;
	else if(opr==2) return a*b;
	else if(opr==3)
	{
		if(b!=0 && a%b==0) return a/b;
		else return INF;
	}
	else
	{
		print(opr);
		return INF;
	}
}

bool formula_1(int num[4],int opr[3],string &result)
{
	//（a#b）#(c#d) 
	int a=calc(num[0],num[1],opr[0]);
	int b=calc(num[2],num[3],opr[2]);
	int c=calc(a,b,opr[1]);
	if(a==INF || b==INF || c==INF) return false;
	if(c==24)
	{
		char tmp[256];
		sprintf(tmp,"(%d %c %d) %c (%d %c %d)", \
					num[0],chopr[opr[0]],
					num[1],chopr[opr[1]],
					num[2],chopr[opr[2]],num[3]);
		result=string(tmp);
		
		return true;
	}
	else return false;
}

bool formula_2(int num[4],int opr[3],string &result)
{
	// ((a#b)#c)#d 
	int a=calc(num[0],num[1],opr[0]);
	int b=calc(a,num[2],opr[1]);
	int c=calc(b,num[3],opr[2]);
	if(a==INF || b==INF || c==INF) return false;
	if(c==24)
	{
		char tmp[256];
		sprintf(tmp,"( (%d %c %d) %c %d) %c %d", \
					num[0],chopr[opr[0]],
					num[1],chopr[opr[1]],
					num[2],chopr[opr[2]],num[3]);
		result=string(tmp);
		
		return true;
	}
	else return false;
}

bool formula_3(int num[4],int opr[3],string &result)
{
	// (a#(b#c)#d)
	int a=calc(num[1],num[2],opr[1]);
	int b=calc(num[0],a,opr[0]);
	int c=calc(b,num[3],opr[2]);
	if(c==24)
	{
		
		char tmp[256];
		sprintf(tmp,"(%d %c (%d %c %d)) %c %d", \
					num[0],chopr[opr[0]],
					num[1],chopr[opr[1]],
					num[2],chopr[opr[2]],num[3]);
		result=string(tmp);
		
		return true;
	}
	else return false;
}

bool slove(int num[4],string &result)
{
	int opr[3];
	sort(num,num+4);
	for(int i=0;i<4;i++)
	{
		for(int j=0;j<4;j++)
		{
			for(int k=0;k<4;k++)
			{
				opr[0]=i;opr[1]=j;opr[2]=k;
				do
				{
					if(formula_1(num,opr,result)) return true;
					else if(formula_2(num,opr,result)) return true;
					else if(formula_3(num,opr,result)) return true;
				}while(next_permutation(num,num+4));
			}
		}
	}
	return false;
}

int main()
{
	freopen("input.txt","r",stdin);
	//freopen("output.txt","w",stdout);
	int num[4];
	char str[256];
	string result;
	while(gets(str))
	{
		if(!*str || *str==' ') continue;
		char *p=str;
		for(int i=0;i<4;i++)
		{
			int w=0;
			char tmp[4]={0};
			while(*p!=' ' && *p!='\0') tmp[w++]=*p++;
			num[i]=atoi(tmp);
			if(num[i]==0)
			{
				if(*tmp=='A') num[i]=1;
				else if(*tmp=='J') num[i]=11;
				else if(*tmp=='Q') num[i]=12;
				else if(*tmp=='K') num[i]=13;
				else print(tmp);
			}
			p++;
		}
		if(slove(num,result)) puts("Yes");
		else puts("No");
		print(result);
	}
	return 0;
}
