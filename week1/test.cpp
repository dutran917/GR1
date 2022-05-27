#include <iostream>
#include <fstream>
#include <vector>
#include <math.h>
#include <list>
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
    int from[3];
    double lastLength;
    GLane(Zone **_zone, double _length, int _number, string _strId, int _from[3], double _lastlength)
    {
        zones = _zone;
        length = _length;
        number = _number;
        strId = _strId;
        for (int i = 0; i < 3; i++)
        {
            from[i] = _from[i];
        }
        lastLength = _lastlength;
    }
};

class Junction
{
public:
    GLane *allLanes[16];
    Junction(GLane *_allLanes[16])
    {
        for (int i = 0; i < 16; i++)
        {
            allLanes[i] = _allLanes[i];
        }
    }
};

// class Searching
// {
// public:
//     list<string> findPaths(GLane **allLanes, int NA, Junction **allJuncs, int NJ, sstring src, string dst)
//     {
//         list<string> path;
//         int check1 = 0;
//         int check2 = 0;
//         for (int i = 0; i < NA; i++)
//         {
//             if (!allLanes[i]->strId.compare(src))
//             {
//                 check1 = 1;
//             }
//             if (!allLanes[i]->strId.compare(dst))
//             {
//                 check2 = 1;
//             }
//         }
//         if (check1 && check2)
//         {
//         }
//     }

// }

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
    else
    {
        index = line.substr(1, to);
        return stoi(index) * 2;
    }
    return stoi(index);
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
    return temp[0];
}
double getLastLengthAllLanes(string line)
{
    double temp = getLengthLanes(line);
    return abs(temp - 1.1 * getNumberLanes(line));
}

int *getFromArrAllLanes(string line, int max)
{
    vector<string> temp = split(line, " ");
    static int from[3];
    if (temp.size() > 2)
    {
        vector<string> temp1 = split(temp[2], "_");
        string juncId = temp1[0].substr(2);
        int j_id = stoi(juncId);

        string junc1 = temp1[1];
        int j_id1 = stoi(junc1);
        if (temp.size() == 3)
        {
            from[0] = (max + j_id) | (j_id1 << 16);
            from[1] = -1;
            from[2] = -1;
        }
        else if (temp.size() == 4)
        {
            string junc2 = split(temp[3], "_")[1];
            int j_id2 = stoi(junc2);
            from[0] = (max + j_id) | (j_id1 << 16);
            from[1] = (max + j_id) | (j_id2 << 16);
            from[2] = -1;
        }
        else
        {
            string junc2 = split(temp[3], "_")[1];
            int j_id2 = stoi(junc2);
            string junc3 = split(temp[4], "_")[1];
            int j_id3 = stoi(junc3);
            from[0] = (max + j_id) | (j_id1 << 16);
            from[1] = (max + j_id) | (j_id2 << 16);
            from[2] = (max + j_id) | (j_id3 << 16);
        }
    }
    else
    {
        from[0] = -1;
        from[1] = -1;
        from[2] = -1;
    }

    return from;
}

vector<string> findJunc(string line, vector<string> allInfo)
{
    vector<string> temp = split(line, " ");
    vector<string> juncs;
    for (int i = 2; i < temp.size(); i++)
    {
        for (string &x : allInfo)
        {
            if (!split(x, " ")[0].compare(temp[i]))
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
    vector<string> temp = split(line, " ");
    vector<string> temp1 = split(temp[2], "_");
    string juncId = temp1[0].substr(2);
    return stoi(juncId);
}

// GLane **getGLaneInJunc(string line, vector<string> allInfo, int max)
// {
//     GLane *all[16];
//     vector<string> juncs_ = findJunc(line, allInfo);
//     for (string &x : juncs_)
//     {
//         Zone **zone;
//         vector<string> test = split(x, " ");
//         if (test.size() > 2)
//         {
//             int index = stoi(split(x, "_")[1]);
//             double length = stod(split(x, " ")[1]);
//             int number = ceil(length / 1.1);
//             string strId = x.substr(0, split(x, " ")[0].rfind("_"));
//             int from[3] = {-1, -1, -1};
//             double lastLength = abs(length - 1.1 * number);
//             if (x.find("E") != string::npos)
//             {
//                 string tmp = split(x, " ")[2];
//                 if (tmp[0] == '-')
//                 {
//                     from[0] = stoi(tmp.substr(2, tmp.find("_"))) * 2;
//                 }
//                 else
//                 {
//                     from[0] = stoi(tmp.substr(1, tmp.find("_"))) * 2;
//                 }
//             }
//             else
//             {
//                 string tmp = split(x, " ")[2];
//                 int j_index = stoi(tmp.substr(2, tmp.find("_") - 2));
//                 int j_ = stoi(split(tmp, "_")[1]);
//                 from[1] = (max + j_index) | (j_ << 16);
//             }

//             all[index] = new GLane(zone, length, number, strId, from, lastLength);
//         }
//     }
//     return all;
// }

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
    ifstream input_file(filename);

    if (!input_file.is_open())
    {
        cerr << "Could not open the file - '"
             << filename << "'" << endl;
        return EXIT_FAILURE;
    }

    while (getline(input_file, line))
    {
        allInfo.push_back(line);
        if (line[0] != ':' && (line[0] == 'E' || line[0] == '-'))
        {

            lanes.push_back(line);
        }
        else
        {
            juncs.push_back(line);
        }
    }

    max = getMaxLanes(lanes);
    j_max = getMaxJunc(juncs);
    // Phan d

    GLane *allLanes[2 * max];
    Junction *allJuncs[j_max];
    for (string &x : lanes)
    {

        Zone **zone;
        int from[3];
        int *p = getFromArrAllLanes(x, max);
        for (int i = 0; i < 3; i++)
        {
            from[i] = *(p + i);
        }
        allLanes[getIndexLanes(x)] = new GLane(zone, getLengthLanes(x), getNumberLanes(x), getStrIdAllLanes(x), from, getLastLengthAllLanes(x));
    }

    for (string &x : lanes)
    {
        vector<string> juncs_ = findJunc(x, allInfo);
        GLane *test_gl[16];
        int index_junc;
        if (juncs_.size() != 0)
        {
            index_junc = getIndexJunc(x);
            for (string &jc : juncs_)
            {
                Zone **zone;
                int index = stoi(split(jc, "_")[1]);
                double length = stod(split(jc, " ")[1]);
                int number = ceil(length / 1.1);
                string strId = jc.substr(0, split(jc, " ")[0].rfind("_"));
                int from[3] = {-1, -1, -1};
                double lastLength = abs(length - 1.1 * number);
                if (jc.find("E") != string::npos)
                {
                    string tmp = split(jc, " ")[2];
                    if (tmp[0] == '-')
                    {
                        from[0] = stoi(tmp.substr(2, tmp.find("_"))) * 2;
                    }
                    else
                    {
                        from[0] = stoi(tmp.substr(1, tmp.find("_"))) * 2;
                    }
                }
                else
                {
                    string tmp = split(jc, " ")[2];
                    int j_index = stoi(tmp.substr(2, tmp.find("_") - 2));
                    int j_ = stoi(split(tmp, "_")[1]);
                    from[1] = (max + j_index) | (j_ << 16);
                }

                test_gl[index] = new GLane(zone, length, number, strId, from, lastLength);
            }
        }
        allJuncs[index_junc] = new Junction(test_gl);
    }

    return 0;
}
