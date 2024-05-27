//OS phase 1
#include <iostream>
#include <string>
using namespace std;

class OS
{
    char M[100][4], IR[4], R[4], buffer[40];
    int IC, SI;
    bool Toggle;

public:
    void INIT(), LOAD(), STARTEXECUTION(), EXECUTEUSERPROGRAM(), MOS(), READ(), WRITE(), TERMINATE();
    void getInput(), printOutput(const string &);
};

void OS::INIT()
{
    for (int i = 0; i < 100; i++)
    {
        for (int j = 0; j < 4; j++)
        {
            M[i][j] = ' ';
        }
    }
    IR[4] = '\0';
    R[4] = '\0';
    Toggle = false;
}

void OS::LOAD()
{
    int x = 0;
    string line;
    while (getline(cin, line))
    {
        if (line[0] == '$' && line[1] == 'A' && line[2] == 'M' && line[3] == 'J')
        {
            INIT();
        }
        else if (line[0] == '$' && line[1] == 'D' && line[2] == 'T' && line[3] == 'A')
        {
            STARTEXECUTION();
        }
        else if (line[0] == '$' && line[1] == 'E' && line[2] == 'N' && line[3] == 'D')
        {
            x = 0;
            continue;
        }
        else
        {
            int b = 0;

            bool isInstruction = (line[0] == 'L' && line[1] == 'R') || (line[0] == 'S' && line[1] == 'R') ||
                                 (line[0] == 'C' && line[1] == 'R') || (line[0] == 'B' && line[1] == 'T') ||
                                 (line[0] == 'G' && line[1] == 'D') || (line[0] == 'P' && line[1] == 'D') ||
                                 (line[0] == 'H');

            if (isInstruction)
            {
                for (; x < 100; x++)
                {
                    for (int j = 0; j < 4; j++)
                    {
                        if (b < line.size())
                        {
                            M[x][j] = line[b];
                            b++;
                        }
                        else
                        {
                            M[x][j] = ' ';
                        }
                    }

                    if (b >= line.size())
                    {
                        x++;
                        break;
                    }
                }
            }
        }
    }

    for (int i = 0; i < 100; i++)
    {
        cout << "M[" << i << "]: ";
        for (int j = 0; j < 4; j++)
        {
            cout << M[i][j];
        }
        cout << endl;
    }
}

void OS::STARTEXECUTION()
{
    IC = 0;
    EXECUTEUSERPROGRAM();
}

void OS::EXECUTEUSERPROGRAM()
{
    while (true)
    {
        for (int i = 0; i < 4; i++)
        {
            IR[i] = M[IC][i];
        }
        IC++;

        if (IR[0] == 'L' && IR[1] == 'R')
        {
            int add = IR[2] - '0';
            add = (add * 10) + (IR[3] - '0');

            for (int i = 0; i < 4; i++)
                R[i] = M[add][i];
        }
        else if (IR[0] == 'S' && IR[1] == 'R')
        {
            int add = IR[2] - '0';
            add = (add * 10) + (IR[3] - '0');

            for (int i = 0; i < 4; i++)
                M[add][i] = R[i];
        }
        else if (IR[0] == 'C' && IR[1] == 'R')
        {
            int flag = 0;
            int add = IR[2] - '0';
            add = (add * 10) + (IR[3] - '0');

            for (int i = 0; i < 4; i++)
            {
                if (R[i] != M[add][i])
                    flag = 1;
            }

            if (flag == 1)
                Toggle = false;
            else
                Toggle = true;
        }
        else if (IR[0] == 'B' && IR[1] == 'T')
        {
            int add = IR[2] - '0';
            add = (add * 10) + (IR[3] - '0');
            if (Toggle == true)
                IC = add;
        }
        else if (IR[0] == 'G' && IR[1] == 'D')
        {
            SI = 1;
            READ();
        }
        else if (IR[0] == 'P' && IR[1] == 'D')
        {
            SI = 2;
            WRITE();
        }
        else if (IR[0] == 'H')
        {
            SI = 3;
            MOS();
            break;
        }
    }
}

void OS::MOS()
{
    switch (SI)
    {
    case 3:
        TERMINATE();
        break;
    }
}

void OS::READ()
{
    string line;
    getline(cin, line);

    int b = 0;
    int n = (IR[2] - '0') * 10 + (IR[3] - '0');

    for (int l = 0; l < 10; l++)
    {
        for (int j = 0; j < 4; j++)
        {
            if (b < line.size())
            {
                M[n][j] = line[b];
                b++;
            }
            else
            {
                M[n][j] = ' ';
            }
        }
        n++;
    }

    if (M[IR[2] - '0'][IR[3] - '0'] == '$' && M[IR[2] - '0'][IR[3] - '0' + 1] == 'E' && M[IR[2] - '0'][IR[3] - '0' + 2] == 'N' && M[IR[2] - '0'][IR[3] - '0' + 3] == 'D')
    {
        cout << "End of data encountered. Aborting." << endl;
    }

    SI = 0;
}

void OS::WRITE()
{
    int b = 0;
    int n = (IR[2] - '0') * 10 + (IR[3] - '0');
    string line;

    for (int l = 0; l < 10; l++)
    {
        for (int j = 0; j < 4; j++)
        {
            line += M[n][j];
        }
        n++;
    }

    printOutput(line);
    SI = 0;
}

void OS::TERMINATE()
{
    printOutput("\n");
    printOutput("\n");
    SI = 0;
}

void OS::printOutput(const string &output)
{
    cout << output << endl;
}

int main()
{
  //Sampe input:
//   $AMJ000100030001
// GD10PD10H
// $DTA
// Hello World
// $END0001
  
    OS os;
    os.LOAD();
    return 0;
}
