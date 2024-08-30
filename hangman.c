#include<stdio.h>
#include<time.h>
#include<stdlib.h>    //to use srand() function
#include<string.h>
#include<ctype.h>    //cause using toupper()
//#include<conio.h>   //to use clrscr();
void lives(int);

void lives(int count){
    printf("\n\n");
    switch(count){
        case 1: printf("  +---+\n  |   |\n      |\n      |\n      |\n      |\n=========");
            break;
        case 2: printf("  +---+\n  |   |\n  O   |\n      |\n      |\n      |\n=========");
            break;
        case 3: printf("  +---+\n  |   |\n  O   |\n  |   |\n      |\n      |\n=========");
            break;
        case 4: printf("  +---+\n  |   |\n  O   |\n /|   |\n      |\n      |\n========="); 
            break;
        case 5: printf("  +---+\n  |   |\n  O   |\n /|\\  |\n      |\n      |\n=========");
            break;
        case 6: printf("  +---+\n  |   |\n  O   |\n /|\\  |\n /    |\n      |\n=========");
            break;
        default:
                printf("  +---+\n  |   |\n  O   |\n /|\\  |\n / \\  |\n      |\n=========");



    }

}

int main(){
    FILE *db;
    char uname[30];
    char cname[30];
    char pwd[30];
    char cpwd[30];
    int in;
label_uname:
    printf("\n\nEnter your choice:\n1.Sign In\n2.Create Account\n");
    scanf("%d",&in);
    switch(in){
        case 1:
        
            printf("Enter your username: (If new user press E to exit)\n");
            scanf("%s",uname);
            printf("Enter your password\n");
            scanf("%s",pwd);
            strlwr(uname);
            if(strcmp(uname,"e")==0){
                goto label_uname;
            }
            db=fopen("database.txt","r");
            while(fscanf(db,"%s%s",cname,cpwd)==2){           //added == 2 to ensure that fscanf correctly reads two strings from the file
                if(strcmp(uname,cname)==0 && strcmp(pwd,cpwd)==0){
                    fclose(db);
                    goto label_start;
                }
            }
            fclose(db);
            printf("Username or password doesnot match. Try again...\n");
            goto label_uname;
            /*printf("Enter your password");
            scanf("%s",uname);
            db=fopen("database.txt","a");
            fprintf(db,uname)
            */
           break;
        
        case 2:
            printf("Create your username: (Already have one?, press E)\n");
            scanf("%s",uname);
            strlwr(uname);
            if(strcmp(uname,"e")==0){
                goto label_uname;
            }
            db=fopen("database.txt","r");
            while(fscanf(db,"%s%s",cname,cpwd)==2){     //added == 2 to ensure that fscanf correctly reads two strings from the file
                if(strcmp(uname,cname)==0){
                    printf("Username already chosed. Please choose a unique one or sign in if it is yours.\n");
                    fclose(db);
                    goto label_uname;
                }
            }
            fclose(db);
            db=fopen("database.txt","a");
            printf("Create a password:\n");
            scanf("%s",pwd);
            fprintf(db,"%s %s\n",uname,pwd);
            fclose(db);

    }




label_start:
    printf("\e[1;1H\e[2J");
    printf("\n\nWelcome! @%s\n",uname);
    printf("The game begins....\n");
    FILE *fp;
    
    char word[30];
    char lett;
    int count=0;
    int match=0;

    srand(time(NULL));          //random number integrated with time
    int line_num=rand()%2400+1;    //random number upto 5

    fp=fopen("hangman_words.txt","r");
    for(int i=1;i<=line_num;i++){
        fgets(word,30,fp);
    }


    int len = strlen(word);
    if (word[len - 1] == '\n') {           //The problem is that strlen(word) is calculated after reading the word from the file using fgets, which includes the newline character '\n' at the end of the word
        word[len - 1] = '\0'; // Removing the newline character
       // len;// Update the length accordingly
    }

    for(int i=0;i<len-1;i++){
        printf("%c ",'_');
    }
    printf("\n\n");

    int arr[30];       //NOTE: cannot use strlen(word) instead of 30 because this will generate a variable index connected to index of array word
    char usedlett[30];     //because maximum no. of letters is only 26
    char ans[30];   //to store and later check the winning condition to terminate the loop
                    //NOTE: cannot use strlen(word) instead of 30 because this will generate a variable index connected to index of array word

    int ct=0;             // used letter counter and index
    
    while(count<=6){
        printf("\nGuess a letter: ");
       
        scanf(" %c",&lett);  /*   The "%d" format specifier includes skipping leading white-space.
                            The "%c" format doesn't have that,
                            it reads the next character in the input buffer no matter what kind of character it is.
                            If you want to skip leading white-space using the "%c" format,
                            you need to tell scanf explicitly to do so with a space in the format string, like e.g. " %c".
                    */
        lett=toupper(lett);
        printf("\e[1;1H\e[2J");
        
        for(int i=0;i<=ct;i++){
            if(lett==usedlett[i]){
                printf("Duplicate Entry");
                goto last;
            }
        }

        usedlett[ct]=lett;
        
        printf("\n");
        for(int i=0;i<len-1;i++){      //printing dashes and letters
            //printf("%c",word[i]);
            
            if(arr[i]==1){              // to avoid printing dashes in places of letters which has already been in correctly guessed. The same arr data is used in each iteration of while loop.
                printf("%c ",word[i]);
                ans[i]=word[i];
                //continue;
            }
            else if(word[i]==lett){
                arr[i]=1;
                //printf("yes");
                printf("%c ",word[i]);
                match=1;
                ans[i]=word[i];
            }else{
                printf("%c ",'_');
            }
            if(strcmp(ans,word)==0){
                printf("\n\n%s",word);
                printf("\nwinner");
                goto label_end;
            }
            
        
        }
        ans[len - 1] = '\0';
        /*
        printf("\t%s",ans);
        printf(",,%d",strlen(ans));
        printf("\t%s",word);
        printf(",,%d",strlen(word));
        */

        

        if(match==1){     //to count misses only when no match is found or when guessed incorrectly
            match=0;
        }else{
            count++;
            lives(count);
        }  
        ct++;

        printf("\n\nUsed Letters: ");
       printf("%s",usedlett);
last:;
    }

    
    
    printf("\n");
    printf("\n");
    printf("\n");
    printf("You lose");
    printf("\nThe word was %s",word);
    //printf("%d",strlen(word));
    fclose(fp);
    

    char again;
label_end:
    printf("\n\n\n To play again enter Y (Enter any other key to end)\n");
    scanf(" %c",&again);

    if(again=='Y' || again=='y'){
        memset(usedlett,'\0',sizeof(usedlett));         //memset is used to set a range of memory to a specific value by copying that value into each BYTE of the memory block.
        //strcpy(usedlett,"");     //this didn't worked
        //usedlett[0]='\0';   //will not work because we are accessing specific index as usedlett[i]
        //arr[0]='\0';      //doesnot work for this because we are using each arr[i] in above program
        for(int i=0;i<10;i++){     //can use memset as above.
            arr[i]=0;
        }
        printf("start\n");
        goto label_start;
    }
    return 0;
    
}
