
#include <iostream>
#include <string>


using namespace std;

string GetText();
string FindLongestWord(string text, bool isMeaningful);

int main()
{            
    setlocale(LC_ALL, "Russian");
    string testText = "ss sssss 6789876";
    bool isMeaningful = false;
    while (true)
    {
        cout << "учитывать ли разделители в тексте?" << endl << "y/n" << endl;
        char answer = getchar();
        switch (answer)
        {
        case('y'):
            isMeaningful = true;
            break;
        case('n'):
            isMeaningful = false;
            break;
        default:
            cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
            continue;
        }
        break;
    }
    
    string answer = FindLongestWord(testText, isMeaningful);
    cout << answer << endl;
    return 0;
}

string FindLongestWord(string text, bool isMeaningful)
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
            if (isMeaningful && (text[i + j - 1] == ' ' || text[i + j - 1] == '.' || text[i + j - 1] == '!'|| text[i + j - 1] == '?'||
                text[i + j - 1] == ';'|| text[i + j - 1] == ':'|| text[i + j - 1] == '"'))
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



