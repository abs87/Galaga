#include <GL/glut.h>
#include <string.h>
#include<stdio.h>
#include<stdlib.h>
#include<time.h>
int page1st=1,page2nd=0;

struct BBot //Rocket Bot
{
    float x;
    float y;
    float step;
};

struct Bullet   //Bullet Bot
{
    float x;
    float y;
    struct Bullet *next;
}*head=NULL,*tail=NULL,*temp=NULL,*temp1,*temp2;

struct TBot    // Bullet Generator
{
    float x;
    float y;
    struct TBot *next;
}*Thead=NULL,*Ttail=NULL,*Ttemp=NULL,*Ttemp1,*Ttemp2;

/***********************************/
BBot bottomBot= {375,80,30.0};
TBot topBot= {0,750};
float maxL=0,maxR=750,maxU=750,maxD=0;
int flag=0,num,max=710,min=40,menu,score=0;
char str[]="Score :";
bool bullet=false,topbot=false;
float charx=0;
/*****************structure for bullet****************************/

void createBullet(float x1,float y1)
{
if(head==NULL)
    {
        head=(struct Bullet*)malloc(1*sizeof(struct Bullet));
        head->x=x1;
        head->y=y1;
        head->next=NULL;
        tail=head;
    }
else
    {
        temp=(struct Bullet*)malloc(1*sizeof(struct Bullet));
        temp->x=x1;
        temp->y=y1;
        temp->next=NULL;
        tail->next=temp;
        tail=temp;
    }
}
/*************************************/
void DeleteBullet(float yvalue)
{
	temp1=head;
	temp2=head;
	while(temp1->y!=yvalue)
		{
			temp1=temp1->next;
		}
	if(temp1==head)
	{
       if(head->next==NULL)
            {
                head=NULL;
            }
        else
            {
                head=temp1->next;
                free(temp1);
            }
	}
	else
	{
		temp2=head;
		while(temp2->next!=temp1)
		{
            temp2=temp2->next;
		}
		if(temp1->next==NULL)
		{
			tail=temp2;
			tail->next=NULL;
            free(temp1);
		}
		else
		{
			temp2->next=temp1->next;
			free(temp1);
        }
	}
}
/*********************************************/
/*****************structure for ****************************/
void createTopBot(float x1,float y1)
{
    if(Thead==NULL)
    {
        Thead=(struct TBot*)malloc(1*sizeof(struct TBot));
        Thead->x=x1;
        Thead->y=y1;
        Thead->next=NULL;
        Ttail=Thead;    
    }
    else
    {
        Ttemp=(struct TBot*)malloc(1*sizeof(struct TBot));
        Ttemp->x=x1;
        Ttemp->y=y1;
        Ttemp->next=NULL;
        Ttail->next=Ttemp;
        Ttail=Ttemp;
    }
}
/*************************************/
void DeleteTopBot(float yvalue)
{
	Ttemp1=Thead;
	Ttemp2=Thead;	
	while(Ttemp1->y!=yvalue)
	{
		Ttemp1=Ttemp1->next;
	}
	if(Ttemp1==Thead)
	{
		if(Thead->next==NULL)
		{
            Thead=NULL;
        }
		else
		{
            Thead=Ttemp1->next;
			free(Ttemp1);
		}
	}
	else
	{
		Ttemp2=Thead;
		while(Ttemp2->next!=Ttemp1)
		{
			Ttemp2=Ttemp2->next;
		}
		if(Ttemp1->next==NULL)
		{
			Ttail=Ttemp2;
			Ttail->next=NULL;
			free(Ttemp1);
		}
		else
		{
        	Ttemp2->next=Ttemp1->next;
			free(Ttemp1);
		}
	}
}
/*********************************************/
void BottomBot()
{
	glBegin(GL_POLYGON);
		glVertex2f(bottomBot.x,bottomBot.y-20);
		glVertex2f(bottomBot.x-25,bottomBot.y-40);
		glVertex2f(bottomBot.x,bottomBot.y+30);
	glEnd();
		glBegin(GL_POLYGON);
		glVertex2f(bottomBot.x,bottomBot.y-20);
		glVertex2f(bottomBot.x+25,bottomBot.y-40);
		glVertex2f(bottomBot.x,bottomBot.y+30);
	glEnd();
}
/*********************************************/
void displayTopBot(float x,float y)
{
	glBegin(GL_POLYGON);
		glVertex2f(x-15,y+10);
		glVertex2f(x-15,y+30);
		glVertex2f(x+15,y+30);
		glVertex2f(x+15,y+10);
		glVertex2f(x,y);
	glEnd();
}
/*********************************************/
void displayBullet(float x,float y)
{
	glBegin(GL_POLYGON);
		glVertex2f(x-5,y);
		glVertex2f(x-5,y+5);
		glVertex2f(x,y+10);
		glVertex2f(x+5,y+5);
		glVertex2f(x+5,y);
	glEnd();
}
/*********************************************/
void scoreDisplay()
{
    glColor3f(1.0,0.0,0.0);
    glRasterPos2f(20,700);
    for(char *i=str;*i!='\0';i++)
    {
        glutBitmapCharacter(GLUT_BITMAP_TIMES_ROMAN_24,*i);
    }
    int j=0,k,posx=80,p,n=10;
    p=score;
    while(p>9)
    {
        k=p%10;
        glRasterPos2f(posx+n,700);
        glutBitmapCharacter(GLUT_BITMAP_TIMES_ROMAN_24,k+48);
        j++;
        p=p/10;
    }
    glRasterPos2f(posx-j,700);
    glutBitmapCharacter(GLUT_BITMAP_TIMES_ROMAN_24,48+p);
}

