#include <iostream>
#include<cstdlib>
#include<time.h>
using namespace std;
enum enquestionslevel { easylevel = 1, medlevel = 2, hardlevel = 3, mix = 4 };
enum enoperationtype{add=1,sub=2,mult=3,Div=4,mixop=5};

string getoptypesymbol(enoperationtype optype)
{
	switch (optype)
	{
	case add:
		return "+";
		break;
	case sub:
		return "-";
		break;
	case mult:
		return "x";
		break;
	case Div:
		return "/";
		break;
	default:
		return "Mix";
		break;
	}
}
string getquestionleveltext(enquestionslevel questionlevel)
{
	string arrquestionleveltaxt[4] = { "Easy","Med","Hard","Mix" };
	return arrquestionleveltaxt[questionlevel - 1];
}
int randomnumber(int from, int to)
{
	int random = rand() % (to - from + 1) + from;
	return random;
}
void setscreencolor(bool rigth)
{
	if (rigth)
		system("color 2f");
	else
	{
		system("color 6f");
		cout << "\a";
	}
}
short readhowmanyquestions()
{
	short numberofquestions;
	do
	{
		cout << "How many Questions do you want to answer ? ";
		cin >> numberofquestions;
	} while (numberofquestions < 1 || numberofquestions>10);

	return numberofquestions;
}
enquestionslevel readquestionlevel()
{
	short questinolevel = 0;
	do
	{
		cout << "Enter questions level [1]Easy,[2] Med,[3] Hard, [4]Mix ? ";
		cin >> questinolevel;
	} while (questinolevel < 1 || questinolevel>4);
	return (enquestionslevel)questinolevel;
}
enoperationtype readtype()
{
	short optype;
	do
	{
		cout << "Enter operation type [1] add, [2] sub, [3] mul, [4] div, [5] Mix ? ";
		cin >> optype;
	} while (optype < 1 || optype>5);
	return (enoperationtype)optype;
}

struct stquestion
{
	int number1 = 0;
	int number2 = 0;
	enoperationtype operationtype;
	enquestionslevel questionlevel;
	int correctanswer = 0;
	int playeranswer = 0;
	bool answerresult = false;
};
struct stquizz
{
	stquestion questionlist[100];
	short numberofquestions;
	enquestionslevel questionslevel;
	enoperationtype optype;
	short numberofwrongwnswers = 0;
	short numberofrigthanswers = 0;
	bool ispass = false;
};

int simplecalculator(int number1, int number2, enoperationtype optype)
{
	switch (optype)
	{
	case add:
		return number1 + number2;
		break;
	case sub:
		return number1 - number2;
		break;
	case mult:
		return number1 * number1;
		break;
	case Div:
		return number1 / number2;
		break;
	default:
		return number1 + number2;
		break;
	}
}

enoperationtype getrandomoperationtype()
{
	int op = randomnumber(1, 4);
	return (enoperationtype)op;
}

stquestion generatequestion(enquestionslevel questionlevel, enoperationtype optype)
{  
	stquestion question;
	if (questionlevel == enquestionslevel::mix)
	{
		questionlevel = (enquestionslevel)randomnumber(1, 3);
	}
	if (optype == enoperationtype::mixop)
	{
		optype = getrandomoperationtype();//(enoperationtype)randomnumber(1, 4);
	}
	question.operationtype = optype;
	switch (questionlevel)
	{
	case easylevel:
		question.number1 = randomnumber(1, 10);
		question.number2 = randomnumber(1, 10);

		question.correctanswer = simplecalculator(question.number1, question.number2, question.operationtype);

		question.questionlevel = questionlevel;
		return question;
		break;
	case medlevel:
		question.number1 = randomnumber(10, 50);
		question.number2 = randomnumber(10, 50);

		question.correctanswer = simplecalculator(question.number1, question.number2, question.operationtype);
		question.questionlevel = questionlevel;
		return question;
		break;
	case hardlevel:
		question.number1 = randomnumber(50, 100);
		question.number2 = randomnumber(50, 100);

		question.correctanswer = simplecalculator(question.number1, question.number2, question.operationtype);
		question.questionlevel = questionlevel;
		return question;
		break;
	}
	return question;
}

