/**
 * @file reactiontimetest.h
 * @author Ha Tran
 */

#ifndef REACTIONTIMETEST_H
#define REACTIONTIMETEST_H

#include "enums.h"
#include <QDialog>

QT_BEGIN_NAMESPACE
namespace Ui { class Dialog; }
QT_END_NAMESPACE

class TimerHandler;

class ReactionTimeTest : public QDialog {
  Q_OBJECT

public:
  ReactionTimeTest(QWidget *parent = nullptr);
  ~ReactionTimeTest();

signals:
    void startTest();
    void inputReaction();
  public slots:
    void startButtonActions();
    void setStartButtonGreen();
    void reset();
    void setReactionTimeLineEdit(QString);

  private:
    Ui::Dialog *ui = nullptr;
    State m_currentState = State::Initial;
    TimerHandler *timerHandler = nullptr;
};
#endif // REACTIONTIMETEST_H
