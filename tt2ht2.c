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
	char basic_array[100];
	int i = 0;
	
	while( fgets(basic_array, 100, stdin ) )
	{
		basic_array[ strlen(basic_array) - 1 ] = '\0';
		//puts(basic_array);		
	
		if ( strcmp(basic_array, "<noprocess>") == 0 )
		{
			current_state = 1;
		} else if ( strcmp(basic_array, "</noprocess>") == 0 )
		{
			current_state = 0;
		} else if ( strcmp(basic_array, "<attributes>") == 0 )
		{
			current_state = 2;
		} else if ( strcmp(basic_array, "</attributes>") == 0 )
		{
			current_state = 3;
		}
		
		if ( current_state == 1)
		{
			puts(basic_array);
		} else if ( current_state == 3)
		{
			puts(basic_array);
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



