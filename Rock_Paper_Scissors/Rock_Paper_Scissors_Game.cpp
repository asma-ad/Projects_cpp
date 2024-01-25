#include <iostream>
using namespace std;

// Rock_Paper_Scissors_Game | level (1)
// 10/11/2023

enum enGameChoices
{
    Stone = 1,
    Paper = 2,
    Scissors = 3
};

enum enWinner
{
    Player = 1,
    Computer = 2,
    Draw = 3
};

struct stGameRound
{
    short roundNumber = 0;
    enGameChoices playerChoice;
    enGameChoices computerChoice;
    enWinner winner;
    string winnerName;
};

struct stGameResult
{
    short roundsNumber = 0;
    short playerWonTimes;
    short computerWonTimes;
    short drawTimes;
    enWinner gameWinner;
    string winnerName;
};

void restScreen()
{
    system("cls");
    system("color 0F");
}

int RandomNumber(int from, int to)
{
    return (rand() % (to - from + 1) + from);
}

int readRoundsNumber()
{
    int number;
    do
    {
        cout << "How many rounds do you want to play (1 to 10)? ";
        cin >> number;
    } while (number < 1 || number > 10);
    return number;
}

enGameChoices readPlayerChoice()
{
    short number;
    do
    {
        cout << "Your choice: "
             << " Stone [1] , Paper [2] , Scissors [3] ? ";
        cin >> number;
    } while (number < 1 || number > 3);

    return (enGameChoices)number;
}

enGameChoices getComputerChoice()
{
    return (enGameChoices)(RandomNumber(1, 3));
}

enWinner winner(stGameRound round)
{
    if (round.playerChoice == round.computerChoice)
        return enWinner::Draw;

    switch (round.computerChoice)
    {
    case enGameChoices::Stone:
        if (round.playerChoice == enGameChoices::Paper)
            return enWinner::Player;
        break;
    case enGameChoices::Paper:
        if (round.playerChoice == enGameChoices::Scissors)
            return enWinner::Player;
        break;
    case enGameChoices::Scissors:
        if (round.playerChoice == enGameChoices::Stone)
            return enWinner::Player;
        break;
    }

    return enWinner::Computer;
}

enWinner winnerGame(short playerWonTimes, short computerWonTimes)
{
    if (playerWonTimes > computerWonTimes)
        return enWinner::Player;
    else if (playerWonTimes < computerWonTimes)
        return enWinner::Computer;
    else
        return enWinner::Draw;
}

string winnerName(enWinner winner)
{
    string strWinner[3] = {"Player", "Computer", "Draw"};
    return strWinner[winner - 1];
}

void winnerColorScreen(enWinner winner)
{
    switch (winner)
    {
    case enWinner::Player:
        system("color 2F");
        break;
    case enWinner::Computer:
        system("color 4F");
        cout << "\a";
        break;

    default:
        system("color 6F");
        break;
    }
}

string choicesName(enGameChoices choice)
{
    string strChoice[3] = {"Stone", "Paper", "Scissors"};
    return strChoice[choice - 1];
}

void printRoundResult(stGameRound round)
{
    cout << "\n__________________"
         << "Round [" << round.roundNumber << "]"
         << "__________________\n";
    cout << "Player choice   :" << choicesName(round.playerChoice) << "\n";
    cout << "Computer choice :" << choicesName(round.computerChoice) << "\n";
    cout << "Round's winner  :" << round.winnerName << "\n";
    cout << "__________________________________________";
    winnerColorScreen(round.winner);
}

stGameResult fillGameResult(short roundsNumber, short playerWonTimes, short computerWonTimes, short draw)
{
    stGameResult finalResult;
    finalResult.roundsNumber = roundsNumber;
    finalResult.playerWonTimes = playerWonTimes;
    finalResult.computerWonTimes = computerWonTimes;
    finalResult.drawTimes = draw;
    finalResult.gameWinner = winnerGame(playerWonTimes, computerWonTimes);
    finalResult.winnerName = winnerName(finalResult.gameWinner);
    return finalResult;
}

string tabs(short number)
{
    string t = "";
    for (int i = 0; i < number; i++)
    {
        t += "\t";
    }
    return t;
}

void showFinalResult(stGameResult finalResult)
{

    cout << "\n\n"
         << tabs(2) << "__________________________________________________________\n\n";
    cout << tabs(2) << "                 +++ G a m e  O v e r +++\n";
    cout << tabs(2) << "__________________________________________________________\n\n";

    cout << tabs(2) << "[ Final result ]\n";
    cout << tabs(2) << "Game rounds        :" << finalResult.roundsNumber << "\n";
    cout << tabs(2) << "Player won times   :" << finalResult.playerWonTimes << "\n";
    cout << tabs(2) << "Computer won times :" << finalResult.computerWonTimes << "\n";
    cout << tabs(2) << "Draw times         :" << finalResult.drawTimes << "\n";
    cout << tabs(2) << "Final winner       :" << finalResult.winnerName << "\n";
    cout << tabs(2) << "______________________________________\n";
}

stGameResult playGame(short roundsNumber)
{
    stGameRound round;
    short playerWonTimes = 0, computerWonTimes = 0, draw = 0;

    for (int i = 0; i < roundsNumber; i++)
    {
        cout << "\nRound [" << i + 1 << "] begins:\n";
        round.roundNumber = i + 1;
        round.playerChoice = readPlayerChoice();
        round.computerChoice = getComputerChoice();
        round.winner = winner(round);
        round.winnerName = winnerName(round.winner);

        if (round.winner == enWinner::Computer)
            computerWonTimes++;
        else if (round.winner == enWinner::Player)
            playerWonTimes++;
        else
            draw++;

        printRoundResult(round);
    }

    return fillGameResult(roundsNumber, playerWonTimes, computerWonTimes, draw);
}

void startGame()
{
    char playAgain = 'Y';
    do
    {
        restScreen();
        showFinalResult(playGame(readRoundsNumber()));

        cout << "\nDo you want to play again?\n";
        cin >> playAgain;
    } while (playAgain == 'y' || playAgain == 'Y');
}

int main()
{
    srand(unsigned(time(NULL)));
    startGame();

    return 0;
}