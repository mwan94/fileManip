/*
      Amr Wanly
      V.1

      V.1 Completed on: Thursday 12/15/2018

      Description: Read two files and compare the first column in file 1 with
      the first column in file 2. After doing so, report the differences between
      the two columns and make sure the columns are sorted in alphabetical order.


      NOTE: This is version 1 of the code, I will keep updating and modifying it to make it more optimized as I learn more C programming concepts and techniques.

---------------------------------------------------------------------------------------------------------------------------
|/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////|
---------------------------------------------------------------------------------------------------------------------------

      HOW TO COMPILE AND EXECUTE:
      ---------------------------

      To compile the file in terminal, make sure you have the gcc compiler installed.
      Then:

      type gcc project.c

      if you don't get any error, a file called "a.out" will be generated.This file will display the program on the terminal.

      type ./a.out "direc1" "direc2"
            direc1 is the directory of the first file you want to open
            direc2 is the directory of the second file you want to open



        When exectuing the program by typing, for example:

        ./a.out /home/giga/Desktop/test/file1.txt /home/giga/Desktop/test/file2.txt /home/giga/Desktop/test/file3.txt

        ------------------------------------------how did two london fucks fighting each other evolve into a group of stand users fighting a time rewinding kinker-------------------------------------------------------------------------

        ./a.out is be passed as an argument and will be stored in argv[0]

        /home/giga/Desktop/test/file1.txt will be stored in argv[1]

        /home/giga/Desktop/test/file2.txt will be stored in argv[2]
*/
/*



---------------------------------------------------------------------------------------------------------------------------
|/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////|
---------------------------------------------------------------------------------------------------------------------------
*/


#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define BUFFER  12288         //Change the number as you see fit


