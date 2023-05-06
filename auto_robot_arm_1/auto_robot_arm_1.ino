#include <Servo.h>
#include <EEPROMex.h>

Servo servoa, servob, servoc,servod;

int a0 = 503, a1 = 508, a2 = 515, a3 = 513;
int timer;
int posa = 90, posb = 45, posc = 90, posd = 10;

bool save = false, oto = false;
int alamat, ser;

void setup() {
  Serial.begin(9600);

  EEPROM.setMemPool(1000, EEPROMSizeUno);
  EEPROM.setMaxAllowedWrites(200);

  servoa.attach(11);
  servob.attach(10);
  servoc.attach(9);
  servod.attach(5);

  pinMode(A0, INPUT);
  pinMode(A1, INPUT);
  pinMode(A2, INPUT);
  pinMode(A3, INPUT);

  pinMode(2, INPUT_PULLUP);
  pinMode(3, OUTPUT);
  digitalWrite(3, LOW);
  pinMode(4, INPUT_PULLUP);
}

void loop() {
  if(oto){automatis();}
  else{
    delay(5);

    if(analogRead(A0) <= a0-5 or analogRead(A0) >= a0+5){
      if(analogRead(A0) > a0){
        timer = map(analogRead(A0), a0, 1023, 100, 10);
        if(millis()%timer > timer-10){posa--;}
        if(posa < 0){posa = 0;}
      }
      else if(analogRead(A0) < a0){
        timer = map(analogRead(A0), a0, 0, 100, 10);
        if(millis()%timer > timer-10){posa++;}
        if(posa > 180){posa = 180;}
      }
      servoa.write(posa);
    }

    if(analogRead(A1) <= a1-5 or analogRead(A1) >= a1+5){
      if(analogRead(A1) > a1){
        timer = map(analogRead(A1), a1, 1023, 100, 10);
        if(millis()%timer > timer-10){posb--;}
        if(posb < 0){posb = 0;}
      }
      else if(analogRead(A1) < a1){
        timer = map(analogRead(A1), a1, 0, 100, 10);
        if(millis()%timer > timer-10){posb++;}
        if(posb > 180){posb = 180;}
      }
      servob.write(posb);
    }

    if(analogRead(A2) <= a2-10 or analogRead(A2) >= a2+10){
      if(analogRead(A2) > a2){
        timer = map(analogRead(A2), a2, 1023, 100, 10);
        if(millis()%timer > timer-10){posc--;}
        if(posc < 0){posc = 0;}
      }
      else if(analogRead(A2) < a2){
        timer = map(analogRead(A2), a2, 0, 100, 10);
        if(millis()%timer > timer-10){posc++;}
        if(posc > 180){posc = 180;}
      }
      servoc.write(posc);
    }
    
    if(analogRead(A3) <= a3-5 or analogRead(A3) >= a3+5){
      if(analogRead(A3) > a3){
        timer = map(analogRead(A3), a3, 1023, 100, 10);
        if(millis()%timer > timer-10){posd--;}
        if(posd < 0){posd = 0;}
      }
      else if(analogRead(A3) < a3){
        timer = map(analogRead(A3), a3, 0, 100, 10);
        if(millis()%timer > timer-10){posd++;}
        if(posd > 180){posd = 180;}
      }
      servod.write(posd);
    }
  }

  if(!digitalRead(2) and !oto){
    while(!digitalRead(2)){}
    if(!save){
      digitalWrite(3, HIGH);
      alamat = 0;
      save = true;
    }
    else{
      save = false;
      alamat++;
      EEPROM.write(alamat, 255);
      digitalWrite(3, LOW);
    }
  }

  if(!digitalRead(4) and !save){
    while(!digitalRead(4)){}
    if(!oto){alamat = 0; oto = true;}
    else{oto = false;}
  }
  else if(!digitalRead(4) and save){
    while(!digitalRead(4)){digitalWrite(3, LOW);}
    alamat++;
    EEPROM.write(alamat, 1);
    alamat++;
    EEPROM.write(alamat, posa);
    alamat++;
    EEPROM.write(alamat, 2);
    alamat++;
    EEPROM.write(alamat, posb);
    alamat++;
    EEPROM.write(alamat, 3);
    alamat++;
    EEPROM.write(alamat, posc);
    alamat++;
    EEPROM.write(alamat, 4);
    alamat++;
    EEPROM.write(alamat, posd);

    // Serial.print(posa);
    // Serial.print("\t");
    // Serial.print(posb);
    // Serial.print("\t");
    // Serial.print(posc);
    // Serial.print("\t");
    // Serial.println(posd);

    digitalWrite(3, HIGH);
  }
}

void automatis(){
  digitalWrite(3, HIGH);
  alamat++;
  ser = EEPROM.read(alamat);
  if(ser == 1){
    alamat++;
    ser = EEPROM.read(alamat);
    while(ser < posa){
      posa--;
      servoa.write(posa);
      delay(10);
    }
    while(ser > posa){
      posa++;
      servoa.write(posa);
      delay(10);
    }
    posa = ser;
  }
  else if(ser == 2){
    alamat++;
    ser = EEPROM.read(alamat);
    while(ser < posb){
      posb--;
      servob.write(posb);
      delay(10);
    }
    while(ser > posb){
      posb++;
      servob.write(posb);
      delay(10);
    }
    posb = ser;
  }
  else if(ser == 3){
    alamat++;
    ser = EEPROM.read(alamat);
    while(ser < posc){
      posc--;
      servoc.write(posc);
      delay(10);
    }
    while(ser > posc){
      posc++;
      servoc.write(posc);
      delay(10);
    }
    posc = ser;
  }
  else if(ser == 4){
    alamat++;
    ser = EEPROM.read(alamat);
    while(ser < posd){
      posd--;
      servod.write(posd);
      delay(10);
    }
    while(ser > posd){
      posd++;
      servod.write(posd);
      delay(10);
    }
    posd = ser;
  }
  else if(ser == 255){alamat = 0;}
  digitalWrite(3, LOW);
}