/**
 * @file timerhandler.h
 * @author Ha Tran
 */

#ifndef TIMERHANDLER_H
#define TIMERHANDLER_H

#include <QObject>

class QTimer;
class QElapsedTimer;
class TimerHandler : public QObject {
  Q_OBJECT
public:
  explicit TimerHandler(QObject *parent);
  ~TimerHandler();
signals:
    void randomTimeout();
    void setReactionTime(QString);
public slots:
    void startRandomTimer();
    void startReactionTimer();
    void endReactionTimer();

private:
    QTimer *randomTimer = nullptr;
    QElapsedTimer *reactionTimer = nullptr;
};

#endif // TIMERHANDLER_H
