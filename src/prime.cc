/*
 * prime.cc
 *
 *  Created on: Nov 11, 2016
 *      Author: gjl19930713
 */
#include <algorithm>
#include <cstdio>
#include <iostream>
#include <string>
#include <cstring>
#include <climits>
#include<cmath>
#include <ctime>
#include <fstream>
#include <vector>
#include <sys/stat.h>
#include<algorithm>
using namespace std;
#define MAX_SIZE 1000


float map[MAX_SIZE][MAX_SIZE], pathWeight[MAX_SIZE];
float sum;
bool visit[MAX_SIZE];
int nodeNum, edgeNum;
FILE *fp;
FILE *newfp;
string fileName, newFileName ;


int getNumberOfNodes()
{
	int verticeNum;
	fp=fopen(fileName.c_str(),"rt+");
	if(fp==NULL) cout<<"no file "<<endl;
    fscanf(fp,"%d\n",&verticeNum);
    fclose(fp);
    cout<<" the node number is "<<verticeNum<<endl;
    return verticeNum;

}


int getNumberOfEdges()
{
	char flag;
	int edgeNum,count;
	fp=fopen(fileName.c_str(),"rt+");
	while(!feof(fp)){

		flag=fgetc(fp);
		if(flag=='\n') count++ ;
	}

	edgeNum=count;
	fclose(fp);
	cout<<" the edge number is "<<edgeNum<<endl;
	return edgeNum;

}

void readFile()
{
	fp=fopen(fileName.c_str(),"rt+");
	fscanf(fp,"%d\n",&nodeNum);
	//int nodeNum=getNumberOfNodes();
	float weight;
	int a,b;
	for( int i=1;i<=edgeNum;i++)
	{

		fscanf(fp,"%d%d%f\n",&a,&b,&weight);
		cout<<a<<" "<<b<<" "<<weight<<endl;
		if(weight<map[a][b])
		{
			map[a][b]=map[b][a]=weight;

		}


	}
	fclose(fp);

}


void initialMap()
{
	for(int i=0;i<nodeNum;i++){
		for(int j=0;j<nodeNum;j++){
			map[i][j]=INT_MAX;
		}
	}
}


void prime()
{
	newfp=fopen(newFileName.c_str(),"wt+");


	int k;
    float buffer;
	sum=0;
	//initial the original node collection
	for(int i=0;i<nodeNum;i++){
		visit[i]=false;
	}
    ///////involve the 0 node into the MST collection ///////////////////
	visit[0]=true;

	///////////////find the path from 0 node to other nodes//////////////
	for(int i=0;i<nodeNum;i++)
	{
		pathWeight[i]=map[0][i];
		//cout<<"pathWeight"<<" "<< i <<" "<<pathWeight[i]<<endl;
	}

	for(int i=0;i<nodeNum;++i)
	{
		buffer=INT_MAX;//buffer is actually the key value of original nodes

		for(int j=0;j<nodeNum;++j)
		{
			/////////////find the adjacent nodes of MST and update their key valves/////////////
			if((!visit[j])&&(buffer>pathWeight[j]))
			{
				k=j;
				//cout<<"pathweight k=j "<<pathWeight[k]<<endl;

				buffer=pathWeight[k];
				//cout<<"buffer is "<<buffer<<endl;


			}

		}
		if(buffer==INT_MAX) break;
		visit[k]=true;
		sum+=buffer;

		////////////////update the pathWeight[j]///////////////
		for(int j=0;j<nodeNum;++j)
		{
			if((!visit[j])&&(pathWeight[j]>map[k][j]))
			{
				pathWeight[j]=map[k][j];
				int tem;
				if(k>j) {
					tem=k;
					k=j;
					j=tem;
				}
				fprintf(newfp,"%d",k);
				fputs(" ",newfp);
				fprintf(newfp,"%d",j);
				fputs(" ",newfp );
				fprintf(newfp,"%f\n",map[k][j]);
				cout<<"k "<<k<<" "<<"j "<<j<<endl;
				cout<<"map[k][j] "<<map[k][j]<<endl;

			}

		}

	}
	fclose(newfp);
}


int main()
{
	fileName="test.txt";
	newFileName="result.txt";
	cout<<"sum is "<<endl;

	nodeNum=getNumberOfNodes();
	edgeNum=getNumberOfEdges();
	initialMap();
	for(int i=0;i<10;i++){
		cout<<map[i][2]<<endl;
	}
	readFile();
	prime();
	cout<<"sum is "<<sum<<endl;


}



