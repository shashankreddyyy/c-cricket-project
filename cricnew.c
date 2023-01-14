/* C PROJECT FOR 4TH SEM USING BINARY TREES
	PLAYERS DATABASE SYSTEM

	AUTHORS: SHASHANK G. REDDY

*/



#include<stdio.h>
#include<string.h>
#include<stdlib.h>
#include<time.h>
#include<graphics.h>
#include<dos.h>

struct node
{
int age, runs,jerseyno;
char nm[20], team[20];
struct node *left,*right;
};

struct node * insert_node(struct node *root,char nm[],int jerseyno,char team[],int age,int runs);
struct node * FindMin(struct node *);
void in_display(struct node *root);
void rank_display(struct node *root);
void search(struct node *root,int num);
struct node * delete_node(struct node *,int);
int addtoarray(struct node*,int[],int);
int count(struct node*);
int compare(const void *a,const void *b);
FILE *fp;

void main()
{

struct node *root=NULL;
int age,runs,ch,jerseyno,i,size;
int *arr=NULL;
char name[20], team[20];
int ans;char c;
int del_player,srch_player;
//FILE *fp;
WelcomeScreen();
LoginScreen();
clrscr();
Title();

do
{
printf("\n");
printf("\n\t\t1.Insert a new information in the database");
printf("\n\t\t2.Save all the information into the database and exit");
printf("\n\t\t3.Delete an information you entered");
printf("\n\t\t4.Search an information you entered");
printf("\n\t\t5.Rank all players you entered");
printf("\n\t\t6.Show the scores of the entered players");
printf("\n\t\t7.Show the total no. of players stored in database");
printf("\n\t\t8.Display all records in the database");
printf("\n\t\t9.Delete records permanantly from database");
printf("\n\t\t10.Exit");
printf("\n\t\tEnter your choice:");
scanf("%d",&ch);
switch(ch)
{
case 1:printf("\nEnter the name of the player:\t");
scanf("%s",&name);
printf("\nEnter the team of the player:\t");
scanf("%s",&team);
printf("\nEnter the jersey number of player:\t");
scanf("%d",&jerseyno);
printf("\nEnter the age of the player:\t");
scanf("%d",&age);
printf("\nEnter the runs scored by the player:\t");
scanf("%d",&runs);

root = insert_node(root,name,jerseyno,team,age,runs);

/* printf("\nDo you wish to view the data entered? (1/0)");
scanf("%d",&ans);

if(ans == 1)
{
    in_display(root);
}

	fp = fopen("filename.txt","ab");
	fprintf(fp,"\nPlayer name -- %s",root->nm);
	fprintf(fp,"\nJersey no. -- %d",root->jerseyno);
	fprintf(fp,"\nAge -- %d",root->age);
	fprintf(fp,"\nTeam -- %s",root->team);
	fprintf(fp,"\nRuns -- %d",root->runs);
	fseek(fp,0,SEEK_END);
	free(root);
	fclose(fp);
*/
break;

case 2:
fp = fopen("filename.txt","ab+");
in_display(root);
fseek(fp,0,SEEK_END);
fclose(fp);
clrscr();
printf("\n\t\tData stored successfully!");
printf("\n\t\tNow exiting program");printf("."); delay(1000);printf(".");delay(1000);printf(".");delay(1000);
exit(0);
break;

case 3:
printf("\nEnter the jersey number of the player:\t");
scanf("%d",&del_player);
root=delete_node(root,del_player);
break;

case 4:
printf("\nEnter the jersey number of player to be searched:\t");
scanf("%d",&srch_player);
search(root,srch_player);
break;

case 5:
printf("\n\n\t\tPLAYER NAME\tRUNS\n");
rank_display(root);
break;

case 6:
size = count(root);
printf("The no. of players entered in database are %d\n",size);
arr = calloc(size,sizeof(int));
addtoarray(root,arr,0);
qsort(arr,size,sizeof(int),compare);

printf("\nThe scores now entered are:\t ");

for(i=0;i<size;i++)
{
	printf("\nPlayer[%d]: %d\n",i,arr[i]);
}
break;

case 7:
countsumin();
break;

case 8:
fp = fopen("filename.txt","r");
    if (fp == NULL)
    {
	printf("Cannot open file \n");
	exit(0);
    }

    printf("\nDisplaying all records stored in database.Please Wait");
    printf("."); delay(1000);printf(".");delay(1000);printf(".");
    printf("\n");
    c = fgetc(fp);
    while (c != EOF)
    {
	printf ("%c", c);
	c = fgetc(fp);
    }

    fclose(fp);

break;

case 9:
delsumin();
//fail();
break;

case 10:
clrscr();
printf("\n\n\n\t\tA sample graphical representation of an empty cricket pitch...");
delay(2000);
ground();
ball();
//delay(6000);
exit(0);

break;

default: printf("\nInvalid Choice: ");

}
}while(1);
}

