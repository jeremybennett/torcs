////////////////////////////////////////////////////////////////////////////
//
// K1999.cpp
//
// car driver for TORCS
// (c) Remi Coulom
// March 2000
//
// This program is free software; you can redistribute it and/or modify
// it under the terms of the GNU General Public License as published by
// the Free Software Foundation; either version 2 of the License, or
// (at your option) any later version.
//
////////////////////////////////////////////////////////////////////////////
#include <iostream.h>
#include <iomanip.h>
#include <math.h>
#include <stdlib.h>
#include <fstream.h>
#include <string.h>

#include "tgf.h" 
#include "track.h" 
#include "car.h" 
#include "raceman.h" 
#include "robot.h" 
#include "robottools.h"

////////////////////////////////////////////////////////////////////////////
// Parameters
////////////////////////////////////////////////////////////////////////////

//
// These first parameters depend on your car's tuning
//
static const char * const szSettings = "drivers/K1999/settings.xml";
static const double TireAccel1 = 13.20;
static const double WingRInverse = 0.0029;
static const double MaxBrake = 13.00;

//
// These parameters are for the computation of the path
//
static const int Iterations = 100;     // Number of smoothing operations
static const double DivLength = 1.0;   // Length of path elements in meters
 
static const double SecurityR = 100.0; // Security radius
static double SideDistExt = 1.4; // Security distance wrt outside
static double SideDistInt = 1.2; // Security distance wrt inside          

//
// Debugging options
//
//#define VERBOSE
//#define DOLOG
//#define DRAWPATH

#ifdef DOLOG
ofstream ofsLog("K1999.log", ios::out);
#define LOG(x) do {ofsLog << (x) << ' ';} while(0)
#else
#define LOG(x)
#endif

/////////////////////////////////////////////////////////////////////////////
// Some utility macros and functions
/////////////////////////////////////////////////////////////////////////////
#ifdef VERBOSE
#define OUTPUT(x) do {(cout << "K1999: " << x << '\n').flush();} while(0)
#else
#define OUTPUT(x)
#endif
 
#define FATAL(x) do{if (x){OUTPUT("Fatal error: " << #x); exit(1);}}while(0)

static double Mag(double x, double y)
{
 return sqrt(x * x + y * y);
}
 
static double Min(double x1, double x2)
{
 if (x1 < x2)
  return x1;
 else
  return x2;
}
 
static double Max(double x1, double x2)
{
 if (x1 < x2)
  return x2;
 else
  return x1;
}
 
////////////////////////////////////////////////////////////////////////////
// Global data
////////////////////////////////////////////////////////////////////////////
const int MaxSegments = 1000;
const int MaxDivs = 20000;
 
static int Divs;
static int Segs;
static double Width;
static double Length;
static double tSegDist[MaxSegments];
static int tSegIndex[MaxSegments];
static double tElemLength[MaxSegments];
static double tx[MaxDivs];
static double ty[MaxDivs];
static double tDistance[MaxDivs];
static double tRInverse[MaxDivs];
static double tMaxSpeed[MaxDivs];
static double tSpeed[MaxDivs];
static double txLeft[MaxDivs];
static double tyLeft[MaxDivs];
static double txRight[MaxDivs];
static double tyRight[MaxDivs];
static double tLane[MaxDivs];
static double tFriction[MaxDivs];

static tTrack *ptrack;
static double wheeltrack;
static int fDirt = 0;

/////////////////////////////////////////////////////////////////////////////
// Update tx and ty arrays
/////////////////////////////////////////////////////////////////////////////
static void UpdateTxTy(int i)
{
 tx[i] = tLane[i] * txRight[i] + (1 - tLane[i]) * txLeft[i];
 ty[i] = tLane[i] * tyRight[i] + (1 - tLane[i]) * tyLeft[i];
}                                                                               

