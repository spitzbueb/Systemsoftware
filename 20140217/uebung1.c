#include <stdio.h>
#include <errno.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <unistd.h>
#include <string.h>
#include <stdlib.h>

int main()
{
	struct stat stat_buf;
	int r;
	char *name = "tmp";
	int e;
	FILE *datei;
	char *dateiname = "Das Alphabet";
	int dateiCheck;
	char *alphabet = {"abcdefghijklmnopqrstuvwxyz"};
	
	r = stat(name, &stat_buf);
	
	if(r < 0)
	{
		int myerrno = errno;
		const char *error_string = strerror(myerrno);
		printf("errno=%d\nmessage=%s\n",myerrno,error_string);
		
		/* Ordner erstellen */
		e = mkdir(name,S_IRWXU);
		if(e == 0)
		{
			printf("Ordner wurde erstellt!\n");
			r = stat(name, &stat_buf);
		}
	}
	
	if(r == 0)
	{
		int changeDirectory = chdir(name);
		dateiCheck = stat(dateiname, &stat_buf);
		if(dateiCheck < 0)
		{
			int myerrno = errno;
			const char *error_string = strerror(myerrno);
			printf("errno=%d\nMessage=%s\n",myerrno,error_string);
			
			/*Datei erstellen*/
			datei = fopen(dateiname,"w");
			if(datei < 0)
			{
				prinft("Fehler beim erstellen\n");
			}
			fclose(datei);
			dateiCheck = stat(dateiname, &stat_buf);
		}
		
		if(dateiCheck == 0)
		{
			datei = fopen(dateiname,"w");
			char buchstabe;
			
			if(datei != NULL)
			{
				
				int strlength = strlen(alphabet)+1;
				int zaehler;
				int fd = fileno(datei);
				for(zaehler = strlength; zaehler>0;zaehler--)
				{
					printf("%i\n",zaehler);
					lseek(fd,zaehler,0);
					buchstabe = alphabet[zaehler-1];
					printf("%c\n",buchstabe);
					fputc(buchstabe,datei);
				}
			}
			else
			{
				
			}
			
			fclose(datei);
		}
		
	}
	
	return 0;
}