int countsumin()
{
    FILE *fp;
    int count = 0;  // Line counter (result)
    char filename[50] = "filename.txt";
    char c;  // To store a character read from file

    // Open the file
    fp = fopen(filename, "r");

    // Check if file exists
    if (fp == NULL)
    {
	printf("Could not open file %s", filename);
	return 0;
    }

    // Extract characters from file and store in character c
    for (c = getc(fp); c != EOF; c = getc(fp))
	if (c == '\n') // Increment count if this character is newline
	    count = count + 1;

    // Close the file
    fclose(fp);
    printf("\nThe database consists of the records of %d players\n ",(count/5));

    return 0;
}


WelcomeScreen(void)
{
	clrscr();
	printf("\n\n\n\n\n\t################################################");
	printf("\n\t#\t\tWELCOME TO\t\t#");
	printf("\n\t#\tPLAYERS DATABASE SYSTEM\t#");
	printf("\n\t################################################");
	printf("\n\n\n\n\nPress any key to continue.........\n");
	getch();
	clrscr();
}

Title(void)
{
	printf("\n\n\t\t--------------------------------------------------");
	printf("\n\t\t\t    PLAYERS DATABASE SYSTEM           ");
	printf("\n\t\t--------------------------------------------------");

}


LoginScreen(void)
{
	int e = 0;
	char Username[15];
	char Password[15];
	char original_Username[25] = "Sid";
	char original_Password[15] = "9999";

	do
	{
		printf("\n\n\n\n\t\tEnter your username & password :");
		printf("\n\n\n\t\t\tUSERNAME:");
		scanf("%s",&Username);
		printf("\n\n\t\t\tPASSWORD:");
		scanf("%s",&Password);

		if(strcmp(Username,original_Username)==0 && strcmp(Password,original_Password)==0)
		{
			printf("\n\n\n\t\t\t...LOGIN SUCCESSFULL...");
			printf("\n\n\n\t\t\tHit any key to continue!");
			getch();
			break;
		}
		else
		{
			printf("\n\t\t\tThe Username or Password is incorrect: (Try Again)");
			e++;
			getch();
			clrscr();
		}
	}while(e<=2);

	if(e>2)
	{
		printf("\n\nToo many unsuccessful attempts! Login failed. ");
		getch();
		exit(0);
	}
	system("cls");
}

