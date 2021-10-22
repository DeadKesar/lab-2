
#include <iostream>
#include <string>


using namespace std;

string GetText();
string FindLongestWord(string text);

int main()
{            
    string testText = "aa sds ss sssss a a a a a a a a a 6789876";
    
   // getline(cin, testText);
    
    string answer = FindLongestWord(testText);
    cout << answer << endl;
    return 0;
}

string FindLongestWord(string text)
{
    string longestWord;
    if (text.length() > 0)
    {
        longestWord = text.substr(0, 1);
    }
    else
    {
        //определить поведения при пустом вводе.
    }
    int maxLength = 1;
    for (int i = 0; i < text.length() - 1; i++)
    {
        for (int j = 1; j < text.length() - i; j++)
        {
            if (text[i + j - 1] == ' ' || text[i + j - 1] == '.' || text[i + j - 1] == '!', text[i + j - 1] == '?')
                //  поиск среди осмысленных слов. Мы пологаем что слова отделены друг от друга разделителями.
            {
                i += j - 1;
                break;
            }
            string sub = text.substr(i, j);
            string reSub = sub;
            reverse(reSub.begin(), reSub.end());
            if (sub == reSub && sub.length() > maxLength)
            {
                longestWord = sub;
                maxLength = sub.length();
            }
        }
    }
    return longestWord;
}

string GetText()
{
    string text;
    getline(cin, text);
    return "";
}



