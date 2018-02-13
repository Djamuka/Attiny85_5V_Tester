
Skip to content

    All gists
    GitHub

    New gist

    0

@Djamuka Djamuka/Tester_3.7V_Attiny85.ino
Created 8 minutes ago
Code
Revisions 1
Attiny85 Testeur 3.7V
Tester_3.7V_Attiny85.ino
int Batt = A1;  // Attiny45 Physical 7
int Led_R = 1;  // Attiny45 Physical 6 , Doit étre sur OC0 pour PWM séparé
int Led_V = 4;  // Attiny45 Physical 3 , Doit étre sur OC1 pour PWM séparé
int Read_Batt;
float Value = 0.000;
float Ratio = 0.000;
int PWM_V;
int PWM_R;
unsigned long Previous_Blink;
boolean LedBlink=0;
const int Interval = 250;
 
void setup() {
  analogReference(INTERNAL);
  Ratio = (1024/5); // Diviseur de tension mesuré, calcul sur 5V donc 1024/5...
  pinMode(Led_R, OUTPUT);
  pinMode(Led_V, OUTPUT);
  for(int a = 0;a<255;a++){
    int b ;
    b = 255 - a;
    analogWrite(Led_V,a);
    analogWrite(Led_R,b);
    delay (2);
  }
  digitalWrite (Led_V,HIGH);
  delay(150);
  digitalWrite (Led_V,LOW);
  delay(75);
  digitalWrite (Led_V,HIGH);
  digitalWrite (Led_R,HIGH);
  delay(150);
  digitalWrite (Led_V,LOW);
  digitalWrite (Led_R,LOW);
  delay(75);
  digitalWrite (Led_R,HIGH);
  delay(150);
  digitalWrite (Led_R,LOW);
}
 
void loop() {
  Read_Batt = analogRead(Batt);
  delay(75);
  Value =  (Read_Batt/Ratio)*100;
  if (Value >=330){ // Si la batterie est supérieur à 3.3V
  /* Une LiPo/Li-ion 3.7V complétement chargé fait 4.23v, Déchargé  2.7v et nominal 3.7v
   * Ne jamais, déchargé une Lipo à moins de 3Volt pour la durée de vie.*/
    LedBlink = 0;
    PWM_V = map(Value,340,430,0,255); // Si la batterie est entre 3.4V et 4.3V
    PWM_V  = constrain (PWM_V,0,255);
    PWM_R = map(Value,400,330,0,255); // Si la batterie est entre 4 V et 3.3V
    PWM_R  = constrain (PWM_R,0,255);
    analogWrite(Led_V,PWM_V);
    analogWrite(Led_R,PWM_R);
  }else if ( Value <= 329 && Value >= 305){ // Si la batterie est entre 3.29V et 3.05V
    unsigned long Bounce_Led = millis();
    if (Bounce_Led - Previous_Blink >= Interval) {
        Previous_Blink = Bounce_Led;
        if (LedBlink == 0) {
          digitalWrite (Led_R,HIGH);
          LedBlink = 1;
         }else{
           LedBlink = 0;
           digitalWrite (Led_R,LOW);
          }
     }
  }else if (Value <=304){ // Si la batterie est inférieur à 3.04V
    digitalWrite (Led_R,LOW);
    digitalWrite (Led_V,LOW);
    LedBlink = 0;
   }
}
@Djamuka

Attach files by dragging & dropping,

, or pasting from the clipboard.
Styling with Markdown is supported

    © 2018 GitHub, Inc.
    Terms
    Privacy
    Security
    Status
    Help

    Contact GitHub
    API
    Training
    Shop
    Blog
    About

