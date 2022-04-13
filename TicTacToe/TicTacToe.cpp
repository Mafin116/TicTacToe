// TicTacToe.cpp : Этот файл содержит функцию "main". Здесь начинается и заканчивается выполнение программы.
//

#include <iostream>
#include <vector>
#include <random>

using namespace std;


unsigned int cellCount = 5;
unsigned int stepCount = 0;
int botFirst = 0;
vector<vector<string>> spot(cellCount, vector<string>(cellCount, " "));
//vector<vector<string>> spot{ {" ", "X", "O"},{"O", "X", "X"},{" ", "O", " "} };
vector<vector<int>> spotRisk(cellCount, vector<int>(cellCount, 0));
bool endGame = false;

void drawCell(unsigned int cellCount, vector<vector<string>> spot)
{
    for (int i = 0; i < cellCount * 2 - 1; i++)
    {
        if(i%2 == 0)
        {
            for (int j = 0; j < cellCount * 2 - 1; j++)
            {
                if (j % 2 == 0)
                {
                    cout << spot[i / 2][j / 2];
                }
                else {
                    cout << "|";
                }
                
            }
            cout << endl;
        }
        else {
            for (int j = 0; j < cellCount * 2 - 1; j++)
            {
                cout << "-";
            }
            cout << endl;
        }
        
    }
    cout << endl;
}

void cinPos(int line, int column)
{
    
    
    if (stepCount % 2 == 0)
    {
        spot[line][column] = "X";
    }
    else {
        spot[line][column] = "O";
    }
    spotRisk[line][column] = -100;
    stepCount++;
}

void playerIn()
{
    int column, line;
    bool t = false;
    while (!t)
    {
        
        cout << "Номер строки ";
        cin >> line;
        cout << "Номер столбца ";
        cin >> column;
        if (column > cellCount || line > cellCount)
        {
            cout << "Неверные значения" << endl;
        }
        else {
            t = true;
        }
        if (spot[line-1][column-1] != " ")
        {
            t = false;
            cout << "Клетка занята" << endl;
        }
        else {
            t = true;
        }
    }
    cinPos(line - 1, column - 1);
}


bool endCheck(vector<vector<string>> spot)
{
    //verticals
    for (int i = 0; i < cellCount; i++)
    {
        string str = spot[i][0];
        if (str != " ")
        {
            for (int j = 1; j < cellCount; j++)
            {
                if (str != spot[i][j])
                {
                    break;
                }
                if (j == cellCount - 1)
                {
                    return true;
                }
            }
        }
    }
    //horizontal
    for (int i = 0; i < cellCount; i++)
    {
        string str = spot[0][i];
        if (str != " ")
        {
            for (int j = 1; j < cellCount; j++)
            {
                if (str != spot[j][i])
                {
                    break;
                }
                if (j == cellCount - 1)
                {
                    return true;
                }
            }
        }
    }
    // \/
    for (int i = 0; i < cellCount; i++)
    {
        string str = spot[0][0];
        if (str != " ")
        {
            if (str != spot[i][i])
            {
                break;
            }
            if (i == cellCount - 1)
            {
                return true;
            }
        }
    }
    for (int i = 0; i < cellCount; i++)
    {
        string str = spot[0][cellCount - 1];
        if (str != " ")
        {
            if (str != spot[i][cellCount - 1 - i])
            {
                break;
            }
            if (i == cellCount - 1)
            {
                return true;
            }
        }
    }
    return false;
}

int score(vector<vector<string>> spot, int stepCount)
{
    if (stepCount >= cellCount * cellCount && !endCheck(spot))
    {
        return 5;
    }
    if (endCheck(spot) && stepCount % 2 == botFirst)
    {
        return 10;
    }
    if (endCheck(spot) && stepCount % 2 != botFirst)
    {
        return 0;
    }
    return 5;
}

int miniMax(vector<vector<string>> spot)
{
    int count = score(spot, stepCount);

    if (endCheck(spot))
    {
        return count;
    }
    else
    {
        if (stepCount % 2 == 0)
        {
            for (int i = 0; i < cellCount; i++)
            {
                for (int j = 0; j < cellCount; j++)
                {
                    if (spot[i][j] == " ")
                    {
                        spot[i][j] = "X";
                        stepCount++;

                        int co = miniMax(spot);
                        if (botFirst == 0)
                        {
                            count += co;
                        }
                        else
                        {
                            count -= co;
                        }
                        
                        spot[i][j] = " ";
                        stepCount--;

                        return count;
                    }
                }
            }
        }
        else {
            for (int i = 0; i < cellCount; i++)
            {
                for (int j = 0; j < cellCount; j++)
                {
                    if (spot[i][j] == " ")
                    {
                        spot[i][j] = "O";
                        stepCount++;

                        int co = miniMax(spot);
                        if (botFirst == 0)
                        {
                            count += co;
                        }
                        else
                        {
                            count -= co;
                        }
                        spot[i][j] = " ";
                        stepCount--;

                        return count;
                    }
                }
            }
        }
    }
    return count;
}

