/***************************************************************************

    file        : profiler.h

 ***************************************************************************/

/***************************************************************************
 *                                                                         *
 *   This program is free software; you can redistribute it and/or modify  *
 *   it under the terms of the GNU General Public License as published by  *
 *   the Free Software Foundation; either version 2 of the License, or     *
 *   (at your option) any later version.                                   *
 *                                                                         *
 ***************************************************************************/

#ifndef _PROFILER_H_
#define _PROFILER_H_

#if (DEBUG || _DEBUG)

#include <vector>
#include <map>

#define START_PROFILE(name) Profiler::getInstance()->startProfile(name)
#define STOP_PROFILE(name) Profiler::getInstance()->stopProfile()
#define STOP_ACTIVE_PROFILES() Profiler::getInstance()->stopActiveProfiles()
#define PRINT_PROFILE() Profiler::getInstance()->printProfile()

class ProfileInstance {
 public:
  ProfileInstance(const char * pname);
  ~ProfileInstance();
  char name[256];
  int calls;
  int openCalls;
  double totalTime;
  double addTime;
  double subTime;
  double tmpStart;
  std::map<ProfileInstance *, void *> mapChildren;
};

/** A simple high-level profiler for non-threaded non-recursive functions. */
class Profiler {
 protected:
  Profiler();
 public:
  ~Profiler();
  static Profiler * getInstance();
  void startProfile(const char * pname);
  void stopProfile();
  void stopActiveProfiles();
  void printProfile();
 private:
  static Profiler * profiler;
  ProfileInstance * curProfile;
  double fStartTime;
  std::vector<ProfileInstance *> vecProfiles;
  std::vector<ProfileInstance *> stkProfiles;
  std::map<ProfileInstance *, void *> mapWarning;
};

#else /* not DEBUG */
#define START_PROFILE(a)
#define STOP_PROFILE(a)
#define STOP_ACTIVE_PROFILES()
#define PRINT_PROFILE()
#endif

#endif /* _PROFILER_H_ */ 



