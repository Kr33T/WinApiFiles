#define _CRT_SECURE_NO_WARNINGS
#include <Windows.h>
#include <string.h>
#include <stdio.h>
#include <math.h>

#define SIZE_OF_BUFFER 300
#define READFILE L"data.txt"
#define WRITEFILE L"res.txt"

void writeResultInFile(char*);
float* getCoefficients();
void solveMethod(float* array);

int main()
{
	system("chcp 1251 > nul");

	DeleteFile(WRITEFILE);
	float* array = getCoefficients();
	solveMethod(array);
	return 0;
}

void solveMethod(float* array)
{
	float a = array[0], b = array[1], c = array[2];

	char* resBuffer = calloc(SIZE_OF_BUFFER, sizeof(char));

	if (a != 0 && b != 0 && c != 0)
	{
		float D;
		D = pow(b, 2) - (4 * a * c);

		sprintf(resBuffer, "Дискриминант: %f\n", D);
		printf(resBuffer);

		if (D < 0)
		{
			sprintf(resBuffer, "Корней у уравнения нет");
			printf(resBuffer);
		}
		else if (D == 0)
		{
			float x;
			x = -b / (2 * a);
			sprintf(resBuffer, "У уравнения есть один корень:\nx: %f", x);
			printf(resBuffer);
		}
		else if (D > 0)
		{
			float x1, x2;
			x1 = (-b + sqrt(D)) / (2 * a);
			x2 = (-b - sqrt(D)) / (2 * a);
			sprintf(resBuffer, "Уравнение имеет два корня:\nx1: %f, x2: %f", x1, x2);
			printf(resBuffer);
		}
	}
	else if (a == 0 && c == 0)
	{
		sprintf(resBuffer, "У уравнения имеется один корень:\nx: 0");
		printf(resBuffer);
	}
	else if (b == 0 && c == 0)
	{
		sprintf(resBuffer, "Уравнение имеет один корень:\nx: 0");
		printf(resBuffer);
	}
	else if (b == 0)
	{
		c *= -1;
		c /= a;
		if (c < 0)
		{
			sprintf(resBuffer, "Корней у уравнения нет");
			printf(resBuffer);
		}
		else
		{
			c = sqrt(c);
			sprintf(resBuffer, "У уравнения имеется 2 корня:\nx1: %f, x2: %f", c, -c);
			printf(resBuffer);
		}
	}
	else if (c == 0)
	{
		sprintf(resBuffer, "Уравнение имеет два корня:\nx1: 0, x2: %f", -b / a);
		printf(resBuffer);
	}
	else if (a == 0)
	{
		c *= -1;
		c /= b;
		sprintf(resBuffer, "Уравнение имеет один корень:\nx: %f", c);
		printf(resBuffer);
	}
	writeResultInFile(resBuffer);
}

float* getCoefficients()
{
	char* resBuffer = calloc(SIZE_OF_BUFFER, sizeof(char));
	HANDLE hFile = CreateFile(READFILE, GENERIC_READ, FILE_SHARE_READ, NULL, OPEN_ALWAYS, FILE_ATTRIBUTE_NORMAL, NULL);
	char Buffer[SIZE_OF_BUFFER];
	DWORD lpNumberOfBytesRead;
	if (hFile == INVALID_HANDLE_VALUE)
	{
		printf("Ошибка, не удалось открыть файл");
		CloseHandle(hFile);
		return 1;
	}
	while (ReadFile(hFile, Buffer, sizeof(Buffer), &lpNumberOfBytesRead, NULL) != FALSE)
	{
		if (lpNumberOfBytesRead == 0)
			break;
	}
	CloseHandle(hFile);

	char* str;
	float* array = calloc(3, sizeof(float*));
	str = strtok(Buffer, " ");

	for (int i = 0; str != NULL; i++)
	{
		array[i] = atof(str);
		str = strtok(NULL, " ");
	}

	float a = array[0], b = array[1], c = array[2];
	sprintf(resBuffer, "Коэффициенты уравнения:\na: %f, b: %f, c: %f\n", array[0], array[1], array[2]);
	printf(resBuffer);
	writeResultInFile(resBuffer);

	return array;
}

void writeResultInFile(char* answer)
{
	HANDLE resFile = CreateFile(WRITEFILE, GENERIC_WRITE, FILE_SHARE_WRITE, NULL, CREATE_ALWAYS, FILE_ATTRIBUTE_NORMAL, NULL);
	DWORD lpNumberOfBytesWrite;
	if (resFile == INVALID_HANDLE_VALUE)
	{
		printf("Ошибка при открытии файла для записи");
		return 1;
	}
	WriteFile(resFile, answer, strlen(answer), &lpNumberOfBytesWrite, NULL);
	CloseHandle(resFile);
}