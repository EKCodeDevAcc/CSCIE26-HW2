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

	char testtest[10];
	strcpy(testtest, "<p>test</p>");

	char basic_array[12];
	char noprocess[12];
	int i = 0;

	while ( (c=getchar()) != EOF )
	{
		putchar('a');
		basic_array[i++] = c;
		basic_array[11] = '\0';
		if (strcmp(basic_array, "<noprocess>") == 0)
		{
			//strcpy(noprocess, basic_array);
			current_state = 1;
		} else if (strcmp(basic_array, "</noprocess>") == 0)
		{
			//strcpy(noprocess, basic_array);
			current_state = 0;
		}

		if (current_state == 0)
		{
			putchar(c);
		} else
		{
			puts(basic_array);
		}
	}
}