void mm()
{
    for (int i = 0; i < cellCount; i++)
    {
        for (int j = 0; j < cellCount; j++)
        {
            if (spot[i][j] == " ")
            {
                if (stepCount % 2 == 0)
                {
                    stepCount++;
                    spot[i][j] = "X";
                }
                else
                {
                    stepCount++;
                    spot[i][j] = "O";
                }
                spotRisk[i][j] = miniMax(spot);
                spot[i][j] = " ";
                stepCount--;
            }
            else {
                spotRisk[i][j] = -100;
            }

        }
    }
}

void pcGo()
{
    int xMax = -100;
    int yMax = -100;
    int val = -100;
    for (int i = 0; i < cellCount; i++)
    {
        for (int j = 0; j < cellCount; j++)
        {

            if (spotRisk[i][j] > val)
            {
                val = spotRisk[i][j];
                xMax = i;
                yMax = j;
            }
            srand(time(NULL));
            if (spotRisk[i][j] == val && rand() % 2 == 1)
            {
                val = spotRisk[i][j];
                xMax = i;
                yMax = j;
            }

        }
    }
    cinPos(xMax, yMax);
}

void gameCyclePvP()
{
    while (!endGame)
    {
        playerIn();
        drawCell(cellCount, spot);
        if (stepCount >= cellCount * 2 - 1)
        {
            if (endCheck(spot))
            {
                if (stepCount % 2 == 0)
                {
                    cout << "win O" << endl;
                }
                else
                {
                    cout << "win X" << endl;
                }
                endGame = true;
            }
            int count = 0;
            for (int i = 0; i < cellCount; i++)
            {
                for (int j = 0; j < cellCount; j++)
                {
                    if (spot[i][j] == " ")
                    {
                        count++;
                    }
                }
            }
            if (count == 0) {
                cout << "win XO" << endl;
                endGame = true;
            }
        }
        
    }
}

void gameCyclePvE()
{
    while (!endGame)
    {
        if (stepCount % 2 == 0)
        {
            playerIn();
        }
        else
        {
            mm();
            pcGo();
        }
        drawCell(cellCount, spot);
        if (stepCount >= cellCount * 2 - 1)
        {
            if (endCheck(spot))
            {
                if (stepCount % 2 == 0)
                {
                    cout << "win O" << endl;
                }
                else
                {
                    cout << "win X" << endl;
                }
                endGame = true;
            }
            int count = 0;
            for (int i = 0; i < cellCount; i++)
            {
                for (int j = 0; j < cellCount; j++)
                {
                    if (spot[i][j] == " ")
                    {
                        count++;
                    }
                }
            }
            if (count == 0) {
                cout << "win XO" << endl;
                endGame = true;
            }
        }

    }
}

void gameCycleEvE()
{
    while (!endGame)
    {
        if (stepCount % 2 == 0)
        {
            botFirst = 1;
            mm();
            pcGo();
        }
        else
        {
            botFirst = 0;
            mm();
            pcGo();
        }
        drawCell(cellCount, spot);

            if (endCheck(spot))
            {
                if (stepCount % 2 == 0)
                {
                    cout << "win O";
                }
                else if (stepCount % 2 != 0)
                {
                    cout << "win X";
                }
                endGame = true;
            }
            int count = 0;
            for (int i = 0; i < cellCount; i++)
            {
                for (int j = 0; j < cellCount; j++)
                {
                    if (spot[i][j] == " ")
                    {
                        count++;
                    }
                }
            }
            if (count == 0) {
                cout << "win XO" << endl;
                endGame = true;
            }
        

    }
}

void menu()
{
    int gameMode = 0;
    bool cont = false;
    while (!cont)
    {
        cout << "1) PVP" << endl;
        cout << "2) PVE" << endl;
        cout << "3) EVE (Demo)" << endl;
        cin >> gameMode;
        if (gameMode > 1 || gameMode < 3)
        {
            cont = true;
        }
    }
    cont = false;
    while (!cont)
    {
        int cell = 0;
        cout << "1) 3x3" << endl;
        cout << "2) 4x4" << endl;
        cout << "3) 5x5" << endl;
        cin >> cell;
        if (cell > 1 || cell < 3)
        {
            cont = true;
            if (cell == 1){ cellCount = 3; }
            if (cell == 2) { cellCount = 4; }
            if (cell == 3) { cellCount = 5; }
        }
    }
    int v = 0;
    switch (gameMode)
    {

    case 1:
        gameCyclePvP();
        break;
    case 2:
        
        cont = false;
        while (cont)
        {
            cout << "Первый ход:" << endl;
            cout << "1) Компьютр" << endl;
            cout << "2) Человек" << endl;
            if (v < 1 || v > 2)
            {
                cont = true;
            }
        }
        if (v == 1)
        {
            stepCount = 7;
        }
        else
        {
            stepCount = 6;
        }
        gameCyclePvE();
        break;
    case 3:
        gameCycleEvE();
        break;
    default:
        break;
    }

}

int main()
{
    setlocale(LC_ALL, "Russian");
    bool close = false;
    while (!close)
    {
        menu();
        cout << "Закрыть \n 1) Да \n 2) Нет" << endl;
        int q = 0;
        cin >> q;
        if (q == 1)
        {
            close = true;
        }
    }


}
