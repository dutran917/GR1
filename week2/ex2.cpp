#include <iostream>
#include <string>
#include <cstdlib>
#include <ctime>
#include <vector>
#include <assert.h>
#include <bits/stdc++.h>
#include <fstream>
#define SIZE_OF_ARRAY(array) (sizeof(array) / sizeof(array[0]))
using namespace std;

class PersonFlow
{                   // The class
public:             // Access specifier
    string from[3]; // Attribute
    string to[3];   // Attribute
    int begin;
    int end;
    float impatience = (float)(rand() % 10) / 10;
    PersonFlow(string x, string y, int a, int b)
    { // Constructor with parameters
        from[0] = x;
        to[0] = y;
        begin = a;
        end = b;
    }
    PersonFlow(string x, string y, string x1, string y1, string x2, string y2, int a, int b)
    { // Constructor with parameters
        from[0] = x;
        to[0] = y;
        from[1] = x1;
        to[1] = y1;
        from[2] = x2;
        to[2] = y2;
        begin = a;
        end = b;
    }
};
int random(int minN, int maxN)
{
    return minN + rand() % (maxN + 1 - minN);
}
void reInitArr(float src[], float out[], int n)
{
    for (int i = 0; i < n; i++)
    {
        out[i] += src[i];
    }
}
float *randAlpha(int inc)
{
    static float alpha[7];
    alpha[0] = rand() % 10;
    if (inc == 1)
    {
        for (int i = 1; i < 7; i++)
        {
            alpha[i] = alpha[i - 1] + (float)(rand() % 10) / 10;
        }
    }
    else if (inc == -1)
    {
        for (int i = 1; i < 7; i++)
        {
            alpha[i] = alpha[i - 1] - (float)(rand() % 100) / 10;
        }
    }
    else
    {
        float x = rand() % 100;
        for (int i = 0; i < 7; i++)
        {
            alpha[i] = x;
        }
    }
    return alpha;
}
// function to generate and retrun random numbers.
int *turkeyWFunc(int i, float alpha, int duration)
{

    static int r[2];
    // set the seed
    if ((alpha <= 0 || alpha >= 1) || (duration % 3600 != 0 || duration % 600 != 0) || (i < 0 || i > 6))
    {
        return r;
    }
    switch (i)
    {
    case 0:
    {
        r[0] = 0;
        r[1] = 3600 + random(0, 600);
        break;
    }
    case 1:
    {
        r[0] = 7200;
        r[1] = 10800 + random(0, 600);
        break;
    }
    case 2:
    {
        r[0] = 14400;
        r[1] = 18000 + random(0, 600);
        break;
    }
    case 3:
    {
        r[0] = 21600;
        r[1] = 25200 + random(0, 600);
        break;
    }
    case 4:
    {
        r[0] = 28800;
        r[1] = 32400 + random(0, 600);
        break;
    }
    case 5:
    {
        r[0] = 36000;
        r[1] = 39600 + random(0, 600);
        break;
    }
    case 6:
    {
        r[0] = 43200;
        r[1] = 46800 + random(0, 600);
        break;
    }
    default:
        break;
    }
    return r;
}

int chanle(int k)
{
    if (k % 2 == 0)
    {
        return 1;
    }
    return 0;
}