/////////////////////////////////////////////////////////////////////////////
// Draw a path (use gnuplot)
/////////////////////////////////////////////////////////////////////////////
#ifdef DRAWPATH
static void DrawPath(ostream &out)
{
 for (int i = 0; i <= Divs; i++)
 {
  int j = i % Divs;
  out << txLeft[j] << ' ' << tyLeft[j] << ' ';
  out << tx[j] << ' ' << ty[j] << ' ';
  out << txRight[j] << ' ' << tyRight[j] << '\n';
 }
 out << '\n';
}
#endif

/////////////////////////////////////////////////////////////////////////////
// Set segment info
/////////////////////////////////////////////////////////////////////////////
static void SetSegmentInfo(const tTrackSeg *pseg, double d, int i, double l)
{
 if (pseg)
 {
  FATAL(pseg->id >= MaxSegments);
  tSegDist[pseg->id] = d;
  tSegIndex[pseg->id] = i;
  tElemLength[pseg->id] = l;
  if (pseg->id >= Segs)
   Segs = pseg->id + 1;
 }
}

/////////////////////////////////////////////////////////////////////////////
// Split the track into small elements
// ??? constant width supposed
/////////////////////////////////////////////////////////////////////////////
static void SplitTrack()                                                        
{
 Segs = 0;
 OUTPUT("Analyzing track...");
 const tTrackSeg *psegCurrent = ptrack->seg;

 double Distance = 0;
 double Angle = psegCurrent->angle[TR_ZS];
 double xPos = 0;
 double yPos = 0;

 int i = 0;

 do
 {
  int Divisions = 1 + int(psegCurrent->length / DivLength);
  double Step = psegCurrent->length / Divisions;

  SetSegmentInfo(psegCurrent, Distance + Step, i, Step);
#if 0
  SetSegmentInfo(psegCurrent->lalt, Distance + Step, i, Step);
  SetSegmentInfo(psegCurrent->ralt, Distance + Step, i, Step);
  SetSegmentInfo(psegCurrent->lside, Distance + Step, i, Step);
  SetSegmentInfo(psegCurrent->rside, Distance + Step, i, Step);
#endif

  for (int j = Divisions; --j >= 0;)
  {
   double cosine = cos(Angle);
   double sine = sin(Angle);
   
   if (psegCurrent->type == TR_STR)
   {
    xPos += cosine * Step;
    yPos += sine * Step;
   }
   else
   {
    double r = psegCurrent->radius;
    double Theta = psegCurrent->arc / Divisions;
    double L = 2 * r * sin(Theta / 2);
    double x = L * cos(Theta / 2);
    double y;
    if (psegCurrent->type == TR_LFT)
    {
     Angle += Theta;
     y = L * sin(Theta / 2);
    }
    else
    {
     Angle -= Theta;
     y = -L * sin(Theta / 2);
    }
    xPos += x * cosine - y * sine;
    yPos += x * sine + y * cosine;
   }

   double dx = -psegCurrent->width * sin(Angle) / 2;
   double dy = psegCurrent->width * cos(Angle) / 2;
   txLeft[i] = xPos + dx;
   tyLeft[i] = yPos + dy;
   txRight[i] = xPos - dx;
   tyRight[i] = yPos - dy;
   tLane[i] = 0.5;
   tFriction[i] = psegCurrent->kFriction;
   if (tFriction[i] < 1) // ??? ugly trick for dirt
   {
    tFriction[i] *= 0.70;
    fDirt = 1;
    SideDistInt = -1.0;
    SideDistExt = 1.0;
   }
   UpdateTxTy(i);

   Distance += Step;
   tDistance[i] = Distance;
   i++;
   FATAL(i > MaxDivs);
  }

  psegCurrent = psegCurrent->next;
 }
 while (psegCurrent != ptrack->seg);

 Divs = i - 1;
 Width = psegCurrent->width;
 Length = Distance;

 OUTPUT("Position of the last point (should be (0, 0))");
 OUTPUT("xPos = " << xPos);
 OUTPUT("yPos = " << yPos);
 OUTPUT("Number of path elements : " << Divs);
 OUTPUT("Segs = " << Segs);
 OUTPUT("Track length : " << Length);
}
 