void marque()
{
    char string[]="abc";
    glColor3f(1.0,0.0,0.0);
    glRasterPos2f(charx,700);  
    for(char *i=string;*i!='\0';i++)
    {
        glutBitmapCharacter(GLUT_BITMAP_TIMES_ROMAN_24,*i);
    }
    if(charx<=750)
    {
        charx+=0.1;
    }
    else
    {
        charx=0;
    }
}

/*********************************************/
void page1()
{
    marque();
    glColor3f(1.0,0.0,0.0);
    glRasterPos2f(20,500);
    for(char *i=str;*i!='\0';i++)
    {
        glutBitmapCharacter(GLUT_BITMAP_TIMES_ROMAN_24,*i);
    }
	glFlush();				
}

void page2()
{
    glColor3f(1.0,0.0,0.0);
    glRasterPos2f(20,700);
    for(char *i=str;*i!='\0';i++)
    {
        glutBitmapCharacter(GLUT_BITMAP_TIMES_ROMAN_24,*i);
    }
    glFlush();				
}

void display()
{
    glClearColor(1.0,1.0,1.0,1.0);
	glClear(GL_COLOR_BUFFER_BIT);
    if(page1st==1)
    {
        page1();
    }
    else if(page2nd==1)
    {
        page2();
    }
    else
    {
        glPointSize(5);
        glBegin(GL_QUADS);
            glColor3f(0.0,0.0,3.0);
            glVertex2f(0,0);
            glColor3f(0.0,0.0,3.0);
            glVertex2f(0,40);
            glColor3f(0.0,0.0,3.0);
            glVertex2f(750,40);
            glColor3f(0.0,0.0,3.0);
            glVertex2f(750,0);
        glEnd();
        BottomBot();
        if(bullet)
        {
            temp1=head;
            while(temp1!=NULL)
            {
                displayBullet(temp1->x,temp1->y);
                temp1=temp1->next;
            }
        }
        if(topbot)
        {
            Ttemp1=Thead;
            while(Ttemp1!=NULL)
            {
                displayTopBot(Ttemp1->x,Ttemp1->y);
                Ttemp1=Ttemp1->next;
            }
        }
        scoreDisplay();
    }
    glFlush();
    glutSwapBuffers();
}

/***************************************/
void keyboard(unsigned char key,int x,int y)
{
    switch(key)
    {
        case 'S':page1st=0;
            page2nd=1;
            break;
        case 'D':page2nd=0;
            break;
    }
	if(key=='a' or key=='A')
    {
        if(bottomBot.x-30 > maxL)
        {
            bottomBot.x-= bottomBot.step;
        }
    }
    else if(key=='d' or key=='D')
    {
        if(bottomBot.x+30 < maxR)
        {
            bottomBot.x += bottomBot.step;
        }
    }
	else if(key=='w' or key=='W')
	{
		createBullet(bottomBot.x,bottomBot.y+30);
		bullet=true;
	}
	glutPostRedisplay();
}

/***********************************/
void mouse(int btn,int state,int x,int y)
{
	if(btn==GLUT_LEFT_BUTTON && state==GLUT_DOWN)
	{
		createBullet(bottomBot.x,bottomBot.y+30);
		bullet=true;
	}
	glutPostRedisplay();
}
/**************************************/
void idle()
{
	temp1=head;
	if(temp1==NULL)
	{
		bullet=false;
	}
	else
	{
		while(temp1!=NULL)
		{
			temp1->y=temp1->y+1;
			if(temp1->y > maxU)
            {
                DeleteBullet(temp1->y);
            }
			temp1=temp1->next;
		}
	}
	if(flag==1)
	{
		srand(time(NULL));
		num=(min)+rand()%(((max)-(min)+1));
		createTopBot(float(num),maxU);
		flag=0;
		topbot=true;
	}
	Ttemp1=Thead;
	if(Ttemp1==NULL)
	{
		topbot=false;
	}
	else
	{
		while(Ttemp1!=NULL)
		{
            Ttemp1->y=Ttemp1->y-0.1;
			if(Ttemp1->y < maxD)
			{
				DeleteTopBot(Ttemp1->y);
                exit(1);
			}
            Ttemp1=Ttemp1->next;
		}
		if(Ttail->y < 650)
        {
			flag=1;
        }
	}
    temp1=head;//bullts
    Ttemp1=Thead;//topbot
    while(temp1!=NULL)
    {
        while(Ttemp1!=NULL)
        {
            if(temp1->x < Ttemp1->x +15 and temp1->x > Ttemp1->x -15)
            {
                if(temp1->y+10 < Ttemp1->y +30 and temp1->y+10 > Ttemp1->y)
                {
                    DeleteBullet(temp1->y);
                    DeleteTopBot(Ttemp1->y);
                    score+=1;
                }
            }
            Ttemp1=Ttemp1->next;
        }
        temp1=temp1->next;
    }
    glutPostRedisplay();
}

/*****************************/
void options(int id)
{
    switch(id)
    {
        case 1:flag=1;
        break;
        case 2:exit(1);
        break;
    }
}

/*****************************/
int main(int argc,char **argv)
{
	glutInit(&argc,argv);
	glutInitDisplayMode(GLUT_SINGLE|GLUT_RGB);
	glutInitWindowSize(1000,1000);
	glutCreateWindow("First Program");
	gluOrtho2D(0.0,750.0,0.0,750.0);
	glutDisplayFunc(display);
	glutKeyboardFunc(keyboard);
	glutMouseFunc(mouse);
	glutIdleFunc(idle);
	menu=glutCreateMenu(options);
		glutAddMenuEntry("Start",1);
		glutAddMenuEntry("Quit",2);
	glutAttachMenu(GLUT_RIGHT_BUTTON);
	//glutSpecialFunc(specialkey);
	glutMainLoop();
	return 0;
}
