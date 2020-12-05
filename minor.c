#include <dos.h>
#include <stdio.h>
#include <conio.h>
#include <string.h>
#include "frontt.h"
#include "dishead.h"





/////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////

struct info{
	char emp_name[30],father_name[30];
	int emp_id;
	char emp_ph_no[15],ft_ph_no[10];
	char gender[10];
	char email[40];
	char branch[30],dept[10];
}s;

struct user
{
	int usr_name;
	char usr_password[10];
}USR;



/////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////

FILE *fp;
int flag;
int add=0;//for new user is added

/////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////

void list_all();
void admin();
void R_box();
void L_box();
void newuser();
void viewprof(int id);
void usr_search();
void modify();
void adm_search();
void main();

/////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////
/*

									USER

*/
/////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////

void newuser()
{
	char masterkey[5],password[20];
	int username;
	window(45,10,79,25);
	printf("Enter masterkey: ");
	fflush(stdin);
	window(62,10,79,25);
	gets(masterkey);
	if(strcmp(masterkey,"mohit")==0)
	{
		fp=fopen("usr_login.DAT","rb");
		fflush(stdin);
		window(45,6,79,25);
		clrscr();
		window(45,10,79,25);
		printf("Enter Username: ");
		window(62,10,79,25);
		scanf("%d",&username);
		while((fread(&USR,sizeof(USR),1,fp))>0)
		{
			if(username==USR.usr_name)
			{
				flag=1;
			}
		}
		fclose(fp);

		if(flag==1)
		{
			window(45,20,79,25);
			printf("Cannot add same employee again...!!!");
		}
		else
		{
			fp=fopen("USR_LOGIN.DAT","ab");
			fflush(stdin);
			window(45,6,79,25);
			clrscr();
		 //	printf("\nEnter Username: ");
		 //	scanf("%d",&USR.usr_name);
		 //	fflush(stdin);
			USR.usr_name=username;
			window(45,12,79,25);
			printf("Enter Password: ");
			window(62,12,79,25);
			gets(USR.usr_password);
			fwrite(&USR,sizeof(USR),1,fp);
			fclose(fp);
			fp=fopen("USR_LOGIN.DAT","rb");
			while((fread(&USR,sizeof(USR),1,fp)>0))
			{
				if(USR.usr_name==username)
				{
					window(45,18,79,25);
					printf("New User Successfully Added");
					delay(2000);
				}
			}

			add=1;
		}
	}
	else
	{
		window(45,20,79,25);
		printf("Unauthorized Acess Denied...!!!");
		delay(2000);
		exit();
	}
	if(add==1)
	{
		clrscr();

		fp=fopen("EMPLOYEE.DAT","ab");
		window(45,6,79,25);
		clrscr();
		s.emp_id=USR.usr_name;
		fflush(stdin);
		window(45,10,79,25);
		printf("Enter Employee Name: ");
		window(66,10,79,25);
		gets(s.emp_name);
		fflush(stdin);
		window(45,11,79,25);
		printf("Enter Father's Name: ");
		window(66,11,79,25);
		gets(s.father_name);
		window(45,12,79,25);
		printf("Enter Employee's Phone number: ");
		fflush(stdin);
		window(45,13,79,25);
		gets(s.emp_ph_no);
		window(45,14,79,25);
		printf("Enter Father's Phone number: ");
		fflush(stdin);
		window(45,15,79,25);
		gets(s.ft_ph_no);
		fwrite(&s,sizeof(s),1,fp);
		fclose(fp);
		window(45,20,79,25);
		printf("Employee record has been created");
	}
}

/////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////

