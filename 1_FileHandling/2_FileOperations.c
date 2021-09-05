#include<stdio.h>
#include<stdlib.h> // For exit()
#include<ctype.h> // For toupper(), tolower()

FILE *fptr1, *fptr2; // declare file pointers
char filename[100]; // to store filename

// error handling
void check(FILE *fptr)
{
    if(fptr==NULL)
    {
        printf("Cannot open file %s\n", filename);
        printf("Check whether %s exists\n", filename);
        exit(0);
    }
}

// function to Copy file
void copy()
{
    char c;

    printf("Enter the filename to copy\n");
    scanf("%s", filename);
  
    // Open one file for reading
    fptr1=fopen(filename, "r");

    // error handling
    check(fptr1);
  
    printf("Enter the filename for writing\n");
    scanf("%s", filename);
  
    // Open another file for writing
    fptr2=fopen(filename, "w");

    // error handling
    check(fptr2);
  
    // read contents from file one 
    c=fgetc(fptr1); // from start of file (first character)
    while(c != EOF) // to end of file (EOF)
    {
        fputc(c, fptr2); // put in file two character wise
        c=fgetc(fptr1); // get next character of file one
    }
  
    printf("Contents copied to %s\n", filename);
  
    // closing the files
    fclose(fptr1);
    fclose(fptr2);
}

// function to Convert file from lowercase to uppercase
void lowerToUpper()
{
    int c;

    printf("Enter the filename to convert from lowercase to uppercase\n");
    scanf("%s", filename);

    // opening the file for both reading and writing.
    fptr1=fopen(filename, "r+");

    // error handling
    check(fptr1);

    // access file character wise with each iteration
    while((c=fgetc(fptr1)) != EOF)
    {
        c=toupper(c); // converting char to uppercase
        fseek(fptr1, -1, SEEK_CUR); // move fptr1 one position back from current position for writing
        fputc(c,fptr1); // write uppercase char
        fseek(fptr1, 0, SEEK_CUR); // move fptr1 to correct current position
    }

    printf("%s converted from lowercase to uppercase\n", filename);
  
    // closing the file
    fclose(fptr1);
}

// function to Convert file from uppercase to lowercase
void upperToLower()
{
    int c;

    printf("Enter the filename to convert from uppercase to lowercase\n");
    scanf("%s", filename);

    // opening the file for both reading and writing.
    fptr1=fopen(filename, "r+");

    // error handling
    check(fptr1);
    
    // access file character wise with each iteration
    while((c=fgetc(fptr1)) != EOF) 
    {
        c=tolower(c); // converting char to lowercase
        fseek(fptr1, -1, SEEK_CUR); // move fptr1 one position back from current position for writing
        fputc(c,fptr1); // write lowercase char
        fseek(fptr1, 0, SEEK_CUR); // move fptr1 to correct current position
    }
  
    printf("%s converted from uppercase to lowercase\n", filename);

    // closing the file
    fclose(fptr1);
}

// function to display file
// just for utility or use cat command
void display()
{
    char c;

    printf("Enter the filename to display \n");
    scanf("%s", filename);

    // opening the file in read mode
    fptr1=fopen(filename, "r");
    
    // error handling
    check(fptr1);

    // read contents from file 
    c=fgetc(fptr1);
    while(c != EOF) 
    {
        printf("%c", c); // print
        c=fgetc(fptr1);
    }

    // closing the file
    fclose(fptr1); 
}

int main()
{
    int choice;
    while(1)
	{
		printf("Choose any one of the following options\n");
		printf("------------------------------------------\n");
		printf("\t  1    Copy file \n");
        	printf("\t  2    Convert file from lowercase to uppercase \n");
        	printf("\t  3    Convert file from uppercase to lowercase \n");
        	printf("\t  4    Display file \n");
        	printf("\t  5    Exit \n");
        	printf("------------------------------------------\n");
        	printf ("Enter your choice: ");
		scanf("%d",&choice);

		switch(choice)
		{
            case 1:
                copy();
                break;
            case 2:
                lowerToUpper();
                break;
            case 3:
                upperToLower();
                break;
            case 4:
                display();
                printf("\n");
                break;
            case 5:
                printf("Exiting program");
                return 0;
            default:
                printf("Wrong choice, try again!\n");
		}
	}
}