/////////////////////////////////////////////////////////////////////////////
// Compute the inverse of the radius
/////////////////////////////////////////////////////////////////////////////
static double GetRInverse(int prev, double x, double y, int next)
{
 double x1 = tx[next] - x;
 double y1 = ty[next] - y;
 double x2 = tx[prev] - x;
 double y2 = ty[prev] - y;
 double x3 = tx[next] - tx[prev];
 double y3 = ty[next] - ty[prev];
 
 double det = x1 * y2 - x2 * y1;
 double n1 = x1 * x1 + y1 * y1;
 double n2 = x2 * x2 + y2 * y2;
 double n3 = x3 * x3 + y3 * y3;
 double nnn = sqrt(n1 * n2 * n3);
 
 return 2 * det / nnn;
}
                                                                                /////////////////////////////////////////////////////////////////////////////
// Change lane value to reach a given radius
/////////////////////////////////////////////////////////////////////////////
static void AdjustRadius(int prev,
                         int i,
                         int next,
                         double TargetRInverse,
                         double Security = 0)
{
 double OldLane = tLane[i];
 
 //
 // Start by aligning points for a reasonable initial lane
 //
 tLane[i] = (-(ty[next] - ty[prev]) * (txLeft[i] - tx[prev]) +
              (tx[next] - tx[prev]) * (tyLeft[i] - ty[prev])) /
            ( (ty[next] - ty[prev]) * (txRight[i] - txLeft[i]) -
              (tx[next] - tx[prev]) * (tyRight[i] - tyLeft[i]));
 if (tLane[i] < -0.2)
  tLane[i] = -0.2;
 else if (tLane[i] > 1.2)
  tLane[i] = 1.2;
 UpdateTxTy(i);
 
 //
 // Newton-like resolution method
 //
 const double dLane = 0.0001;
 
 double dx = dLane * (txRight[i] - txLeft[i]);
 double dy = dLane * (tyRight[i] - tyLeft[i]);
 
 double dRInverse = GetRInverse(prev, tx[i] + dx, ty[i] + dy, next);
 
 if (dRInverse > 0.000000001)
 {
  tLane[i] += (dLane / dRInverse) * TargetRInverse;
 
  double ExtLane = (SideDistExt + Security) / Width;
  double IntLane = (SideDistInt + Security) / Width;
  if (ExtLane > 0.5)
   ExtLane = 0.5;
  if (IntLane > 0.5)
   IntLane = 0.5;
 
  if (TargetRInverse >= 0.0)
  {
   if (tLane[i] < IntLane)
    tLane[i] = IntLane;
   if (1 - tLane[i] < ExtLane)
   {
    if (1 - OldLane < ExtLane)
     tLane[i] = Min(OldLane, tLane[i]);
    else
     tLane[i] = 1 - ExtLane;
   }
  }
  else
  {
   if (tLane[i] < ExtLane)
   {
    if (OldLane < ExtLane)
     tLane[i] = Max(OldLane, tLane[i]);
    else
     tLane[i] = ExtLane;
   }
   if (1 - tLane[i] < IntLane)
    tLane[i] = 1 - IntLane;
  }
 }
 
 UpdateTxTy(i);
}

