#include <stdio.h>
#include <string.h>
#include <stdlib.h>

//max length of a file name is 255 bytes.
//max lnegth of a file is 1024 bytes. (for our preprocessor)
/*so far my preprocessor is able to :
1) remove single line comments.
*/

FILE* file_handle; // declared globally for it to be acessed thorughout the entire code.

int first_character_of_line(char * line){ //function to return the first character of a given line(will be useful for stripping comments and checking for directives)
    char c= *line;
    if(c!=EOF)
    return (int)c;
    return -1;
}

void comment_stripping(char * file_name){
    file_handle=fopen(file_name,"r+");
    FILE* temp_handle;
    temp_handle=fopen("temp_file.c","w");      // creating a temporary file to copy contents such that comments are replaced with newline.
    if(!file_handle||!temp_handle){            // checking if files can be opened.
        printf("FILE OPEN FAILED, UNABLE TO STRIP COMMENTS. \n");
        return;
    }
    else{
        char line[1024];
        printf("FILE SUCCESSFULLY OPENED. \n");
        while(fgets(line,1024,file_handle)!=NULL){
            if(*(line)==(char)47){
                fputc('\n',temp_handle);
            }
            else{
                fputs(line,temp_handle);
            }
        }
        printf("SINGLE-LINE COMMENTS SUCCESSFULLY REMOVED. \n");
        fclose(file_handle);
        fclose(temp_handle);
        remove(file_name);
        rename("temp_file.c",file_name);        //deleting the old file and renaming the new file to the old file.
    }

}

int main(){
    char file_name[256];
    printf("ENTER THE COMPLETE NAME OF THE C FILE TO BE PROCESSED(INCLUDING THE .C) : \n");
    scanf("%s",file_name);
    comment_stripping(file_name);
    return 0;
}