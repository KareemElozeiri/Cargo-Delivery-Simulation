#include "customs.h"

/// <summary>
/// used to split the string word into array of strings on certain seperator char.
/// </summary>
/// <returns>array of strings</returns>
string* split(string str, char ch)
{
    string* strings = new string[MAX];
    int current = 0, i = 0;
    int iStart = 0, iEnd = 0;
    while (i <= str.length())
    {
        if (str[i] == ch || i == str.length())
        {
            iEnd = i;
            string subStr = "";
            subStr.append(str, iStart, iEnd - iStart);
            strings[current] = subStr;
            current++;
            iStart = iEnd + 1;
        }
        i++;
    }
    return strings;
}

/// <summary>
/// converts into array of ints
/// </summary>
int* splitInt(string str, int len)
{
    int* intTime = new int[MAX];
    string* strTime = new string[MAX];
    strTime = split(str, ':');
    for (int i=0; i < len; i++) {
        intTime[i] = stoi(strTime[i]);
    }
    return intTime;
}

/// <summary>
/// used to split the string time into our std Time class
/// ex: "5:22" --> Time(5,22)
/// </summary>
/// <returns> Time* </returns>
Time* splitTime(string str)
{
    int* intTime = splitInt(str,2);
    Time* time = new Time(intTime[0],intTime[1]);
    return time;

}