/////////////////////////////////////////////////////////////////////////////
// Smooth path
/////////////////////////////////////////////////////////////////////////////
static void Smooth(int Step)
{
 int prev = ((Divs - Step) / Step) * Step;
 int prevprev = prev - Step;
 int next = Step;
 int nextnext = next + Step;
 
 for (int i = 0; i <= Divs - Step; i += Step)
 {
  double ri0 = GetRInverse(prevprev, tx[prev], ty[prev], i);
  double ri1 = GetRInverse(i, tx[next], ty[next], nextnext);
  double lPrev = Mag(tx[i] - tx[prev], ty[i] - ty[prev]);
  double lNext = Mag(tx[i] - tx[next], ty[i] - ty[next]);

//  if (fabs(ri1) < fabs(ri0))
//   lNext *= 1.05;

  double TargetRInverse = (lNext * ri0 + lPrev * ri1) / (lNext + lPrev);
 
  double Security = lPrev * lNext / (8 * SecurityR);
  AdjustRadius(prev, i, next, TargetRInverse, Security);
 
  prevprev = prev;
  prev = i;
  next = nextnext;
  nextnext = next + Step;
  if (nextnext > Divs - Step)
   nextnext = 0;
 }
}

/////////////////////////////////////////////////////////////////////////////
// Interpolate between two control points
/////////////////////////////////////////////////////////////////////////////
static void StepInterpolate(int iMin, int iMax, int Step)
{
 int next = (iMax + Step) % Divs;
 if (next > Divs - Step)
  next = 0;
 
 int prev = (((Divs + iMin - Step) % Divs) / Step) * Step;
 if (prev > Divs - Step)
  prev -= Step;
 
 double ir0 = GetRInverse(prev, tx[iMin], ty[iMin], iMax % Divs);
 double ir1 = GetRInverse(iMin, tx[iMax % Divs], ty[iMax % Divs], next);
 for (int k = iMax; --k > iMin;)
 {
  double x = double(k - iMin) / double(iMax - iMin);
  double TargetRInverse = x * ir1 + (1 - x) * ir0;
  AdjustRadius(iMin, k, iMax % Divs, TargetRInverse);
 }
}
 
/////////////////////////////////////////////////////////////////////////////
// Calls to StepInterpolate for the full path
/////////////////////////////////////////////////////////////////////////////
static void Interpolate(int Step)
{
 if (Step > 1)
 {
  int i;
  for (i = Step; i <= Divs - Step; i += Step)
   StepInterpolate(i - Step, i, Step);
  StepInterpolate(i - Step, Divs, Step);
 }
}

////////////////////////////////////////////////////////////////////////////
// Function declaration 
////////////////////////////////////////////////////////////////////////////
static void initTrack(int index, tTrack* track, void **carParmHandle,
tSituation *p); 
static void drive(int index, tCarElt* car, tSituation *s); 
static void newrace(int index, tCarElt* car, tSituation *s); 
static int InitFuncPt(int index, void *pt); 

////////////////////////////////////////////////////////////////////////////
// Module entry point  
////////////////////////////////////////////////////////////////////////////
extern "C" int K1999(tModInfo *modInfo) 
{ 
 OUTPUT("modInfo");
 modInfo->name    = "K1999";    // name of the module (short)
 modInfo->desc    = "K1999";    // description of the module
 modInfo->fctInit = InitFuncPt; // init function
 modInfo->gfId    = ROB_IDENT;  // supported framework version
 modInfo->index   = 1;          // same as in XML file
 return 0; 
} 

////////////////////////////////////////////////////////////////////////////
// Module Initialization : give addresses of functions
////////////////////////////////////////////////////////////////////////////
static int InitFuncPt(int index, void *pt) 
{ 
 OUTPUT("InitFuncPt");
 tRobotItf *itf = (tRobotItf *)pt; 
 itf->rbNewTrack = initTrack;
 itf->rbNewRace = newrace; 
 itf->rbDrive = drive;
 itf->index = index; 
 return 0; 
} 