void generatequizzquestions(stquizz & quizz)
{
	for (short question = 0; question < quizz.numberofquestions; question++)
	{
		quizz.questionlist[question] = generatequestion(quizz.questionslevel, quizz.optype);
	}
}

int readquestionanswer()
{
	int answer = 0;
	cin >> answer;
	return answer;
}

void printthequestion(stquizz quizz, short questionnumber)
{
	cout << "\n";
	cout << "Question [" << questionnumber + 1 << "/" << quizz.numberofquestions << "]\n\n";
	cout << quizz.questionlist[questionnumber].number1 << endl;
	cout << quizz.questionlist[questionnumber].number2 << " ";
	cout << getoptypesymbol(quizz.questionlist[questionnumber].operationtype);
	cout << "\n-------------" << endl;
}

void correctthequestionanswer(stquizz &quizz, short questionnumber)
{
	if (quizz.questionlist[questionnumber].playeranswer != quizz.questionlist[questionnumber].correctanswer)
	{
		quizz.questionlist[questionnumber].answerresult = false;
		quizz.numberofwrongwnswers++;

		cout << "Wrong Answer :-( \n";
		cout << "The rigth answer is : ";
		cout << quizz.questionlist[questionnumber].correctanswer;
		cout << "\n";
	}
	else
	{
		quizz.questionlist[questionnumber].answerresult = true;
		quizz.numberofrigthanswers++;

		cout << "Rigth Answer :-) \n";
	}
	cout << endl;
	setscreencolor(quizz.questionlist[questionnumber].answerresult);
}

void askandcorrectquestionlistanswers(stquizz& quizz)
{
	for (short questionnumber = 0; questionnumber < quizz.numberofquestions; questionnumber++)
	{
		printthequestion(quizz, questionnumber);
		quizz.questionlist[questionnumber].playeranswer = readquestionanswer();
		correctthequestionanswer(quizz, questionnumber);
	}
	quizz.ispass = (quizz.numberofrigthanswers >= quizz.numberofwrongwnswers);
}

string getfinalresuttext(bool pass)
{
	if (pass)
		return "Pass :-)";
	else
		return "Fail :-(";
}

void prentquizzresults(stquizz quizz)
{

	cout << endl;
	cout << "----------------------------------------\n\n";
	cout << "Final Result is " << getfinalresuttext(quizz.ispass)<<endl;
	cout << "----------------------------------------\n\n";
	cout << "Number of question     : " << quizz.numberofquestions << endl;
	cout << "Question level         : " << getquestionleveltext(quizz.questionslevel) << endl;
	cout << "OPtype                 : " << getoptypesymbol(quizz.optype) << endl;
	cout << "Number of right Answer : " << quizz.numberofrigthanswers << endl;
	cout << "Number of wrong Answer : " << quizz.numberofwrongwnswers << endl;
	cout << "-----------------------------------------\n";
}

void playmathgame()
{
	stquizz quizz;

	quizz.numberofquestions = readhowmanyquestions();
	quizz.questionslevel = readquestionlevel();
	quizz.optype = readtype();
	
	generatequizzquestions(quizz);
	askandcorrectquestionlistanswers(quizz);
    prentquizzresults(quizz);
}

void resetscreen()
{
	system("cls");
	system("color af");
}

void startgame()
{
	char playagain = 'Y';
	do
	{
		resetscreen();
		playmathgame();

		cout << endl << "Do you want to play again ? Y/N ?";
		cin >> playagain;
	} while (playagain == 'Y' || playagain == 'y');
}

int main()
{
	srand((unsigned)time(NULL));

	startgame();
}