void viewprof(int id)
{
	clrscr();
	fp=fopen("EMPLOYEE.DAT","rb");
	R_box();
	while((fread(&s,sizeof(s),1,fp))>0)
	{
		if(id==s.emp_id)
		{
			window(45,8,79,23);
			printf("Record Found");
			window(45,10,79,23);
			printf("ERP: %d",s.emp_id);
			window(45,11,79,23);
			printf("Employee Name: %s",s.emp_name);
			window(45,12,79,23);
			printf("Father Name: %s",s.father_name);
			window(45,13,79,23);
			printf("Employee's Phone number:");
			window(45,14,79,23);
			fflush(stdin);
			puts(s.emp_ph_no);
			fflush(stdin);
			window(45,15,79,23);
			printf("Father's Phone Name: ");
			window(45,16,79,23);
			puts(s.ft_ph_no);
		}
	}
	fclose(fp);
}

/////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////

void usr_search()
{
	int no, flag=0;
	R_box();
	window(45,8,79,23);
	printf("Enter EMP Id to search details: ");
	window(45,9,79,23);
	scanf("%d",&no);
	fp=fopen("EMPLOYEE.DAT","rb");
	while((fread(&s,sizeof(s),1,fp))>0)
	{
		if(s.emp_id==no)
		{
			window(43,6,79,25);
			clrscr();
			R_box();
			window(45,8,79,23);
			printf("Record Found\n\n");
			window(45,10,78,23);
			printf("ERP: %d\n",s.emp_id);
			window(45,11,78,23);
			printf("Name: %s\n\n",s.emp_name);
			flag=1;
		}
	}
	if(flag==0)
	{
		window(45,11,78,23);
		printf("Record not found");
	}
	fclose(fp);
}

/////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////
/*

									USER

*/
/////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////

void user(int id,char password[10])
{
	int usr_choice,a;
	clrscr();
	fp=fopen("usr_login.DAT","rb");

	while((fread(&USR,sizeof(USR),1,fp))>0)
	{
		if(id==USR.usr_name && strcmp(password,USR.usr_password)==0)
		{
			flag=1;
		}
	}
	fclose(fp);

	if(flag==1)
	{


		DISP:
			clrscr();
			display_head();
			L_box();
			window(6,8,40,23);
			printf("1. View your profile.\n");
			window(6,9,40,23);
			printf("2. Search Employee.\n");
			window(6,10,40,23);
			printf("3. View Attendance\n");
			window(6,11,40,23);
			printf("4. View Payroll.\n");
			window(6,12,40,23);
			printf("5. Logout\n");
			window(6,16,40,23);
			printf("Enter your choice: ");
			window(26,16,40,23);
			scanf("%d",&usr_choice);


			switch(usr_choice)
			{
				case 1: viewprof(id);
						display_head();
						window(45,20,79,25);
						printf("Enter 1 for main menu or");
						window(45,21,79,25);
						printf("2 for logout and exit..: ");
						window(71,21,79,25);
						scanf("%d",&a);
						switch(a)
						{
							case 1: window(1,1,79,25);
									clrscr();
									goto DISP;
							case 2: printf("Logging out...");
									delay(1000);
									exit();
						}
						break;
				case 2:	usr_search();
						window(45,20,79,25);
						printf("Enter 1 for main menu or");
						window(45,21,79,25);
						printf("2 for logout and exit..: ");
						window(71,21,79,25);
						scanf("%d",&a);
						switch(a)
						{
							case 1: window(1,1,79,25);
									clrscr();
									goto DISP;
							case 2: printf("Logging out...");
									delay(1000);
									exit();
						}
						break;
				case 3: R_box();
						window(45,10,79,25);
						printf("WORK UNDER RPROGRESS\n\n");
						/////////////
						window(45,20,79,25);
						printf("Enter 1 for main menu or");
						window(45,21,79,25);
						printf("2 for logout and exit..: ");
						window(71,21,79,25);
						scanf("%d",&a);
						switch(a)
						{
							case 1: window(1,1,79,25);
									clrscr();
									goto DISP;
							case 2: printf("Logging out...");
									delay(1000);
									exit();
						}

						break;
				case 4: R_box();
						window(45,10,79,25);
						printf("WORK UNDER RPROGRESS\n\n");
						//payroll();
						window(45,20,79,25);
						printf("Enter 1 for main menu or");
						window(45,21,79,25);
						printf("2 for logout and exit..: ");
						window(71,21,79,25);
						scanf("%d",&a);
						switch(a)
						{
							case 1: window(1,1,79,25);
									clrscr();
									goto DISP;
							case 2: printf("Logging out...");
									delay(1000);
									exit();
						}
						break;
				case 5: window(45,21,79,25);
						printf("Logging out ");
						delay(2000);
						window(1,1,79,25);
						clrscr();
						main();

			}
	}
	else
	{
		printf("Invalid login...");
		printf("\n\nLogging out...");
		delay(1000);
		exit();
	}
}

