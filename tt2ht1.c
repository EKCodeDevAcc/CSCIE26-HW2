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

	puts(table1);

	while((c=getchar()) != EOF)
	{
		if (current_state == 0)
		{
			puts(tr1);
			puts(td1);
			putchar(c);
			current_state = 2;
		} else if ( current_state == 1 ) {
			puts(td1);
			putchar(c);
			current_state = 2;
		} else if (current_state == 2)
		{
			putchar(c);
			if ( isspace(c) )
			{
				if ( c == '\n')
				{
					puts(td2);
					puts(tr2);
					current_state = 0;
				} else {
					puts(td2);
					current_state = 1;
				}
			}
		}
	}
	
	puts(table2);
}