int main(int argc, char *argv[]){

    int i = 0;

    // Verify that both file names\directories have been provided
    if ((argv[1] == NULL) || (argv[2] == NULL)){ printf("\nERROR!!! not enough files have been provided \n"); exit(1);}
    else { printf("\nThe provided files are:\n\n%s\n\tand\t\n%s\n\n", argv[1], argv[2]);}

    char *file1Content = NULL; // declare a pointer and initalize it to NULL
    file1Content = malloc(200 * sizeof(file1Content)); //Initial dynamic memory allocation
    if( file1Content == NULL ) { printf("Error - unable to allocate required memory\n"); exit(1);}

    char *file2Content = NULL; // declare a pointer and initalize it to NULL
    file2Content = malloc(200 * sizeof(file2Content)); //Initial dynamic memory allocation
    if( file2Content == NULL ) { printf("Error - unable to allocate required memory\n"); exit(1);}


    //initialize the file pointers
    FILE *oldDocs = NULL;
    FILE *newDocs = NULL;

    /*
    -----------------------------------------------------------------------------------------------------------------------------
    |------------------------------------------------- COPYING FIRST OLD FILE---------------------------------------------------|
    -----------------------------------------------------------------------------------------------------------------------------
    */

    oldDocs = fopen(argv[1], "r");   //open the original File #1 in read only mode, hence the "r"
    //check if the file was successfully opened
      if (oldDocs == NULL){ printf("Error! could not opening the first provided directory\n"); /*if not, exit*/ exit(1);}



    newDocs = fopen("/home/giga/Desktop/test/tempF1.txt", "w"); //Open or Create a new File (called file11) to store copied content from the old File #1
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

    /*
    -----------------------------------------------------------------------------------------------------------------------------
    |------------------------------------------------- COPYING SECOND OLD FILE---------------------------------------------------|
    -----------------------------------------------------------------------------------------------------------------------------
    */

    oldDocs = fopen(argv[2], "r");   //open the original File #1 in read only mode, hence the "r"
    //check if the file was successfully opened
      if (oldDocs == NULL){
          printf("Error! could not opening the second provided directory\n"); //if not, exit
          exit(1);
      }


    newDocs = fopen("/home/giga/Desktop/test/tempF2.txt", "w"); //Open\Create a new File (called file11) to store copied content from the old File #1
      //check if the file was successfully opened
      if (newDocs == NULL){
          printf("Error opening the new file 2\n"); //if not, exit
          exit(1);
      }

      rewind(oldDocs);                      //Go to the beginning of this file
      printf("STATUS: CURRENTLY COPYING FIRST COLUMN OF FILE 2 TO A NEW FILE!....\n\n");
        do {
            fscanf(oldDocs,"%s%*[^\n]", file2Content);   //read content from the old file "file1"
            fprintf(newDocs, "%s\n", file2Content);     //write that content to a new file.
        } while (fgets(file2Content, BUFFER, oldDocs));
    fclose(oldDocs);  //Close the old File #1 since we are done with it
    fclose(newDocs);  //Close the new File #1 since we are done with it for now



    /*
    -----------------------------------------------------------------------------------------------------------------------------
    |------------------------------------------------- DONE COPYING BOTH FILES--------------------------------------------------|
    -----------------------------------------------------------------------------------------------------------------------------
    */

    // free the allocated memory when done.
    free(file1Content);
    free(file2Content);

    /*
    -----------------------------------------------------------------------------------------------------------------------------
    |------------------------------------------- Sorting Files Using CMD in Terminal--------------------------------------------|
    -----------------------------------------------------------------------------------------------------------------------------
    */

     // The function system(); passes command name or program name specified between () to the host enviornment

     printf("Sorting the Content of new FILE 1 via Command Line.....\n\n");
     system("sort /home/giga/Desktop/test/tempF1.txt | uniq > /home/giga/Desktop/test/SortedF1.txt"); //sort the file and remove duplicates
     system("sed -i '/^$/d' /home/giga/Desktop/test/SortedF1.txt"); //remove empty lines

     printf("Sorting the Content of new FILE 2 via Command Line.....\n\n");
     system("sort /home/giga/Desktop/test/tempF2.txt | uniq > /home/giga/Desktop/test/SortedF2.txt"); //sort the file and remove duplicates
     system("sed -i '/^$/d' /home/giga/Desktop/test/SortedF2.txt"); //remove empty lines



     /*
     ------------------------------------------------------------------------------------------------------------------------------
     |---------------------------------------------- Delete Temporary Files F1 and F2----------------------------------------------|
     ------------------------------------------------------------------------------------------------------------------------------
     */

      int verify = 0;
      verify = remove("/home/giga/Desktop/test/tempF1.txt");
      if (verify == 0){printf("tempF1 deleted!\n\n");}
      else {printf("Error!!! couldn't delete\n\n");}

      verify = remove("/home/giga/Desktop/test/tempF2.txt");
      if (verify == 0){printf("tempF2 deleted!\n\n");}
      else {printf("Error!!! couldn't delete\n\n");}




      /*
      ------------------------------------------------------------------------------------------------------------------------------
      |----------------------------------- Access the host enovironment (in this case Linux)----------------------------------------|
      |----------------------------------- and send commands to the terminal to be executed ----------------------------------------|
      ------------------------------------------------------------------------------------------------------------------------------
      */

      //Generate a report of the unique devices in File 1 in a file called Report
      printf("Comparing files via Command Line.....\n\n");
      system("comm -23 /home/giga/Desktop/test/SortedF1.txt /home/giga/Desktop/test/SortedF2.txt > /home/giga/Desktop/test/Report.txt");
      system("(echo ""LIST of UNIQUE DEVICES IN FILE 1:"" && cat /home/giga/Desktop/test/Report.txt) > /home/giga/Desktop/test/tempo.txt && mv /home/giga/Desktop/test/tempo.txt /home/giga/Desktop/test/Report.txt");



      //Generate a report of the unique devices in File 2 in a file called Unique2
      system("comm -13 /home/giga/Desktop/test/SortedF1.txt /home/giga/Desktop/test/SortedF2.txt > /home/giga/Desktop/test/Unique2.txt");
      system("(echo ""LIST of UNIQUE DEVICES IN FILE 2:"" && cat /home/giga/Desktop/test/Unique2.txt) > /home/giga/Desktop/test/tempo.txt && mv /home/giga/Desktop/test/tempo.txt /home/giga/Desktop/test/Unique2.txt");

      //insert a space\whiteline at the beginning of Unique2
      system("(echo ""                                 "" && cat /home/giga/Desktop/test/Unique2.txt) > /home/giga/Desktop/test/tempo.txt && mv /home/giga/Desktop/test/tempo.txt /home/giga/Desktop/test/Unique2.txt");

      //Move the content of Unique 2 to Report
      system("cat /home/giga/Desktop/test/Unique2.txt >> /home/giga/Desktop/test/Report.txt");

      //delete Unique 2
      verify = remove("/home/giga/Desktop/test/Unique2.txt");
      if (verify == 0){printf(".....\n\n");}
      else {printf("Error!!! couldn't delete\n\n");}




    return 0;
}