vector<vector<int>> generateWholeDay(int inc, int N, string center, string direction)
{
    int arr[7][2 * N];
    float alpha[7];
    int duration = 3600;
    if (inc != INT_MAX)
    {
        float *temp = randAlpha(inc);
        for (int i = 0; i < 7; i++)
        {
            alpha[i] = *(temp + i);
        }
    }
    else
    {
        float temp[7] = {0.75, 0.4, 0.5, 0.3, 0.75, 0.4, 0.6};
        for (int i = 0; i < 7; i++)
        {
            alpha[i] = temp[i];
        }
        if (center == "Gastro" && direction == "West")
        {
            float adjust[7] = {0, 0.6, 0, 0.6, 0, 0.6, 0};
            reInitArr(adjust, alpha, 7);
        }
        else if (center == "Gastro" && direction == "East")
        {
            float adjust[7] = {0.1, 0, 0.2, 0, 0.1, 0, 0.2};
            reInitArr(adjust, alpha, 7);
        }
        else if (center == "Gastro" && direction == "North")
        {
            float adjust[7] = {0, 0.6, 0, 0.6, 0, 0.6, 0};
            reInitArr(adjust, alpha, 7);
        }
        else if (center == "Gastro" && direction == "South")
        {
            float adjust[7] = {0.2, 0.6, 0, 0.6, 0.2, 0.6, 0};
            reInitArr(adjust, alpha, 7);
        }
        else if (center == "Neuro" && direction == "West")
        {
            float adjust[7] = {0.1, 0, 0.2, 0, 0.1, 0, 0.2};
            reInitArr(adjust, alpha, 7);
        }
        else if (center == "Neuro" && direction == "East")
        {
            float adjust[7] = {0, 0.6, 0, 0.6, 0, 0.6, 0};
            reInitArr(adjust, alpha, 7);
        }
        else if (center == "Neuro" && direction == "North")
        {
            float adjust[7] = {0, 0.6, 0, 0.6, 0, 0.6, 0};
            reInitArr(adjust, alpha, 7);
        }
        else if (center == "Neuro" && direction == "South")
        {
            float adjust[7] = {0.2, 0.6, 0, 0.6, 0.2, 0.6, 0};
            reInitArr(adjust, alpha, 7);
        }
        else if (center == "Supply" && direction == "West")
        {
            float adjust[7] = {0.2, 0.55, 0.45, 0.65, 0.2, 0.55, 0.35};
            reInitArr(adjust, alpha, 7);
        }
        else if (center == "Supply" && direction == "East")
        {
            float adjust[7] = {0.2, 0, 0.45, 0.65, 0.2, 0.55, 0.35};
            reInitArr(adjust, alpha, 7);
        }
        else if (center == "Supply" && direction == "North")
        {
            float adjust[7] = {0.2, 0.55, 0.45, 0.65, 0.2, 0.55, 0.35};
            reInitArr(adjust, alpha, 7);
        }
        else if (center == "Supply" && direction == "South")
        {
            float adjust[7] = {0.2, 0.55, 0.45, 0.65, 0.2, 0.55, 0.35};
            reInitArr(adjust, alpha, 7);
        }
        else if (center == "Disposal" && direction == "West")
        {
            float adjust[7] = {0.2, 0, 0.45, 0.65, 0.2, 0.55, 0.35};
            reInitArr(adjust, alpha, 7);
        }
        else if (center == "Disposal" && direction == "East")
        {
            float adjust[7] = {0.2, 0.55, 0.45, 0.65, 0.2, 0.55, 0.35};
            reInitArr(adjust, alpha, 7);
        }
        else if (center == "Disposal" && direction == "North")
        {
            float adjust[7] = {0.2, 0.55, 0.45, 0.65, 0.2, 0.55, 0.35};
            reInitArr(adjust, alpha, 7);
        }
        else if (center == "Disposal" && direction == "South")
        {
            float adjust[7] = {0.2, 0.55, 0.45, 0.65, 0.2, 0.55, 0.35};
            reInitArr(adjust, alpha, 7);
        }
        else if (center == "Emergency" && direction == "West")
        {
            float adjust[7] = {0.2, 0, 0, 0, 0.2, 0, 0};
            reInitArr(adjust, alpha, 7);
        }
        else if (center == "Emergency" && direction == "East")
        {
            float adjust[7] = {0.23, 0.3, 0, 0.3, 0.2, 0, 0};
            reInitArr(adjust, alpha, 7);
        }
        else if (center == "Emergency" && direction == "North")
        {
            float adjust[7] = {0.23, 0.05, 0, -0.05, 0.2, -0.05, 0};
            reInitArr(adjust, alpha, 7);
        }
        else if (center == "Emergency" && direction == "South")
        {
            float adjust[7] = {0.23, 0.05, 0, -0.05, 0.2, -0.05, 0};
            reInitArr(adjust, alpha, 7);
        }
        else if (center == "Mobility" && direction == "West")
        {
            float adjust[7] = {-0.05, 0, -0.2, 0, -0.05, 0, -0.1};
            reInitArr(adjust, alpha, 7);
        }
        else if (center == "Mobility" && direction == "East")
        {
            float adjust[7] = {-0.05, 0, -0.2, 0, -0.05, 0, -0.1};
            reInitArr(adjust, alpha, 7);
        }
        else if (center == "Mobility" && direction == "North")
        {
            float adjust[7] = {-0.05, 0, -0.2, 0, -0.2, 0, -0.1};
            reInitArr(adjust, alpha, 7);
        }
        else if (center == "Mobility" && direction == "South")
        {
            float adjust[7] = {-0.05, 0, -0.2, -0.2, -0.2, -0.1, -0.1};
            reInitArr(adjust, alpha, 7);
        }
        else if (center == "Woman" && direction == "West")
        {
            float adjust[7] = {-0.25, -0.2, -0.2, -0.2, -0.25, -0.2, -0.2};
            reInitArr(adjust, alpha, 7);
        }
        else if (center == "Woman" && direction == "East")
        {
            float adjust[7] = {-0.25, -0.2, -0.2, -0.2, -0.25, -0.2, -0.2};
            reInitArr(adjust, alpha, 7);
        }
        else if (center == "Woman" && direction == "North")
        {
            float adjust[7] = {-0.25, -0.2, -0.2, -0.2, -0.25, -0.2, -0.2};
            reInitArr(adjust, alpha, 7);
        }
        else if (center == "Woman" && direction == "South")
        {
            float adjust[7] = {-0.25, -0.2, -0.2, -0.2, -0.25, -0.2, -0.2};
            reInitArr(adjust, alpha, 7);
        }
        else if (center == "Brain" && direction == "West")
        {
            float adjust[7] = {-0.05, -0.1, -0.1, -0.1, 0, 0, -0.1};
            reInitArr(adjust, alpha, 7);
        }
        else if (center == "Brain" && direction == "East")
        {
            float adjust[7] = {-0.15, 0.2, -0.1, 0.2, -0.25, 0.2, 0.2};
            reInitArr(adjust, alpha, 7);
        }
        else if (center == "Brain" && direction == "North")
        {
            float adjust[7] = {-0.15, 0.2, -0.1, 0.2, 0.15, 0.2, 0.2};
            reInitArr(adjust, alpha, 7);
        }
        else if (center == "Brain" && direction == "South")
        {
            float adjust[7] = {-0.25, 0.2, -0.1, 0.2, -0.25, 0.2, 0.2};
            reInitArr(adjust, alpha, 7);
        }
        else if (center == "Admin" || center == "Knowledge" || center == "Lab")
        {
            duration = 15 * 3600;
            for (int i = 0; i < 7; i++)
            {
                alpha[i] = 0.29;
            }
        }
        else
        {
            vector<vector<int>> empty(2 * N, vector<int>(7, 0));
            return empty;
        }
    }
    for (int i = 0; i < 7; i++)
    {
        int *turkey_ = turkeyWFunc(i, alpha[i], duration);
        float deltaT = (float)alpha[i] * (duration - 1) / (2 * N);
        arr[i][0] = *(turkey_ + 0);
        arr[i][1] = *(turkey_ + 1);
        for (int k = 2; k < 2 * N; k++)
        {
            if (chanle(k))
            {
                arr[i][k] = arr[i][0] + k * ceil(deltaT);
            }
            else
            {
                arr[i][k] = arr[i][1] - k * ceil(deltaT);
            }
        }
    }
    vector<vector<int>> data(7, vector<int>(2 * N, 0));
    for (int i = 0; i < 7; i++)
    {
        for (int j = 0; j < 2 * N; j++)
        {
            data[i][j] = arr[i][j];
        }
    }
    return data;
}

