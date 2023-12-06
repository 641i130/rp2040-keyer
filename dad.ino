int dit;
int dah;

// Describe this function...
void light() {
  digitalWrite(6, HIGH);
  delay(2000);
  digitalWrite(6, LOW);
  delay(50);
}


// Describe this function...
void dit_output() {
  digitalWrite(LED_BUILTIN, HIGH);
  digitalWrite(7, HIGH);
  delay(dit);
  digitalWrite(LED_BUILTIN, LOW);
  digitalWrite(7, LOW);
  delay(50);
}


// Describe this function...
void dah_output() {
  digitalWrite(LED_BUILTIN, HIGH);
  digitalWrite(7, HIGH);
  delay(dah);
  digitalWrite(LED_BUILTIN, LOW);
  digitalWrite(7, LOW);
  delay(50);
}



void setup() {
  Serial.begin(9600);
  pinMode(6, OUTPUT);
  pinMode(7, OUTPUT);
}

void loop() {
  light();
  dit = 100;
  for (int count = 0; count < 50; count++) {
    if (analogRead(0) == 0) {
      digitalWrite(6, HIGH);
      delay(50);
      digitalWrite(6, LOW);
      delay(50);
      dit = dit - 10;

    }
    delay(100);
  }
  light();
  Serial.write("dit = ");
  Serial.println(dit,DEC);
  delay(1000);
  if (dit < 40) {
    dit = 40;
 
  }
  if (dit > 100) {
    dit = 100;

  }
  dah = dit * 3  ;
  while (!false) {
     
int dit;
int dah;

// Describe this function...
void light() {
  digitalWrite(6, HIGH);
  delay(2000);
  digitalWrite(6, LOW);
  delay(50);
}


// Describe this function...
void dit_output() {
  digitalWrite(LED_BUILTIN, HIGH);
  digitalWrite(7, HIGH);
  delay(dit);
  digitalWrite(LED_BUILTIN, LOW);
  digitalWrite(7, LOW);
  delay(50);
}


// Describe this function...
void dah_output() {
  digitalWrite(LED_BUILTIN, HIGH);
  digitalWrite(7, HIGH);
  delay(dah);
  digitalWrite(LED_BUILTIN, LOW);
  digitalWrite(7, LOW);
  delay(50);
}



void setup() {
  Serial.begin(9600);
  pinMode(6, OUTPUT);
  pinMode(7, OUTPUT);
}

void loop() {
  light();
  dit = 100;
  for (int count = 0; count < 50; count++) {
    if (analogRead(0) == 0) {
      digitalWrite(6, HIGH);
      delay(50);
      digitalWrite(6, LOW);
      delay(50);
      dit = dit - 10;

    }
    delay(100);
  }
  light();
  Serial.write("dit = ");
  Serial.println(dit,DEC);
  delay(1000);
  if (dit < 40) {
    dit = 40;
 
  }
  if (dit > 100) {
    dit = 100;

  }
  dah = dit * 3  ;
  while (!false) {
    if (analogRead(0) == 0) {
      dit_output();

    }
    if (analogRead(1) == 0) {
      dah_output();

    }
  }

} 
    if (analogRead(0) == 0) {
      dit_output();

    }
    if (analogRead(1) == 0) {
      dah_output();

    }
  }

}
