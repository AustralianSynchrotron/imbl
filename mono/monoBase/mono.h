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
  static const double maxEnergy111 = 150.0; // keV
  static const double minEnergy311 = 31.0; // keV
  static const QString pvBaseName;

  enum Motors {
    Bragg1,
    Bragg2,
    Tilt1,
    Tilt2,
    Z1, // 0 when in beam
    Z2, // zDist when in beam
    Xdist,
    Bend1ob,
    Bend2ob,
    Bend1ib,
    Bend2ib
  };

  static const QHash<Motors,QCaMotor*> motors;

  static const double standardZseparation = 20.0; // standard Z-separation of crystals;
  static const double zOut = -45.0; // Z1 when the mono is out of the beam;
  static const double alpha = 14.75; // asymmetry angle (deg) "+" for 111 "-" for 311
  // OLD CRYSTALS // static const double alpha = -4.652; // asymmetry angle (deg)
  static const double source2monoDistance = 16.307;//m

  static const double benderGapH = 0.3; // halph bender gap
  static const double bend1rt = 58.112;
  static const double bend2rt = 62.2;
  // static const double bend1BraggCorrection = 0.00373; // deg(correction) / mm(tip travel)
  // static const double bend2BraggCorrection = 0.00326; // deg(correction) / mm(tip travel)
  static const double bend1BraggCorrection = 0.0; // no correction
  static const double bend2BraggCorrection = 0.0; // no correction


private:

  double bendR2X(double curvature, Motors mot);
  double bendX2R(Motors mot);
  double benderCorrection(Motors mot);
  double benderBraggCorrection();


  static QHash<Motors,QCaMotor*> init_motors();
  static const QHash < Motors, QPair<double,double> > travelRanges;
  static QHash< Motors, QPair<double,double> > init_ranges();

  double motorAngle(double enrg, int crystal, Diffraction diff);

  bool iAmMoving;
  double _energy; // kev
  Diffraction _diff;
  double _dBragg; // displacement of the second crystal
  double _dX; // mm , X displacement of the stage
  double _zSeparation; // mm , Z nominal separation of the 2nd crystal
  double _dZ; // mm , The difference between Z nominal separation and actual Z.
  double b1ob;
  double b1ib;
  double b2ob;
  double b2ib;
  InOutPosition _inBeam;

  static QEpicsPv * Bragg1Enc;
  static QEpicsPv * Bragg2Enc;
  static QEpicsPv * XdistEnc;
  static QEpicsPv * Bragg1EncLoss;
  static QEpicsPv * Bragg2EncLoss;
  static QEpicsPv * XdistEncLoss;
  QHash<Motors,bool> calibratedMotors;
  bool incalibration;

public:

  explicit Mono(QObject *parent = 0);

  inline double energy() const {return _energy; }
  inline Diffraction diffraction() const {return _diff; }
  inline double dBragg() const {return _dBragg;}
  inline double dX() const {return _dX;}
  inline double zSeparation() const {return _zSeparation;}
  inline double zTweak() const {return _dZ;}
  inline double tilt1() const {return motors[Tilt1]->getUserPosition();}
  inline double tilt2() const {return motors[Tilt2]->getUserPosition();}
  inline double bend1ob() const {return b1ob;}
  inline double bend2ob() const {return b2ob;}
  inline double bend1ib() const {return b1ib;}
  inline double bend2ib() const {return b2ib;}
  inline InOutPosition inBeam() const {return _inBeam;}
  inline const QHash<Motors,bool> calibrated() const {return calibratedMotors;}
  bool isCalibrated();

  inline bool isMoving() const { return iAmMoving; }
  void wait_stop();

public slots:

  void setEnergy(double enrg, bool keepDBragg=true, bool keepDX=true);
  void setEnergy(double enrg, Mono::Diffraction diff, bool keepDBragg=true, bool keepDX=true);
  void setDBragg(double val);
  void setDX(double val);
  void setZseparation(double val, bool keepZ, bool keepX);
  void setDZ(double val);
  void setTilt1(double val);
  void setTilt2(double val);
  void setBend1ob(double val);
  void setBend2ob(double val);
  void setBend1ib(double val);
  void setBend2ib(double val);
  void setInBeam(bool val);
  inline void makeConsistent() { setEnergy(energy(), diffraction()); }
  inline void moveIn() { setInBeam(true); }
  inline void moveOut() { setInBeam(false); }
  void calibrate( const QList<Mono::Motors> & motors2calibrate = QList<Mono::Motors>() );

  void stop();

private slots:

  void updateMotion();
  void updateConnection();
  void updateDBragg();
  void updateEnergy();
  void updateTilt1();
  void updateTilt2();
  void updateZ1();
  void updateZ2();
  void updateX();
  void updateBend1ob();
  void updateBend2ob();
  void updateBend1ib();
  void updateBend2ib();
  void updateCalibration();

signals:

  void motionChanged(bool);

  void energyChanged(double);
  void dBraggChanged(double);
  void dXChanged(double);
  void zSeparationChanged(double);
  void dZChanged(double);
  void tilt1Changed(double);
  void tilt2Changed(double);
  void bend1obChanged(double);
  void bend2obChanged(double);
  void bend1ibChanged(double);
  void bend2ibChanged(double);
  void inBeamChanged(Mono::InOutPosition);
  void calibrationChanged(bool);

};


double energy2bragg(double energy, Mono::Diffraction diff);


#endif // MONO_H










