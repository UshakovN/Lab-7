// dllmain.cpp : Определяет точку входа для приложения DLL.

#include "pch.h"
#include "Export.h"
#include <cstdio>
#pragma warning (disable: 6064)
#define EXPORT extern "C" __declspec(dllexport)

BOOL APIENTRY DllMain(HMODULE hModule,
	DWORD  ul_reason_for_call,
	LPVOID lpReserved
)
{
	switch (ul_reason_for_call)
	{
	case DLL_PROCESS_ATTACH:
	case DLL_THREAD_ATTACH:
	case DLL_THREAD_DETACH:
	case DLL_PROCESS_DETACH:
		break;
	}
	return TRUE;
}

void resize_str(char*& x, char*& y, int& i, int n, int k) {
	if (k < i) { y[k] = x[k]; resize_str(x, y, i, n, ++k); }
	return;
}

void change_str(char* x, char* y, char*& z, int pos_sub, int n_che, int i, int j, int k) {
	if (i < pos_sub) { z[i] = x[i]; change_str(x, y, z, pos_sub, n_che, ++i, j, k); }
	else if (j < n_che) { z[i] = y[j]; change_str(x, y, z, pos_sub, n_che, ++i, ++j, k); }
	else if (x[k] != '\0') { z[i] = x[k]; change_str(x, y, z, pos_sub, n_che, ++i, j, ++k); }
	return;
}

int sub_str(char* x, char* y, int i, int j, int k) {
	int pos = -1;
	if (x[i] != '\0') {
		if (y[k] != '\0') {
			if (x[j] == y[k]) { j++; k++; pos = sub_str(x, y, i, j, k); }
			else { k = 0; i++; j = i; pos = sub_str(x, y, i, j, k); }
		}
		else pos = i;
	} return pos;
}

void output_str(char* x, int i, int n, FILE* f) {
	if (i < n) { printf("%c", x[i]); fprintf(f, "%c", x[i]); output_str(x, ++i, n, f); }
	return;
}

void input_str(char *&x, int &i, int n, FILE * f) {
	if (n == 0) {
		char* y = new char[i * 2 + 2];
		resize_str(x, y, i, n, 0); n = i + 2; x = y;
	}
	if (fscanf_s(f, "%c", &x[i]) == 1 && x[i] != '\n') { input_str(x, ++i, --n, f); }
	else x[i] = '\0';
	return;
}

void process_str(FILE * input, FILE * log, char* sub, char* che, int n_sub, int n_che) {
	int n_str = 0; int pos = -1;
	char* str = nullptr; char *changed_str = nullptr;
	input_str(str, n_str, 0, input);
	fprintf(log, "Original string: ");
	output_str(str, 0, n_str, log);
	fprintf(log, "\n"); printf("\n");
	pos = sub_str(str, sub, 0, 0, 0); if (pos != -1) {
		fprintf(log, "Substring position: %d \n", pos);
		changed_str = new char[n_str - n_sub + n_che]; fprintf(log, "Changed string: ");
		change_str(str, che, changed_str, pos, n_che, 0, 0, (pos + n_sub));
		output_str(changed_str, 0, (n_str - n_sub + n_che), log);
		fprintf(log, "\n"); printf("\n");
		delete[] str; delete[] changed_str;
	}
	else { printf("Substring not found.\n"); fprintf(log, "Substring not found.\n"); }
	return;
}

EXPORT void solve_problem(FILE* input, FILE* log, FILE* file_sub) {
	char* sub = nullptr; char* che = nullptr;
	int n_sub = 0; int n_che = 0; int end = -1;
	input_str(sub, n_sub, 0, file_sub);
	input_str(che, n_che, 0, file_sub);
	while (end != 0 && !feof(input)) {
		process_str(input, log, sub, che, n_sub, n_che);
		printf("Press 0: exit. \n"); scanf_s("%d", &end); fprintf(log, "\n");
	}
	delete[] sub; delete[] che;
}