////////////////////////////////////////////////////////////////////////////
// New track
////////////////////////////////////////////////////////////////////////////
static void initTrack(int index, tTrack* track, void **carParmHandle,
tSituation *p) 
{ 
 OUTPUT("initTrack");
 *carParmHandle = GfParmReadFile(szSettings, GFPARM_RMODE_STD);
 if (*carParmHandle)
  OUTPUT("settings.xml read, name = " << name);
 else
  OUTPUT("Settings not loaded : " << szSettings);
 ptrack = track;
 SplitTrack();

 //
 // Smoothing loop
 //
 for (int Step = 128; (Step /= 2) > 0;)
 {
  OUTPUT("Step = " << Step);
  for (int i = Iterations * int(sqrt(Step)); --i >= 0;)
   Smooth(Step);
  Interpolate(Step);
 }
 
 //
 // Compute curvature and speed along the path
 //
 for (int i = Divs; --i >= 0;)
 {
  double TireAccel = TireAccel1 * tFriction[i];
  int next = (i + 1) % Divs;
  int prev = (i - 1 + Divs) % Divs;

  double rInverse = GetRInverse(prev, tx[i], ty[i], next);
  tRInverse[i] = rInverse;

  double MaxSpeed;

  if (fabs(rInverse) > WingRInverse * 1.01)
   MaxSpeed = sqrt(TireAccel / (fabs(rInverse) - WingRInverse));
  else
   MaxSpeed = 10000;

  tSpeed[i] = tMaxSpeed[i] = MaxSpeed;
 }
 
 //
 // Anticipate braking
 //
 for (int j = 100; --j >= 0;)
 for (int i = Divs; --i >= 0;)
 {
  double TireAccel = TireAccel1 * tFriction[i];
  int prev = (i - 1 + Divs) % Divs;
 
  double dx = tx[i] - tx[prev];
  double dy = ty[i] - ty[prev];
  double dist = Mag(dx, dy);
 
  double Speed = (tSpeed[i] + tSpeed[prev]) / 2;

  double LatA = tSpeed[i] * tSpeed[i] *
                (fabs(tRInverse[prev]) + fabs(tRInverse[i])) / 2;
 
  double TanA = TireAccel * TireAccel - LatA * LatA;
  if (TanA < 0.0)
   TanA = 0.0;
  TanA = sqrt(TanA) + WingRInverse * Speed * Speed;
  if (TanA > MaxBrake)
   TanA = MaxBrake;
 
  double Time = dist / Speed;
  double MaxSpeed = tSpeed[i] + TanA * Time;
  tSpeed[prev] = Min(MaxSpeed, tMaxSpeed[prev]);
 }                                                                              

#ifdef DRAWPATH
 ofstream ofs("k1999.path", ios::out);
 DrawPath(ofs);
#endif
} 

////////////////////////////////////////////////////////////////////////////
// New race
////////////////////////////////////////////////////////////////////////////
static double wheelbase;
static void newrace(int index, tCarElt* car, tSituation *s) 
{ 
 OUTPUT("newrace");
 wheelbase = (car->priv->wheel[FRNT_RGT].relPos.x +
              car->priv->wheel[FRNT_LFT].relPos.x -
              car->priv->wheel[REAR_RGT].relPos.x -
              car->priv->wheel[REAR_LFT].relPos.x) / 2;
 wheeltrack = (car->priv->wheel[FRNT_LFT].relPos.y +
               car->priv->wheel[REAR_LFT].relPos.y -
               car->priv->wheel[FRNT_RGT].relPos.y -
               car->priv->wheel[REAR_RGT].relPos.y) / 2;
 OUTPUT("wheelbase = " << wheelbase);
 OUTPUT("wheeltrack = " << wheeltrack);
} 

