#include <cstdlib>
#include <ctime>
#include <iostream>
#include <iomanip>
#include <fstream>
#include <string>

using namespace std;

void printMenu(int user, int turn, int devil);
void printNumbers(int i, int user, int turn, int devil);

int main()
{
#ifdef JARVIS
  srand(0);
#else
  srand(time(NULL));
#endif
  // Define variables and initiate ones needed
  int rollSum, userScore, devil, userTurn, devilTurn, roll, wins, losses;
  char input = 'a';
  ifstream scoresIn;
  ofstream scoresOut;
  string welcome = "---- Welcome to Devil's Dice! ----";
  string options = "Hold[h], roll[r], or forfeit[f]: ";
  userScore = 0;
  userTurn = 0;
  devil = 0;
  roll = 0;
  devilTurn = 0;
  rollSum = 0;

  cout << welcome << endl;

  // Game will run until user holds over 100 or devil reaches 100
  while ((userScore < 100) && (devil < 100))
  {
      // Users Turn loops until user rolls a one or enters f to quit.
      while ((input != 'f') && (roll != 1))
      {
          cout << options;
          cin >> input;
          if (input == 'h')
          {
              cout << "You banked " << rollSum << " points" << endl;
              userScore += rollSum;
              userTurn = 0;
              rollSum = 0;
              break;
          }
          if (input == 'r')
          {
              roll = rand() % 6 + 1;
              if (roll == 1)
              {
                  cout << "You rolled a 1 :(" << endl;
                  userTurn = 0;
                  rollSum = 0;
                  break;
              }
              else
              {
                  rollSum = rollSum + roll;
                  userTurn = rollSum + userScore;
                  cout << "You rolled a " << roll << "!" << endl;
                  printMenu(userScore, userTurn, devil);
              }
          }
          if (input == 'f')
          {
              cout << "Game Over!" << endl;
              break;
          }
      }
      // Breaks the loop if User has held over 100 points
      if (userScore > 100)
          break;

      // Breaks the loop if user has chosen to quit
      if (input == 'f')
          break;

      // Devils Turn

      // If the devil is tied or winning run this loop
      if (devil >= userScore)
      {
          while ((rollSum < 21) && (devilTurn < 100))
          {
              roll = rand() % 6 + 1;
              if (roll == 1)
              {
                  // cout << "HE rolled a 1 :(" << endl; -- uncomment this line for debugging/verbose game play
                  devilTurn = 0;
                  rollSum = 0;
                  break;
              }
              else
              {
                  rollSum = rollSum + roll;
                  devilTurn = rollSum + devil;
                  // cout << "HE rolled a " << roll << "!" << endl; -- uncomment this line for debugging/verbose game play
                  // cout << "score " << devilTurn << endl; -- uncomment this line for debugging/verbose game play
              }
          }
      }

      // If the devil is losing run this loop
      else if (devil < userScore)
      {
          while ((rollSum < 30) && (devilTurn < 100))
          {
              roll = rand() % 6 + 1;
              if (roll == 1)
              {
                  // cout << "HE rolled a 1 :(" << endl; -- uncomment this line for debugging/verbose game play
                  devilTurn = 0;
                  rollSum = 0;
                  break;
              }
              else
              {
                  rollSum = rollSum + roll;
                  devilTurn = rollSum + devil;
                  // cout << "HE rolled a " << roll << "!" << endl; -- uncomment this line for debugging/verbose game play
                  // cout << "score " << devilTurn << endl; -- uncomment this line for debugging/verbose game play
              }
          }
      }

      devil += rollSum;
      cout << "Devil got " << rollSum << " points" << endl;
      rollSum = 0;
      devilTurn = 0;
      printMenu(userScore, userScore, devil);
      roll = 0;
  }

  // gets the previous number of wins/loses
  scoresIn.open("games.txt");
  scoresIn >> wins >> losses;
  scoresIn.close();

  // Shows who the winner was
  if (userScore >= 100)
  {
      cout << "You Win!" << endl;
      wins += 1;
  }
  else if (input == 'f')
      losses += 1;
  if (devil >= 100)
  {
      cout << "Devil Wins!" << endl;
      losses += 1;
  }

  // displays the number of wins/loses
  cout << "Total Wins: " << wins << endl;
  cout << "Total Losses: " << losses << endl;

  // writes wins/loses to file games.txt
  scoresOut.open("games.txt");
  scoresOut << wins << " " << losses << endl;
  scoresOut.close();

return 0;
}


// this function prints the headers and starts the loop to display scores and numbers
void printMenu(int user, int turn, int devil)
{
    cout << right << setw(5) << " ";
    cout << left << setw(6) << "Player";
    cout << left << setw(5) << " ";
    cout << right << setw(15) << "Devil";
    cout << left << setw(5) << " " << endl;
    cout << right << setw(5) << " ";
    cout << left << setw(6) << "------";
    cout << left << setw(5) << " ";
    cout << right << setw(15) << "-----";
    cout << left << setw(5) << " " << endl;
    for (int i = 100; i >= 0; i -= 10)
    {
        printNumbers(i, user, turn, devil);
    }
    cout << endl;
}


// this function displays the scores and number table
void printNumbers(int i, int user, int turn, int devil)
{
    if ((user >= i)  &&  (user < i + 10) )
    {
        cout << right << setw(3) << user;
        cout << right << setw(2) << " >";
    }
    else
        cout << setw(5) << " ";

    cout << left << setw(3) << "-- ";
    cout << left << setw(3) << i;

    if ((turn >= i) && (turn < i + 10) )
    {
        cout << left << setw(2) << "<";
        cout << left << setw(3) << turn;
    }
    else
        cout << left << setw(5) << " ";

    cout << right << setw(12) << i;
    cout << right << setw(3) << " --";

    if (devil >= i && devil < i + 10)
    {
        cout << "< ";
        cout << left << setw(3) << devil;
    }
    else
        cout << setw(5) << " ";
    cout << endl;
}
