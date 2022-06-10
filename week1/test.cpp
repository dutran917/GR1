#include <iostream>
#include <fstream>
#include <vector>
#include <math.h>
#include <unordered_map>
#include <vector>
#include <iterator>
using namespace std;

class Zone
{
public:
    double _forcast = 0;
    // Zone(double a)
    // {
    //     _forcast = a;
    // }
};

class GLane
{
public:
    Zone **zones;
    double length;
    int number;
    string strId;
    int from[3] = {-1, -1, -1};
    double lastLength;
    // GLane(Zone **_zone, double _length, int _number, string _strId, int *_from, double _lastlength)
    // {
    //     zones = _zone;
    //     length = _length;
    //     number = _number;
    //     strId = _strId;
    //     for (int i = 0; i < 3; i++)
    //     {
    //         from[i] = *(_from + i);
    //     }
    //     lastLength = _lastlength;
    // }
};

class Junction
{
public:
    GLane **allLanes = new GLane *[16];
    // Junction(GLane **_allLanes)
    // {
    //     allLanes = _allLanes;
    // }
};

class Searching
{
public:
    void findPaths(GLane **allLanes, int NA, Junction **allJuncs, int NJ, string src, string dst)
    {
        int dem1 = 0;
        int dem2 = 0;
        vector<string> list;
        vector<string> list2;
        vector<string> empty;
        unordered_map<string, int> hashMap2;
        unordered_map<string, int> hashMap3;
        unordered_map<string, int> hashMap;
        int check = 531;
        int max = check + NJ;
        for (int i = 0; i < NA; i++)
        {
            if (allLanes[i] != nullptr)
            {
                if (allLanes[i]->strId.compare(src) == 0)
                {
                    dem1++;
                }
                if (allLanes[i]->strId.compare(dst) == 0)
                {
                    dem2++;
                }
            }
        }
        if (dem1 > 0 && dem2 > 0)
        {
            for (int i = 0; i < NA; i++)
            {
                if (allLanes[i] != nullptr)
                {
                    if (allLanes[i]->strId.compare(src) == 0)
                    {

                        for (int k = 0; k < 3; k++)
                        {
                            if (allLanes[i]->from[k] > check)
                            {

                                int x = allLanes[i]->from[k] >> 16;
                                int y = allLanes[i]->from[k] - (x << 16) - check;

                                if (allJuncs[y]->allLanes[x] != NULL)
                                {

                                    list.push_back(allJuncs[y]->allLanes[x]->strId);
                                    hashMap.insert({allLanes[i]->strId + allJuncs[y]->allLanes[x]->strId, 1});
                                    hashMap2.insert({list[list.size() - 1], x});
                                    hashMap3.insert({list[list.size() - 1], y});
                                }
                            }
                            else if (allLanes[i]->from[k] != -1)
                            {

                                if (allLanes[i]->from[k] % 2 == 1)
                                {
                                    list.push_back("-E" + to_string(allLanes[i]->from[k] / 2));
                                    hashMap.insert({allLanes[i]->strId + "-E" + to_string(allLanes[i]->from[k] / 2), 1});
                                    hashMap3.insert({list[list.size() - 1], allLanes[i]->from[k]});
                                }
                                else
                                {
                                    list.push_back("E" + to_string(allLanes[i]->from[k] / 2));
                                    hashMap.insert({allLanes[i]->strId + "E" + to_string(allLanes[i]->from[k] / 2), 1});
                                    hashMap3.insert({list[list.size() - 1], allLanes[i]->from[k]});
                                }
                            }
                        }
                        cout << "OK" << endl;
                        while (list[0] != dst)
                        {
                            list2.push_back(list[0]);
                            list.erase(list.begin() + 0);
                            int index = list2.size() - 1;
                            if (list2[index][0] == '-' || list2[index][0] == 'E')
                            {
                                for (int k = 0; k < 3; k++)
                                {
                                    int index1 = hashMap3[list2[index]];
                                    if (allLanes[index1] != nullptr)
                                    {
                                        if (allLanes[index1]->from[k] > check)
                                        {
                                            int x = allLanes[index1]->from[k] >> 16;
                                            int y = allLanes[index1]->from[k] - (x << 16) - check;
                                            if (allJuncs[y]->allLanes[x] != nullptr)
                                            {
                                                list.push_back(allJuncs[y]->allLanes[x]->strId);
                                                hashMap.insert({list2[index] + allJuncs[y]->allLanes[x]->strId, 1});
                                                hashMap2.insert({list[list.size() - 1], x});
                                                hashMap3.insert({list[list.size() - 1], y});
                                            }
                                        }
                                        else if (allLanes[index1]->from[k] != -1)
                                        {
                                            if (allLanes[index1]->from[k] % 2 == 1)
                                            {
                                                list.push_back("-E" + to_string(allLanes[index1]->from[k] / 2));
                                                hashMap.insert({list2[index] + "-E" + to_string(allLanes[index1]->from[k] / 2), 1});
                                                hashMap3.insert({list[list.size() - 1], allLanes[index1]->from[k]});
                                                if (list[0] == dst)
                                                {

                                                    break;
                                                }
                                            }
                                            else
                                            {
                                                list.push_back("E" + to_string(allLanes[index1]->from[k] / 2));
                                                hashMap.insert({list2[index] + "-E" + to_string(allLanes[index1]->from[k] / 2), 1});
                                                hashMap3.insert({list[list.size() - 1], allLanes[index1]->from[k]});
                                                if (list[0] == dst)
                                                {

                                                    break;
                                                }
                                            }
                                        }
                                    }
                                }
                            }
                            else
                            {

                                for (int k = 0; k < 3; k++)
                                {
                                    int index1 = hashMap3[list2[index]];
                                    int index2 = hashMap2[list2[index]];
                                    if (allJuncs[index1]->allLanes[index2]->from[k] > check * 2)
                                    {
                                        int x = allJuncs[index1]->allLanes[index2]->from[k] >> 16;
                                        int y = allJuncs[index1]->allLanes[index2]->from[k] - (x << 16) - check;
                                        if (allJuncs[y]->allLanes[x] != nullptr)
                                        {
                                            list.push_back(allJuncs[y]->allLanes[x]->strId);
                                            hashMap.insert({list2[index] + allJuncs[y]->allLanes[x]->strId, 1});
                                            hashMap2.insert({list[list.size() - 1], x});
                                            hashMap3.insert({list[list.size() - 1], y});
                                        }
                                    }
                                    else if (allJuncs[index1]->allLanes[index2]->from[k] != -1)
                                    {
                                        if (allJuncs[index1]->allLanes[index2]->from[k] % 2 == 1)
                                        {
                                            list.push_back("-E" + to_string(allJuncs[index1]->allLanes[index2]->from[k] / 2));
                                            hashMap.insert({list2[index] + "-E" + to_string(allJuncs[index1]->allLanes[index2]->from[k] / 2), 1});
                                            hashMap3.insert({list[list.size() - 1], allJuncs[index1]->allLanes[index2]->from[k]});
                                            if (list[0] == dst)
                                            {

                                                break;
                                            }
                                        }
                                        else
                                        {
                                            list.push_back("E" + to_string(allJuncs[index1]->allLanes[index2]->from[k] / 2));
                                            hashMap.insert({list2[index] + "E" + to_string(allJuncs[index1]->allLanes[index2]->from[k] / 2), 1});
                                            hashMap3.insert({list[list.size() - 1], allJuncs[index1]->allLanes[index2]->from[k]});
                                            if (list[0] == dst)
                                            {

                                                break;
                                            }
                                        }
                                    }
                                }
                            }
                            if (list.size() == 0)
                            {
                                cout << "ko tim dc" << endl;
                                // return empty;
                            }
                        }
                        break;
                    }
                }
            }
        }
        else
        {
            cout << "ko tim dc???" << endl;
            // return empty;
        }
        list2.push_back(dst);
        list2.insert(list2.begin() + 0, src);
        int i = list2.size() - 2;
        for (; i > 0; i--)
        {
            if (hashMap[list2[i] + list2[i + 1]] != 1)
            {
                list2.erase(list2.begin() + i);
            }
        }
        for (string &x : list2)
        {
            if (x[0] != ':')
                cout << x << " ";
        }
        // return list2;
    }
};