/////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////
/*

									ADMIN

*/
/////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////

void list_all()
{
	FILE *fp;
	clrscr();
	fp=fopen("EMPLOYEE.DAT","rb");
	if(fp==NULL)
	{
		window(45,20,79,25);
		printf("File Doesn't exits");
	}
	window(1,6,79,25);
	clrscr();
	display_head();
	window(1,6,79,25);
	while((fread(&s,sizeof(s),1,fp)>0))
	{
			printf("\nEMP_ID: %d",s.emp_id);
			printf("\nEmployee Name: %s",s.emp_name);
			printf("\nFather Name: %s",s.father_name);
			printf("\nEmployee's Ph. No.: %s",s.emp_ph_no);
			printf("\nFather's Ph. No.: %s",s.ft_ph_no);
			printf("\n=========");
			printf("\n");
	}
	window(1,1,79,5);
	clrscr();
	display_head();
	fclose(fp);
}

/////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////
/*

									ADMIN

*/
/////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////

void admin()
{

	int adm_choice,a,flag;
	char masterkey[5],username[10],name[10],password[10];
	clrscr();

	fflush(stdin);

	printf("Enter username: ");
	gets(name);
	fflush(stdin);
	printf("Enter password: ");
	gets(password);
	if(strcmp(name,"mohit")==0)
	{
		if(strcmp(password,"mohit")==0)
		{

		DISP:
			clrscr();
			display_head();
			L_box();
			window(6,10,40,23);
			printf("1. View Employee details.");
			window(6,11,40,23);
			printf("2. Search Employee.");
			window(6,12,40,23);
			printf("3. Modify Employee details.");
			window(6,13,40,23);
			printf("4. Employee Payroll.");
			window(6,14,40,23);
			printf("5. Add New User login.");
			window(6,15,40,23);
			printf("6. Logout");
			window(6,17,40,23);
			printf("Enter your choice: ");
			window(28,17,40,23);
			scanf("%d",&adm_choice);


			switch(adm_choice)
			{
				case 1: list_all();

						window(45,20,79,25);
						printf("Enter 1 for main menu or");
						window(45,21,79,25);
						printf("2 for logout and exit..: ");
						window(71,21,79,25);
						scanf("%d",&a);
						switch(a)
						{
							case 1: window(1,1,79,25);
									clrscr();
									goto DISP;
							case 2: printf("Logging out...");
									delay(1000);
									exit();
						}
						break;
				case 2:	adm_search();
						window(45,20,79,25);
						printf("Enter 1 for main menu or");
						window(45,21,79,25);
						printf("2 for logout and exit..: ");
						window(71,21,79,25);
						scanf("%d",&a);
						switch(a)
						{
							case 1: window(1,1,79,25);
									clrscr();
									goto DISP;
							case 2: printf("Logging out...");
									delay(1000);
									exit();
						}
						break;
				case 3: modify();
						window(45,20,79,25);
						printf("Enter 1 for main menu or");
						window(45,21,79,25);
						printf("2 for logout and exit..: ");
						window(71,21,79,25);
						scanf("%d",&a);
						switch(a)
						{
							case 1: window(1,1,79,25);
									clrscr();
									goto DISP;
							case 2: printf("Logging out...");
									delay(1000);
									exit();
						}
						break;
				case 4: R_box();
						window(45,10,79,25);
						printf("WORK UNDER RPROGRESS\n\n");
						//payroll();
						window(45,20,79,25);
						printf("Enter 1 for main menu or");
						window(45,21,79,25);
						printf("2 for logout and exit..: ");
						window(71,21,79,25);
						scanf("%d",&a);
						switch(a)
						{
							case 1: window(1,1,79,25);
									clrscr();
									goto DISP;
							case 2: printf("Logging out...");
									delay(1000);
									exit();
						}
						break;
				case 5: display_head();
						newuser();
						display_head();
						window(45,20,79,25);
						printf("Enter 1 for main menu or");
						window(45,21,79,25);
						printf("2 for logout and exit..: ");
						window(71,21,79,25);
						scanf("%d",&a);
						switch(a)
						{
							case 1: window(1,1,79,25);
									clrscr();
									goto DISP;
							case 2: printf("Logging out...");
									delay(1000);
									exit();
						}
						break;
		logout:
				case 6: window(38,20,79,25);
						printf("Logging out ");
						delay(2000);
						window(1,1,79,25);
						clrscr();
						main();

			}
		}
	}
}

