#include<stdio.h>
#include<stdlib.h>

FILE *fptr; // declare file pointers
char filename[100]; // to store filename

// error handling
void check()
{
    if(fptr==NULL)
    {
        printf("Cannot open file %s\n", filename);
        printf("Check whether %s exists\n", filename);
        exit(0);
    }
}

// function to remove vowels from file
void removeVowels()
{
    int c;
 
    // opening the file for both reading and writing.
    fptr=fopen(filename, "r+");
    
    // error handling
    check();

    // access file character wise with each iteration
    while((c=fgetc(fptr)) != EOF)
    {
        // checking for vowels
        if(c=='a' || c=='A' || c=='e' || c=='E' || c=='i' || c=='I' || c=='o' || c=='O' || c=='u' || c=='U')
        {
            // if character is vowel 
            fseek(fptr, -1, SEEK_CUR); // move fptr one position back from current position for writing
            fputc(' ',fptr); // write blank
            fseek(fptr, 0, SEEK_CUR); // move fptr to correct current position
        }
    }

    // closing the file
    fclose(fptr);
}

// function to display file
void display()
{
    char c;

    // opening the file in read mode
    fptr=fopen(filename, "r");
    
    // error handling
    check();

    // read contents from file 
    c=fgetc(fptr); // from start of file (first character)
    while(c != EOF) // to end of file (EOF)
    {
        printf("%c", c); // print character
        c=fgetc(fptr); // get next character of file 
    }

    // closing the file
    fclose(fptr); 
}

int main(void)
{
    printf("Enter the filename to remove vowels\n");
    scanf("%s", filename);

    printf("Displaying original file:\n");
    display();
    printf("\n");

    removeVowels();
    printf("Displaying file after removing vowels:\n");
    display();

    return 0;
}