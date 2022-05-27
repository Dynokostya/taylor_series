#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
#include <stdio.h>
#include <conio.h>
#include <stdlib.h>
#include <tuple>
#include <math.h>
#include <iomanip>
#include <io.h>
using namespace std;

void main_menu();
tuple <float, float, float, float>
input_parameters(float x_begin, float x_end, float step, float epsilon);
void calculate(float x_begin, float x_end, float step, float epsilon);

const char* KR = "-----------------------------KR----------------------------\n";
char file_name[256] = "";

//-------------------------------------------
void return_to_main()
{
    cout << "Press any button to return to main menu...\n";
    _getch();
    main_menu();
}

//-------------------------------------------
tuple <float, float, float, float>
input_parameters(float x_begin, float x_end, float step, float epsilon)
{
    /*Function that inputs parameters x_begin, x_end, step and accuracy in console.
    If x_begin, x_end, step and accuracy are real, returns this parameters*/

    system("CLS");
    cout << KR << "Input X begin:\n";
    cin >> x_begin;
    system("CLS");
    cout << KR << "Input X end:\n";
    cin >> x_end;
    system("CLS");
    cout << KR << "Input step:\n";
    cin >> step;
    system("CLS");
    cout << KR << "Input accuracy:\n";
    cin >> epsilon;

    if (x_begin > x_end) // check that numbers are real
    {
        system("CLS");
        cout << KR << "X begin cannot be greater than X end!\n";
        return_to_main();
    }
    if (step <= 0)
    {
        system("CLS");
        cout << KR << "Step cannot be less than 0!\n";
        return_to_main();
    }
    if (epsilon <= 0 || epsilon >= 1)
    {
        system("CLS");
        cout << KR << "Accuracy cannot be less than 0 or greater than 1!\n";
        return_to_main();
    }

    return { x_begin, x_end, step, epsilon };
}

//-------------------------------------------
void open_input_file()
{
    /*Function that opens file with data for computation.
    Then calls the function calculate()*/

    system("CLS");
    cout << KR << "1. To open file, write the name of file (with an extension \".txt\")\n"
        "2. To move backwards, type 0\n";
    cin >> file_name;

    if (file_name[0] == '0')
        main_menu();

    if (_access(file_name, 0))
    {
        system("CLS");
        cout << KR << "There is no file with this name!\n";
        return_to_main();
    }
    else
    {
        FILE* file = fopen(file_name, "r");
        if (file == NULL)
        {
            system("CLS");
            cout << KR <<"Cannot open the file\n";
            return_to_main();
        }
        float data[4] = { 0.0, 0.0, 0.0, 0.0 };
        char text[128] = "";
        for (int i = 0; i < 4; ++i)
        {
            fgets(text, 128, file);
            data[i] = atof(text);
        }

        fclose(file);

        char choice = 'n';
        system("CLS");
        cout << KR << "Input data:\n"
            << "X begin: " << fixed << setprecision(2) << data[0] << "\n"
            << "X end: " << fixed << setprecision(2) << data[1] << "\n"
            << "Step: " << fixed << setprecision(2) << data[2] << "\n"
            << "Accuracy: " << fixed << setprecision(6) << data[3] << "\n\n"
            << "Do you want to continue computation?(y/n)\n";
        cin >> choice;
        if (choice == 'y')
            calculate(data[0], data[1], data[2], data[3]);
        else
        {
            system("CLS");
            return_to_main();
        }
    }
}

//-------------------------------------------
void create_file()
{
    /*Function, where user can create a file
    and input parameters (x_begin, x_end, step and accuracy) in file*/

    system("CLS");
    cout << KR << "1. To create file, write the name of file (with an extension \".txt\"):\n"
        "2. To move backwards, type 0\n";
    cin >> file_name;
    if (file_name[0] == '0')
        main_menu();
    if (!_access(file_name, 0))
    {
        char choice = 'n';
        system("CLS");
        cout << KR << "This file already exists!\n"
            "Do you want to manually owerwrite data in this file?(y/n)\n";
        cin >> choice;
        if (choice != 'y')
        {
            system("CLS");
            return_to_main();
        }
    }

    float x_begin = 0, x_end = 0, step = 0, epsilon = 0;
    tie(x_begin, x_end, step, epsilon) = input_parameters(x_begin, x_end, step, epsilon);
    FILE* file = fopen(file_name, "w");
    if (file == NULL)
    {
        system("CLS");
        cout << KR << "Cannot open the file\n";
        return_to_main();
    }

    system("CLS");
    if (fprintf(file, "%f\n%f\n%f\n%f", x_begin, x_end, step, epsilon))
        cout << KR << "Data has been written succesfully!\n";
    else
        cout << KR << "Cannot write data in file!\n";
    fclose(file);
    return_to_main();
}

