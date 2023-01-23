#include "stdio.h"
#include "stdlib.h"
#define SIZE 10000
struct Worker{
    int id;
    int age;
    char name[30];
    char email[50];
    char password[50];

};

struct Worker info[SIZE];

void printingAllData();
void login();
int charCounting(char toCount[50]);
void myStrCmp(char userInputChar[50]);
void passChecking(char pass[50] , int userIndex);
void recordingAllDataToFile();
void userActionSector();
void loadingAllDataFromFile();
void registration();
void lobby();
void checkEmail(char userInputEmail[]);
void infoId();

int eFound = -1;
int pFound=-1;
int globalIndex=0;
int id=0;
int b=0;

int main(){
    infoId();
    loadingAllDataFromFile();
    printingAllData();
    lobby();

    return 0;
}
void lobby(){
    int lob=0;
    printf("This is Lobby Sector!\n");
    printf("Press 1 to Register:\n");
    printf("Press 2 to Login:\n");
    printf("Press 3 to Exit:");

    scanf(" %d",&lob);

    if(lob == 1){
        registration();

    } else if(lob == 2){

        login();
    } else if(lob == 3){
        recordingAllDataToFile();
        exit(1);
    } else{
        printf("Invalid Option!\n");
    }


}

void printingAllData(){

    for(int gcc=0; gcc< id ; gcc++ ){

        printf("id: %d-name:%s - age:%d - email:%s - password:%s\n",info[gcc].id,info[gcc].name , info[gcc].age , info[gcc].email , info[gcc].password);

    }
}

void login(){
    char lEmail[50];
    char passWord[50];
    int found  = -1;
    printf("This is login form:\n");

    printf("Enter your email to login:");
    scanf(" %[^\n]",&lEmail);

    eFound = -1;
    myStrCmp(lEmail);

    printf("Enter your password :");
    scanf(" %[^\n]",&passWord);

    pFound = -1;
    passChecking(passWord , eFound);

    if(eFound != -1 && pFound == 1){
        userActionSector();

    } else{
        printf("Invalid email: or Password \n");
        login();
    }

}

void myStrCmp(char userInputChar[50]){

    int sameCount=0;
    int sec = charCounting(userInputChar);

    for(int i=0; i<globalIndex ; i++){
        int first = charCounting(info[i].email);

        if( first == sec){

            for(int gcc=0; gcc<first ; gcc++){

                if( info[i].email[gcc] != userInputChar[gcc]){

                    break;
                } else{
                    sameCount++;

                }

            }

        }
        if( sec == sameCount){
            eFound = i;
            break;
        }

    }

}

void passChecking(char pass[50] , int userIndex){

    int passCount = charCounting(pass);
    int infoPassCount = charCounting(info[userIndex].password);

    int sameCount=0;

    if(passCount == infoPassCount) {

        for (int ncc = 0; ncc < passCount; ncc++) {

            if (pass[ncc] == info[userIndex].password[ncc]) {

                sameCount++;

            } else{
                break;
            }

        }

        if( sameCount == passCount){
            pFound = 1;
        }
    }

}

int charCounting(char toCount[50]){
    int charCount = 0;
    for(int gcc=0; gcc<50 ; gcc++){

        if( toCount[gcc] == '\0'){
            break;
        } else{
            charCount++;
        }
    }
    return charCount;
}

void recordingAllDataToFile(){

    FILE *fptr = fopen("dipDB.txt","w");

    if(fptr == NULL){
        printf("Error at recordingAllDataToFile fun():\n");
    } else{

        for(int gcc=0; gcc<id; gcc++){


            fprintf(fptr , "%d %d %s %s %s\n",info[gcc].id , info[gcc].age , info[gcc].name , info[gcc].email  , info[gcc].password);


        }
        printf("Recording all data to dipDB.txt is complete!\n");
    }

    fclose(fptr);

}

void userActionSector(){

    int userAction=0;

    printf("Welcome Sir: %s\n",info[eFound].name);
    printf("Press 1 to User Action Sector:\n");
    printf("Press 2 to Home:\n");
    printf("Press 3 to Exit:");
    scanf(" %d",&userAction);

    if(userAction == 1){
        printf("this is user action sector:\n");
    } else if( userAction == 2){
        login();
    } else if(userAction == 3){
        lobby();
    } else{
        printf("Invalid Option!\n");
        userActionSector();
    }
}

void loadingAllDataFromFile(){

    FILE *fptr = fopen("dipDB.txt","r");

    if(fptr == NULL){
        printf("Error at loading!\n");
    } else{

        for(int gcc=0; gcc<SIZE ; gcc++){

            fscanf(fptr ,"%d%d%s%s%s",&info[gcc].id , &info[gcc].age, &info[gcc].name,&info[gcc].email,&info[gcc].password);

            if(info[gcc].name[0] == '\0'){
                break;
            }
            globalIndex++;

        }

    }


}

void registration(){

    char arr[10]={'@','g','m','a','i','l','.','c','o','m'};
    int a = 0;
    char userEmail[50];
    printf("This is register\n");
    printf("Enter your email:");
    FILE *fptr = fopen("dipDB.txt","w");

    scanf("%s",&userEmail);
    checkEmail(userEmail);

    for(int i=0;i<50;i++){

        if(userEmail[i]==arr[a]) {
            a++;
            if (a == 10) {
                if (userEmail[i+1] != '\000') {
                    printf("email invalid\n");
                    lobby();
                }
                info[id].id=id;
                printf("Enter your age:");
                scanf("%d",&info[id].age);
                printf("Enter your name:");
                scanf("%s",&info[id].name);
                printf("Enter your password:");
                scanf("%s",&info[id].password);
                printf("register successfully :\n");
                for (int j = 0; j < 50; j++) {
                    info[id].email[j] = userEmail[j];
                }
                id++;
                loadingAllDataFromFile();
                printingAllData();
                lobby();
            }

        } else if (userEmail[i]=='\000'){
            printf("email invalid:\n");
            lobby();
        } else if (userEmail[i+1]=='\000'){
            printf("email invalid\n");
            lobby();
        } else if (userEmail[i] == arr[a-1]){
            printf("email invalid\n");
            lobby();
        } else if (userEmail[i+1]==arr[a] && userEmail[i+1] != '@'){
            printf("email invalid\n");
            lobby();
        }
    }

    fclose(fptr);

}

void checkEmail(char userInputEmail[]){
    int c=0;

    for (int i = 0; i < 50; i++) {

        if (userInputEmail[0] == info[i].email[0] && userInputEmail[i] != '\000' && id >= 1){
            for (int j = 0; j < 50; j++) {
                if (userInputEmail[j+1] == info[i].email[j+1] && userInputEmail[j] != '\000'){
                    c++;
                    if(userInputEmail[c]=='m'){
                        printf("email already exists:\n");
                        lobby();
                    }
                } else if (userInputEmail[j+1] != info[i].email[j+1]){
                    break;
                }
            }

        }

    }
}
void infoId(){
    FILE *fptr = fopen("dipDB.txt","r");
    char c;
    do {
        c = fgetc(fptr);
        if (c=='\n'){
            id++;
        }
    }while (c != EOF);
    fclose(fptr);
}