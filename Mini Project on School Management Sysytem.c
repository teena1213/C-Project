#include<stdio.h>
#include<string.h>
#include<stdlib.h>
#include<math.h>

#define Student struct Stud

void add(FILE * fp); //to add to list fpfile pointer
FILE * del(FILE * fp);//to delete from list
void modify(FILE * fp);//to modify a record
void displayList(FILE * fp);//display whole list
void searchRecord(FILE *fp);//find a particular record
void printChar(char ch,int n);//printing a character ch n times
void printHead();//printing head line for each screen

struct Stud{
    char name[100];
    char class[50];
    int roll;
    int fee;
    float sgpa[6]; //sgpa for total no. of marks
    float cgpa; //cgpa %age
};
	
int main(){
 FILE * fp;
 Student s;
int option;
char another;

if((fp=fopen("studentInfo.txt","rb+"))==NULL)	//txt base file rb+ read mode
{
    if((fp=fopen("studentInfo.txt","wb+"))==NULL) //wb+ write mode
       {
           printf("can't open file");
           return 0;
       }
}

printHead();	//to show char values
printf("\n\t\tpress any key to continue");
getch();

while(1)
{
    printHead();
    printf("\n\t");
    printChar('-',64);	//ascii code to enter char 

    printf("\n\n\t\t\t1. ADD Student");
    printf("\n\n\t\t\t2. DELETE Student");
    printf("\n\n\t\t\t3. MODIFY Student");
    printf("\n\n\t\t\t4. DISPLAY Student LIST");
    printf("\n\n\t\t\t5. Search Record");
    printf("\n\n\t\t\t0. EXIT");

    printf("\n\n\t\tEnter Your Option :--> ");
    scanf("%d",&option);

    switch(option)
    {
        case 0: return 1;
                break;
        case 1: add(fp);
                break;
        case 2: fp=del(fp);
                break;
        case 3: modify(fp);
                break;
        case 4: displayList(fp);
                break;
        case 5: searchRecord(fp);
                break;
        default: printf("\n\t\tYou Pressed wrong key");
                  printf("\n\t\tProgram terminated");
                  getch();
                  exit(0);

    }
}
return 1;

}

void printChar(char ch,int n) //to prnt character ch, n variables
{
    while(n--)
    {
        putchar(ch);	//to print char. 
    }
}

void printHead()
{ system("cls");

printf("\n\n\t");
printChar('=',16);
printf("[SCHOOL] [FEE] [MANAGEMENT] [SYSTEM]");
printChar('=',16);
printf("\n\n\t");
printf("\n ****************************************\t");
printf("\n WELCOME TO SCHOOL FEE MANAGEMENT SYSTEM \t");
printf("\n ****************************************\t");
printf("\n");
}

// ==========ADDING NEW RECORD==========================

void add(FILE * fp)
{
printHead();
            
char another='y';	//varable y, s, i
Student s;			//s is object
int i;
float cgpa;

fseek(fp,0,SEEK_END);
while(another=='y'||another=='Y')	//	||or operator for 2 contions true
{
    printf("\n\n\t\tEnter Full Name of Student\t");
    fflush(stdin);				//clear buffer memory
    fgets(s.name,100,stdin); 
    s.name[strlen(s.name)-1]='\0';

    printf("\n\n\t\tEnter Class\t");
    fflush(stdin);
    fgets(s.class,50,stdin);
    s.class[strlen(s.class)-1]='\0';

    printf("\n\n\t\tEnter Roll number \t");
    scanf("%d",&s.roll);
    printf("\n\n\t\tEnter  Total fee of Student \t");
    scanf("%d",&s.fee);
    printf("\n\n\tEnter cgpa for 6 semesters\n\t");
    for(i=0,cgpa=0;i<6;i++)			//to enter marks
    {
	scanf("%f",&s.sgpa[i]);	//to enter marks randomly
    cgpa+=s.sgpa[i];	//formula marks add

    }

   	cgpa/=6.0;		//formula marks =%age
    s.cgpa=cgpa;	//access percentage

    fwrite(&s,sizeof(s),1,fp);

    printf("\n\n\t\tWant to enter another student info (Y/N)\t");
    fflush(stdin);
    another=getchar();
}
}

