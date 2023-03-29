#include <stdlib.h>
#include <stdio.h>
#include <string.h>
//notes: if there is no encoding sign the input in printed back to the output,hint: (echo).
// you then should exit normally, use fgetc and fputc

// ./encoder ----- ---- -----
    /*
    1. debugmode +D, -D
    2. encoder, meaning if there is +e or -e in any order
    3. 

In this case the makefile should be set so that "make encoder" generates an 
executable file of your program with the name "encoder" in its current directory,
 and with no additional directory structure.     

!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!
they want this: Check whether a character is an lowercase (letter resp. uppercase, or number)
 by using a single "if" statement with two conditions. How? 
!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!

 i still have to do the argv, meaning i need to get values from it and init my variables.
 i stil have to do part3, that wants me to add filename and output file, instead of stdin, stdout.

 and change the make file to compiple like: make encoder, instead of make.
    */




int main(int argc, char **argv){
    // all should be init to 0, if checked its for testing.
    int deBugMode = 0;

    FILE* output = stdout;
    FILE* input = stdin;
    int toEncode = 0;
    int encodeAdd = 0;
    int encodeSub = 0;
    char* key;
    //what i want is an array to store the key if there is a key.
    //char key[100];
    char* outputKey;
    char* inputKey;

    for(int i = 1; i < argc; i++){
        if(strncmp(argv[i], "+e", 2) == 0){
           // strcpy(buffer, argv[i] + 2);
            toEncode = 1;
            encodeAdd = 1;
            key = argv[i] + 2;// this will put me on the 3rd place in the string for example +e12345, it will point to 12345
            //key = buffer + 2;
        }
        if(strncmp(argv[i], "-e", 2) == 0){// dfsfdsdfs dsfdfds +e32321321\0
           // strcpy(buffer, argv[i] + 2);
            toEncode = 1;
            encodeSub = 1;
            //key = buffer + 2;
            key = argv[i] + 2;
        }
        if(strncmp(argv[i], "+D", 2) == 0){
            deBugMode = 1;
        }
        //part 3
        if(strncmp(argv[i], "-i", 2) == 0){
            inputKey = argv[i] + 2;
            input = fopen(inputKey, "r");
        }

        if(strncmp(argv[i], "-o", 2) == 0){
            outputKey = argv[i] + 2;
            output = fopen(outputKey, "w");
        }
        
    }

    if (output == NULL) {
      printf("Error opening file!");
      return 1;
   }

      
       
    // this is maree explantion.
    //    int indexAt = 0;
    //    while(!=EOF){
    //     //key[indexAt] - '0'
    //     indexAt++;
    //     if(key[indexAt] == '\0')  indexAt = 0;
    //    }
       
    
    

    for(int i = 1; i < argc; i++){
        
       
       
        fflush(output);
        for(int j = i; j < argc; j++){
            if(deBugMode){
            
            fprintf(stderr," %d %s \n", j, argv[j]);
            }
             if(strncmp(argv[j], "+D", 2) == 0){
             printf("You entered deDug mode:\n");    
            deBugMode = 1;
            }

             if(strncmp(argv[j], "-D", 2) == 0){
            deBugMode = 0;
            }

        }

    }
printf("u exited debug mode\n");

    char c;
    int indexAt = 0;
   // int key[] = {1, 2, 3, 4, 5};
   // int arrayLength = sizeof(key) / sizeof(key[0]);
    // arrayLength is unnesseary to use. use instead if(key[indexAt] == '\0) indexAt = 0;, key a pointer to an array of chars so to get the int value 
    // in the ascii table you do key[i] - '0'.
    
    
    while ((c = fgetc(input)) != EOF) {

        if(!toEncode){
            fputc(c, output);
            continue;
        }


        if(c == '\n'){
            printf("\n");
            indexAt++;
            if(key[indexAt] == '\0'){
                indexAt = 0;
            }
            continue;
        }

        if(key[indexAt] == '\0'){
            printf("u reached nullptr\n");
            indexAt = 0;
        }
             

        else{
        int encoded = (int)c;
        int num = key[indexAt] - '0';
    
            if(encodeAdd){
                encoded = encoded + num;
                if ((c >= 'a' && c <= 'z' && encoded > 'z') || (c >= 'A' && c <= 'Z' && encoded > 'Z')) {
                    encoded = encoded - 26; // "wrap around" to beginning of alphabet
                }
                //need another "wrap around" for numbers between 0 - 9.
                if(c >= '0' && c <= '9' && encoded > '9'){
                    encoded = encoded - 10;
                }
            }

            if(encodeSub){//care next time to change the bounds, meaning the a with z...
                encoded = encoded - num;
                 if ((c >= 'a' && c <= 'z' && encoded < 'a') || (c >= 'A' && c <= 'Z' && encoded < 'A')) {
                    encoded = encoded + 26; // "wrap around" to beginning of alphabet
                }
                //need another "wrap around" for numbers between 0 - 9.
                if(c >= '0' && c <= '9' && encoded < '0'){
                    encoded = encoded + 10;
                }
              
            }

        char modifed = (char)encoded; // convert back to character
        // printf("Original character: %c\n", c);
        // printf("Encoded character: %c\n", modifed);
        fputc(modifed, output);  
        }
        indexAt++;
        if(key[indexAt] == '\0'){
            indexAt = 0;
        }
              
   }
    fclose(input);
    fclose(output);
    // if(!fclose(input)) 
    //     fprintf(stderr,"error happend");
    return 0;
}