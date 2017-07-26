#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <string.h>

int main(void)
{
    // Prefixes of a jpeg file
    static const uint8_t gif1[6] = {0x47,0x49,0x46,0x38,0x39,0x61};
    static const uint8_t gif[3] = {0x00,0x00,0x3b};
    int flag=memcmp("mukul","mukul",sizeof("mukul"));
    //printf("%d",(int)flag);
    // open file for reading
    FILE* file = fopen("pengif.raw", "r"); // Open the file for reading
    if (file == NULL)
    {
      //  printf("mmkk");
        return EXIT_FAILURE;
    }

    // target file
    FILE* image = NULL;

    // keep track of jpegs opened
    int pic = 5;
    int check=0;
    // while there are bytes to be read in the file
    uint8_t buffer[8];
    size_t n_bytes = 0;
    while( (n_bytes = fread(buffer,1, 8, file)) > sizeof(gif1))
    {  
        //sleep(1);
        
        // compares first 4 bytes of buffer segment to jpeg prefixes to determine match
        if( memcmp(buffer, gif1, sizeof(gif1)) == 0){
           // printf("mkhk\n");
            // stores the jpeg file name with the # jpeg
            char gifName[64];
            sprintf(gifName ,"00%d.gif" , pic++);

            // match. close current file if present.
            if (image){
 	               fclose(image);}	
		
            // open new image file (sets NULL on failure)
            
            image = fopen(gifName, "wb");
	 // write to target file image
            
        }
        
        // write whatever we have for our current bytes
        if (image)
            fwrite(buffer, n_bytes, 1, image);
	if(memcmp(buffer, gif, sizeof(gif)) == 0){
	
		//printf("working");
   break;
		
		}
    }

    // the above loop can exit with a file open (in fact, it is guaranteed
    // if we opened at least one file), so close it if one is active.
    if (image)
        fclose(image);
}
