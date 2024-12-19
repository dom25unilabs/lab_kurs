#include <iostream>
#include <fstream>
#include <string>
#include <io.h>
#include <fcntl.h>
static void fin_mat(std::ifstream& fin, int n, double* mat)
{
	for (int i = 0; i < n * n; i++)
	{
		fin >> mat[i];
		if (!fin.eof() && fin.peek() == ';')
		{
			fin.ignore(1);
		}
	}
}
static void cin_mat(int n, double* mat)
{
	for (int i = 0; i < n * n; i++)
	{
		std::wcin >> mat[i];
	}
}
static void fout_mat(std::ofstream& fout, int n, double* mat)
{
	for (int i = 0; i < n; i++)
	{
		for (int j = 0; j < n - 1; j++)
		{
			fout << mat[i * n + j] << ";";
		}
		fout << mat[(i + 1) * n - 1] << "\n";
	}
}
static void cout_mat(int n, double* mat)
{
	for (int i = 0; i < n; i++)
	{
		for (int j = 0; j < n - 1; j++)
		{
			std::wcout << mat[i * n + j] << " ";
		}
		std::wcout << mat[(i + 1) * n - 1] << "\n";
	}
}
int wmain(int argc, wchar_t* argv[])
{
	if (!(_setmode(_fileno(stdout), _O_U8TEXT) && _setmode(_fileno(stdin), _O_U8TEXT) && _setmode(_fileno(stderr), _O_U8TEXT)))
		return 1;
	int n, cmd = 7;
	double* a = nullptr, * b = nullptr, * c = nullptr;
	while (cmd != 0)
	{
		if (cmd != 7)
		{
			std::wcout << L"Введите команду: ";
			std::wcin >> cmd;
		}
		switch (cmd)
		{
		case 1:
		{
			std::wcout << L"Введите размер матриц: ";
			std::wcin >> n;
			delete[] a;
			a = new double[n * n];
			delete[] b;
			b = new double[n * n];
			delete[] c;
			c = new double[n * n];
			std::wcout << L"Введите элементы матрицы A:\n";
			cin_mat(n, a);
			std::wcout << L"Введите элементы матрицы B:\n";
			cin_mat(n, b);
			std::wcout << L"Введите элементы матрицы C:\n";
			cin_mat(n, c);
			break;
		}
		case 2:
		{
			std::wstring name;
			std::wcout << L"Введите имя файла: ";
			std::wcin >> name;
			std::ifstream fin;
			fin.open(name);
			if (!fin)
			{
				std::wcout << L"Некорректная команда!";
				break;
			}
			fin >> n;
			delete[] a;
			a = new double[n * n];
			delete[] b;
			b = new double[n * n];
			delete[] c;
			c = new double[n * n];
			fin_mat(fin, n, a);
			fin_mat(fin, n, b);
			fin_mat(fin, n, c);
			fin.close();
			std::wcout << L"Файл считан!\n";
			break;
		}
		case 3:
		{
			int row, col;
			double val;
			std::wcout << L"Введите букву выбранной матрицы (A, B, C) для редактирования: ";
			wchar_t name;
			std::wcin >> name;
			row = 1;
			std::wcout << L"Введите номер строки: ";
			std::wcin >> row;
			std::wcout << L"Введите номер столбца: ";
			std::wcin >> col;
			std::wcout << L"Введите новое значение изменяемого элемента: ";
			std::wcin >> val;
			switch (name)
			{
			case L'A':
			{
				a[(row - 1) * n + col - 1] = val;
				break;
			}
			case L'B':
			{
				b[(row - 1) * n + col - 1] = val;
				break;
			}
			case L'C':
			{
				c[(row - 1) * n + col - 1] = val;
				break;
			}
			default: {
				std::wcout << L"Некорректная команда!";
				break;
			}
			}
			break;
		}
		case 4:
		{
			for (int col = 0; col < n; col++)
			{
				int cntza = 0, cntzb = 0;
				for (int row = 0; row < n; row++)
				{
					if (a[row * n + col] == 0)
					{
						cntza++;
					}
					if (b[row * n + col] == 0)
					{
						cntzb++;
					}
				}
				if (cntza >= cntzb)
				{
					for (int row = 0; row < n; row++)
					{
						c[row * n + col] = a[row * n + col];
					}
				}
				else
				{
					for (int row = 0; row < n; row++)
					{
						c[row * n + col] = b[row * n + col];
					}
				}
			}
			std::wcout << L"Операция выполнена!\n";
			break;
		}
		case 5:
		{
			std::wcout << L"Матрица A:\n";
			cout_mat(n, a);
			std::wcout << L"Матрица B:\n";
			cout_mat(n, b);
			std::wcout << L"Матрица C:\n";
			cout_mat(n, c);
			break;
		}
		case 6:
		{
			std::wstring name;
			std::wcout << L"Введите имя файла: ";
			std::wcin >> name;
			std::ofstream fout;
			fout.open(name, std::ios::app);
			if (!fout)
			{
				std::wcout << L"Некорректная команда!";
				break;
			}
			fout << n << '\n';
			fout_mat(fout, n, a);
			fout_mat(fout, n, b);
			fout_mat(fout, n, c);
			fout.close();
			std::wcout << L"Файл заполнен!\n";
			break;
		}
		case 7:
		{
			std::wcout << L"Список команд:\n1 - ввод матриц A, B и C из консоли;\n2 - ввод матриц А, В и С из файла;\n3 - редактирование элементов матриц A, B и C;\n4 - скопировать в матрицу С столбцы матриц А или В в зависимости от того, какой из столбцов содержит большее количество нулей;\n5 - вывод матриц в консоль;\n6 - вывод матриц в файл;\n7 - вывод списка команд;\n0 - выход из программы.\n";
			cmd = 1;
			break;
		}
		case 0:
		{
			std::wcout << L"Программа завершена.\n";
			break;
		}
		default:
		{
			std::wcout << L"Некорректная команда!\n";
			break;
		}
		}
	}
	delete[] a, b, c;
}