// Author: Neeraj Mishra
// nmcnemis@gmail.com

// GameofLife.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>
#include <time.h>
#include <iomanip>
#include <cstdlib>
#include <Windows.h>

using namespace std;

void Render(int** a, int w, int h);

// Order of functions is low-level to high-level.
// For example, first complex calculations then painting the canvas of console. 

// Function to print 2D array with all values as 0 (dead state) whereas 1 is alive state.
// Yeah no shit.

void DeadState(int** array, int width, int height)
{
    for (int i = 0; i < width; ++i)
    {
        for (int j = 0; j < height; ++j)
        {
            array[i][j] = { 0 };
        }
    }
}

// Function to randomize the states to either 0 or 1 (Dead or alive, if you will ;D).

void RandomizeStates(int** array, int width, int height)
{
    // Explicit type casting as time_t to unsigned int, there's possibility of data loss.

    srand((int)time(NULL));
    for (int i = 0; i < width; ++i)
    {
        for (int j = 0; j < height; ++j)
        {
            array[i][j] = { rand() % 2 };
        }
    }
}

// This function will be used by the NewState function
// to take note of the numbers of neigbors and apply rules of life to them.

void RulesOfLife(int** array, int count)
{
    count -= 1;

    for (int i = 0; i < 2; ++i)
    {
        for (int j = 0; j < 2; ++j)
        {    
            if (array[i][j] == 1)
            {
                if (count <= 1)
                {
                    array[i][j] = 0;
                }
                else
                    if (array[i][j] <= 3)
                    {
                        array[i][j] = 1;
                    }
                    else
                    {
                        array[i][j] = 0;
                    }
            }
            else
            {
                if (count == 3)
                {
                    array[i][j] = 1;
                }
                else
                {
                    array[i][j] = 0;
                }
            }
        }
    }
}
// Use width and height of >= 3.

void NextState(int** array, int width, int height)
{
    for (int i = 0; i < width; ++i)
    {
        for (int j = 0; j < height; ++j)
        {
         // Corner cases where the neighbor size is 3.

            if ((i == 0 && j == 0) || (i == width - 1 && j == 0)
                || i == 0 && j == height - 1 || (i == width - 1 && j == height - 1))
            {
                if (i == 0 && j == 0)
                {
                    int count = 0;
                    count += array[0][0]; // Itself. Do we consider the neighbors of the dead? If yes, this is what it is here for. If not, just remove it and from below code too.
                    count += array[0][1];
                    count += array[1][1];
                    count += array[1][0];
                    
                    cout << "Top Left"  << " : " << count << "\n";
                }
                if (i == width - 1 && j == 0)
                {
                    int count = 0;
                    count += array[width - 1][0]; // Itself.
                    count += array[width - 2][0];
                    count += array[width - 2][height - 2];
                    count += array[width - 1][height - 2];

                    cout << "Bottom Left" << " : " << count << "\n";
                }
                if (i == 0 && j == height - 1)
                {
                    int count = 0;
                    count += array[0][height - 1]; // Itself.
                    count += array[0][height - 2];
                    count += array[width - 2][height - 2];
                    count += array[width - 2][height - 1];
                    
                    cout << "Top Right" << " : " << count << "\n";
                }
                if (i == width - 1 && j == height - 1)
                {
                    int count = 0;
                    count += array[width - 1][height - 1]; // Itself.
                    count += array[width - 2][height - 1];
                    count += array[width - 2][height - 2];
                    count += array[width - 1][height - 2];
                    
                    cout << "Bottom Right" << " : " << count << "\n";
                }
            }

            // Edge cases where the neighbor size is 5.

            if ((i == 0 && j >= 1 || j < height - 1) || (i >= 1 || i < width - 1 && j == 0)
                || (i >= 1 || i < width - 1 && j == height - 2) || (i == width -2 && j >= 1 || j < height - 1))
            {
                if (i == 0 && j >= 1 && j < height - 1)
                {
                    int count = 0;
                    int itself = array[i][j];
                    count += array[i][j - 1] + array[i + 1][j - 1] + array[i + 1][j] + array[i + 1][j + 1]
                        + array[i][j + 1] + itself;
                    
                    cout << "Top Edge : " << count << "\n";
                }

                if (i >= 1 && i < width - 1 && j == 0)
                {
                    int count = 0;
                    int itself = array[i][j];
                    count += array[i - 1][j] + array[i - 1][j + 1] + array[i][j + 1] + array[i + 1][j + 1]
                        + array[i + 1][j] + itself;

                    cout << "Left Edge : " << count << "\n";
                }

                if (i >= 1 && i < width - 1 && j == height - 1)
                {
                    int count = 0;
                    int itself = array[i][j];
                    count += array[i - 1][j] + array[i - 1][j - 1] + array[i][j - 1] + array[i + 1][j - 1]
                        + array[i + 1][j] + itself;
                    
                    cout << "Right Edge : " << count << "\n";
                }

                if (i == width - 1 && j >= 1 && j < height - 1)
                {
                    int count = 0;
                    int itself = array[i][j];
                    count += array[i][j - 1] + array[i - 1][j - 1] + array[i - 1][j] + array[i - 1][j + 1]
                        + array[i][j + 1] + array[i][j];

                    cout << "Bottom Edge : " << count << "\n";
                }
            }


            // Normal cases when neighbors are 8.

            if (i >= 1 && i < width - 1 && j >= 1 && j < height - 1)
            {
                int count = 0;
                int itself = array[i][j];
                count +=  array[i - 1][j - 1] + array[i - 1][j] + array[i - 1][j + 1] + array[i][j + 1]
                    + array[i + 1][j + 1] + array[i + 1][j] + array[i + 1][j - 1] + array[i][j - 1] + itself;
                
                cout << "Middle : " << count << "\n";
            }
        }
    }
}

