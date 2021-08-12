
  
#include <iostream>
#include <iomanip>
#include <algorithm>
#include <limits>
#define INF 1e9;

using namespace std;

class Game
{
    enum class Player
    {
        none = '-',
        human = 'X',
        computer = 'O'
    };

    Player board[3][3];

public:
    Game()
    {
        for ( int i = 0; i < 3; i++)
        {
            for ( int j = 0; j < 3; j++)
            {
                board[i][j] = Player::none;
            }
        }
    }

    void printBoard()
    {
        cout << "+-----------------+";
        for ( int i = 0; i < 3; i++)
        {
            cout << "\n|";
            for (int j = 0; j < 3; j++)
            {
                cout << setw(3) << static_cast<char>(board[i][j]) << setw(3) << " |";
            }
        }
        cout << "\n+-----------------+\n";
    }

    bool isTie()
    {
        for (unsigned int i = 0; i < 3; i++)
        {
            if (board[i][0] == Player::none || board[i][1] == Player::none || board[i][2] == Player::none)
                return false;
        }
        return true;
    }

    bool checkWin(Player player)
    {
        for (unsigned int i = 0; i < 3; i++)
        {
            // Check horizontals if all are same
            if (board[i][0] == player && board[i][1] == player && board[i][2] == player)
                return true;

            // Check verticals if all are same
            if (board[0][i] == player && board[1][i] == player && board[2][i] == player)
                return true;
        }

        // Check diagonals if all are same
        if (board[0][0] == player && board[1][1] == player && board[2][2] == player)
            return true;

        if (board[0][2] == player && board[1][1] == player && board[2][0] == player)
            return true;

        return false;
    }

    pair<int,int> minimax()
    {
        int score = -INF;
        pair<int,int> move;

        for ( int i = 0; i < 3; i++)
        {
            for ( int j = 0; j < 3; j++)
            {
                if (board[i][j] == Player::none)
                {
                    board[i][j] = Player::computer;

                    int temp = minSearch();

                    if (temp > score)
                    {
                        score = temp;
                        move.first = i;
                        move.second = j;
                    }
                    board[i][j] = Player::none;
                }
            }
        }

        return move;
    }

    int maxSearch()
    {
        if (checkWin(Player::human)) { return -1; }
        else if (checkWin(Player::computer)) { return 1; }
        else if (isTie()) { return 0; }

        int score = -INF;

        for ( int i = 0; i < 3; i++)
        {
            for ( int j = 0; j < 3; j++)
            {
                if (board[i][j] == Player::none)
                {
                    board[i][j] = Player::computer;
                    score = std::max(score, minSearch());
                    board[i][j] = Player::none;
                }
            }
        }

        return score;
    }

    int minSearch()
    {
        if (checkWin(Player::human)) { return -1; }
        else if (checkWin(Player::computer)) { return 1; }
        else if (isTie()) { return 0; }

        int score = INF;

        for ( int i = 0; i < 3; i++)
        {
            for ( int j = 0; j < 3; j++)
            {
                if (board[i][j] == Player::none)
                {
                    board[i][j] = Player::human;
                    score = std::min(score, maxSearch());
                    board[i][j] = Player::none;
                }
            }
        }

        return score;
    }

    void getHumanMove()
    {
        bool fail = true;
        unsigned int x = -1, y = -1;

        do
        {
            cout << "Your Move: ";

            char c;
            std::cin >> c;
            x = c - '0';
            std::cin >> c;
            y = c - '0';

            fail = board[x][y] != Player::none;

        } while (fail);

        board[x][y] = Player::human;
    }

    void play()
    {
        unsigned int turn = 0;
        bool exit = false;

        printBoard();
        cout << "Enter your move in coordinate form[row, col]. ex: 02\n";

        do
        {
            // human move
            if (turn == 0)
            {
                getHumanMove();

                if (checkWin(Player::human))
                {
                    cout << "You Wins :)\n";
                    exit=1;
                }
            }
            else
            {
                cout << "\nComputer Move: ";

                pair<int,int> aimove = minimax();
                cout << aimove.first << aimove.second << "\n";
                board[aimove.first][aimove.second] = Player::computer;

                if (checkWin(Player::computer))
                {
                    cout<<"Computer Wins\n ";
                    exit=1;
                }
            }

            if (isTie())
            {
                cout << "\n*** Tie ***\n";
                exit=1;
            }

            turn ^= 1;
            printBoard();

        } while (!exit);
    }
};

int main()
{
    Game tictactoe;
    tictactoe.play();
}