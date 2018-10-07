#include	<stdio.h>
#include	<ctype.h>
#include	<string.h>

/*
 * tt2ht2.c -- table converter version 2
 *
 *	this version supports <attrbutes> and <noprocess>
 *	it uses a state machine to keep track of which mode
 *	the input is to be processed by.
 *
 *      the states are defined here 
 *
 * 	unless otherwise specifued the program is in process data mode
 *	that is the default and where it starts
 *
 */


#define	CONVERT_ROW	0	// convert the row into html table row
#define	NOPROCESS_PRINT	1
#define	ATTRIBUTES	2
#define	END_OF_ATTRIBS	3

#define	START_LINE	0
#define	START_COL	1
#define	PRINT_DATA	2

#define	LINELEN		500
#define ATTRINUM	50
#define ATTRILEN	200

#define	TR1		"<tr>"
#define	TR2		"</tr>"
#define	TD1		"<td "
#define TD2		">"
#define	TD3		"</td>"

void	process_input();
int	print_line(char [], int );
void	convert_row(char[], char*);
//void	get_attribute(char[]);

int
main()
{
	process_input();
	return 0;
}

/*
 * the main function to read input and process it
 * args: none
 * rets: nothing
 * does: loops using fgets and checks for tags
 */
void process_input()
{
	int current_state = CONVERT_ROW;
	char basic_array[LINELEN];
	
	/* we read in a b c */
	while( fgets(basic_array, LINELEN, stdin ) )
	{
		// check for mode changes
		if ( strcmp(basic_array, "<noprocess>\n") == 0 )
		{
			// when we see <noprocess, change mode and print line
			current_state = NOPROCESS_PRINT;
		} else if ( strcmp(basic_array, "</noprocess>\n") == 0 )
		{
			current_state = CONVERT_ROW;
		} else if ( strcmp(basic_array, "<attributes>\n") == 0 )
		{
			current_state = ATTRIBUTES;
		} else if ( strcmp(basic_array, "</attributes>\n") == 0 )
		{
			current_state = CONVERT_ROW;
		}
		// if not a tag, process as data or as noprocess raw text
		else {
			print_line(basic_array, current_state);
		}
	}
}
		
/*
 * print_line
 *   purp: called when we print out a line
 *	   used when state is NOPROCESS_PRINT or CONVERT_ROW
 *   args: the input line, currnet state
 *   does: checks mode and either just prints the line or converts
 *   rets: 0 for now
 */
int print_line(char basic_array[], int current_state)
{
	int i = 0;
	char attribute_array[ATTRINUM][ATTRILEN];

	if ( current_state == NOPROCESS_PRINT )
	{
		puts(basic_array);
	} else if ( current_state == CONVERT_ROW )
	{	
		convert_row(basic_array, &attribute_array);
		//convert_row(basic_array);
	} else if ( current_state == ATTRIBUTES )
	{
		strcpy(attribute_array[i], basic_array);
		//puts(attribute_array[i]);
	}
	return 0;
}

/*
 * convert_row: convert a row of text table to html table
 *	args: the array of text
 *	rets: nothing
 *	does: looks for spaces and inserts <td> <tr> etc
 */
void convert_row(char basic_array[], char *atribute_array)
{
	int	line_state = START_LINE;
	int	j;
	int	td_count = 0;
	
	//puts(attribute_array[0]);
	//puts(attribute_array[2]);

	for ( j=0; j<strlen(basic_array) ; j++)
	{
		if (line_state == START_LINE)
		{
			puts(TR1);
			puts(TD1);
			//puts(attribute_array[td_count]);
			puts(TD2);
			putchar(basic_array[j]);
			line_state = PRINT_DATA;								
			//td_count++;
		} else if (line_state == START_COL)
		{
			puts(TD1);
			//puts(attribute_array[td_count]);
			puts(TD2);
			putchar(basic_array[j]);
			line_state = PRINT_DATA;
			//td_count++;
		} else if (line_state == PRINT_DATA)
		{
			putchar(basic_array[j]);
			if ( isspace(basic_array[j]) )
			{
				if ( basic_array[j] == '\n')
				{
					puts(TD3);
					puts(TR2);
					line_state = START_LINE;

				} else
				{
					puts(TD3);
					line_state = START_COL;
				}
			}
		}
	}
}