/// <summary>
/// Works like a fancy mask for the 0 and 1 states.
/// 1. It takes into account the 0 and 1 states and prints them fancy.
/// 2. I was thinking to replace the int with char to pretty print but it didn't quite worked out.
///    So, instead I am not overwriting the int with char, I am making new char 2D array to achieve the same.
/// 3. Using setw() manipulator to make the rendering look more compact, precise and cool.

/// Use render function in the end as it is just taking the array we are working on currently and not overwriting it.
/// So, when we have final 0 and 1 states only then use it.

/// </summary>
/// <param name="array"></param>
/// <param name="width"></param>
/// <param name="height"></param>
void Render(int** array, int width, int height)
{
    cout << "\n";
    for (int i = 0; i < width; ++i)
    {
        for (int j = 0; j < height; ++j)
        {
            if (array[i][j] == 1)
            {
                cout << "#";
                cout << setw(2);
            }
            if (array[i][j] == 0)
            {
                cout << " ";
                cout << setw(2);
            }
        }
        cout << "\n";
    }
}


// Function to print the 2D array to the console.
void PrintStuff(int** array, int width, int height)
{
    for (int i = 0; i < width; ++i)
    {
        cout << "\n" << "[ ";
        for (int j = 0; j < height; ++j)
        {
            cout << array[i][j] << " ";
        }
        cout << "]";
    }
}

int main()
{
    system("color 0a");
    // Dimensions for the 2D array.
    int width, height;
    cout << "width = ";
    cin >> width;
    cout << "\n";
    cout << "height = ";
    cin >> height;

    cout << "\n";

    // Creating and Initializing the 2D array with dimensions widht and height.
    int** array = new int*[width];
    for (int i = 0; i < width; ++i)
        array[i] = new int[height];
    
    RandomizeStates(array, width, height);

    Render(array, width, height);

    NextState(array, width, height);

    delete[] array;
    
    return 0;
}
