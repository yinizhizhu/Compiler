#include "gui.h"

compiler::compiler(QWidget *parent)
	: QWidget(parent)
{
	QGridLayout *grid = new QGridLayout;

	lex = new QPushButton(tr("&Lex"));
	lex->setDisabled(false);
	connect(lex, SIGNAL(clicked()), this, SLOT(doLex()));

	synSem = new QPushButton(tr("&SynSem"));
	synSem->setDisabled(true);
	connect(synSem, SIGNAL(clicked()), this, SLOT(doSynSem()));

	pro = new QPushButton(tr("&Process"));
	pro->setDisabled(true);
	connect(pro, SIGNAL(clicked()), this, SLOT(showPro()));

	three = new QPushButton(tr("&ThreeAddress"));
	three->setDisabled(true);
	connect(three, SIGNAL(clicked()), this, SLOT(showThree()));

	middle = new QPushButton(tr("&MiddelCode"));
	middle->setDisabled(true);
	connect(middle, SIGNAL(clicked()), this, SLOT(showMiddle()));

	editor = new QTextEdit();
	setContent("", "sample.txt");

	grid->addWidget(lex, 0, 0);
	grid->addWidget(synSem, 0, 1);
	grid->addWidget(pro, 0, 2);
	grid->addWidget(three, 0, 3);
	grid->addWidget(middle, 0, 4);
	grid->addWidget(editor, 1, 0, 1, 5);
	grid->setColumnStretch(6, 1);
	grid->setContentsMargins(50, 50, 50, 50);
	setLayout(grid);
	setWindowTitle(tr("Compiler&Lee"));
	resize(480, 600);
}

void compiler::setContent(char *guide, char *fileName)
{
	int move = 0;
	char tmp, *content = new char[N];
	if (content == NULL)
	{
		editor->setText("The room is not enough for content!\n");
		return;
	}
	for (int i = 0; i < strlen(guide); i++)
		content[move++] = guide[i];
	FILE *in = fopen(fileName, "r");
	do{
		tmp = fgetc(in);
		if (tmp == EOF)
			content[move] = '\0';
		else
			content[move++] = tmp;
	} while (tmp != EOF);
	editor->setText(content);
	delete[]content;
	fclose(in);
	return;
}

void compiler::doLex()
{
	setContent("The result of lex:\n", "inputSyn.txt");
	lex->setDisabled(true);
	synSem->setDisabled(false);
	return;
}

void compiler::doSynSem()
{
	editor->setText("Accpet!\n");
	synSem->setDisabled(true);
	pro->setDisabled(false);
	three->setDisabled(false);
	middle->setDisabled(false);
	return;
}

void compiler::showPro()
{
	setContent("", "process.txt");
	return;
}

void compiler::showThree()
{
	setContent("", "threeCode.txt");
	return;
}

void compiler::showMiddle()
{
	setContent("", "middleCode.txt");
	return;
}