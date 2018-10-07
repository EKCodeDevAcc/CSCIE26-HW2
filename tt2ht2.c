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
#define	NOPROCESS_PRINT	1	// print line
#define	ATTRIBUTES	2	// store line as an attribute

#define	START_LINE	0	// start table row with <tr> <td>
#define	START_COL	1	// start table row with <td>
#define	PRINT_DATA	2	// print char for <td>

#define	LINELEN		500	// length of each lines
#define ATTRINUM	50	// number of attribute lines
#define ATTRILEN	200	// length of each attribute lines

#define	TR1		"<tr>"
#define	TR2		"</tr>"
#define	TD1		"<td "
#define TD2		">"
#define	TD3		"</td>"

void	process_input();
int	print_line(char [], int );
void	convert_row(char[], char[][ATTRILEN]);

int	i = 0;	// counter for string array of attributes in print_line method

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
	int current_state = CONVERT_ROW;	// state of current lines
	char basic_array[LINELEN];		// array for current line
	
	while( fgets(basic_array, LINELEN, stdin ) )
	{
		// check for mode changes
		if ( strcmp(basic_array, "<noprocess>\n") == 0 )
		{
			// when we see <noprocess, change state to noprocess and just printout the line with no conversion
			current_state = NOPROCESS_PRINT;
		} else if ( strcmp(basic_array, "</noprocess>\n") == 0 )
		{	// when we see closing noprocess tab, change state to convert row
			current_state = CONVERT_ROW;
		} else if ( strcmp(basic_array, "<attributes>\n") == 0 )
		{	// when we see attribtes, change state to attributes tab
			current_state = ATTRIBUTES;
		} else if ( strcmp(basic_array, "</attributes>\n") == 0 )
		{	// when we see closing attributes tab, change state to convert row
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
 *	   used when state is NOPROCESS_PRINT, ATTRIBUTES, or CONVERT_ROW
 *   args: the input line, currnet state
 *   does: checks mode and either just prints the line, converts, or store attributes in string array
 *   rets: 0 for now
 */
int print_line(char basic_array[], int current_state)
{
	static char attribute_array[ATTRINUM][ATTRILEN];	// string array for attributes

	if ( current_state == NOPROCESS_PRINT )
	{	// noprocess, just print the line with no conversion
		puts(basic_array);
	} else if ( current_state == CONVERT_ROW )
	{	// convert row, convert it into HTML table form then print out
		convert_row(basic_array, attribute_array);
	} else if ( current_state == ATTRIBUTES )
	{	// store each line as an attribute string array
		strcpy(attribute_array[i], basic_array);
		i++;
	}

	return 0;
}

/*
 * convert_row: convert a row of text table to html table
 *	args: the array of text
 *	rets: nothing
 *	does: looks for spaces and inserts <td> <tr> etc
 */
void convert_row(char basic_array[], char attribute_array[][ATTRILEN])
{
	int	line_state = START_LINE;	// state for each column
	int	j;				// counter for each char of the line
	int	td_count = 0;			// counter to follow the number of columns

	for ( j=0; j<strlen(basic_array) ; j++)
	{
		if (line_state == START_LINE)	// when it begins, start with <tr> tag then <td> with attribute
		{
			puts(TR1);			// <tr>
			puts(TD1);			// <td
			puts(attribute_array[td_count]);// class='tty' for example
			puts(TD2);			// >
			putchar(basic_array[j]);	// then print out each chars
			line_state = PRINT_DATA;								
			td_count++;
		} else if (line_state == START_COL)	// not the beginning of the line, but column
		{
			puts(TD1);			// print out <td> tag only
			puts(attribute_array[td_count]);
			puts(TD2);
			putchar(basic_array[j]);
			line_state = PRINT_DATA;
			td_count++;
		} else if (line_state == PRINT_DATA)	// keep printing char
		{
			putchar(basic_array[j]);
			if ( isspace(basic_array[j]) )	// check if it hits any space char
			{
				if ( basic_array[j] == '\n')	// if it is the end of the row, close tr tag
				{
					puts(TD3);
					puts(TR2);
					line_state = START_LINE;

				} else
				{			// other than that, just close td tag only
					puts(TD3);
					line_state = START_COL;
				}
			}
		}
	}
}

