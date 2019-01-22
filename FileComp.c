/*
      Amr Wanly
      V.1.1

      V.1.0 Completed on: Thursday 12/15/2018
      V.1.1   Updated on: Tuesday  01/15/2019

      Description: Read two files and compare the first column in file 1 with
      the first column in file 2. After doing so, report the differences between
      the two columns and make sure the columns are sorted in alphabetical order.

      Update V.1.1:
        > I added a feature that when a use enters a third argument, it will be used as the name of the generated report.
        > The generated report file will now open in VIM as soon as the program finishes the execution process.


      NOTE: This is version 1 of the code, I will keep updating and modifying it to make it more optimized as I learn more C programming concepts and techniques.


      HOW TO COMPILE AND EXECUTE:
      ---------------------------

      To compile the file in terminal, make sure you have the gcc compiler installed.
      Then:

      type gcc project.c

      if you don't get any error, a file called "a.out" will be generated.This file will display the program on the terminal.

OPTION A:   type ./a.out "file1.txt" "file2.txt"
            file1.txt is the first file you want to open
            file2.txt is the second file you want to open

OPTION B:   type ./a.out "file1.txt" "file2.txt" "file3.txt"
            file1.txt is the first file you want to open
            file2.txt is the second file you want to open
            file3.txt is the report file wheret the list of different devices will be stored.


        When exectuing the program by typing, for example:

        ./a.out file1.txt file2.txt file3.txt


        ./a.out is be passed as an argument and will be stored in argv[0]

        file1.txt will be stored in argv[1]

        file2.txt will be stored in argv[2]

        file3.txt will be stored in argv[3]


*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define BUFFER  12288         //Change the number as you see fit

void fileDeletion();          //declaration of a function that will delete the unwanted files

int main(int argc, char *argv[]){

    char addressDest[25] = "report.txt"; //a variable that holds the name of the output report file

    // Verify that both file names\directories have been provided
    if ((argv[1] == NULL) || (argv[2] == NULL)){ printf("\nERROR!!! not enough files have been provided \n"); exit(1);}
    else { printf("\nThe provided files are:\n\n%s\tand\t%s\n\n", argv[1], argv[2]);}

    // Verify whether a value was passed to argument argv[3]. If so, use it to name the output report file. Otherwise, use the default name in addressDest.
    if (argv[3] != NULL){strncpy(addressDest, argv[3], 25);  printf("\nThe output file is:\t%s\n\n", addressDest);}
    else {printf("\nThe output file will be named:\t%s\n\n", addressDest);}

    char *file1Content = NULL; // declare a pointer and initalize it to NULL
    file1Content = malloc(200 * sizeof(file1Content)); //Initial dynamic memory allocation
    if( file1Content == NULL ) { printf("Error - unable to allocate required memory\n"); exit(1);}

    char *file2Content = NULL; // declare a pointer and initalize it to NULL
    file2Content = malloc(200 * sizeof(file2Content)); //Initial dynamic memory allocation
    if( file2Content == NULL ) { printf("Error - unable to allocate required memory\n"); exit(1);}

    //initialize the file pointers
    FILE *oldDocs = NULL;
    FILE *newDocs = NULL;


//|------------------------------------------------- COPYING FIRST OLD FILE---------------------------------------------------|

    oldDocs = fopen(argv[1], "r");   //open the original File #1 in read only mode, hence the "r"
    //check if the file was successfully opened
      if (oldDocs == NULL){ printf("Error! could not opening the first provided directory\n"); /*if not, exit*/ exit(1);}

    newDocs = fopen("tempF1.txt", "w"); //Open or Create a new File (called file11) to store copied content from the old File #1
      //check if the file was successfully opened
      if (newDocs == NULL){ printf("Error opening the new file 1\n"); /*if not, exit*/ exit(1);}

      rewind(oldDocs);                      //Go to the beginning of this file
      printf("STATUS: CURRENTLY COPYING FIRST COLUMN OF FILE 1 TO A NEW FILE!.....\n\n");
        do {
            fscanf(oldDocs,"%s%*[^\n]", file1Content);   //read content from the old file "file1"
            fprintf(newDocs, "%s\n", file1Content);     //write that content to a new file.
        } while (fgets(file1Content, BUFFER, oldDocs));
    fclose(oldDocs);  //Close the old File #1 since we are done with it
    fclose(newDocs);  //Close the new File #1 since we are done with it for now


