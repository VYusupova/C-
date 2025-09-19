#include <QApplication>
#include <QFont>
#include <QKeyEvent>
#include <QPainter>
#include <QString>
#include <QTimer>
#include <QWidget>

#include "../../include/library_spec.h"
#include "qt_front.h"

/**
 * @file qt_front.cpp
 * @brief qt представление
 */
class GameWindow : public QWidget {
  Q_OBJECT
 public:
  GameWindow(UserInputFunc userInput, UpdateCurrentStateFunc updateCurrentState,
             QWidget *parent = nullptr)
      : QWidget(parent),
        userInput_(userInput),
        updateCurrentState_(updateCurrentState),
        timer_(nullptr) {
    setFixedSize(600, 600);

    setStyleSheet(
        "QWidget {"
        "    background-color: #333333;"
        "    color: #FFFFFF;"
        "}");

    timer_ = new QTimer(this);
    connect(timer_, &QTimer::timeout, this, [this]() { updateGame(); });
    timer_->start(16);
  }

  ~GameWindow() {
    if (timer_) {
      timer_->stop();
      timer_->deleteLater();
      timer_ = nullptr;
    }
  }

 protected:
  void paintEvent(QPaintEvent *) override {
    QPainter painter(this);
    painter.setFont(QFont("Arial", 12));
    GameInfo_t game_info = updateCurrentState_();
    if (game_info.field && !game_info.pause)
      for (int i = 0; i < 20; ++i) {
        for (int j = 0; j < 10; ++j) {
          if (game_info.field[i][j]) {
            switch (game_info.field[i][j]) {
              case 1:
                painter.setBrush(Qt::red);
                break;
              case 2:
                painter.setBrush(Qt::green);
                break;
              case 3:
                painter.setBrush(Qt::yellow);
                break;
              default:
                painter.setBrush(Qt::black);
                break;
            }
            painter.fillRect(j * 20 + 20, i * 20 + 20, 20, 20, painter.brush());
          } else {
            painter.setBrush(Qt::black);
            painter.fillRect(j * 20 + 20, i * 20 + 20, 20, 20, Qt::black);
            painter.drawRect(j * 20 + 20, i * 20 + 20, 20, 20);
          }
        }
      }

    if (game_info.next) {
      painter.setPen(Qt::white);
      painter.drawText(250, 30, "Next:");
      for (int i = 0; i < 5; ++i) {
        for (int j = 0; j < 5; ++j) {
          if (game_info.next[i][j]) {
            painter.setBrush(Qt::red);
            painter.fillRect(j * 20 + 250, i * 20 + 40, 20, 20,
                             painter.brush());
          } else {
            painter.setBrush(Qt::black);
            painter.drawRect(j * 20 + 250, i * 20 + 40, 20, 20);
          }
        }
      }
    }

    painter.setPen(Qt::white);
    painter.drawText(
        250, 170, QString("Score: %1").arg(game_info.score, 6, 10, QChar('0')));
    painter.drawText(
        250, 190,
        QString("High Score: %1").arg(game_info.high_score, 6, 10, QChar('0')));
    painter.drawText(
        250, 210, QString("Speed: %1").arg(game_info.speed, 6, 10, QChar('0')));
    painter.drawText(250, 230, game_info.pause ? "Pause: ON" : "Pause: OFF");
    painter.drawText(250, 250, "Controls:");
    painter.drawText(250, 270, "WASD - MOVE");
    painter.drawText(250, 290, "SPACEBAR - ACTION");
    painter.drawText(250, 310, "Q - QUIT");
    painter.drawText(250, 330, "E - START");
    painter.drawText(250, 350, "P - PAUSE");
  }

  void keyPressEvent(QKeyEvent *event) override {
    UserAction_t action = Pause;
    switch (event->key()) {
      case Qt::Key_W:
        action = Up;
        break;
      case Qt::Key_S:
        action = Down;
        break;
      case Qt::Key_A:
        action = Left;
        break;
      case Qt::Key_D:
        action = Right;
        break;
      case Qt::Key_E:
        action = Start;
        break;
      case Qt::Key_Q:
        action = Terminate;
        break;
      case Qt::Key_P:
        action = Pause;
        break;
      case Qt::Key_Space:
        action = Action;
        break;
      default:
        return;
    }
    userInput_(action, false);
    update();
  }

 private:
  bool handleExitConditions(const GameInfo_t &game_info) {
    return (game_info.field == NULL && game_info.pause);
  }

 private:
  void updateGame() {
    if (!timer_) return;
    GameInfo_t game_info = updateCurrentState_();
    if (handleExitConditions(game_info)) {
      timer_->stop();
      QApplication::quit();
      return;
    }
    update();
  }

 private:
  UserInputFunc userInput_;
  UpdateCurrentStateFunc updateCurrentState_;
  QTimer *timer_;
};

extern "C" {
void startWindows(UserInputFunc userInput,
                  UpdateCurrentStateFunc updateCurrentState) {
  int argc = 0;
  char *argv[] = {nullptr};
  QApplication app(argc, argv);
  GameWindow window(userInput, updateCurrentState);
  window.show();
  app.exec();
}
}

#include "front.moc"
