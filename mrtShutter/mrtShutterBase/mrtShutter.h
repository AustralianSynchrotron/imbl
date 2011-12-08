#ifndef MRTSHUTTER_H
#define MRTSHUTTER_H

#include "component.h"
#include <qtpv.h>
#include <QHash>
#include <QTimer>
#include <QTime>

class Shutter1A;

class MrtShutter : public Component {
  Q_OBJECT;

public:

  enum State {
    OPENED = 1,
    CLOSED = 0,
    BETWEEN = 2
  };

  enum ExposureMode {
    TIME=0,
    SOFT=1
//    HARD=2
  };



private:


  static const QString pvBaseName;
  static const QHash<QString,QEpicsPv*> pvs;
  static const QHash<QString,QEpicsPv*> init_static();
  static Shutter1A * shut1A; // needed to address the bug (see implimentation of start() member).

  /*
  QTimer dwellTimer;
  QTime startTime;
  */

  double _exposure;
  ExposureMode _expMode;
  double _cycle;
  int _repeats;
  double _minCycle;
  int _progress; // 0 - not running, >0 - current repetiotion
  State _state;
  bool _canStart;
  bool _valuesOK;

public:

  explicit MrtShutter(QObject * parent=0);

  inline double exposure() const {return _exposure;}
  inline ExposureMode exposureMode() const {return _expMode;}
  inline double cycle() const {return _cycle;}
  inline int repeats() const {return _repeats;}
  inline double minCycle() const {return _minCycle;}
  inline int progress() const {return _progress;}
  inline State state() const {return _state;}
  inline bool canStart() const {return _canStart;}
  inline bool valuesOK() const {return _valuesOK;}

public slots:

  void setOpened(bool opn);
  inline void open() {setOpened(true);}
  inline void close() {setOpened(false);}
  void start(bool beAwareOf1A=false);
  void trig(bool wait=false);
  void stop();
  void setExposure(double msec);
  void setExposureMode(ExposureMode val);
  void setCycle(double msec);
  void setRepeats(int val);

private slots:
  void actual_start(); // needed to avoid a buggy situation: see more desc in the implementation of start().

protected slots:

  void updateConnection();
  void updateExposure();
  void updateExposureMode();
  void updateCycle();
  void updateRepeats();
  void updateMinCycle();
  void updateProgress();
  void updateState();
  void updateCanStart();
  void updateValuesOK();


signals:

  void exposureChanged(double);
  void exposureModeChanged(MrtShutter::ExposureMode);
  void cycleChanged(double);
  void repeatsChanged(int);
  void minCycleChanged(double);
  void progressChanged(int);
  void stateChanged(MrtShutter::State);
  void canStartChanged(bool);
  void valuesOKchanged(bool);

};

#endif // MRTSHUTTER_H