/////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////


void adm_search()
{
	int no;
	R_box();
	window(45,8,79,23);
	printf("Enter EMP Id to search details: ");
	window(45,9,79,23);
	scanf("%d",&no);
	fp=fopen("EMPLOYEE.DAT","rb");
	while((fread(&s,sizeof(s),1,fp))>0)
	{
		if(s.emp_id==no)
		{
			window(43,6,79,25);
			clrscr();
			R_box();
			window(45,8,79,23);
			printf("Record Found");
			window(45,10,79,23);
			printf("ERP: %d",s.emp_id);
			window(45,11,79,23);
			printf("Employee Name: %s",s.emp_name);
			window(45,12,79,23);
			printf("Father's Name: %s",s.father_name);
			flag=1;
		}
	}
	if(flag==0)
	{
		gotoxy(40,15);
		printf("\n\nRecord not found\n\n");
	}
	fclose(fp);
}

/////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////

void modify()
{
	FILE *fp;
	int no,flag=0;
	R_box();
	window(45,8,79,23);
	printf("Enter EMP_ID to modify: ");
	window(70,8,79,23);
	scanf("%d",&no);
	fp=fopen("EMPLOYEE.DAT","rb+");
	while((fread(&s,sizeof(s),1,fp))>0)
	{
		if(s.emp_id==no)
		{
			window(43,6,79,25);
			clrscr();
			R_box();
			window(45,10,79,23);
			printf("EMP_ID: %d",s.emp_id);
			window(45,11,79,23);
			printf("Employee Name: %s",s.emp_name);
			window(45,12,79,23);
			printf("Father's Name: %s",s.father_name);
			window(45,15,79,23);
			printf("Press any key ...");
			getch();
			window(43,6,79,25);
			clrscr();
			R_box();
			window(45,8,79,23);
			printf("Enter new Detials");
			fflush(stdin);
			window(45,10,79,23);
			printf("Enter Employee Name: ");
			window(66,10,79,23);
			gets(s.emp_name);
			fflush(stdin);
			window(45,11,79,23);
			printf("Enter Father's Name: ");
			window(66,11,79,23);
			gets(s.father_name);

			fseek(fp,-(long)sizeof(s),1);
			fwrite(&s,sizeof(s),1,fp);

			window(45,15,79,25);
			printf("Record Updated");
		}
		if(s.emp_id==no)
		{
			flag=1;
		}
	}

	fclose(fp);
	if(flag==0)
	{
		window(45,15,79,25);
		printf("Record doesn't exist");
	}
}

/////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////

