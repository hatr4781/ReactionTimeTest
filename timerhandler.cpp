/**
 * @file timerhandler.cpp
 * @author Ha Tran
 */

#include "timerhandler.h"
#include <QElapsedTimer>
#include <QRandomGenerator>
#include <QTimer>

/**
 * @brief Constructor for ReactionTimeTest class.  This class handles the
 * processing within the application.
 */
TimerHandler::TimerHandler(QObject *parent) : QObject{parent} {
  randomTimer = new QTimer(this);
  randomTimer->setSingleShot(true);

  reactionTimer = new QElapsedTimer();

  connect(randomTimer, &QTimer::timeout, this,
          &TimerHandler::randomTimeout); // this connection updates Ui to
                                         // initiate reaction
  connect(this, &TimerHandler::randomTimeout, this,
          &TimerHandler::startReactionTimer); // start counting reaction time
}

/**
 * @brief Starts timer with a random timeout value between 1.5 and 7 secs
 */
void TimerHandler::startRandomTimer() {
  int value = QRandomGenerator::global()->bounded(1500, 7000);
  randomTimer->start(value);
}

/**
 * @brief Starts the timer counting reaction time
 */
void TimerHandler::startReactionTimer() { reactionTimer->start(); }

/**
 * @brief Records the reaction time elapsed and invalidates timer
 */
void TimerHandler::endReactionTimer() {
  // accesing an invalid QElaspedTimer is undefined behavior
  if (reactionTimer->isValid()) {
    qint64 reactionTime = reactionTimer->elapsed();
    emit setReactionTime(QString::number(reactionTime));
    reactionTimer->invalidate();
  }
}

/**
 * @brief TimerHandler::~TimerHandler
 */
TimerHandler::~TimerHandler() {
  delete reactionTimer; // need to delete reactionTimer since it does not
                        // inherit QObject
}
