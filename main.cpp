
#include<stdio.h>
#include<stdlib.h>//exit
#include<sys/types.h>//open call
#include<sys/stat.h>//open call
#include <fcntl.h>
#include <errno.h>
#include <unistd.h>
#include<sstream>
#include<iostream>
#include<fstream>
#include<string.h>
#include<dirent.h>
int n;
using namespace std;
int printdata(int pid )
{

	cout<<"pid:"<<pid<<"\n";
char file1[1000],ll[400];

sprintf(file1,"/proc/%d/comm",pid);//sprintf is used to add pid to the path
FILE *f=fopen(file1,"r");

if(!f)
return -1;

while(fgets(ll,400,f))
{
	cout<<"1.executable path:"<<ll<<"\n";
}

fclose(f);

sprintf(file1,"/proc/%d/status",pid);
f=fopen(file1,"r");

if(!f)
return -1;

while(fgets(ll,400,f))
{
	if(strncmp(ll,"State:",6)!=0)
		continue;
	char *str=ll+7;
	cout<<"2.status:"<<str<<"\n";
}

fclose(f);

sprintf(file1,"/proc/%d/status",pid);
f=fopen(file1,"r");
 
if(!f)
return -1;

while(fgets(ll,400,f))
{
	if(strncmp(ll,"PPid:",5)!=0)
		continue;
	char *str=ll+6;
	cout<<"3. Parent ID: "<<str<<"\n";
}

fclose(f);

sprintf(file1,"/proc/%d/sessionid",pid);
f=fopen(file1,"r");
 
if(!f)
return -1;

while(fgets(ll,400,f))
{
	cout<<"4. SESSION ID: "<<ll<<"\n";
}

fclose(f);


if(n==1)
{
cout<<"5. ENVIRONMENT VARIABLES: "<<"\n\n";
sprintf(file1,"/proc/%d/environ",pid);
f=fopen(file1,"r");
 
if(!f)
return -1;

while(fgets(ll,100,f))
{
	
	cout<<ll;
}

cout<<"\n";
fclose(f);



cout<<"6. file Descriptors: "<<"\n";
sprintf(file1,"/proc/%d/fd",pid);

struct dirent *fop;
DIR *dirs=opendir(file1);
while((fop=readdir(dirs))!=NULL)
	{
		char buffer[4096];

	string paths=string(file1);
		char *source=&*paths.begin();

		strcat(strcat(source,"/"),fop->d_name);
		size_t ca=readlink(source,buffer,sizeof(buffer));
		if(ca!=-1)
		{
			buffer[ca]='\0';
			cout<<string(buffer)<<endl;
			}

	}

closedir(dirs);
}

cout<<"7. ROOT FOLDER: "<<"\n";
sprintf(file1,"/proc/%d/exe",pid);

		char buffer1[4096];

		size_t ca=readlink(file1,buffer1,sizeof(buffer1));
		if(ca!=-1)
		{
			buffer1[ca]='\0';
			cout<<string(buffer1)<<endl;
			}

	cout<<"\n";




}



void list_files()
{
struct dirent *fop;
	int count=0,i;
	DIR *dirs=opendir("/proc");
if(dirs==NULL)
	{return;}

while((fop=readdir(dirs))!=NULL)
	{
		if(strcmp(fop->d_name,".")!=0 && strcmp(fop->d_name,"..")!=0)
		{
			if(isdigit(*fop->d_name))
			{
				sscanf(fop->d_name, "%d", &i);
				int m=printdata(i);
			}
		}
	}
}


int main(int argc, char *argf[])
{
//int n;
cout<<"enter choice 1.enter process \n 2.All process";
cin>>n;
int pid;

cout<<"\npid:";

if(n==1)
{
cin>>pid;
printdata(pid);
}

else if(n==2)
{
	list_files();

}
//this part print context switches,no. of processes running,blockrd ,i/o complete
ifstream mm;
string word;
mm.open("/proc/stat");

if(!mm)
return -1;

while(mm>>word)
{
	if(word=="ctxt")
	{
		mm>>word;
		cout<<"8.CONTEXT SWITCHES :"<<word<<"\n";

	}

       else if(word=="procs_running")
	{
		mm>>word;
		cout<<"9.PROCESS RUNNING :"<<word<<"\n";

	}

 else if(word=="procs_blocked")
	{
		mm>>word;
		cout<<"10.PROCESS blocked :"<<word<<"\n";

	}


}
return 0;

}
