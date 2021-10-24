
#include <iostream>   //ввод-вывод   
#include <string.h>  //работа со строками

using namespace std;

// выбор функции поиска слова.
char GetYesNo();
// получаем пользовательский текст
char ** GetText(int size);
//обрабатываем вектор построчно используя функцию с учётом разделителей
char* ArrayProcessing(char** text, int stringsCount);
//обрабатываем вектор построчно используя функцию без учёта разделителей
char* ArrayProcessingNoMeaningful(char** text, int stringsCount);
//предпологаем что слово это некая единица отделёная разделителями.
char* FindLongestWord(char* text);
// функция расматривает любую последовательность символов как слово.
char* FindLongestWordNoMeaningful(char* text);
// получить числовое значение от пользователя с проверкой ввод, используется для получения количества строк
char* GetSubstring(char* text, int start, int size);
//разворот строки
char* reverseStr(char* text);
//получить копию строки
char* GetCopy(char* origin, int size);
// получить числовое значение с проверкой ввода
double GetNumber();


int main()
{     
    //отображение русских символов в консоли
    setlocale(LC_ALL, "Russian");
    char* answer = new char[] {"\0"};
    cout << "введите количество строк:  ";
    // ограничение для выхода из цикла получения текста.
    int countStrings = GetNumber();
    //запрашиваем текст у пользовотеля.
    char** text = GetText(countStrings);
    //ветвим программу на 2 случая
    switch (GetYesNo())    {
    case('y'):
        //случай с учётом разделителей
        delete[] answer;
        answer = ArrayProcessing(text, countStrings);
        break;
    case('n'):
        //без учёта разделителей
        delete[] answer;
        answer = ArrayProcessingNoMeaningful(text, countStrings);
        break;
    } 
    cout << answer<< "   " << strlen(answer) << endl;
    //чистим память
    for (int i = 0; i < countStrings; i++)
    {
        delete[] text[i];
    }
    delete[] answer;
    delete [] text; 
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
char* ArrayProcessing(char** text, int stringsCount)
{
    char* answer = new char[]{ "\0" };
    for (int i = 0; i < stringsCount; i++)
    {
        char* localMax = FindLongestWord(text[i]);
        if (strlen(localMax) > strlen(answer))
        {
            delete[] answer;
            answer = GetCopy(localMax, strlen(localMax));
        }
        delete[] localMax;
    }
    return answer;

}

// построчно вызываем функцию поиска палиндрома без учёта разделителей.
char* ArrayProcessingNoMeaningful(char** text, int stringsCount)
{
    char* answer = new char[] { "\0" };
    for (int i = 0; i < stringsCount; i++)
    {
        char* localMax = FindLongestWordNoMeaningful(text[i]);
        if (strlen(localMax) > strlen(answer))
        {
            delete[] answer;
            answer = GetCopy(localMax, strlen(localMax));
        }
        delete[] localMax;
    }
    return answer;
}

//ищем в строке самый длинный палиндром пологая что слова разделены чем-либо.
char* FindLongestWord(char* text)
{
    char* longestWord = new char[] { "\0" };
    bool isWord = false;
    //проверка на пустую строку
    if (strlen(text) < 1)
    {
        return longestWord;
    }
    int maxLength = 0;
    for (int i = 0; i < strlen(text); i++)
    {
        for (int j = 1; j <= strlen(text) - i; j++)
        {
            if ((isWord) && (text[i + j - 1] == ' ' || text[i + j - 1] == '.' || text[i + j - 1] == '!'|| text[i + j - 1] == '?'||
                text[i + j - 1] == ';'|| text[i + j - 1] == ':'|| text[i + j - 1] == '"'))
                //  случай когда после слова встретился разделитель
            {
                char* sub = GetSubstring(text, i, j - 1);
                char* reSub = reverseStr(sub);
                if (strcmp(sub, reSub) == 0 && strlen(sub) > maxLength)
                {
                    delete[] longestWord;
                    longestWord = GetCopy(sub, strlen(sub));
                    maxLength = strlen(sub);
                }
                i += j-1;
                j = 0;
                isWord = false;
                delete[] reSub;
                delete[] sub;
                break;
                // берем подстроку длиной с последнее слово разварачиваем и сравниваем саму с собой,
                //если они совпали, следовательно имеем палиндром. Сравниваем с найденым ранее. 
                //сдвигаем итератор на длину слова и продолжаем поиск.
            }
            else if(i + j == strlen(text) && !(text[i + j - 1] == ' ' || text[i + j - 1] == '.' || text[i + j - 1] == '!' || text[i + j - 1] == '?' ||
                text[i + j - 1] == ';' || text[i + j - 1] == ':' || text[i + j - 1] == '"'))
                //проверяем случай конца строки
            {
                char* sub = GetSubstring(text, i, j);
                char* reSub = reverseStr(sub);
                if (strcmp(sub, reSub) == 0 && strlen(sub) > maxLength)
                {
                    delete[] longestWord;
                    longestWord = GetCopy(sub, strlen(sub));
                    maxLength = strlen(sub);
                }
                i += j;
                delete[] reSub;
                delete[] sub;
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
char* FindLongestWordNoMeaningful(char* text)
{
    char* longestWord = new char[] { "\0" };
    if (strlen(text) > 0)
        //так как мы предполагаем что любой символ может быть частью "слова" берём первый символ в качестве
        //потенциального ответа
    {
        delete[] longestWord;
        longestWord = GetSubstring(text, 0, 1);
    }
    else
    {
        return longestWord;
    }
    int maxLength = 1;
    for (int i = 0; i < strlen(text) - maxLength; i++)
    {
        //двигаемся вдоль текста увеличевая сравниваемое слово пока не дойдём до конца строки
        //после чего увеличиваем итератор первого цикла на один и начинаем со следующего символа
        //перебирать все возможные слова
        for (int j = 1; j <= strlen(text) - i; j++)
        {
            char* sub = GetSubstring(text, i, j);
            char* reSub = reverseStr(sub);
            if (strcmp(sub, reSub) == 0 && strlen(sub) > maxLength)
            {
                delete[] longestWord;
                longestWord = GetCopy(sub, strlen(sub));
                maxLength = strlen(sub);
            }
            delete[] reSub;
            delete[] sub;
        }
    }
    return longestWord;
}

char** GetText(int countStrings)
{
    cout << "введите текст (внимание! русский язык не поддерживается!) :  " << endl;
    char ** text = new char* [countStrings];
    for (int j = 0; j < countStrings; j++)
    {
        char ch;
        cin.get(ch);//блокируем поток, пока вводим символы
        cin.putback(ch);//возвращаем считаные символы во входной поток
        int size = cin.ios::rdbuf()->in_avail();//определяем размер входного буфера
        if (size > 0)
        {
            char* str = new char[size];

            for (int i = 0; i < size; i++)
            {
                cin.get(str[i]);
            }
            str[size - 1] = '\0';
            text[j] = str;
        }
    }
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
char* GetSubstring(char* text, int start, int size)
{
    char* str = new char[size+1];
    for (int i = 0; i <  size; i++)
    {
        str[i] = text[i + start];
    }
    str[size] = '\0';
    return str;
}
//разворот строки
char* reverseStr(char* text)
{
    char* str = new char[strlen(text)+1];
    for (int i = strlen(text) - 1,j = 0; i >= 0; i--, j++)
    {
        str[j] = text[i];
    }
    str[strlen(text)] = '\0';
    return str;
}
//получение копии строки через указатели
char* GetCopy(char* origin, int size)
{
    char* copy = new char[size + 1];
    for (int i = 0; i < size; i++)
    {
        *copy = *origin;
        copy++;
        origin++;
    }
    copy -= size;
    origin -= size;
    copy[size] = '\0';
    return copy;
}
