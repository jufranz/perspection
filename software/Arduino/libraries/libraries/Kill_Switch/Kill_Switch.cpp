
#include <Kill_Switch.h>
#include <Arduino.h>

//returns true if we've timed out
bool timeout(unsigned long time0, unsigned int MAX){
    return (millis() - time0) > MAX;
}

int parsePacket(unsigned int MAX) {
    const char nullTerminator = '\0';
    unsigned char inByte;
    char message[4];
    unsigned long time0;
    
    
    /// step 1. get SoP
    time0 = millis();
    while (Serial.available() < 1) {
        if( timeout(time0, MAX) )  return 3;
    };
    
    inByte = Serial.read();
    if (inByte != SoP) {
        Serial.print("ERROR: Expected SOP, got: ");
        Serial.write((byte)inByte);
        Serial.print("\n");
        return 2;
    }
    
    /// step 2. get message length
    time0 = millis();
    while (Serial.available() < 1) {
        if( timeout(time0, MAX) )  return 3;
    };
    
    inByte = Serial.read();
    if (inByte == EoP || inByte == SoP) {
        Serial.println("ERROR: SoP/EoP in length field");
        return 2;
    }
    int message_size = inByte - '0';
    if (message_size > 4 || message_size < 0) {
        Serial.println("ERROR: Packet Length out of range");
        return 2;
    }
    
    /// step 3. get message
    
    for (int i = 0; i < message_size; i++) {
        time0 = millis();
        while (Serial.available() < 1 ) {
            if( timeout(time0, MAX) )  return 3;
        };
        
        inByte = Serial.read();
        if ((inByte == EoP || inByte == SoP)) {
            Serial.println("ERROR: SoP/EoP in command field");
            return 2;
        }
        message[i] = (char)inByte;
    }
    message[message_size] = nullTerminator;
    
    /// step 4. get EoP
    time0 = millis();
    while (Serial.available() < 1 ) {
        if( timeout(time0, MAX) )  return 3;
    };
    inByte = Serial.read();
    if (inByte != EoP) {
        Serial.println("EoP not found");
        return 2;
    } else {
        
        if(message[0] == 'K')
            return 1;
        else
            return 0;
        
    }
}

void sendPacket(char command){
    //1. signify start of packet
    Serial.write((byte)'A');
    delay(10);
    Serial.write((byte)'1');
    delay(10);
    Serial.write((byte)command);
    delay(10);
    Serial.write((byte)'Z');
    
}

