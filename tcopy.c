#include	<stdio.h>
#include	<ctype.h>

int
main()
{
	/*
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
	*/

	int c;
	int current_state = 0;
	char basic_array[12];
	int i = 0;
	
	while( (c=getchar()) != EOF )
	{
		basic_array[i] = c;
		i++;
		basic_array[i] = '\0';

		if ( strcmp(basic_array, "<noprocess>" ) == 0 )
		{
			current_state = 1;
		} else if ( strcmp(basic_array, "</noprocess>" ) == 0 )
		{
			current_state = 0;
		} else {
			printLine(c, basic_array, i);
		}
	}	
}

int
printLine( int c_char, char b_array[], int i_counter )
{
	if ( c_char == '\n')
	{
		puts(b_array);
		memset(b_array, ' ', i_counter);
	}
}	



