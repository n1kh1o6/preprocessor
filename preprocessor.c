#include <stdio.h>
#include <string.h>
#include <stdlib.h>

//max length of a file name is 255 bytes.
//max lnegth of a file is 1024 bytes. (for our preprocessor)
/*so far my preprocessor is able to :
1) remove single line comments.
2) include external files.
*/

FILE* file_handle; // declared globally for it to be acessed thorughout the entire code.

int first_character_of_line(char * line){ //function to return the first character of a given line(will be useful for stripping comments and checking for directives)
    char c= *line;
    if(c!=EOF)
    return (int)c;
    return -1;
}

void file_inclusion(char * file_name){
    file_handle=fopen(file_name,"r");
    FILE* temp_handle;
    temp_handle=fopen("temp_file.c","w");
    if(!file_handle||!temp_handle){            // checking if files can be opened.
        printf("FILE OPEN FAILED, UNABLE TO INCLUDE EXTERNAL FILE. \n");
        return;
    }
    else{
        char line[1024];
        char included_file[256];
        char check[8];
        printf("FILE SUCCESSFULLY OPENED FOR EXTERNAL FILE INLCUSION. \n");
        while(fgets(line,1024,file_handle)!=NULL){
            int flag=0;
            int flag2=0;
            for(int i=0;*(line+i)!='\0';i++){
                if(*(line+i)==(char)35){
                    flag=1;
                    for(int j=i+1;j<i+8;j++){
                        check[j-(i+1)]=line[j];
                    }
                    if((strcmp("include",check))==0){
                        int location;
                        for(int j=i+8;*(line+j)!='\0';j++){
                            if(*(line+j)==(char)60||*(line+j)==(char)34){
                                if(*(line+j)==(char)60)
                                flag2=1;
                                location=j;
                                break;
                            }
                        }
                        int k;
                        for(k=location+1;(*(line+k)!='>')&&(*(line+k)!=(char)34);k++){
                            included_file[k-location-1]=*(line+k);
                        }
                        included_file[k]='\0';
                    }
                    break;
                }
            }
            if(flag){
                printf("PREPARING TO INCLUDE %s \n",included_file);
                FILE* inc_handle;
                char file_path[256]="/usr/include/";
                if(flag2){
                    int length=strlen(included_file);
                    int i;
                    for(i=13;i<=13+length;i++){
                        file_path[i]=included_file[i-13];
                    }
                    file_path[i]='\0';
                    inc_handle=fopen(file_path,"r");
                }
                else{
                    inc_handle=fopen(included_file,"r");
                }
                char file_line[1024];
                while(fgets(file_line,1024,inc_handle)!=NULL){
                    fputs(file_line,temp_handle);
                }
                fputs("\n",temp_handle);
                printf("%s SUCCESFULLY INCLUDED. \n",included_file);
                fclose(inc_handle);
                included_file[0]='\0';
                file_path[13]='\0';
            }
            else{
                fputs(line,temp_handle);
            }
            check[0]='\0';
            line[0]='\0';
        }
        fclose(file_handle);
        fclose(temp_handle);
        remove(file_name);
        rename("temp_file.c",file_name); 
    }   
}

void comment_stripping(char * file_name){
    file_handle=fopen(file_name,"r");
    FILE* temp_handle;
    temp_handle=fopen("temp_file.c","w");      // creating a temporary file to copy contents such that comments are replaced with newline.
    if(!file_handle||!temp_handle){            // checking if files can be opened.
        printf("FILE OPEN FAILED, UNABLE TO STRIP COMMENTS. \n");
        return;
    }
    else{
        char line[1024];
        printf("FILE SUCCESSFULLY OPENED FOR STRIPPING SINGLE_LINE COMMENTS. \n");
        while(fgets(line,1024,file_handle)!=NULL){
            int flag =0;
            int start_location=-1,end_location=-1;
            for(int i=0;*(line+i)!='\0';i++){
                if(*(line+i)==(char)34){
                    start_location=i;
                    for(int j=i+1;*(line+j)!='\0';j++){
                        if(*(line+j)==(char)34)
                        end_location=j;
                    }
                    break;
                }
            }
            for(int i=0;*(line+i)!='\0';i++){
                if(((*(line+i)==(char)47)&&(*(line+i+1)==(char)47))&&!(i>start_location&&i<end_location)){
                    line[i]='\n';
                    line[i+1]='\0';
                    break;
                }
            }
            fputs(line,temp_handle);
        }
        printf("SINGLE-LINE COMMENTS SUCCESSFULLY REMOVED. \n");
        fclose(file_handle);
        fclose(temp_handle);
        remove(file_name);
        rename("temp_file.c",file_name);        //deleting the old file and renaming the new file to the old file.
    }

}

int main(){
    printf("ENTER THE COMPLETE NAME OF THE C FILE TO BE PROCESSED(INCLUDING THE .C) : \n");
    char file_name[256];
    while(1){
        char file_name[256];
        scanf("%s",file_name);
        int file_length= strlen(file_name);
        if(file_name[file_length-1]=='c'&&file_name[file_length-2]=='.'){
            printf("PREPROCESSING WILL NOW PROCEED. \n");
            break;
        }
        else{
            file_name[0]='\0';
            printf("PLEASE ENTER A VALID FILE NAME. \n");
        }
    }
    //file_inclusion(file_name);
    comment_stripping(file_name);
    return 0;
}