#include <iostream>
using namespace std;

enum enDifficultyLevel { Easy = 1, Medium = 2, Hard = 3, Mix_a = 4 };

enum enOperatorsType { Add = 1, Sup = 2, Mul = 3, Div = 4, Mix_b = 5 };

struct stQuestion 
{
	int Number1 = 0;
	int Number2 = 0;
	enDifficultyLevel DL;
	enOperatorsType OT;
	int CorrectAnswer = 0;
	int UserAnswer = 0;
	bool Result = false;
};

struct stQuiz
{
	stQuestion QuesList[100];
	short HowManyQuestions = 0;
	short NoRightAnswers = 0;
	short NoWrongAnswers = 0;
	enDifficultyLevel DL;
	enOperatorsType OT;
	string strDLevel;
	string strOType;
	bool IsPass = false;
};

int ReadNumber()
{
	int num = 0;
	cin >> num;
	return num;
}

int Read(string msg)
{
	char num;
	do
	{
		cout << msg ;
		cin >> num;
		cout << "\n";
	} while (!isdigit(num));
	return (int)(num - 48);
}

int RandomNumber(int from, int to)
{
	int RandNum = rand() % (to - from + 1) + from;
	return RandNum;
}

int ReadNoQuestion()
{
	int NoQuestion = Read("How Many Questions Do You Want To Answer ?... ");
	return NoQuestion;
}

enDifficultyLevel ReadQuestionLevel()
{
	return (enDifficultyLevel)Read("Choice Questions Level :-\n(1) Easy\t(2) Medium\n(3) Hard\t(4) Mix\n");
}

enOperatorsType ReadOperationType()
{
	return (enOperatorsType)Read("Choice Operation Type :-\n(1) Addition\t\t(2) Subtraction\n(3) Multiplication\t(4) Division\n(5) Mix\n");
}

string strDLevel(enDifficultyLevel DL)
{
	string arr[4] = { "Easy", "Medium" , "Hard" , "Mix" };
	return arr[DL - 1];
}

string strOType(enOperatorsType OT)
{
	string arr[5] = { "(+)", "(-)" , "(*)" , "(/)" , "Mix"};
	return arr[OT - 1];
}

void SetScreenColor(bool i)
{
	if (i == true)
	{
		system("color 2F");
	}
	else
	{
		system("color 4F");
	}
}

void CheckAnswers(stQuiz& Quiz, short NOQ)
{
	if (Quiz.QuesList[NOQ].UserAnswer != Quiz.QuesList[NOQ].CorrectAnswer)
	{
		Quiz.QuesList[NOQ].Result = false;
		Quiz.NoWrongAnswers++;

		cout << "Wrong Answer\n";
		cout << "The Right Answer Is : ";
		cout << Quiz.QuesList[NOQ].CorrectAnswer << "\n";
	}
	else
	{
		Quiz.QuesList[NOQ].Result = true;
		Quiz.NoRightAnswers++;
		cout << "Right Answer :)\n";
	}
	cout << endl;
	SetScreenColor(Quiz.QuesList[NOQ].Result);
}

int SimpleCalculator(int num1, int num2, enOperatorsType OT)
{
	switch (OT)
	{
	case Add: return num1 + num2;
		break;
	case Sup: return num1 - num2;
		break;
	case Mul: return num1 * num2;
		break;
	case Div: return (num2 != 0) ? num1 / num2 : 0 ;
		break;
	default:
		return num1 + num2;
	}
}

