#ifndef _ATC_H
#define _ATC_H

class ATC {
  public:
    static void doSendDirection(bool isClockWise);
    static void doSendPulse();
    static void turnCW();
    static void turnCCW();
};

#endif
