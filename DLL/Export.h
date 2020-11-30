#pragma once
#include <cstdio>
#define EXPORT extern "C" __declspec(dllexport)

EXPORT void solve_problem(FILE* input, FILE* log, FILE* file_sub);


