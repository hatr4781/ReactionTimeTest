/**
 * @file reactiontimetest.cpp
 * @author Ha Tran
 */

#include "reactiontimetest.h"
#include "enums.h"
#include "timerhandler.h"
#include "ui_dialog.h"
#include <QMessageBox>

/**
 * @brief Constructor for ReactionTimeTest class.  This class focuses on
 * handling the user interactions within the application.
 */
ReactionTimeTest::ReactionTimeTest(QWidget *parent)
    : QDialog(parent), ui(new Ui::Dialog),
      timerHandler(new TimerHandler(this)) {
  ui->setupUi(this);
  ui->resetButton->setEnabled(false); // reset button is disabled on startup

  // set up connections
  connect(ui->startButton, &QAbstractButton::clicked, this,
          &ReactionTimeTest::startButtonActions);
  connect(this, &ReactionTimeTest::startTest, timerHandler,
          &TimerHandler::startRandomTimer);
  connect(timerHandler, &TimerHandler::randomTimeout, this,
          &ReactionTimeTest::setStartButtonGreen);
  connect(ui->resetButton, &QAbstractButton::clicked, this,
          &ReactionTimeTest::reset);
  connect(this, &ReactionTimeTest::inputReaction, timerHandler,
          &TimerHandler::endReactionTimer);
  connect(timerHandler, &TimerHandler::setReactionTime, this,
          &ReactionTimeTest::setReactionTimeLineEdit);
}

/**
 * @brief Performs specific actions when the push button is clicked, depending
 * on the current state of the application
 */
void ReactionTimeTest::startButtonActions() {
  switch (static_cast<State>(m_currentState)) {
  case State::Initial: {
    ui->resetButton->setEnabled(true); // allow reset once test started
    ui->startButton->setStyleSheet("background-color: red; color: black");
    ui->startButton->setText("Click button once \nit turns green");
    m_currentState = State::Started;
    emit startTest();
    break;
  }
  case State::Started: {
    // user clicked button too early
    reset();
    QMessageBox msgBox;
    msgBox.setText("Too Early!");
    msgBox.exec();
    break;
  }
  case State::Reaction: {
    emit inputReaction();
    ui->startButton->setStyleSheet("background-color: green");
    ui->startButton->setText("DONE!");
    m_currentState = State::End;
    break;
  }
  case State::End:
    // does nothing if user clicks button after test completed, requires hitting
    // reset
    break;
  }
}

/**
 * @brief Sets startButton color to green to initiate reaction from user
 */
void ReactionTimeTest::setStartButtonGreen() {
  // only set startButton to green if still in Started state, test is resetted
  // before randomTimeout
  if (m_currentState == State::Started) {
    ui->startButton->setStyleSheet("background-color: green");
    ui->startButton->setText("");
    m_currentState = State::Reaction;
  }
}

/**
 * @brief Resets UI for new reaction time test
 */
void ReactionTimeTest::reset() {
  ui->resetButton->setEnabled(false);
  ui->reactionTimeLineEdit->setText("");
  ui->startButton->setStyleSheet("background-color: grey");
  ui->startButton->setText("Click button to \nto Start Test");
  m_currentState = State::Initial;
}

/**
 * @brief Sets text for recorded reaction time
 * @param input - time recorded by timerHandler
 */
void ReactionTimeTest::setReactionTimeLineEdit(QString input) {
  ui->reactionTimeLineEdit->setText(QString(input + "ms"));
}

/**
 * @brief ReactionTimeTest::~ReactionTimeTest
 */
ReactionTimeTest::~ReactionTimeTest() { delete ui; }
