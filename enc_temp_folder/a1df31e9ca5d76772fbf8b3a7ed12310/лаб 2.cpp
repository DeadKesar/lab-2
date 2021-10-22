
#include <iostream>
#include <string>


using namespace std;

string GetText();

int main()
{            
    string testText = "aa sds ss sssss a a a a a a a a a 6789876";
    
   // getline(cin, testText);
    
    string longestWord;
    if (testText.length() > 0)
    {
        longestWord = testText.substr(0, 1);
    }
    else
    {
        //определить поведения при пустом вводе.
    }
    int maxLength = 1;
    for (int i = 0; i < testText.length()-1; i++)
    {
        for (int j = 2; j < testText.length()-i; j++)
        {
            if (testText[i+j-1] == ' ')
            {
                i += j - 1;
                break;
            }
            string sub = testText.substr(i, j);
            string reSub = sub;
            reverse(reSub.begin(), reSub.end());
            if (sub == reSub && sub.length() > maxLength)
            {
                longestWord = sub;
                maxLength = sub.length();
            }
        }
    }
    cout << longestWord << "    " << maxLength << endl;
    return 0;
}

string GetText()
{
    string text;
    getline(cin, text);
    return "";
}