// function

vector<string>
split(string str, string delimiter)
{
    size_t pos = 0;
    vector<string> result;
    string token;
    while ((pos = str.find(delimiter)) != string::npos)
    {
        token = str.substr(0, pos);
        result.push_back(token);
        str.erase(0, pos + delimiter.length());
    }
    if ((pos = str.find(delimiter)) == string::npos)
    {
        token = str;
        result.push_back(token);
    }
    return result;
}

int getIndexLanes(string line)
{
    size_t to = line.find("_");
    string index;
    if (line[0] == '-')
    {
        index = line.substr(2, to);
        return stoi(index) * 2 + 1;
    }

    index = line.substr(1, to);
    return stoi(index) * 2;
}

int getMaxLanes(vector<string> lanes)
{
    int max = 0;
    for (string &x : lanes)
    {
        string temp = split(split(x, " ")[0], "_")[0];
        int a;
        if (temp[0] == '-')
        {
            a = stoi(temp.substr(2, temp.find("_")));
        }
        else
        {
            a = stoi(temp.substr(1, temp.find("_")));
        }
        if (a > max)
        {
            max = a;
        }
    }
    return max;
}

int getMaxJunc(vector<string> juncs)
{
    int max = 0;
    for (string &x : juncs)
    {
        string temp = split(split(x, " ")[0], "_")[0];
        int a = stoi(temp.substr(2, temp.find("_")));

        if (a > max)
        {
            max = a;
        }
    }
    return max;
}

