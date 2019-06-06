
#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <string.h>
#include <io.h>
#include <direct.h>
#include <errno.h>

#define MY_DIR		1
#define MY_FILE		2
#define MY_UNKNOWN	3
#define MY_MAX_PATH		1024
#define	MY_MAX_FILENAME	256

struct _finddata_t fileinfo;

int my_rename(char *path, char *filename);

int main(int argc, char **argv)
{	
	char	path[MY_MAX_PATH];
	char	filename[MY_MAX_FILENAME];

	if ( argc != 3)
	{
		printf("Usage: lower <path> <filename or dirname>\n");
		return -1;
	}

	if ( strlen(argv[1]) > MY_MAX_PATH)
	{
		return -1;
	}

	/* */
	strcpy(path, argv[1]);
	strcpy(filename, argv[2]);

	my_rename(path, filename);
	return 0;
}

int my_rename(char *in_path, char *in_filename)
{
	char	path[MY_MAX_PATH];
	char	filename[MY_MAX_FILENAME];
	char	newname[MY_MAX_PATH];
	struct stat buffer;
	char	filemode;
	char	*p, *q;
	long	my_findhandle;

	strcpy(path, in_path);
	strcpy(filename, in_filename);

	if ( filename[0] == '.') 
		return 0;

	if ( chdir(path) < 0)
		return -1;

	if ( stat(filename, &buffer) < 0)
	{
		return -1;
	}

	if ( (buffer.st_mode & _S_IFDIR) == _S_IFDIR) 
	{
		filemode = MY_DIR;
	}
	else if ( (buffer.st_mode & _S_IFREG) == _S_IFREG)
	{
		filemode = MY_FILE;
	}
	else
	{
		filemode = MY_UNKNOWN;
	}

	p = filename;
	q = newname;
	while ( *p != '\0')
	{
		*q++ = tolower(*p++);
	}
	*q = '\0';
	
	if ( strcmp(filename, newname) != 0)
	{
		if ( rename(filename, newname) < 0)
			return -1;
	}

	if ( filemode == MY_DIR)
	{
		strcat(path, "/");
		strcat(path, filename);

		if ( chdir(path) < 0)
			return -1;

		my_findhandle = _findfirst("*.*", &fileinfo);
		if ( my_findhandle < 0)
			return -1;

		my_rename(path, fileinfo.name);	

		while ( _findnext(my_findhandle, &fileinfo) >= 0)
		{
			my_rename(path, fileinfo.name);
		}

		_findclose(my_findhandle);
	}

	return 0;
}