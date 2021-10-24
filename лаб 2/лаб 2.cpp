
#include <iostream>   //ввод-вывод
#include <string>     //работа со строками

using namespace std;

// выбор функции поиска слова.
char GetYesNo();
// получаем пользовательский текст
string * GetText(int size);
//обрабатываем вектор построчно используя функцию с учётом разделителей
string ArrayProcessing(string* text, int stringsCount);
//обрабатываем вектор построчно используя функцию без учёта разделителей
string ArrayProcessingNoMeaningful(string* text, int stringsCount);
//предпологаем что слово это некая единица отделёная разделителями.
string FindLongestWord(string text);
// функция расматривает любую последовательность символов как слово.
string FindLongestWordNoMeaningful(string text);
// получить числовое значение от пользователя с проверкой ввод, используется для получения количества строк
string GetSubstring(string text, int start, int size);
//разворот строки
string reverseStr(string text);
double GetNumber();


int main()
{     
    //отображение русских символов в консоли
    setlocale(LC_ALL, "Russian");
    string answer;
    cout << "введите количество строк:  ";
    // ограничение для выхода из цикла получения текста.
    int countStrings = GetNumber();
    //запрашиваем текст у пользовотеля.
    string* text = GetText(countStrings);
    //ветвим программу на 2 случая
    switch (GetYesNo())    {
    case('y'):
        //случай с учётом разделителей
        answer = ArrayProcessing(text, countStrings);
        break;
    case('n'):
        //без учёта разделителей
        answer = ArrayProcessingNoMeaningful(text, countStrings);
        break;
    } 
    cout << answer<< "   " << answer.length() << endl;
    delete [] text; //чистим память
    return 0;
}
char GetYesNo()
{
    cout << "учитывать ли разделители в тексте?" << endl << "y/n" << endl;
    while (true)
        //запрашиваем пока не получим коректный ввод от пользователя
    {
        char answer = getchar();
        cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
        if (tolower(answer) == 'y' || tolower(answer) == 'n')
        {
            return tolower(answer);
            //сбрасываем полученное значение в нижний регистр на случай если пользователь введёт 'Y', 'N'
        }
        cout << "something wrong, try again. y/n" << endl;
    }
}

// просто построчно вызываем соответствующую функцию поиска самого длинного палиндрома в строке.
string ArrayProcessing(string* text, int stringsCount)
{
    string answer = "";
    for (int i = 0; i < stringsCount; i++)
    {
        string localMax = FindLongestWord(text[i]);
        if (localMax.length() > answer.length())
        {
            answer = localMax;
        }
    }
    return answer;

}

// построчно вызываем функцию поиска палиндрома без учёта разделителей.
string ArrayProcessingNoMeaningful(string * text, int stringsCount)
{
    string answer = "";
    for (int i = 0; i < stringsCount; i++)
    {
        string localMax = FindLongestWordNoMeaningful(text[i]);
        if (localMax.length() > answer.length())
        {
            answer = localMax;
        }
    }
    return answer;
}

//ищем в строке самый длинный палиндром пологая что слова разделены чем-либо.
string FindLongestWord(string text)
{
    string longestWord = "";
    bool isWord = false;
    //проверка на пустую строку
    if (text.length() < 1)
    {
        return "";
    }
    int maxLength = 0;
    for (int i = 0; i < text.length(); i++)
    {
        for (int j = 1; j <= text.length() - i; j++)
        {
            if ((isWord) && (text[i + j - 1] == ' ' || text[i + j - 1] == '.' || text[i + j - 1] == '!'|| text[i + j - 1] == '?'||
                text[i + j - 1] == ';'|| text[i + j - 1] == ':'|| text[i + j - 1] == '"'))
                //  случай когда после слова встретился разделитель
            {
                string sub = GetSubstring(text, i, j-1);
                if (sub == reverseStr(sub) && sub.length() > maxLength)
                {
                    longestWord = sub;
                    maxLength = sub.length();
                }
                i += j-1;
                j = 0;
                isWord = false;
                break;
                // берем подстроку длиной с последнее слово разварачиваем и сравниваем саму с собой,
                //если они совпали, следовательно имеем палиндром. Сравниваем с найденым ранее. 
                //сдвигаем итератор на длину слова и продолжаем поиск.
            }
            else if(i + j == text.length() && !(text[i + j - 1] == ' ' || text[i + j - 1] == '.' || text[i + j - 1] == '!' || text[i + j - 1] == '?' ||
                text[i + j - 1] == ';' || text[i + j - 1] == ':' || text[i + j - 1] == '"'))
                //проверяем случай конца строки
            {
                string sub = GetSubstring(text, i, j);
                if (sub == reverseStr(sub) && sub.length() > maxLength)
                {
                    longestWord = sub;
                    maxLength = sub.length();
                }
                i += j;
                break;
            }
            else   if (text[i + j - 1] == ' ' || text[i + j - 1] == '.' || text[i + j - 1] == '!' || text[i + j - 1] == '?' ||
                text[i + j - 1] == ';' || text[i + j - 1] == ':' || text[i + j - 1] == '"')
                //если встретился разделитель
            {
                i++;
                j = 0;
                isWord = false;
            }
            else //если идёт слово
            {
                isWord = true;
            }
        }
    }
    return longestWord;
}
string FindLongestWordNoMeaningful(string text)
{
    string longestWord;
    if (text.length() > 0)
        //так как мы предполагаем что любой символ может быть частью "слова" берём первый символ в качестве
        //потенциального ответа
    {
        longestWord = GetSubstring(text, 0, 1);
    }
    else
    {
        return "";
    }
    int maxLength = 1;
    for (int i = 0; i < text.length() - 1; i++)
    {
        //двигаемся вдоль текста увеличевая сравниваемое слово пока не дойдём до конца строки
        //после чего увеличиваем итератор первого цикла на один и начинаем со следующего символа
        //перебирать все возможные слова
        for (int j = 1; j <= text.length() - i; j++)
        {
            string sub = GetSubstring(text, i, j);
            if (sub == reverseStr(sub) && sub.length() > maxLength)
            {
                longestWord = sub;
                maxLength = sub.length();
            }
        }
    }
    return longestWord;
}

 string * GetText(int countStrings)
{
    string *text = new string [countStrings] ;
    cout << "введите текст (внимание! русский язык не поддерживается!) :  " << endl;
    for (int i = 0; i < countStrings; i++)
    std::getline(std::cin, text[i]);
    return text;
}

double GetNumber()
{
    double num;
    while (true)
    {
        cin >> num;
        if (cin.fail()) //проверяем, не заблокирован ли буфер ввода, если да, значит значения ввода юыло некоректным.
        {
            cin.clear(); //возвращаем буфер в обычный режим
            cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n'); // очищаем буфер ввода
            cout << "некоректное значение, попробуйте снова" << endl; //просим повторный ввод
        }
        else
        {
            cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n'); // очищаем буфер ввода от лишних символов, если таковые есть
            return num; // выходим из функции.
        }
    }
}
//получение подстроки по стартовому индексу и длине
string GetSubstring(string text, int start, int size)
{
    char* str = new char[size+1];
    for (int i = 0; i <  size; i++)
    {
        str[i] = text[i + start];
    }
    str[size] = '\0';
    string answer = (const char*) str;
    delete[] str;
    return answer;
}
//разворот строки
string reverseStr(string text)
{
    char* str = new char[text.length()+1];
    for (int i = text.length() - 1,j = 0; i >= 0; i--, j++)
    {
        str[j] = text[i];
    }
    str[text.length()] = '\0';
    string answer = (const char*)str;
    delete[] str;
    return answer;
}

