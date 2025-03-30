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
//	cout << "�� �������, ��� ������ ����������?" << endl;
//	cout << "���� ��, �� ������� ����� �����, ����� ENTER" << endl;
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
    char tmp[MAX_PATH]; // ��������� ������
    char name[MAX_PATH];

    HANDLE hSearch = NULL;
    WIN32_FIND_DATA wfd;
    memset(&wfd, 0, sizeof(WIN32_FIND_DATA));

    // ������� ����� ������ ��������� ����� ...
    if(bInnerFolders)
    {
        if(GetFullPathName(lpszFileName, MAX_PATH, tmp, &part) == 0) return FALSE;
        strcpy(name, part);
        strcpy(part, "*.*");

        // ���� ����� ����������, �� ������ �����
        wfd.dwFileAttributes = FILE_ATTRIBUTE_DIRECTORY;
        if (!((hSearch = FindFirstFile(tmp, &wfd)) == INVALID_HANDLE_VALUE))
        do
        {
            // � ������ ����� ���� ��� ����� � ������� "." � ".."
            // � ��� ����� �� �� �������

            // ���������� ����� "." � ".."
            if (!strncmp(wfd.cFileName, ".", 1) || !strncmp(wfd.cFileName, "..", 2))
            continue;

            if (wfd.dwFileAttributes & FILE_ATTRIBUTE_DIRECTORY) // ���� �� ����� �����
            {
                char next[MAX_PATH];
                if(GetFullPathName(lpszFileName, MAX_PATH, next, &part) == 0) return FALSE;
                strcpy(part, wfd.cFileName);
                strcat(next, "\\");
                strcat(next, name);

                SearchFiles(next, TRUE);
            }
        }
        while (FindNextFile(hSearch, &wfd)); // ���� ��������� ����

        FindClose (hSearch); // ����������� �����
    }

    if ((hSearch = FindFirstFile(lpszFileName, &wfd)) == INVALID_HANDLE_VALUE)
        return TRUE; // � ��������� ������ �������
    do
    if (!(wfd.dwFileAttributes & FILE_ATTRIBUTE_DIRECTORY)) // ���� �� ����� ����
    {
        char file[MAX_PATH];
        if(GetFullPathName(lpszFileName, MAX_PATH, file, &part) == 0) return FALSE;
        strcpy(part, wfd.cFileName);
 

	//	printf("%s\n", file);
		N++;
		book_file << N <<" "<< file <<"  " << endl;

    }
    while (FindNextFile(hSearch, &wfd)); // ���� ��������� ����
    FindClose (hSearch); // ����������� �����

    return TRUE;
}