double getLengthLanes(string line)
{
    vector<string> temp = split(line, " ");
    return stod(temp[1]);
}

int getNumberLanes(string line)
{
    // double temp = getLengthLanes(line);
    vector<string> temp = split(line, " ");
    double x = stod(temp[1]);
    return ceil(x / 1.1);
}

string getStrIdAllLanes(string line)
{
    vector<string> temp = split(line, " ");
    vector<string> temp1 = split(temp[0], "_");
    return temp1[0];
}
double getLastLengthAllLanes(string line)
{
    double temp = getLengthLanes(line);
    return abs(temp - 1.1 * getNumberLanes(line));
}

int fromElement(string from, int max)
{
    if (from.find('E') < from.length())
    {
        if (from[0] == '-')
        {
            vector<string> temp = split(from, "_");
            return stoi(temp[0].substr(2)) * 2 + 1;
        }
        else
        {
            vector<string> temp = split(from, "_");
            return stoi(temp[0].substr(1)) * 2;
        }
    }
    else if (from.find('J') < from.length())
    {
        vector<string> temp = split(from, "_");
        int j1 = stoi(temp[0].substr(2));
        int j2 = stoi(temp[1]);
        return (max + j1) | (j2 << 16);
    }
    return -1;
}

// int *getFromArr(string line, int max)
// {
//     static int arr[3] = {-1, -1, -1};
//     vector<string> temp = split(line, " ");
//     if (temp.size() > 2)
//     {
//         if (temp.size() == 3)
//         {
//             arr[0] = fromElement(temp[2], max);
//             return arr;
//         }
//         else if (temp.size() == 4)
//         {
//             arr[0] = fromElement(temp[2], max);
//             arr[1] = fromElement(temp[3], max);
//             return arr;
//         }
//         else
//         {
//             arr[0] = fromElement(temp[2], max);
//             arr[1] = fromElement(temp[3], max);
//             arr[2] = fromElement(temp[4], max);
//             return arr;
//         }
//     }

//     return arr;
// }

vector<string> findJunc(string line, vector<string> allInfo)
{
    vector<string> temp = split(line, " ");
    vector<string> juncs;
    for (int i = 2; i < temp.size(); i++)
    {
        for (string &x : allInfo)
        {
            if (split(x, " ")[0].compare(temp[i]) == 0)
            {
                juncs.push_back(x);
                // break;
            }
        }
    }
    return juncs;
}

int getIndexJunc(string line)
{
    vector<string> temp = split(line, "_");
    return stoi(temp[0].substr(2));
}