int delsumin()
{
	FILE *fp;
    FILE *fileptr1, *fileptr2;

    char filenamee[40] = "filename.txt";

    char ch1;

    int delete_line, temp = 1;
   char word[50];
   char ch;
   char *filename = "filename.txt";
   char *search;
   int count = 0;
   int pos[10];
   int pointer = 0;
   int loop;
   int lineno;


   printf("\nEnter the name of the player whose data to be removed: ");
   scanf("%s",search);
   /*  open for writing */
   fp = fopen(filename, "r");

   do
   {
      ch = fscanf(fp, "%s", word);
      if(strcmp(word, search) == 0)
	{
	 pos[count] = pointer;
	 count++;
	}
      pointer++;
      //printf("%s",word);
   } while (ch != EOF);

    if(count == 0)
       {	printf("\n'%s' not found in %s\n", search, filename);
		printf("\nNow exiting the software!");
		delay(3000);
		exit(0);
       }
    else
	{
	printf("'%s' is found at -> ", search);
	for(loop = 0; loop<count; loop++)
	    {
		printf("%d ", pos[loop]);
		delete_line = pos[loop];
	    }
	printf("positions.\n");
		delete_line = (delete_line/3)+1;
		printf("lineno is %d",delete_line);
		printf("\n\n");
	}

	fclose(fp);

    //open file in read mode

    fileptr1 = fopen(filenamee, "r");

    ch1 = getc(fileptr1);

  while (ch1 != EOF)

    {

	printf("%c", ch1);

	ch1 = getc(fileptr1);

    }

    //seek

    fseek(fileptr1,0,SEEK_SET);

    //open new file in write mode

    fileptr2 = fopen("replica.c", "w");

    ch1 = getc(fileptr1);

    while (ch1 != EOF)

    {

	ch1 = getc(fileptr1);

	if (ch1 == '\n')

	    temp++;

	    //except the line to be deleted

	    if (temp != delete_line && temp!= delete_line+1 && temp!= delete_line+2 && temp!= delete_line +3 && temp!= delete_line+4)

	    {

		//copy all lines in file replica.c

		putc(ch1, fileptr2);


	    }

    }

    fclose(fileptr1);

    fclose(fileptr2);

    remove(filenamee);

    //rename the file replica.c to original name

    rename("replica.c", filenamee);

    printf("\n The contents of file after being modified are as follows:\n");
    delay(10000);
    fileptr1 = fopen(filenamee, "r");

    ch1 = getc(fileptr1);

    while (ch1 != EOF)

    {

	printf("%c", ch1);

	ch1 = getc(fileptr1);

    }

    fclose(fileptr1);

    return 0;

}

struct node * insert_node(struct node *root,char nm[],int jerseyno,char team[], int age, int runs)
{
if(root==NULL)
{
struct node *temp=(struct node *)malloc(sizeof(struct node));
strcpy(temp->nm,nm);
strcpy(temp->team,team);
temp->jerseyno=jerseyno;
temp->age=age;
temp->runs=runs;
temp->left=NULL;
temp->right=NULL;
return temp;
}
if(runs<=root->runs)
{
root->left=insert_node(root->left,nm,jerseyno,team,age,runs);
}
else
{
root->right=insert_node(root->right,nm,jerseyno,team,age,runs);
}
return root;

}
void in_display(struct node *root)
{

if(root==NULL)
{
return;
}
in_display(root->right);
in_display(root->left);
printf("\nPlayer Name -- %s",root->nm);
printf("\nJersey no. -- %d",root->jerseyno);
printf("\nAge -- %d",root->age);
printf("\nTeam -- %s",root->team);
printf("\nRuns -- %d",root->runs);
fprintf(fp,"PlayerName -- %s ",root->nm);
fprintf(fp,"\nJerseyno. -- %d ",root->jerseyno);
fprintf(fp,"\nAge -- %d ",root->age);
fprintf(fp,"\nTeam -- %s ",root->team);
fprintf(fp,"\nRuns -- %d\n",root->runs);
}
struct node * delete_node(struct node *root,int num)
{
if(root == NULL)
{
return root;
}
else if(num < root->jerseyno)
{
root->left = delete_node(root->left ,num);

}
else if(num > root->jerseyno)
{
root->right = delete_node(root->right ,num);
}
else
{
if(root->left == NULL && root->right == NULL)
{
free(root);
root = NULL;

}
else if(root->left == NULL)
{
struct node *temp = root;
root = root->right;
free(temp);
temp = NULL;

}
else if(root->right == NULL)
{
struct node *temp = root;
root = root->left;
free(temp);
temp = NULL;
}
else
{
struct node *temp = root;
root->left = FindMin(root);
root->left->right=root->right;
root = root->left;
temp->age = root->age;
temp->runs = root->runs;
temp->jerseyno = root->jerseyno;
strcpy(temp->nm,root->nm);
strcpy(temp->team,root->team);
free(temp);
temp = NULL;
}
return root;
}
return root;
}