stQuestion GenerateQuestion(enDifficultyLevel DL, enOperatorsType OT)
{
	stQuestion Question;

	if (DL == enDifficultyLevel::Mix_a)
	{
		DL = (enDifficultyLevel)RandomNumber(1,3);
	}

	if (OT == enOperatorsType::Mix_b)
	{
		OT = (enOperatorsType)RandomNumber(1, 4);
	}

	Question.OT = OT;

	switch (DL)
	{
	case enDifficultyLevel::Easy:
		Question.Number1 = RandomNumber(1, 10);
		Question.Number2 = RandomNumber(1, 10);
		Question.CorrectAnswer = SimpleCalculator(Question.Number1, Question.Number2, Question.OT);
		Question.DL = DL;
		return Question;

	case enDifficultyLevel::Medium:
		Question.Number1 = RandomNumber(10, 50);
		Question.Number2 = RandomNumber(10, 50);
		Question.CorrectAnswer = SimpleCalculator(Question.Number1, Question.Number2, Question.OT);
		Question.DL = DL;
		return Question;

	case enDifficultyLevel::Hard:
		Question.Number1 = RandomNumber(50, 100);
		Question.Number2 = RandomNumber(50, 100);
		Question.CorrectAnswer = SimpleCalculator(Question.Number1, Question.Number2, Question.OT);
		Question.DL = DL;
		return Question;

	default:
		break;
	}


	return Question;
}

void GenerateQuizQuestion(stQuiz& Quiz)
{
	for (int i = 0; i < Quiz.HowManyQuestions; i++)
	{
		Quiz.QuesList[i] = GenerateQuestion(Quiz.DL, Quiz.OT);
	}
}

void PrintQuestion(stQuiz& Quiz , short NOQ)	
{
	cout << "\nQuestion [" << NOQ + 1 << "/" << Quiz.HowManyQuestions << "]\n" << endl;
	cout << Quiz.QuesList[NOQ].Number1 << endl;
	cout << Quiz.QuesList[NOQ].Number2 << " " << strOType(Quiz.QuesList[NOQ].OT) << endl;
	cout << "________________\n";
}

void AskAndCorrectQuestionListAnswer(stQuiz& Quiz)
{
	for (int i = 0; i < Quiz.HowManyQuestions; i++)
	{
		PrintQuestion(Quiz, i);
		Quiz.QuesList[i].UserAnswer = ReadNumber();
		CheckAnswers(Quiz, i);
	}

	Quiz.IsPass = (Quiz.NoRightAnswers >= Quiz.NoWrongAnswers);
}

void PrintQuizResult(stQuiz& Quiz)
{
	if (Quiz.IsPass)
	{
		cout << "\n___________________________________\n";
		cout << "          THE FINAL RESULT IS        \n";
		cout << "             YOU ARE PASS        \n";
		cout << "___________________________________\n";
	}
	else
	{
		cout << "\n___________________________________\n";
		cout << "          THE FINAL RESULT IS        \n";
		cout << "             YOU ARE FAIL        \n";
		cout << "___________________________________\n";
	}

	SetScreenColor(Quiz.IsPass);
	
	cout << "Number Of Questions You Answer : " << Quiz.HowManyQuestions << endl;
	cout << "Questions Difficulty Level     : " << strDLevel(Quiz.DL) << endl;
	cout << "Questions Operation Type       : " << strOType(Quiz.OT) << endl;
	cout << "Number Of Right Answers        : " << Quiz.NoRightAnswers << endl;
	cout << "Number Of Wrong Answers        : " << Quiz.NoWrongAnswers << endl;
}

stQuiz PlayMathGame()
{
	stQuiz Quiz;
	
	Quiz.HowManyQuestions = ReadNoQuestion();
	Quiz.DL = ReadQuestionLevel();
	Quiz.OT = ReadOperationType();

	GenerateQuizQuestion(Quiz);
	AskAndCorrectQuestionListAnswer(Quiz);
	PrintQuizResult(Quiz);

	return Quiz;
}

void ResetScreen()
{
	cout << system("cls");
	cout << system("color 0F");
}

void StartGame()
{
	char msg;
	do
	{
		ResetScreen();
		PlayMathGame();
		cout << "\n";
		cout << "Do You Want To Play Again ? ... Y/N" << endl;
		cin >> msg;

	} while (msg == 'Y' || msg == 'y');
}

int main()
{
	srand((unsigned)time(NULL));

	StartGame();

	return 0;
}