int main()
{
    string filename("input.txt");
    vector<string> lanes;
    vector<string> juncs;
    vector<string> allInfo;
    string line;
    int max = 0;
    int j_max = 0;
    vector<int> findMax;
    vector<int> findJMax;
    cout << "moi ban nhap ten File: (Press Enter to input.txt) ";
    string s;
    if (cin.get() == '\n')
    {
        cout << "OK: input.txt" << endl;
        s = "input.txt";
    }
    else
    {
        cin >> s;
    }
    ifstream input_file(s);

    if (!input_file.is_open())
    {
        cerr << "Could not open the file - '"
             << s << "'" << endl;
        return EXIT_FAILURE;
    }
    cout << "moi ban nhap src: ";
    string src;

    cin >> src;
    cout << "moi ban nhap dst: ";
    string dst;
    cin >> dst;
    while (getline(input_file, line))
    {
        allInfo.push_back(line);
        if (line[0] != ':' && (line[0] == 'E' || line[0] == '-'))
        {
            lanes.push_back(line);
        }
        if (line[0] == ':')
        {
            juncs.push_back(line);
        }
    }

    max = getMaxLanes(lanes);
    j_max = getMaxJunc(juncs);
    // Phan d

    GLane **allLanes = new GLane *[2 * max + 2];
    Junction **allJuncs = new Junction *[j_max + 1];
    for (string &x : lanes)
    {
        Zone **zone;
        int index = getIndexLanes(x);
        int arr[3] = {-1, -1, -1};
        vector<string> temp = split(x, " ");
        if (temp.size() > 2)
        {
            if (temp.size() == 3)
            {
                arr[0] = fromElement(temp[2], max);
            }
            else if (temp.size() == 4)
            {
                arr[0] = fromElement(temp[2], max);
                arr[1] = fromElement(temp[3], max);
            }
            else
            {
                arr[0] = fromElement(temp[2], max);
                arr[1] = fromElement(temp[3], max);
                arr[2] = fromElement(temp[4], max);
            }
        }

        allLanes[index] = new GLane();

        allLanes[index]->zones = zone;
        allLanes[index]->length = getLengthLanes(x);
        allLanes[index]->number = getNumberLanes(x);
        allLanes[index]->strId = getStrIdAllLanes(x);
        allLanes[index]->lastLength = getLastLengthAllLanes(x);
        for (int i = 0; i < 3; i++)
        {
            allLanes[index]->from[i] = arr[i];
        }
        // allLanes[getIndexLanes(x)] = new GLane(zone, getLengthLanes(x), getNumberLanes(x), getStrIdAllLanes(x), getFromArr(x, max), getLastLengthAllLanes(x));
    }
    for (int i = 0; i < 2 * max; i++)
    {
        if (allLanes[i] == NULL)
        {
            allLanes[i] = new GLane();
        }
    }

    for (int i = 0; i < j_max + 1; i++)
    {
        allJuncs[i] = new Junction();

        for (int k = 0; k < 16; k++)
        {
            allJuncs[i]->allLanes[k] = new GLane();
        }
    }

    for (string &x : juncs)
    {
        int index_junc = getIndexJunc(x);
        Zone **zone_;
        int index = stoi(split(x, "_")[1]);
        double length = stod(split(x, " ")[1]);
        int number = ceil(length / 1.1);
        string strId = x.substr(0, split(x, " ")[0].rfind("_"));
        double lastLength = abs(length - 1.1 * number);
        allJuncs[index_junc]->allLanes[index]->zones = zone_;
        allJuncs[index_junc]->allLanes[index]->number = number;
        allJuncs[index_junc]->allLanes[index]->length = length;
        allJuncs[index_junc]->allLanes[index]->strId = strId;
        allJuncs[index_junc]->allLanes[index]->lastLength = lastLength;
        int p[3] = {-1, -1, -1};
        vector<string> temp = split(x, " ");
        if (temp.size() > 2)
        {
            if (temp.size() == 3)
            {
                p[0] = fromElement(temp[2], max);
            }
            else if (temp.size() == 4)
            {
                p[0] = fromElement(temp[2], max);
                p[1] = fromElement(temp[3], max);
            }
            else
            {
                p[0] = fromElement(temp[2], max);
                p[1] = fromElement(temp[3], max);
                p[2] = fromElement(temp[4], max);
            }
        }

        for (int i = 0; i < 3; i++)
        {
            allJuncs[index_junc]->allLanes[index]->from[i] = p[i];
        }
    }

    Searching newSearch;

    newSearch.findPaths(allLanes, max * 2, allJuncs, j_max, src, dst);
    return 0;
}