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
#include <strstream.h>
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
// These parameters are for the computation of the path
//
static const int MaxSegments = 1000;
static const int MaxDivs = 20000;

static const int Iterations = 100;     // Number of smoothing operations
static const double DivLength = 3.0;   // Length of path elements in meters
 
static const double SecurityR = 100.0; // Security radius
static double SideDistExt = 2.0; // Security distance wrt outside
static double SideDistInt = 1.0; // Security distance wrt inside          

class CK1999Data
{
 public:
  CK1999Data(double x1, double x2, double x3, double x4, double x5, char * const psz) :
   WingRInverse(x1),
   TireAccel1(x2),
   MaxBrake(x3),
   SlipLimit(x4),
   SteerSkid(x5),
   pszCarName(psz)
  {
   fDirt = 0;
  }
   
  const double WingRInverse;
  const double TireAccel1;
  const double MaxBrake;
  const double SlipLimit;
  const double SteerSkid;
  char * const pszCarName; 

  double ABS;
  double TractionHelp;
  int fStuck;
  double wheelbase;
  double wheeltrack;

  int Divs;
  int Segs;
  double Width;
  double Length;
  double tSegDist[MaxSegments];
  int tSegIndex[MaxSegments];
  double tElemLength[MaxSegments];
  double tx[MaxDivs];
  double ty[MaxDivs];
  double tDistance[MaxDivs];
  double tRInverse[MaxDivs];
  double tMaxSpeed[MaxDivs];
  double tSpeed[MaxDivs];
  double txLeft[MaxDivs];
  double tyLeft[MaxDivs];
  double txRight[MaxDivs];
  double tyRight[MaxDivs];
  double tLane[MaxDivs];
  double tFriction[MaxDivs];

  int fDirt;

  void UpdateTxTy(int i);
  void DrawPath(ostream &out);
  void SetSegmentInfo(const tTrackSeg *pseg, double d, int i, double l);
  void SplitTrack(tTrack *ptrack);
  double GetRInverse(int prev, double x, double y, int next);
  void AdjustRadius(int prev, int i, int next, double TargetRInverse, double Security = 0);
  void Smooth(int Step);
  void StepInterpolate(int iMin, int iMax, int Step);
  void Interpolate(int Step);
  void InitTrack(tTrack* track, void **carParmHandle, tSituation *p);
  void NewRace(tCarElt* car, tSituation *s);
  void Drive(tCarElt* car, tSituation *s);
};

CK1999Data data1(0.0032,  9.50,  8.00, 8.00, 0.40, "K1999-buggy");
CK1999Data data2(0.0032, 12.00, 11.00, 2.00, 0.20, "K1999-cg-nascar-rwd");

CK1999Data *tpdata[] = {&data1, &data2};

#define CARS (sizeof(tpdata)/sizeof(*tpdata))


//
// Debugging options
//
#define VERBOSE
//#define DOLOG
#define DRAWPATH

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
 
/////////////////////////////////////////////////////////////////////////////
// Update tx and ty arrays
/////////////////////////////////////////////////////////////////////////////
void CK1999Data::UpdateTxTy(int i)
{
 tx[i] = tLane[i] * txRight[i] + (1 - tLane[i]) * txLeft[i];
 ty[i] = tLane[i] * tyRight[i] + (1 - tLane[i]) * tyLeft[i];
}                                                                               

/////////////////////////////////////////////////////////////////////////////
// Draw a path (use gnuplot)
/////////////////////////////////////////////////////////////////////////////
#ifdef DRAWPATH
void CK1999Data::DrawPath(ostream &out)
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
void CK1999Data::SetSegmentInfo(const tTrackSeg *pseg, double d, int i, double l)
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
void CK1999Data::SplitTrack(tTrack *ptrack)
{
 Segs = 0;
 OUTPUT("Analyzing track...");
 const tTrackSeg *psegCurrent = ptrack->seg;

 double Distance = 0;
 double Angle = psegCurrent->angle[TR_ZS];
 double xPos = (psegCurrent->vertex[TR_SL].x +
                psegCurrent->vertex[TR_SR].x) / 2;
 double yPos = (psegCurrent->vertex[TR_SL].y +
                psegCurrent->vertex[TR_SR].y) / 2;

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
    //tFriction[i] *= 0.90;
    fDirt = 1;
    SideDistInt = -1.5;
    SideDistExt = 0.0;
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
 OUTPUT("Width : " << Width);
}
 
