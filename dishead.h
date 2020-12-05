void display_head()
{
	int i;
	window(1,1,79,5);
	gotoxy(27,2);
	printf("EMPLOYEE MANAGEMENT SYSTEM");
	window(1,1,79,5);
	gotoxy(34,3);
	printf("MINOR PROJECT");
	window(1,1,79,5);
	for(i=1;i<=79;i++)
	{

		gotoxy(i,5);
		printf("=");
	}
}
