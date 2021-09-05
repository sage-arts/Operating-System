#include<stdio.h>

int main()
{
    int x, n, i;
    int *ptr=&x; // declare pointer to the integer variable x

    printf("Enter the value of integer variable\n");
    scanf("%d", ptr);

    printf("Value and address of the integer variable are\n"); 
    // *ptr holds the value and ptr holds the address of x
    // %p format specifier prints the pointer in hex
    printf("value:%d address:%p\n", *ptr, ptr);
    
    printf("Enter the size of integer array\n");
    scanf("%d", &n);

    int arr[n];
    int *p=arr; // declare pointer to the array arr

    printf("Enter the elements of integer array\n");
    for(i=0; i<n; i++)
    {
        scanf("%d", p+i);
    }
    
    printf("Values and addresses of the integer array entries are\n");
    // p points to the first element of array and p+1 to next and so on till p+n-1
    // so *p gives the value of first element *p+1 for next element and so on
    for(i=0; i<5; i++)
    {
        printf("value:%d address:%p\n", *p+i, p+i);
    }

    return 0;
}