vector<string> locate()
{
    string centerArr[] = {"Gastro",
                          "Neuro",
                          "Brain",
                          "Supply",
                          "Disposal",
                          "Admin",
                          "Knowledge",
                          "Lab",
                          "Emergency", "Mobility"};
    string directionArr[] = {"West", "East", "North", "South"};
    string center = centerArr[rand() % 10];
    string direction = directionArr[rand() % 4];
    string index = to_string((rand() % 100) + 1);
    string from = "E" + index;
    string to = "-E" + index;
    int temp = rand() % 10 + 1;
    string N = to_string(temp);
    if (direction == "North" || direction == "South")
    {
        string index1 = to_string((rand() % 100) + 1);
        string from1 = "E" + index1;
        string to1 = "-E" + index1;
        string index2 = to_string((rand() % 100) + 1);
        string from2 = "E" + index2;
        string to2 = "-E" + index2;

        while (index1 == index || index1 == index2)
        {
            index1 = to_string((rand() % 100) + 1);
            from1 = "E" + index1;
            to1 = "-E" + index1;
        }
        while (index2 == index)
        {
            index2 = to_string((rand() % 100) + 1);
            from2 = "E" + index2;
            to2 = "-E" + index2;
        }
        vector<string> locate{
            center,
            direction,
            from,
            to,
            from1,
            to1,
            from2,
            to2,
            N};
        assert(temp * (locate.size() - 3) < 1000);
        return locate;
    }
    else
    {
        vector<string> locate{
            center,
            direction,
            from,
            to,
            N};
        assert(temp * (locate.size() - 3) < 1000);
        return locate;
    }
}

