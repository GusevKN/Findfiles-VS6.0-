#include <windows.h>
#include <stdlib.h>
#include <stdio.h>
#include <fstream.h>
#include <string.h>
#include <tchar.h>
	BOOL SearchFiles(LPCTSTR, BOOL);
	ofstream book_file(NULL+"DISK_C_ALL_DIRECTORY.txt");
	int N = 0;
int main(){
	char Name[MAX_PATH];
	GetModuleFileNameA(NULL, Name, MAX_PATH);
	system ("chcp 1251 > nul");
//	cout << "Вы уверены, что хотите продолжить?" << endl;
//	cout << "если да, то нажмите любую букву, затем ENTER" << endl;
	char *text = new char[15];
	cout << "Write to disk end press \"Enter\"" << endl;
	cin >> text;
	strncat (text, ":\\*", 5);
	SearchFiles(text, TRUE);
	cout << "All right, press \"ENTER\"" << endl;
	cin >> "\n";
    return 0;
}


BOOL SearchFiles(LPCTSTR lpszFileName, BOOL bInnerFolders = TRUE){
//    
    LPTSTR part;
    char tmp[MAX_PATH]; // временный массив
    char name[MAX_PATH];

    HANDLE hSearch = NULL;
    WIN32_FIND_DATA wfd;
    memset(&wfd, 0, sizeof(WIN32_FIND_DATA));

    // сначала поиск внутри вложенных папок ...
    if(bInnerFolders)
    {
        if(GetFullPathName(lpszFileName, MAX_PATH, tmp, &part) == 0) return FALSE;
        strcpy(name, part);
        strcpy(part, "*.*");

        // если папки существуют, то делаем поиск
        wfd.dwFileAttributes = FILE_ATTRIBUTE_DIRECTORY;
        if (!((hSearch = FindFirstFile(tmp, &wfd)) == INVALID_HANDLE_VALUE))
        do
        {
            // в каждой папке есть две папки с именами "." и ".."
            // и эти папки мы не трогаем

            // пропускаем папки "." и ".."
            if (!strncmp(wfd.cFileName, ".", 1) || !strncmp(wfd.cFileName, "..", 2))
            continue;

            if (wfd.dwFileAttributes & FILE_ATTRIBUTE_DIRECTORY) // если мы нашли папку
            {
                char next[MAX_PATH];
                if(GetFullPathName(lpszFileName, MAX_PATH, next, &part) == 0) return FALSE;
                strcpy(part, wfd.cFileName);
                strcat(next, "\\");
                strcat(next, name);

                SearchFiles(next, TRUE);
            }
        }
        while (FindNextFile(hSearch, &wfd)); // ищем следующий файл

        FindClose (hSearch); // заканчиваем поиск
    }

    if ((hSearch = FindFirstFile(lpszFileName, &wfd)) == INVALID_HANDLE_VALUE)
        return TRUE; // в противном случае выходим
    do
    if (!(wfd.dwFileAttributes & FILE_ATTRIBUTE_DIRECTORY)) // если мы нашли файл
    {
        char file[MAX_PATH];
        if(GetFullPathName(lpszFileName, MAX_PATH, file, &part) == 0) return FALSE;
        strcpy(part, wfd.cFileName);
 

	//	printf("%s\n", file);
		N++;
		book_file << N <<" "<< file <<"  " << endl;

    }
    while (FindNextFile(hSearch, &wfd)); // ищем следующий файл
    FindClose (hSearch); // заканчиваем поиск

    return TRUE;
}