////////////////////////////////////////////////////////////////////////////
// Car control
////////////////////////////////////////////////////////////////////////////
static void drive(int index, tCarElt* car, tSituation *s) 
{
 memset(car->ctrl, 0, sizeof(tCarCtrl));

 // 
 // Find index in data arrays
 //
 int SegId = car->_trkPos.seg->id;
 double dist = car->_trkPos.toStart;
 if (dist < 0)
  dist = 0;
 if (car->_trkPos.seg->type != TR_STR)
  dist *= car->_trkPos.seg->radius;
 int Index = tSegIndex[SegId] + int(dist / tElemLength[SegId]);
 Index = Index % Divs;
 int Next = (Index + 1) % Divs;
 double d = tSegDist[SegId] + dist;
 double d0 = tDistance[Index];
 double d1 = tDistance[Next];
 if (d1 < d0)
  d1 += Length;
 if (d > d1 + Length / 2)
  d -= Length;
 double c0 = (d - d1) / (d0 - d1);

 //
 // Find target lane (=relative distance to the left side of the track)
 //
 double TargetLane = (1 - c0) * tLane[Next] + c0 * tLane[Index];

 //
 // Find target curvature (for the inside wheel)
 //
 double TargetCurvature = (1 - c0) * tRInverse[Next] + c0 * tRInverse[Index];
 if (fabs(TargetCurvature) > 0.01)
 {
  double r = 1 / TargetCurvature;
  if (r > 0)
   r -= wheeltrack / 2;
  else
   r += wheeltrack / 2;
  TargetCurvature = 1 / r;
 }

 //
 // Find target speed
 //
 double TargetSpeed = (1 - c0) * tSpeed[Next] + c0 * tSpeed[Index];

 //
 // Steering control
 //
 double Error = 0;
 double VnError = 0;
 double Skid = 0;
 double CosAngleError = 1;
 double SinAngleError = 0;
 {
  //
  // Ideal value
  //
  {
   double s = atan(wheelbase * TargetCurvature) / car->_steerLock;
   car->ctrl->steer = s;
  }

  //
  // Servo system to stay on the pre-computed path
  //
  Error = TargetLane * Width - car->_trkPos.toLeft;

  int Prev = (Index + Divs - 1) % Divs;
  int NextNext = (Next + 1) % Divs;
  double Prevdx = tx[Next] - tx[Prev];
  double Prevdy = ty[Next] - ty[Prev];
  double Nextdx = tx[NextNext] - tx[Index];
  double Nextdy = ty[NextNext] - ty[Index];
  double dx = c0 * Prevdx + (1 - c0) * Nextdx;
  double dy = c0 * Prevdy + (1 - c0) * Nextdy;
  double n = Mag(dx, dy);
  dx /= n;
  dy /= n;
  double speed = Mag(car->_speed_Y, car->_speed_X);
  double sError = (dx * car->_speed_Y - dy * car->_speed_X) / (speed + 0.01);
  double cError = (dx * car->_speed_X + dy * car->_speed_Y) / (speed + 0.01);
  VnError = asin(sError);
  if (cError < 0)
   VnError = PI - VnError;

  car->ctrl->steer -= (atan(Error * (300 / (speed + 300)) / 20) + VnError) / car->_steerLock;

  //
  // Counter-steering in case of skidding
  //
  double vx = car->_speed_X;
  double vy = car->_speed_Y;
  double dirx = cos(car->_yaw);
  double diry = sin(car->_yaw);
  CosAngleError = dx * dirx + dy * diry;
  SinAngleError = dx * diry - dy * dirx;
  Skid = (dirx * vy - vx * diry) / (speed + 0.1);
  if (Skid > 0.9)
   Skid = 0.9;
  if (Skid < -0.9)
   Skid = -0.9;
  double yr = speed * TargetCurvature;
  car->ctrl->steer += (asin(Skid) - 0.2 * (1 + fDirt) * (100 / (speed + 100)) * (car->_yaw_rate - yr)) / car->_steerLock;
 }

 //
 // Throttle and brake command
 //
 car->ctrl->accelCmd = 0;
 car->ctrl->brakeCmd = 0;

 static double ABS = 1;
 static double AntiSlip = 1;

 double x = (10 + car->_speed_x) * (TargetSpeed - car->_speed_x) / 400;
 if (fDirt)
  x *= 2;
 if (x > 0)
  car->ctrl->accelCmd = Min(x, AntiSlip);
 else
  car->ctrl->brakeCmd = Min(-10 * x, ABS);

 if (car->_speed_x > 30 && fabs(Error) * car->_speed_x > 100)
  car->ctrl->accelCmd = 0;

 if (car->_speed_x > 20)
 {
  const double SkidLimit = 0.2;
  if (fabs(Skid) > SkidLimit)
   car->ctrl->accelCmd = 0;
  else if (fabs(Skid) > SkidLimit / 2)
  {
   double k = 1 - fabs(Skid) / SkidLimit;
   car->ctrl->accelCmd *= k * k;
  }
 }

 if (car->ctrl->accelCmd > 0)
  car->ctrl->brakeCmd = 0;

 //
 // anti-slip
 //
 {
  double slip = 0;
  if (car->_speed_x > 0.1)
   slip = (car->_wheelRadius(3) * car->_wheelSpinVel(3) - car->_speed_x);

  if (slip > 1.0)
   AntiSlip *= 0.9;
  else
  {
   if (AntiSlip < 0.1)
    AntiSlip = 0.1;
   AntiSlip *= 1.1;
   if (AntiSlip > 1.0)
    AntiSlip = 1.0;
  }
 }

 //
 // ABS
 //
 {
  double slip = 0;
  if (car->_speed_x > 0.1)
   slip = (car->_wheelRadius(1) * car->_wheelSpinVel(1) - car->_speed_x);

  if (slip < -2.0)
   ABS *= 0.9;
  else
  {
   if (ABS < 0.1)
    ABS = 0.1;
   ABS *= (1.1 + (slip + 3.0) / 5);
   if (ABS > 1.0)
    ABS = 1.0;
  }
 }

 // 
 // Gearbox command
 //
 car->ctrl->gear = car->_gear;
 if (car->_gear <= 0)
  car->ctrl->gear++;
 else
 {
  static double OldSpeed = 0;
  double Speed = car->_speed_x;
  if (car->_enginerpm > car->_enginerpmRedLine * 0.95)
   car->ctrl->gear++;
  if (car->_gear > 1 &&
      car->_enginerpm /
           car->_gearRatio[car->_gear + car->_gearOffset] *
           car->_gearRatio[car->_gear - 1 + car->_gearOffset] <
      car->_enginerpmRedLine * 0.80)
   car->ctrl->gear--;
  OldSpeed = Speed;
 }

 //
 // Handle getting unstuck
 //
 static int fStuck = 0;

 if (car->_gear < 2 &&
     car->_speed_x < 3.0 &&
     (CosAngleError < 0.6 || (fStuck && CosAngleError < 0.95)) &&
     SinAngleError * Error > 0)
 {
  fStuck = 1;
  car->ctrl->gear = -1;
  if (car->_speed_x < 0)
  {
   if (SinAngleError > 0)
    car->ctrl->steer = 1;
   else
    car->ctrl->steer = -1;
  }
 }
 else
  fStuck = 0;

 if (car->_speed_x * car->_gear < -0.5)
  car->ctrl->brakeCmd = 1.0;

 //
 // Special race commands
 //
 car->ctrl->raceCmd = RM_CMD_NONE;
 if (1)
 {
  car->ctrl->raceCmd = RM_CMD_PIT_ASKED;
  car->pitcmd->fuel = 1;
 }

 LOG(d);
 LOG(car->_trkPos.toLeft);
 LOG(TargetLane);
 LOG(Error);
 LOG(car->ctrl->accelCmd);
 LOG(car->ctrl->brakeCmd);
 LOG(car->ctrl->steer);
 LOG(SegId % 2);
 {
  static double PrevD = 0;
  LOG(d - PrevD);
  PrevD = d;
 }
 LOG('\n');
} 