void OutVector(vector<std::vector<int>> arr)
{
    int rows = arr.size();
    int columns = arr.at(0).size();
    for (int i = 0; i < rows; i++)
    {
        for (int j = 0; j < columns; j++)
        {
            cout << setw(7) << arr[i][j];
        }
        cout << endl;
    }
}

int main()
{

    // a pointer to an int.
    int *p;
    cout << "dMMMMMMMMM" << endl;
    srand(time(NULL));
    p = turkeyWFunc(1, 0.6, 7200);
    PersonFlow test("E10", "-E10", 1, 2144345);
    ofstream ofs("output.txt");

    if (!ofs)
    {
        cerr << "Error: file not opened." << endl;
        return 1;
    }
    char x = 34;
    vector<PersonFlow> persons;
    // vector<string> lc;
    // vector<vector<int>> generate;
    // OutVector(generate);
    for (int i = 0; i < 20; i++)
    {
        vector<string> lc = locate();
        int N = stoi(lc.back());
        vector<vector<int>> generate = generateWholeDay(INT_MAX, N, lc[0], lc[1]);
        OutVector(generate);
        int N1 = lc.size();
        int N2 = generate.size();
        if (lc.size() == 5)
        {
            for (int j = 0; j < 7; j++)
            {
                PersonFlow p(lc[2], lc[3], generate[j][0], generate[j][1]);
                persons.push_back(p);
            }
        }
        else
        {
            for (int j = 0; j < 7; j++)
            {
                PersonFlow p(lc[2], lc[3], lc[4], lc[5], lc[6], lc[7], generate[j][0], generate[j][1]);
                persons.push_back(p);
            }
        }
        int P = persons.size();
        // assert(P <= N1 * N2 * 7 && P >= N1 * N2);
    }

    for (int i = 0; i < persons.size(); i++)
    {
        ofs << "<personFlow begin=" << x << persons[i].begin << x << " id=" << x << i << x << " impatience=" << x << persons[i].impatience << x << " end=" << x << persons[i].end << x << " period=" << x << 1 << x << ">\n";
        for (int j = 0; j < SIZE_OF_ARRAY(persons[i].from); j++)
        {
            if (persons[i].from[j].length() > 0)
            {
                ofs << "\t<walk from=" << x << persons[i].from[j] << x << " to=" << x << persons[i].to[j] << x << "/>\n";
            }
        }
        ofs << "</personFlow>\n";
    }

    // for (int i = 0; i < persons.size(); i++)
    // {
    //     ofs << "dmm: " << persons[i].begin << "loz: " << persons[i].end << endl;
    // }
    ofs.close();
    return 0;
}