struct node * FindMin(struct node *root)
{
while(root->left != NULL)
{
root = root->left;
}
return root;
}

void search(struct node *root,int num)
{
if(root->jerseyno>num)
{
search(root->left,num);
}
else if(root->jerseyno<num)
{
search(root->right,num);
}
else
{
printf("\nPlayer Name -- %s",root->nm);
printf("\nJersey no. -- %d",root->jerseyno);
printf("\nPlayer Age -- %d",root->age);
printf("\nTeam -- %s",root->team);
printf("\nRuns -- %d",root->runs);
}
}

void rank_display(struct node *root)
{
	if(root==NULL)
	{
		return;
	}

	rank_display(root->right);
	printf("\t\t%s\t\t",root->nm);
	printf("%d\n",root->runs);
	rank_display(root->left);
}

int addtoarray(struct node *root,int arr[],int i)
{
	if(root == NULL)
		return i;

	arr[i] = root->runs;
	i++;

	if(root->left!=NULL)
		i = addtoarray(root->left,arr,i);

	if(root->right!=NULL)
		i = addtoarray(root->right,arr,i);


	return i;

}

int count(struct node *root)
{
	int c = 1;

	if(root == NULL)
	{
		return 0;
	}

	else
	{
		c += count(root->left);
		c += count(root->right);
		return c;
	}
}

int compare(const void *a,const void *b)
{
	return(*(int*)a - *(int*)b);
}

int ground()
{
 int gd = DETECT, gm;

    // Initialize of gdriver with
    // DETECT macros
    initgraph(&gd, &gm, "C:\\turboc3\\bgi");

    // Ground Outline
    circle(300, 200, 200);

    // Coloring Green
    setfillstyle(SOLID_FILL, GREEN);
    floodfill(300, 200, 15);

    // 30 Yards Outline
    ellipse(300, 200, 0, 360, 130, 160);

   // Pitch Outer Line
    rectangle(325, 345, 250, 65);

   // Pitch Inner Line
    rectangle(325, 345, 250, 65);

 /*   // Coloring Pitch Brown
    setfillstyle(SOLID_FILL, BROWN);
    floodfill(326,346,6);

    // Upper Stump Line
    rectangle(690, 265, 710, 280);
    line(680, 280, 720, 280);

    // Lower Stump Line
    rectangle(690, 435, 710, 420);
    line(680, 420, 720, 420);
*/
    // Hold Screen For A While
    getch();

    // Close the initialized gdriver
    closegraph();

    return 0;
}

int ball()
{
	int gd = DETECT, gm = DETECT;
	int x, y = 0, j, t = 400, c = 1;
	initgraph(&gd, &gm, "C:\\turboc3\\bgi");
	setcolor(RED);
	setfillstyle(SOLID_FILL, RED);
	for (x = 40; x < 602; x++) {
		cleardevice();
		circle(x, y, 30);
		floodfill(x, y, RED);
		delay(40);
		if (y >= 400) {
			c = 0;
			t -= 20;
		}
		if (y <= (400 - t))
			    c = 1;
		y = y + (c ? 15 : -15);
	}
	getch();
}

/*

int fail()
{
    FILE *fp = fopen("filename.txt", "r");
    if (fp == NULL) {
	fprintf(stderr, "Unable to open file\n");
	exit(EXIT_FAILURE);
    }

    char buffer[1000];
    int arr[MAX_LINES];
    size_t line = 0;

    while ((fgets(buffer, sizeof buffer, fp) != NULL)) {
	if (sscanf(buffer, "%d", &arr[line]) != 1) {
	    fprintf(stderr, "Line formatting error\n");
	    exit(EXIT_FAILURE);
	}
	++line;
    }

    for (size_t i = 0; i < line; i++) {
	printf("%5d\n", arr[i]);
    }

    fclose(fp);

return 0;

} */