void main()
{
	int choice;
	int a,id;
	char password[10];
	front();
	delay(3000);
ADM_DISP:	clrscr();


	gotoxy(20,8);
	printf("\xb2\xb2\xb2\xb2\xb2\xb2\xb2\xb2\xb2\xb2\xb2\xb2\xb2\xb2\xb2\xb2\xb2\xb2\xb2\xb2\xb2\xb2\xb2\xb2\xb2\xb2\xb2\xb2\xb2\xb2\xb2\xb2\xb2\xb2\xb2\xb2\xb2\xb2\xb2");
	gotoxy(20,9);
	printf("\xb2\xb2              LOGIN                \xb2\xb2");
	gotoxy(20,10);
	printf("\xb2\xb2             ~~~~~~~               \xb2\xb2");
	gotoxy(20,11);
	printf("\xb2\xb2 1. ADMIN                          \xb2\xb2");
	gotoxy(20,12);
	printf("\xb2\xb2                                   \xb2\xb2");
	gotoxy(20,13);
	printf("\xb2\xb2 2. USER                           \xb2\xb2");
	gotoxy(20,14);
	printf("\xb2\xb2                                   \xb2\xb2");
	gotoxy(20,15);
	printf("\xb2\xb2 3. EXIT                           \xb2\xb2");
	gotoxy(20,16);
	printf("\xb2\xb2                                   \xb2\xb2");
	gotoxy(20,17);
	printf("\xb2\xb2 Enter your choice:                \xb2\xb2");
	gotoxy(20,18);
	printf("\xb2\xb2                                   \xb2\xb2");
	gotoxy(20,19);
	printf("\xb2\xb2\xb2\xb2\xb2\xb2\xb2\xb2\xb2\xb2\xb2\xb2\xb2\xb2\xb2\xb2\xb2\xb2\xb2\xb2\xb2\xb2\xb2\xb2\xb2\xb2\xb2\xb2\xb2\xb2\xb2\xb2\xb2\xb2\xb2\xb2\xb2\xb2\xb2");
	gotoxy(43,17);
	scanf("%d",&choice);


	switch(choice)
	{
		case 1: admin();
				break;
		case 2: clrscr();

				fflush(stdin);
				printf("Enter username: ");
				scanf("%d",&id);
				fflush(stdin);
				printf("Enter password: ");
				gets(password);
				user(id,password);
				printf("\n\nPress 1 for logout and  main menu or 2 for logout and exit...");
				scanf("%d",&a);
				switch(a)
				{
					case 1:	goto ADM_DISP;
					case 2: exit();
				}
				break;
		case 3: exit();
	}
	getch();
}

/////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////

void R_box()
{
	int i;
	///////////////////
	/*   TOP BOTTOM  */
	///////////////////
	window(43,6,79,25);
	for(i=1;i<36;i++)
	{
		gotoxy(i,1);
		printf("\xcd");

		gotoxy(i,19);
		printf("\xcd");

		gotoxy(1,19);
		printf("\xc8");

		gotoxy(1,1);
		printf("\xc9");

		gotoxy(1,19);
		printf("\xc8");

		delay(10);
	}

	///////////////////
	/*     SIDES     */
	///////////////////

	for(i=2;i<19;i++)
	{
		gotoxy(1,i);
		printf("\xba");

		gotoxy(36,i);
		printf("\xba");

		gotoxy(36,1);
		printf("\xbb");

		gotoxy(36,19);
		printf("\xbc");

		delay(10);
	}
}


/////////////////////////////////////////////window(6,8,40,23);
										   //window(4,6,42,25);
/////////////////////////////////////////////window(45,8,79,23);
										   //window(43,6,79,25);
void L_box()
{
	int i;
	///////////////////
	/*   TOP BOTTOM  */
	///////////////////
	window(4,6,42,25);
	for(i=1;i<38;i++)
	{
		gotoxy(i,1);
		printf("\xcd");

		gotoxy(i,19);
		printf("\xcd");

		gotoxy(1,19);
		printf("\xc8");

		gotoxy(1,1);
		printf("\xc9");

		gotoxy(1,19);
		printf("\xc8");

		delay(10);
	}

	///////////////////
	/*     SIDES     */
	///////////////////

	window(4,6,42,25);
	for(i=2;i<19;i++)
	{
		gotoxy(1,i);
		printf("\xba");

		gotoxy(38,i);
		printf("\xba");

		gotoxy(38,1);
		printf("\xbb");

		gotoxy(38,19);
		printf("\xbc");

		delay(10);
	}
}
