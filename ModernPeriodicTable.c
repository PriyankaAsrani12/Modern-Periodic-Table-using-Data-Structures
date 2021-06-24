#include <stdio.h>
#include <malloc.h>
#include <string.h>
#include <stdlib.h>
#include<windows.h>
#include<dos.h>
#include<dir.h>


typedef struct node
{
    int a_no;
    float a_mass;
    char name[50];
    char sym[10];
    struct node*link;
}NODE;


typedef struct
{
    NODE* start;
    NODE* end;
    int count;
}PERIODIC;
COORD coord={0,0}; // this is global variable
                                    //center of axis is set to the top left corner of the screen
 void gotoxy(int x,int y)
 {
   coord.X=x;
 coord.Y=y;
 SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE),coord);
 }
 void SetColor(int ForgC)
 {
     WORD wColor;


      HANDLE hStdOut = GetStdHandle(STD_OUTPUT_HANDLE);
      CONSOLE_SCREEN_BUFFER_INFO csbi;


                       //We use csbi for the wAttributes word.
     if(GetConsoleScreenBufferInfo(hStdOut, &csbi))
     {
                 //Mask out all but the background attribute, and add in the forgournd     color
          wColor = (csbi.wAttributes & 0xF0) + (ForgC & 0x0F);
          SetConsoleTextAttribute(hStdOut, wColor);
     }
     return;
 }


PERIODIC* create()
{
    PERIODIC* periodic;
    periodic=(PERIODIC*)malloc(sizeof(PERIODIC));
    if(periodic!=NULL)
    {
        periodic->start=periodic->end=NULL;
        periodic->count=0;
        printf("Headnode Created\n");
    }
    return periodic;
}


void table(NODE* p)
{
    char h[5];
    printf("\nEnter the data to insert : ");
    printf("\n\tEnter the atomic number :");
    scanf("%d",&p->a_no);
    printf("\n\tEnter the atomic mass : ");
    scanf("%f",&p->a_mass);
    printf("\n\tEnter the name of the element : ");
    scanf("%s",p->name);
    printf("\n\tEnter the symbol of element : ");
    scanf("%s",p->sym);


}


int insert(PERIODIC* periodic,int position)
{
    NODE*ptr,*p;
    int i;


    ptr=(NODE*)malloc(sizeof(NODE));


    if(ptr==NULL)
    return 0;


    table(ptr);
    ptr->link=NULL;


    if(periodic->count==0)
        periodic->start=periodic->end=ptr;/*Insertion of first element*/
    else
        if(position<=1)
    {
        ptr->link=periodic->start;
        periodic->start=ptr;
    }/*Insertion at beginning*/
    else
        if(position>periodic->count)
    {
        periodic->end->link=ptr;
        periodic->end=ptr;
    }/*Insertion at end*/
    else
    {
        p=periodic->start;
        for(i=1;i<=position-2;i++)
            p=p->link;
        ptr->link=p->link;
        p->link=ptr;
    }/*Insertion inbetween*/
    periodic->count++;
    return 1;
}


void display(NODE* q)
{
       SetColor(3);
    printf("\n\nThe Name of the element is : %s",q->name);
    printf("\nThe atomic number of the element is : %d",q->a_no);
    printf("\nThe atomic mass number of the element is : %f",q->a_mass);
    printf("\nSymbol of element is : %s",q->sym);


}


void traverse(PERIODIC* periodic)
{
    NODE*p;
    p=periodic->start;
    while(p!=NULL)
    {
        display(p);
        p=p->link;
    }
}


int count(PERIODIC*periodic)
{
    return periodic->count;
}


int search(PERIODIC*periodic,char x[])
{
    NODE*p;
    int pos=1;


    p=periodic->start;


    while(p!=NULL&&strcmpi(p->name,x))
    {
        p=p->link;
        pos++;
    }
    if(p==NULL)
        return 0;
    else
        return pos;
}


int delete_no(PERIODIC *periodic,char x[])
{
    NODE*p,*q;


    p=NULL;
    q=periodic->start;


    while(q!=NULL&&strcmpi(q->name,x))
    {
        p=q;
        q=q->link;
    }


    if(q==NULL)
        return 0;
    else
        if(p==NULL)
    {
        periodic->start=q->link;
    }
    else
        if(q==periodic->end)
    {
        p->link=NULL;
        periodic->end=p;
    }
    else
        p->link=q->link;


    free(q);
    periodic->count--;
    return 1;
}


void * retrieve(PERIODIC*periodic, int position)
{
    int i;
    NODE* p;


    if(periodic->count==0)
        return NULL;
    else
    {
        p=periodic->start;
        for(i=0;i<position-2;i++)
            p=p->link;


    }
}










int main()
{
   int position,i;
   void* p;
   PERIODIC* p1=NULL;
   p1=create();
   NODE* ele;
   int option;
   char x[10],a[10];
   int y,b;
   gotoxy(15,1);
 SetColor(5);
printf("****MODERN PERIODIC TABLE****\n");
   do
    {


        SetColor(10);
        printf("\n\n1:Insertion of element\n");
        SetColor(9);
        printf("2:Deletion of element\n");


        SetColor(14);
        printf("3:Display the elements of periodic table.\n");


        SetColor(5);
        printf("4:Searching an element\n");


        SetColor(9);
        printf("5: Retrieving an element\n");


        SetColor(14);
        printf("6.Exit.\n");
        SetColor(4);
        printf("Enter your option :");
        scanf("%d",&option);
        SetColor(3);
        switch(option)
        {
            case 1:
                printf("Enter the position :");
                scanf("%d",&position);
                i=insert(p1,position);
                if(i==1)
                    printf("\nElement successfully inserted\n");
                break;


            case 2:
                printf("Enter which element to delete\n");
                scanf("%s",x);
                y=delete_no(p1,x);
                if(y==1)
                    printf("%s is deleted",&x);
                break;


            case 3:
    printf("\n*******************************************\n");
    printf("The elements of the periodic table are : ");
    printf("\n******************************************\n");
                traverse(p1);
    printf("\n******************************************\n");
                break;


            case 4:
                printf("Enter the element to be searched :\n");
                scanf("%s",a);
                b=search(p1,a);
                if(b!=0)
                    printf("%s found at position %d",a,b);
                else
                    printf("Element not found\n");
                break;


            case 5:
                printf("Enter the position=");
                scanf("%d",&position);
                p=retrieve(p1,position);
                if (p!=NULL)
                    printf("%d retrieved\n",*(int*)p);
                else
                    printf("Unable to retrieve data\n");
                break;


            case 6:
                break;


        }
    }while(option!=5);
    return 0;


}