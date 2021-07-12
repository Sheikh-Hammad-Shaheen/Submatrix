#include<iostream>
#include<fstream>
#include<iomanip>
using namespace std;
void re_grow_2d(int* *&ptr, int &size)
{
	int* *temp = new int*[size + 1];
	for (int i = 0; i < size; i++)
		temp[i] = ptr[i];
	if (size != 0)
		delete[]ptr;
	temp[size++] = nullptr;
	ptr = temp;
	temp = nullptr;
}
void re_grow_1d(int *&ptr, int &size)
{
	int *temp = new int[++size];
	for (int i = 1; i < size - 1; i++)
		temp[i] = ptr[i];
	if (ptr != nullptr)
		delete[]ptr;
	ptr = temp;
	temp = nullptr;
}
void fill_data(int* *&mat, int &row_size)
{
	ifstream fin;
	char f_name[10] = { '\0' }, ch = 0;
	int  col_size = 1, no = 0;
	cout << "Enter file name to read a Matrix: ";
	cin >> f_name;
	fin.open(f_name, ios::in);
	if (!fin)
	{
		cout << "File not found." << endl;
		exit(1);
	}
	while (true)
	{

		if (fin.eof())
			break;
		ch = 0;
		col_size = 1;
		re_grow_2d(mat, row_size);
		mat[row_size - 1] = new int;
		while (ch != '\n'&& !fin.eof())
		{
			fin >> no;
			fin.get(ch);
			re_grow_1d(mat[row_size - 1], col_size);
			mat[row_size - 1][col_size - 1] = no;
		}
		mat[row_size - 1][0] = col_size - 1;
	}
	fin.close();
}
void delete_memory(int* *&data,const int &size)
{
	for (int i = 0; i<size; i++)
		delete[]data[i];
	if (data != nullptr)
		delete[]data;
	data = nullptr;
}
void display(const int *const *const data, const int &start, const int &end)
{
	int col_size = 0;
	for (int i = start; i<end; i++)
	{
		col_size = data[i][0];
		for (int j = 1; j <= col_size; j++)
			cout << setw(3) << data[i][j] << " ";
		cout << endl;
	}
}
bool is_present(const int *const *const mat, const int row, const int col, const int *const *const sub, const int size)
{
	int col_size = sub[0][0];
	for (int i = 0; i < size; i++)
	{
		for (int j = 1; j < col_size; j++)
		{
			if (mat[row + i][col + j] != sub[i][j])
				return false;
		}
	}
	return true;
}
void find_sub_presence(const int *const *const mat, const int &mat_row, const int *const *const sub, const int sub_row)
{
	for (int i = 0; i < mat_row - (sub_row - 1); i++)
	{
		for (int j = 1; j < mat[0][0] - (sub[0][0] - 1); j++)
		{
			if (is_present(mat, i, j, sub, sub_row))
				cout << "Sub Matrix Exist on cordinates start at ( " << i << ", " << j << " ) end at ( " << (i + sub_row) - 1 << ", " << (j + sub[0][0]) - 1 << " )" << endl;
		}
	}
}
int main()
{
	int* *mat = nullptr, mat_row = 0, sub_row = 0;
	int* *sub = nullptr;
	fill_data(mat, mat_row);
	fill_data(sub, sub_row);
	if (sub_row <= mat_row&&sub[0][0] <= mat[0][0])
	{
		cout << "Main Matrix: " << endl;
		display(mat, 0, mat_row);
		cout << "Sub Matrix: " << endl;
		display(sub, 0, sub_row);
		find_sub_presence(mat, mat_row, sub, sub_row);
	}
	else
	{
		cout << "Main Matrix: " << endl;
		display(mat, 0, mat_row);
		cout << "Sub Matrix: " << endl;
		display(sub, 0, sub_row);
		cout << "Sub mat size of row and column must be smaller then Main Array. " << endl;
	}
	delete_memory(mat,mat_row);
	delete_memory(sub,sub_row);
}