#include <cstdio> 
#include <locale.h>
#include <Windows.h>
#include <stdlib.h>
//#include "Export.h"
#pragma warning (disable: 6387)

int main() {
	setlocale(LC_ALL, "Rus");
	FILE* input; FILE* log; FILE* file_sub;
	fopen_s(&input, "input.txt", "rt");
	fopen_s(&file_sub, "sub.txt", "rt");
	fopen_s(&log, "log.txt", "wt");
	
	typedef void (*FUNC)(FILE*, FILE*, FILE*);
	HINSTANCE STRDLL;
	STRDLL = LoadLibrary(L"DLL.dll");
	FUNC solve_problem;
	solve_problem = (FUNC)GetProcAddress(STRDLL, "solve_problem");
	solve_problem(input, log, file_sub);
	fclose(input); fclose(file_sub); fclose(log);
	FreeLibrary(STRDLL);
	
	//solve_problem(input, log, file_sub);
	//fclose(input); fclose(file_sub); fclose(log);

	return 0;
}


/*
typedef void (*FUNC0)(char*, int, int, FILE*);
HINSTANCE link0;
link0 = LoadLibrary(L"StringDll.dll");
FUNC0 input_str;
input_str = (FUNC0)GetProcAddress(link0, "input_str");
input_str(sub, n_sub, 0, file_sub); input_str(che, n_che, 0, file_sub);
FreeLibrary(link0);

typedef void (*FUNC)(FILE*, FILE*, char*, char*, int, int);
HINSTANCE link;
link = LoadLibrary(L"StringDll.dll");
FUNC solve_problem;
solve_problem = (FUNC)GetProcAddress(link, "solve_problem");
*/

/*
	input_str(sub, n_sub, 0, file_sub); input_str(che, n_che, 0, file_sub);
	while (end != 0 && !feof(input)) {
		solve_problem(input, log, sub, che, n_sub, n_che);
		printf("Press 0: exit. \n"); scanf_s("%d", &end); fprintf(log, "\n");
	}
	delete[] sub; delete[] che;

*/