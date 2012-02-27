#ifndef MONO_H
#define MONO_H

#include "component.h"
#include <qcamotor.h>
#include <QHash>

class Mono : public Component {
  Q_OBJECT;

public:

  enum InOutPosition { INBEAM, OUTBEAM, BETWEEN, MOVING };
  enum Diffraction { Si111, Si311 };

  static const QPair<double,double> energyRange;
  static const double maxEnergy111 = 100.0; // keV
  static const double minEnergy311 = 31.0; // keV


private:

  static const double alpha = 14.75; // asymmetry angle (rad) "+" for 111 "-" for 311
  static const double zDist = 2.0; // desired Z-separation of crystals;
  static const double zOut = 40.0; // Z1 when the mono is out of the beam;

  enum Motors {
    Bragg1,
    Bragg2,
    Tilt1,
    Tilt2,
    Z1, // 0 when in beam
    Z2, // 0 when in beam
    Xdist,
    Bend1f,
    Bend2f,
    Bend1b,
    Bend2b
  };

  static const QHash<Motors,QCaMotor*> motors;
  static QHash<Motors,QCaMotor*> init_motors();
  double motorAngle(double enrg, int crystal, Diffraction diff);

  bool iAmMoving;
  double _energy; // kev
  Diffraction _diff;
  double _dBragg; // murad , displacement of the second crystal
  double _dX; // mm , X displacement of the stage
  double _dZ; // mm , Z displacement of the 2nd crystal
  double _tilt1; // mum
  double _tilt2; // mum
  double _bend1f; // mum
  double _bend2f; // mum
  double _bend1b; // mum
  double _bend2b; // mum
  InOutPosition _inBeam;

public:

  explicit Mono(QObject *parent = 0);

  inline double energy() const { return _energy; }
  inline Diffraction diffraction() const { return _diff; }
  inline double dBragg() const {return _dBragg;}
  inline double dX() const {return _dX;}
  inline double dZ() const {return _dZ;}
  inline double tilt1() {return _tilt1;}
  inline double tilt2() {return _tilt2;}
  inline double bend1front() {return _bend1f;}
  inline double bend2front() {return _bend2f;}
  inline double bend1back() {return _bend1b;}
  inline double bend2back() {return _bend2b;}
  inline InOutPosition inBeam() {return _inBeam;}

  inline bool isMoving() const { return iAmMoving; }
  inline QList<QCaMotor*> listMotors() const {return motors.values();}
  void wait_stop();

public slots:

  void setEnergy(double enrg, bool keepDBragg=true, bool keepDX=true);
  void setEnergy(double enrg, Mono::Diffraction diff, bool keepDBragg=true, bool keepDX=true);
  void setDBragg(double val);
  void setDX(double val);
  void setDZ(double val);
  void setTilt1(double val);
  void setTilt2(double val);
  void setBend1front(double val);
  void setBend2front(double val);
  void setBend1back(double val);
  void setBend2back(double val);
  void setInBeam(bool val);
  inline void moveIn() { setInBeam(true); }
  inline void moveOut() { setInBeam(false); }

  void stop();

private slots:

  void updateMotion();
  void updateConnection();

  void updateBragg1();
  void updateBragg2();
  void updateTilt1();
  void updateTilt2();
  void updateZ1();
  void updateZ2();
  void updateX();
  void updateBend1f();
  void updateBend2f();
  void updateBend1b();
  void updateBend2b();


signals:

  void motionChanged(bool);

  void energyChanged(double);
  void dBraggChanged(double);
  void dXChanged(double);
  void dZChanged(double);
  void tilt1Changed(double);
  void tilt2Changed(double);
  void bend1frontChanged(double);
  void bend2frontChanged(double);
  void bend1backChanged(double);
  void bend2backChanged(double);
  void inBeamChanged(Mono::InOutPosition);

};


double energy2bragg(double energy, Mono::Diffraction diff);


#endif // MONO_H
