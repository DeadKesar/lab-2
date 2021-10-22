
#include <iostream>   //ввод-вывод
#include <string>     //работа со строками
#include <vector>     //работа с векторами


using namespace std;

char GetYesNo();
// выбор функции поиска слова.
std::vector<string> GetText();
// получаем пользовательский текст
string VectorProcessing(std::vector<string> text);
//обрабатываем вектор построчно используя функцию с учётом разделителей
string VectorProcessingNoMeaningful(std::vector<string> text);
//обрабатываем вектор построчно используя функцию без учёта разделителей
string FindLongestWord(string text);
//предпологаем что слово это некая единица отделёная разделителями.
string FindLongestWordNoMeaningful(string text);
// функция расматривает любую последовательность символов как слово.
double GetNumber();
// получить числовое значение от пользователя с проверкой ввод, используется для получения количества строк

int main()
{            
    setlocale(LC_ALL, "Russian");
    //отображение русских символов в консоли
    string answer;
    std::vector<string> text = GetText();  
    //запрашиваем текст у пользовотеля.
    switch (GetYesNo())
    //ветвим программу на 2 случая
    {
    case('y'):
        //случай с учётом разделителей
        answer = VectorProcessing(text);
        break;
    case('n'):
        //без учёта разделителей
        answer = VectorProcessingNoMeaningful(text);
        break;
    } 
    cout << answer<< "   " << answer.length() << endl;
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

string VectorProcessing(std::vector<string> text)
// просто построчно вызываем соответствующую функцию поиска самого длинного палиндрома в строке.
{
    string answer = "";
    for (int i = 0; i < text.size(); i++)
    {
        string localMax = FindLongestWord(text[i]);
        if (localMax.length() > answer.length())
        {
            answer = localMax;
        }
    }
    return answer;

}
string VectorProcessingNoMeaningful(std::vector<string> text)
// построчно вызываем функцию поиска палиндрома без учёта разделителей.
{
    string answer = "";
    for (int i = 0; i < text.size(); i++)
    {
        string localMax = FindLongestWordNoMeaningful(text[i]);
        if (localMax.length() > answer.length())
        {
            answer = localMax;
        }
    }
    return answer;
}

string FindLongestWord(string text)
//ищем в строке самый длинный палиндром пологая что слова разделены чем-либо.
{
    string longestWord = "";
    bool isWord = false;
    if (text.length() < 1)
        //проверка на пустую строку
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
                string sub = text.substr(i, j-1);
                string reSub = sub;
                reverse(reSub.begin(), reSub.end());
                if (sub == reSub && sub.length() > maxLength)
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
                string sub = text.substr(i, j);
                string reSub = sub;
                reverse(reSub.begin(), reSub.end());
                if (sub == reSub && sub.length() > maxLength)
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
        longestWord = text.substr(0, 1);
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

std::vector<string> GetText()
{
    cout << "введите количество строк:  ";
    int countStrings = GetNumber();
    // ограничение для выхода из цикла получения текста.
    std::vector<string>  textVector(countStrings);
    cout << "введите текст (внимание! русский язык не поддерживается!) :  " << endl;
    for (int i = 0; i < countStrings; i++)
    std::getline(std::cin, textVector[i]);
    return textVector;
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