//-------------------------------------------
void delete_file()
{
    system("CLS");
    cout << KR << "1. To delete file, write the name of file (with an extension \".txt\")\n"
        "2. To move backwards, type 0\n";
    cin >> file_name;
    if (file_name[0] == '0')
        main_menu();
    system("CLS");
    if (_access(file_name, 0))
        cout << KR << "There is no file with this name!\n";
    else
    {
        remove(file_name);
        cout << KR << "File has been deleted successfully!\n";
    }
    return_to_main();
}

//-------------------------------------------
void main_menu()
{
    /*Function that shows menu and calls other functions*/

    int choice = 0;
    float x_begin = 0, x_end = 0, step = 0, epsilon = 0;
    system("CLS");
    cout << KR << "1. Write in console\n"
        "2. Open file with input data\n"
        "3. Create file with input data\n"
        "4. Delete file\n"
        "5. Type 0 to exit\n";
    cin >> choice;

    switch (choice)
    {
    case 0:
        exit(3);
    case 1:
        tie(x_begin, x_end, step, epsilon) = input_parameters(x_begin, x_end, step, epsilon);
        calculate(x_begin, x_end, step, epsilon);
        break;
    case 2:
        open_input_file();
        break;
    case 3:
        create_file();
        break;
    case 4:
        delete_file();
        break;
    default:
        system("CLS");
        cout << KR << "Wrong data\n";
        return_to_main();
        break;
    } // end of "switch (choice)"
}

//-------------------------------------------
void write_results_in_file(float** arr, int rows, int cols, FILE* file)
{
    /*Function that writes results (array of x, series(x), y(x), absolute error and step) in file*/

    for (int i = 0; i < rows; ++i)
    {
        for (int j = 0; j < cols; ++j)
            fprintf(file, "%f ", arr[j][i]);

        fprintf(file, "\n");
    }
    fclose(file);
    system("CLS");
    cout << KR << "Data has been successfully written to the file!\n";
}

//-------------------------------------------
float exponential(float x, float epsilon, int* n, float num = 1, float res = 1)
{
    if (fabs(num) <= epsilon)
        return res;

    *n += 1;
    num *= x / *n;
    res += num;
    return exponential(x, epsilon, n, num, res);
}

//-------------------------------------------
void calculate(float x_begin, float x_end, float step, float epsilon)
{
    /* Function that computes exp(x) with input parameters and
    outputs two-dimensional array of results*/

    int rows = ceil((x_end - x_begin) / step) + 1;
    int cols = 5;
    auto** data = new float* [cols];
    for (int i = 0; i < cols; ++i)
        data[i] = new float[rows];

    float x = x_begin;
    int* n = new int[1];
    for (int i = 0; i < rows; ++i, x += step)
    {
        *n = 0;
        data[0][i] = x;
        data[1][i] = exp(x);
        data[2][i] = exponential(x, epsilon, n);
        data[3][i] = fabs(data[1][i] - data[2][i]);
        data[4][i] = *n;
    }

    system("CLS");
    cout << KR << setw(8) << "x"
        << setw(32) << "series(x)"
        << setw(32) << "y(x)"
        << setw(32) << "absolute error"
        << setw(8) << "steps" << endl;

    for (int i = 0; i < rows; ++i)
    {
        for (int j = 0; j < cols; ++j)
        {
            if (j == 0)
                cout << fixed << setprecision(2) << setw(8) << data[j][i];
            else if (j == 4)
                cout << fixed << setprecision(0) << setw(8) << data[j][i];
            else
                cout << fixed << setprecision(6) << setw(32) << data[j][i];
        }
        cout << endl;
    }

    char choice = 'n';
    cout << "\nDo you want to save data in file?(y/n)\n";
    cin >> choice;
    if (choice != 'y')
    {
        for (int i = 0; i < cols; i++)
            delete[] data[i];
        delete[] data;
        system("CLS");
        return_to_main();
    }

    system("CLS");
    cout << KR << "Write the name of file to save data (with an extension \".txt\"):\n";
    cin >> file_name;

    if (!_access(file_name, 0))
    {
        char new_choice = 'n';
        system("CLS");
        cout << KR << "File with this name already exists!\n"
            "Do you want to manually owerwrite data?(y/n)\n";
        cin >> new_choice;
        if (new_choice != 'y')
        {
            system("CLS");
            cout << KR;
            return_to_main();
        }
    }

    FILE* file = fopen(file_name, "w");
    if (file == NULL)
    {
        system("CLS");
        cout << KR << "Cannot open the file\n";
        return_to_main();
    }
    write_results_in_file(data, rows, cols, file);

    for (int i = 0; i < cols; i++)
        delete[] data[i];
    delete[] data;
    delete[] n;
    return_to_main();
}

//-------------------------------------------
int main()
{
    main_menu();
    return 0;
}
