#ifndef SHUTTER1A_H
#define SHUTTER1A_H

#include "component.h"
#include <qtpv.h>
#include <QTimer>

class Shutter1A : public Component {
  Q_OBJECT;

public:

  enum State {
    OPENED = 1,
    CLOSED = 0,
    BETWEEN = 2
  };

  static const QString pvBaseName;
  static const int transitionTime = 2000; // msec

protected:

  static const int relaxTime;
  QTimer timer;

  State st;
  bool enabled;

  static QEpicsPv * opnSts;
  static QEpicsPv * clsSts;
  static QEpicsPv * opnCmd;
  static QEpicsPv * clsCmd;
  static QEpicsPv * enabledSts;
  static QEpicsPv * disabledSts;

public:

  explicit Shutter1A(QObject *parent = 0);
  ~Shutter1A();

  inline State state() const {return st;}
  inline bool isRelaxing() const {return timer.isActive();}
  inline bool isEnabled() const {return enabled;}

  static State stateS();
  static bool setOpenedS(bool opn, bool wait=false);

public slots:

  bool open(bool wait=false);
  bool close(bool wait=false);
  bool setOpened(bool opn, bool wait=false);

signals:

  void stateChanged(Shutter1A::State st);
  void relaxChanged();
  void opened();
  void closed();
  void enabledChanged(bool isenabled);

protected slots:

  void updateState();
  void updateConnection();
  void updateEnabled();

};

#endif // SHUTTER1A_H
