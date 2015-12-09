// **********************************************************************************
#ifndef Kill_Switch_h
#define Kill_Switch_h

const char SoP = 'A';
const char EoP = 'Z';
const char good = 'G';
const char kill = 'K';

int parsePacket(unsigned int MAX);

void sendPacket(char command);

#endif