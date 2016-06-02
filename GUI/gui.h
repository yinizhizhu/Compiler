#ifndef GUI_H
#define GUI_H

#include <QMainWindow>
#include <QtWidgets>

#define N 300000

class compiler : public QWidget
{
	Q_OBJECT
public:
	compiler(QWidget *parent = 0);
	void setContent(char *guide, char *fileName);
	private slots:
	void doLex();
	void doSynSem();
	void showPro();
	void showThree();
	void showMiddle();
private:
	QPushButton *lex;
	QPushButton *synSem;
	QPushButton *pro;
	QPushButton *three;
	QPushButton *middle;
	QTextEdit *editor;
};

#endif // LEARNQT5_H
