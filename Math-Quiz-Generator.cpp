#include <iostream>
#include <cstdlib>
using namespace std;
enum enQuestionsLevel { EasyLevel = 1, MediumLevel = 2, HardLevel = 3, Mix = 4 };
enum enOperationType { Add = 1, Sub = 2, Mul = 3, Div = 4, MixOp = 5 };
struct stQuestion {
	int number1;
	int number2;
	enQuestionsLevel questionLevel;
	enOperationType operationType;
	int correctAnswer;
	int playerAnswer;
	bool answerResult = false;
};
struct stQuizz {
	stQuestion questionsList[100]; // imagine how this work :)
	short numberOfQuestion;
	enQuestionsLevel questionLevel;
	enOperationType OpType;
	short numberOfRightAnswers = 0;
	short numberOfWrongAnswers = 0;
	bool isPass = false;
};
short readHowManyQuestion() {
	short numberOfQuestion = 0;

	do {
		cout << "Enter How Many Question You Want? [1/90]: ";
		cin >> numberOfQuestion;
	} while (numberOfQuestion < 1 || numberOfQuestion > 90);

	return numberOfQuestion;
}
enQuestionsLevel readQuestionLevel() {
	short questionLevel;
	do {
		cout << "Enter Quiz Level [1]Easy - [2]Medium - [3]Hard - [4]Mix: ";
		cin >> questionLevel;
	} while (questionLevel < 1 || questionLevel > 4);

	return (enQuestionsLevel)questionLevel;
}
enOperationType readOpType() {
	short operationType = 0;

	do {
		cout << "Enter Quiz Operation Type [1]Add - [2]Sub - [3]Mul - [4]Div - [5]Mix: ";
		cin >> operationType;

	} while (operationType < 1 || operationType > 5);

	return (enOperationType)operationType;
}
int randomNumber(int from, int to) {
	int number = rand() % (to - from + 1) + from;
	return number;
}
int simpleCalculator(int number1, int number2, enOperationType opType) {

	switch (opType) {
	case enOperationType::Add:
		return number1 + number2;
		break;
	case enOperationType::Sub:
		return number1 - number2;
		break;
	case enOperationType::Mul:
		return number1 * number2;
		break;
	case enOperationType::Div:
		return number1 / number2;
		break;
	}
}
stQuestion generateQuesation(enQuestionsLevel questionLevel, enOperationType opType) {

	stQuestion question;

	if (questionLevel == enQuestionsLevel::Mix) {
		questionLevel = (enQuestionsLevel)randomNumber(1, 3);
	}
	if (opType == enOperationType::MixOp) {
		opType = (enOperationType)randomNumber(1, 4);
	}

	question.operationType = opType;
	question.questionLevel = questionLevel;

	switch (questionLevel) {
	case enQuestionsLevel::EasyLevel:
		question.number1 = randomNumber(2, 9);
		question.number2 = randomNumber(2, 9);

		question.correctAnswer = simpleCalculator(question.number1, question.number2, question.operationType);
		return question;

	case enQuestionsLevel::MediumLevel:
		question.number1 = randomNumber(10, 19);
		question.number2 = randomNumber(10, 19);

		question.correctAnswer = simpleCalculator(question.number1, question.number2, question.operationType);
		return question;

	case enQuestionsLevel::HardLevel:
		question.number1 = randomNumber(20, 30);
		question.number2 = randomNumber(20, 30);

		question.correctAnswer = simpleCalculator(question.number1, question.number2, question.operationType);
		return question;
	}
	return question;
}
void generateQuizQuestion(stQuizz& quizz) {

	for (short question = 0; question < quizz.numberOfQuestion; question++) {
		quizz.questionsList[question] = generateQuesation(quizz.questionLevel, quizz.OpType);
	}
}
string getOpTypeSympol(enOperationType opType) {
	switch (opType) {
	case enOperationType::Add:
		return "+";
	case enOperationType::Sub:
		return "-";
	case enOperationType::Mul:
		return "*";
	case enOperationType::Div:
		return "/";
	case enOperationType::MixOp:
		return "Mix";
	}
}
string getQuestionLevelText(enQuestionsLevel questionsLevel) {
	string questionsLevelArr[4] = { "Easy","Medium","Hard", "Mix" };
	return questionsLevelArr[questionsLevel - 1];
}
void printTheQuestion(stQuizz& quizz, short question) {
	cout << "\n";
	cout << "Question [" << question + 1 << "/" << quizz.numberOfQuestion << "]" << endl;
	cout << quizz.questionsList[question].number1 << endl;
	cout << quizz.questionsList[question].number2 << " ";
	cout << getOpTypeSympol(quizz.questionsList[question].operationType);
	cout << "\n______________";
	cout << "\n= ";
}
int readQuestionAnswer() {
	int number;
	cin >> number;
	return number;
}
void setScreenColor(bool answer) {
	if (answer)
		system("color 2F");
	else {
		system("color 4F");
		cout << "\a";
	}
}
void correctTheQuestionAnswer(stQuizz& quizz, short question) {
	if (quizz.questionsList[question].playerAnswer != quizz.questionsList[question].correctAnswer) {
		quizz.questionsList[question].answerResult = false;
		quizz.numberOfWrongAnswers++;

		cout << "Wrong Answer :(\n";
		cout << "The Right Answer is:";
		cout << quizz.questionsList[question].correctAnswer;
		cout << "\n";
	}
	else {
		quizz.questionsList[question].answerResult = true;
		quizz.numberOfRightAnswers++;

		cout << "Right Answer :)\n";
	}

	cout << endl;
	setScreenColor(quizz.questionsList[question].answerResult);
}
void askAndCorrectTheQuestionListAnswers(stQuizz& quizz) {

	for (short question = 0; question < quizz.numberOfQuestion; question++) {

		printTheQuestion(quizz, question);

		quizz.questionsList[question].playerAnswer = readQuestionAnswer();

		correctTheQuestionAnswer(quizz, question);
	}

	quizz.isPass = (quizz.numberOfRightAnswers >= quizz.numberOfWrongAnswers);
}
string getFinalResultText(bool result) {
	if (result)
		return "PASS :)";
	else
		return "FAIL :(";
}
void printQuizResult(stQuizz quizz) {

	cout << "\n_______________________________\n\n";
	cout << "   Final Result Is: " << getFinalResultText(quizz.isPass);
	cout << "\n_______________________________\n\n";

	cout << "Number Of Questions: " << quizz.numberOfQuestion << endl;
	cout << "Questions Level: " << getQuestionLevelText(quizz.questionLevel) << endl;
	cout << "Op Type: " << getOpTypeSympol(quizz.OpType) << endl;
	cout << "Number Of Right Answers:" << quizz.numberOfRightAnswers << endl;
	cout << "Number Of Wrong Answers:" << quizz.numberOfWrongAnswers << endl;
	cout << "_______________________________\n";

}
void playMathGame() {
	stQuizz quizz;
	quizz.numberOfQuestion = readHowManyQuestion();
	quizz.questionLevel = readQuestionLevel();
	quizz.OpType = readOpType();

	generateQuizQuestion(quizz);
	askAndCorrectTheQuestionListAnswers(quizz);
	printQuizResult(quizz);
}
void resetScreen() {
	system("cls");
	system("color 0F");
}
void startGame() {
	char playAgain = 'Y';

	do {
		resetScreen();
		playMathGame();

		cout << endl << "Do you want to play again? [Y/N]: ";
		cin >> playAgain;
	} while (playAgain == 'Y' || playAgain == 'y');
}
int main() {
	srand((unsigned)time(NULL));

	startGame();

	return 0;
}