/////////////////////////////////////////////////////////////////////////////
// Compute the inverse of the radius
/////////////////////////////////////////////////////////////////////////////
double CK1999Data::GetRInverse(int prev, double x, double y, int next)
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
void CK1999Data::AdjustRadius(int prev, int i, int next, double TargetRInverse, double Security)
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
void CK1999Data::Smooth(int Step)
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
void CK1999Data::StepInterpolate(int iMin, int iMax, int Step)
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
void CK1999Data::Interpolate(int Step)
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
static void initTrack(int index, tTrack* track, void **carParmHandle, tSituation *p); 
static void drive(int index, tCarElt* car, tSituation *s); 
static void newrace(int index, tCarElt* car, tSituation *s); 
static int InitFuncPt(int index, void *pt); 

////////////////////////////////////////////////////////////////////////////
// Module entry point  
////////////////////////////////////////////////////////////////////////////
extern "C" int K1999(tModInfo *modInfo) 
{ 
 OUTPUT("modInfo");
 for (int i = CARS; --i >= 0;)
 {
  OUTPUT("modInfo[" << i << "].name = " << tpdata[i]->pszCarName);
  modInfo[i].name    = tpdata[i]->pszCarName;
  modInfo[i].desc    = tpdata[i]->pszCarName;
  modInfo[i].fctInit = InitFuncPt;
  modInfo[i].gfId    = ROB_IDENT;
  modInfo[i].index   = i + 1;
 }
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
static void initTrack(int index, tTrack* track, void **carParmHandle, tSituation *p) 
{
 OUTPUT("initTrack(" << index << ")");
 char szSettings[100];
 ostrstream os(szSettings, sizeof(szSettings));
 os << "drivers/K1999/" << index << "/settings.xml" << ends;
 *carParmHandle = GfParmReadFile(szSettings, GFPARM_RMODE_STD);
 if (*carParmHandle)
  OUTPUT(szSettings << " read.");
 else
  OUTPUT("Settings not loaded : " << szSettings);

 tpdata[index - 1]->InitTrack(track, carParmHandle, p);
}

void CK1999Data::InitTrack(tTrack* track, void **carParmHandle, tSituation *p)
{
 //
 // split track
 //
 SplitTrack(track);

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
 
#if 0
  double TanA = TireAccel * TireAccel - LatA * LatA;
  if (TanA < 0.0)
   TanA = 0.0;
  TanA = sqrt(TanA) + WingRInverse * Speed * Speed;
  if (TanA > MaxBrake)
   TanA = MaxBrake;
#else
  double TanA = TireAccel * TireAccel +
                WingRInverse * Speed * Speed - LatA * LatA;
  if (TanA < 0.0)
   TanA = 0.0;
  if (TanA > MaxBrake * tFriction[i])
   TanA = MaxBrake * tFriction[i];
#endif
 
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
static void newrace(int index, tCarElt* car, tSituation *s) 
{ 
 OUTPUT("newrace(" << index << ")");
 tpdata[index - 1]->NewRace(car, s);
}

void CK1999Data::NewRace(tCarElt* car, tSituation *s)
{
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

 ABS = 1;
 TractionHelp = 1;
 fStuck = 0;
} 

////////////////////////////////////////////////////////////////////////////
// Car control
////////////////////////////////////////////////////////////////////////////
static void drive(int index, tCarElt* car, tSituation *s) 
{
 tpdata[index - 1]->Drive(car, s);
}

void CK1999Data::Drive(tCarElt* car, tSituation *s)
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
 double d = tSegDist[SegId] + dist;

 Index = (Index + Divs - 5) % Divs;
 int Next;
 static const double Time = 0.01;
 double X = car->_pos_X + car->_speed_X * Time / 2;
 double Y = car->_pos_Y + car->_speed_Y * Time / 2;
 while(1)
 {
  Next = (Index + 1) % Divs;
  if ((tx[Next] - tx[Index]) * (X - tx[Next]) +
      (ty[Next] - ty[Index]) * (Y - ty[Next]) < 0)
   break;
  Index = Next;
 }
 double c0 = (tx[Next] - tx[Index]) * (tx[Next] - X) +
             (ty[Next] - ty[Index]) * (ty[Next] - Y);
 double c1 = (tx[Next] - tx[Index]) * (X - tx[Index]) +
             (ty[Next] - ty[Index]) * (Y - ty[Index]);
 {
  double sum = c0 + c1;
  c0 /= sum;
  c1 /= sum;
 }

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
  {
   double dx = tx[Next] - tx[Index];
   double dy = ty[Next] - ty[Index];
   Error = (dx * (Y - ty[Index]) - dy * (X - tx[Index])) / Mag(dx, dy);
  }  

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

  car->ctrl->steer -= (atan(Error * (300 / (speed + 300)) / 15) + VnError) / car->_steerLock;

  //
  // Steer into the skid
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
  car->ctrl->steer += asin(Skid) / car->_steerLock;

  double yr = speed * TargetCurvature;
  double diff = car->_yaw_rate - yr;
  car->ctrl->steer -= (SteerSkid * (1 + fDirt) * (100 / (speed + 100)) * diff) / car->_steerLock;
 }

 //
 // Throttle and brake command
 //
 car->ctrl->accelCmd = 0;
 car->ctrl->brakeCmd = 0;

 double x = (10 + car->_speed_x) * (TargetSpeed - car->_speed_x) / 200;
 if (fDirt && x > 0)
  x = 1;

 if (x > 0)
  car->ctrl->accelCmd = Min(x, TractionHelp);
 else
  car->ctrl->brakeCmd = Min(-10 * x, ABS);
 
 if (car->_speed_x > 30 && fabs(Error) * car->_speed_x > 60)
  car->ctrl->accelCmd = 0;

 if (car->ctrl->accelCmd > 0)
  car->ctrl->brakeCmd = 0;

 //
 // Traction help
 //
 //if (!fDirt)
 {
  double slip = 0;
  if (car->_speed_x > 0.1)
   for (int i = 4; --i >= 0;)
   {
    double s = (car->_wheelRadius(i) * car->_wheelSpinVel(i) - car->_speed_x);
    if (s > slip)
     slip = s;
   }

  if (slip > SlipLimit)
   TractionHelp *= 0.9;
  else
  {
   if (TractionHelp < 0.1)
    TractionHelp = 0.1;
   TractionHelp *= 1.1;
   if (TractionHelp > 1.0)
    TractionHelp = 1.0;
  }
 }

 //
 // ABS
 //
 {
  double slip = 0;
  if (car->_speed_x > 0.1)
   for (int i = 4; --i >= 0;)
   {
    double s = (car->_wheelRadius(i) * car->_wheelSpinVel(i) - car->_speed_x);
    if (s < slip)
     slip = s;
   }

  if (slip < -SlipLimit)
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
  car->ctrl->gear = 1;
 else
 {
  float *tRatio = car->_gearRatio + car->_gearOffset;
  double rpm = (car->_speed_x + SlipLimit) * tRatio[car->_gear] / car->_wheelRadius(2);

  if (rpm > car->_enginerpmRedLine * 0.95)
   car->ctrl->gear = car->_gear + 1;
    
  if (car->_gear > 1 &&
      rpm / tRatio[car->_gear] * tRatio[car->_gear - 1] < car->_enginerpmRedLine * 0.70 + 2 * car->_gear)
   car->ctrl->gear = car->_gear - 1;
 }

 //
 // Handle getting unstuck
 //
 if (car->_gear <= 2 &&
     car->_speed_x < 3.0 &&
     (CosAngleError < 0.7 || (fStuck && CosAngleError < 0.90)) &&
     SinAngleError * Error > 0)
 {
  fStuck = 1;
  car->ctrl->gear = car->_gear -1;
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
#if 0
 if (0)
 {
  car->ctrl->raceCmd = RM_CMD_PIT_ASKED;
  car->pitcmd->fuel = 1;
 }
#endif

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
 LOG(VnError);
 LOG(car->_pos_X);
 LOG(car->_pos_Y);
 LOG(double(Index % 10) / 10.0);
 LOG('\n');
} 