//===================DELETING A RECORD FROM LIST ============
FILE * del(FILE * fp)
{
 	printHead();

	Student s;
	int flag=0,tempRoll,siz=sizeof(s);
	FILE *ft;

if((ft=fopen("temp.txt","wb+"))==NULL)
{
    printf("\n\n\t\t\t\\t!!! ERROR !!!\n\t\t");
    system("pause");
    return fp;
}
printf("\n\n\tEnter Roll number of Student to Delete the Record");
printf("\n\n\t\t\tRoll No. : ");
scanf("%d",&tempRoll);

rewind(fp);

while((fread(&s,siz,1,fp))==1)
{
    if(s.roll==tempRoll)
    { flag=1;
    printf("\n\tRecord Deleted for");
    printf("\n\n\t\t%s\n\n\t\t%s\n\n\t\t%d\n\t",s.name,s.class,s.roll,s.fee);
    continue;
    }

    fwrite(&s,siz,1,ft); //update record
}


fclose(fp);
fclose(ft);

remove("studentInfo.txt");
rename("temp.txt","studentInfo.txt");

if((fp=fopen("studentInfo.txt","rb+"))==NULL)
{
    printf("ERROR");
    return  NULL;
}

if(flag==0) printf("\n\n\t\t!!!! ERROR RECORD NOT FOUND \n\t");

printChar('-',65);
printf("\n\t");
system("pause");
return fp;
}

//===========MODIFY A RECORD ===========================

void modify(FILE * fp)
{
printHead();
            
Student s;
int i,flag=0,tempRoll,siz=sizeof(s);
float cgpa;

printf("\n\n\tEnter Roll Number of Student to MODIFY the Record : ");
scanf("%d",&tempRoll);

rewind(fp);

while((fread(&s,siz,1,fp))==1)
{
    if(s.roll==tempRoll)
        {flag=1;
        break;
        }
}

if(flag==1)
    {
    fseek(fp,-siz,SEEK_CUR);//file size
    printf("\n\n\t\tRECORD FOUND");
    printf("\n\n\t\tEnter New Data for the Record");

    printf("\n\n\t\tEnter Full Name of Student\t");
    fflush(stdin);
    fgets(s.name,100,stdin);
    s.name[strlen(s.name)-1]='\0';

    printf("\n\n\t\tEnter Class\t");
    fflush(stdin);
    fgets(s.class,50,stdin);
    s.class[strlen(s.class)-1]='\0';

    printf("\n\n\t\tEnter Roll number \t");
    scanf("%d",&s.roll);
    printf("\n\n\t\tEnter Total fee of Student \t");
    scanf("%d",&s.fee);
    printf("\n\n\tEnter cgpa for 6 semesters\n\t");//modify
    for(i=0,cgpa=0;i<6;i++)
    {scanf("%f",&s.sgpa[i]);
   cgpa+=s.sgpa[i];

    }
    cgpa=cgpa/6.0;

    fwrite(&s,sizeof(s),1,fp);
}

else printf("\n\n\t!!!! ERROR !!!! RECORD NOT FOUND");

printf("\n\n\t");
system("pause");

}

//====================DISPLAY THE LIST =================

void displayList(FILE * fp)
{   printHead();
    Student s;
    int i,siz=sizeof(s);

    rewind(fp);

    while((fread(&s,siz,1,fp))==1)
    {
        printf("\n\t\tNAME : %s",s.name); //s. access specifier
        printf("\n\n\t\tCLASS : %s",s.class);
        printf("\n\n\t\tROLL : %d",s.roll);
         printf("\n\n\t\tFEE : %d",s.fee);
        printf("\n\n\tSGPA: ");

        for(i=0;i<6;i++)
            printf("| %.2f |",s.sgpa[i]);//space formatting
        printf("\n\n\t\tCGPA : %.2f\n\t",s.cgpa);
        printChar('-',65);
    }
    printf("\n\n\n\t");
     printChar('*',65);
    printf("\n\n\t");
    system("pause");
}


void searchRecord(FILE *fp)
{printHead();

int tempRoll,flag,siz,i;
Student s;
char another='y';

siz=sizeof(s);

while(another=='y'||another=='Y')
{
printf("\n\n\tEnter Roll Number of Student to search the record : ");
scanf("%d",&tempRoll);

rewind(fp);

while((fread(&s,siz,1,fp))==1)
{
    if(s.roll==tempRoll)
        {flag=1;	//keyword flag
        break;
        }
}

if(flag==1)
    {
    	 
    printf("\n\t\tNAME : %s",s.name);
        printf("\n\n\t\tCLASS : %s",s.class);
        printf("\n\n\t\tROLL : %d",s.roll);
        printf("\n\n\t\tFEE : %d",s.fee);
        printf("\n\n\tSGPA: ");

        for(i=0;i<6;i++)
            printf("| %.2f |",s.sgpa[i]);
        printf("\n\n\t\tcgpa : %.2f\n\t",s.cgpa);
        printChar('-',65);

}
else printf("\n\n\t\t!!!! ERROR RECORD NOT FOUND !!!!");
printf("\n\n\t\tWant to enter another search (Y/N)");
fflush(stdin);
another=getchar(); //for input another information
}
}

