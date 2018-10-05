#include	<stdio.h>
#include	<ctype.h>

int
main()
{
	int c, d;
	int new_line = 0;
	int first_td = 0;
	int current_state = 0;

	char table1[8];
	char table2[8];
	char tr1[5];
	char tr2[5];
	char td1[5];
	char td2[5];

	strcpy(table1, "<table>");
	strcpy(table2, "</table>");
	strcpy(tr1, "<tr>");
	strcpy(tr2, "</tr>");
	strcpy(td1, "<td>");
	strcpy(td2, "</td>");

	char noprocess[12];
	int i = 0;
//	puts(table1);

	/*
	while((c=getchar()) != EOF)
	{
		noprocess[i++] = c;
		if (strcmp(noprocess, "<noprocess>") != 0)
		{
			putchar(c);
		}
	}*/

	while ( (c=getchar()) != EOF )
	{
		putchar(c);
	}	

//	puts(table2);
}