//------------------------------------------------- COPYING SECOND OLD FILE---------------------------------------------------|

    oldDocs = fopen(argv[2], "r");   //open the original File #1 in read only mode, hence the "r"
    //check if the file was successfully opened
      if (oldDocs == NULL){printf("Error! could not opening the second provided directory\n"); /*if not, exit*/ exit(1);}

    newDocs = fopen("tempF2.txt", "w"); //Open\Create a new File (called file11) to store copied content from the old File #1
      //check if the file was successfully opened
      if (newDocs == NULL){printf("Error opening the new file 2\n"); /*if not, exit*/ exit(1);}

      rewind(oldDocs);                      //Go to the beginning of this file
      printf("STATUS: CURRENTLY COPYING FIRST COLUMN OF FILE 2 TO A NEW FILE!....\n\n");
        do {
            fscanf(oldDocs,"%s%*[^\n]", file2Content);   //read content from the old file "file1"
            fprintf(newDocs, "%s\n", file2Content);     //write that content to a new file.
        } while (fgets(file2Content, BUFFER, oldDocs));
    fclose(oldDocs);  //Close the old File #1 since we are done with it
    fclose(newDocs);  //Close the new File #1 since we are done with it for now

    //DONE COPYING BOTH FILES
    // free the allocated memory when done.
    free(file1Content);
    free(file2Content);

//|------------------------------------------- Sorting Files Using CMD in Terminal--------------------------------------------|

     // The function system(); passes command name or program name specified between () to the host enviornment
     printf("Sorting the Content of new FILE 1 via Command Line.....\n\n");
     system("sort tempF1.txt | uniq > SortedF1.txt"); //sort the file and remove duplicates
     system("sed -i '/^$/d' SortedF1.txt"); //remove empty lines

     printf("Sorting the Content of new FILE 2 via Command Line.....\n\n");
     system("sort tempF2.txt | uniq > SortedF2.txt"); //sort the file and remove duplicates
     system("sed -i '/^$/d' SortedF2.txt"); //remove empty lines


//|----------------------------------- Access the host enovironment (in this case Linux)----------------------------------------|
//|----------------------------------- and send commands to the terminal to be executed ----------------------------------------|

      //Generate a report of the unique devices in File 1 in a file called Unique1
      printf("Comparing files via Command Line.....\n\n");
      system("comm -23 SortedF1.txt SortedF2.txt >  Unique1.txt");
      system("(echo ""LIST of UNIQUE DEVICES IN FILE 1:"" && cat Unique1.txt) > tempo.txt && mv tempo.txt Unique1.txt");

      //Generate a report of the unique devices in File 2 in a file called Unique2
       system("comm -13 SortedF1.txt SortedF2.txt > Unique2.txt");
       system("(echo ""LIST of UNIQUE DEVICES IN FILE 2:"" && cat Unique2.txt) > tempo.txt && mv tempo.txt Unique2.txt");

      //insert a space\whiteline at the beginning of Unique2
      system("(echo ""                                 "" && cat Unique2.txt) > tempo.txt && mv tempo.txt Unique2.txt");

      //Move the content of Unique 2 to Report
      char command1[100];
      snprintf(command1, sizeof(command1), "cat Unique1.txt >> %s",addressDest);
      system(command1);
      snprintf(command1, sizeof(command1), "cat Unique2.txt >> %s",addressDest);
      system(command1);

      //delete the unwanted files
      fileDeletion();

      //automatically open the report file in VIM after it is generated
      printf("Program has finished executing.... opening the report file in VIM\n\n\n");
      snprintf(command1, sizeof(command1), "vi %s",addressDest);
      system(command1);

    return 0;
}


void fileDeletion(){

   unsigned int verify = 0;

   //delete Temporary Files F1 and F2
   verify = remove("tempF1.txt");
   if (verify == 0){printf("tempF1 deleted!\n\n");}
   else {printf("Error!!! couldn't delete\n\n");}

   verify = remove("tempF2.txt");
   if (verify == 0){printf("tempF2 deleted!\n\n");}
   else {printf("Error!!! couldn't delete\n\n");}


  //delete Unique1 and Unique2
  verify = remove("Unique1.txt");
  if (verify == 0){printf("\n");}
  else {printf("Error!!! couldn't delete\n\n");}

  verify = remove("Unique2.txt");
  if (verify == 0){printf("\n");}
  else {printf("Error!!! couldn't delete\n\n");}


  //delete SortedF1 and SortedF2
  verify = remove("SortedF1.txt");
  if (verify == 0){printf("\n");}
  else {printf("Error!!! couldn't delete\n\n");}

  verify = remove("SortedF2.txt");
  if (verify == 0){printf("\n");}
  else {printf("Error!!! couldn't delete\n\n");}

}
