//as of now this is just a mere copy of project 5. make sure i can detect walls, using analog read if necessray. i can techincally bring this home for some tests later. 
//serial monitor to double check and use prints for sure.


#define IRLED1 A5 //left
//#define IRLED2 A3 //the A5 and A3 for analog, but the digital ones don't need it
#define IRReceiver1 // only working w/ 1 IR led and 1 Receiver.
#define IRLED2 A0 //right
//#define IRLED2 A3 //the A5 and A3 for analog, but the digital ones don't need it
#define IRReceiver2 // only working w/ 1 IR led and 1 Receiver.
//#define IRLED2 A3 //the A5 and A3 for analog, but the digital ones don't need it
//#define IRReceiver3 // only working w/ 1 IR led and 1 Receiver.

#define E1 3  // Enable Pin for motor 1 , using A4 analog write , 1-2 enable pin, should go to A3 
#define E2 6  // Enable Pin for motor 2, using A3 , 3-4 enable pin , should go to A 6

#define I1 5  // Control pin 1 for motor 1, D5 in1
#define I2 12  // Control pin 2 for motor 1, D12 in2 
#define I3 8  // Control pin 1 for motor 2, D8 in 3
#define I4 7  // Control pin 2 for motor 2, D7 in4 



double KI=1,KD=1, KP=6; //You will be tuning these constants 
//kp is how fast we go forward
//ki is how much we turn left right
//kd is how long does it take to react when it goes too much right or left. 
double integralRight;
double pErrorRight;
int dt=2;

double integralLeft;
double pErrorLeft;


int ideal1=973;
int ideal2=973;

int errorRight;
int errorLeft;
int derivativeRight;
int derivativeLeft;


//#define IRReceiver2
int zerofront;
int zerorear;
//pulse width modulation analog for digital ports : 3,5,6,9,10,11
//analogWrite goes from 0-255
//analogRead goes from 0-1023 though, so we need to map that later.
void setup() {
    

    pinMode(I1, OUTPUT);
    pinMode(I2, OUTPUT);
    pinMode(I3, OUTPUT);
    pinMode(I4, OUTPUT);

  
  Serial.begin(9600);
  // put your setup code here, to run once:
pinMode(IRLED1, INPUT);
pinMode(IRLED2, INPUT);
//pinMode(IRLED3, INPUT);

//pinMode(IRRECEIVER1, INPUT); we don't define receivers.
//pinMode(IRRECEIVER1, INPUT);
int nSamples=1000;
for(int n=0;n<nSamples;n++)
{
zerofront+=analogRead(IRLED1);
}
zerofront /=nSamples;
Serial.println("ZeroFront is"); //some values from 134-137
Serial.println(zerofront);
  
//560 is the highest value consistently ish ive been getting.


}
//LED should get brighter the closer your hand is to the IR receiver.
void loop() 
{
//PID CONTROL RIGHT


  //e1 is rhs
 analogWrite(E1, 132);
    analogWrite(E2, 165);
  //high is to activiate and turn it 
  
// digitalWrite(E1, HIGH);
  //  digitalWrite(E2, HIGH); //go forwards my friend.

//straight...
    digitalWrite(I1, LOW); //I 1 moves it back
    digitalWrite(I2, HIGH); //I2 moves it forward
    
    digitalWrite(I3, HIGH); //I 3 moves it forward
    digitalWrite(I4, LOW); //I4 moves it back
//delay(5000);
//earlier, we can were turning i believe left cont by high low high low.

//so turn left is...
/*
digitalWrite(I1, HIGH);
    digitalWrite(I2, LOW);
    
    digitalWrite(I3, HIGH);
    digitalWrite(I4, LOW);
delay(5000);


//so turn right is...
digitalWrite(I1, LOW);
    digitalWrite(I2, HIGH);
    
    digitalWrite(I3, LOW);
    digitalWrite(I4, HIGH);
delay(5000);

    //stop is obv
    digitalWrite(I1, LOW);
    digitalWrite(I2, LOW);
    
    digitalWrite(I3, HIGH);
    digitalWrite(I4, HIGH);
delay(5000);
*/

    


    

  int IR1=analogRead(IRLED1);
int LED1V=IR1;
 int IR2=analogRead(IRLED2);
 int LED2V=IR2;
 
 //int IR3=analogRead(IRLED3);

 
 
 Serial.println("IR1 is ");
 Serial.println(LED1V);
  //129, 135
  

if(LED1V>ideal1-100)
{
  LED1V=ideal1;
}
if(LED2V>ideal2-100)
{
  LED2V=ideal2;
}

errorRight=ideal1-LED1V;
derivativeRight=(pErrorRight-errorRight)/dt;
integralRight = errorRight*dt;
pErrorRight=errorRight;
double CorrectionRight=KP*errorRight+KI*integralRight+KD*derivativeRight;
Serial.println("CORRECTIONLEFT VALUE "); //we are turning left , turn left
Serial.println(CorrectionRight); 
if(CorrectionRight!=0)
{
  Serial.println("PLEASE PLEASE TURN LEFT");
 analogWrite(E1, 115);//rhs motor
    analogWrite(E2, 105);
    Serial.println("left TURN PLEASE");
  
delay(35);
      
    //turn right
}


errorLeft=ideal2-LED2V;
derivativeLeft=(pErrorLeft-errorLeft)/dt;
integralLeft = errorLeft*dt;
pErrorLeft=errorLeft;
double CorrectionLeft=KP*errorLeft+KI*integralLeft+KD*derivativeLeft;

Serial.println("CORRECTIONRIGHT VALUE "); //we are turning right 
Serial.println(CorrectionLeft); 
  if(CorrectionLeft!=0) 
{
  Serial.println("PLEASE PLEASE TURN RIGHT");
  
analogWrite(E1, 68);
    analogWrite(E2, 105); //slow down right wheel
    Serial.println("RIGHT TURN PLEASE");
   

    /*
    digitalWrite(I1, HIGH);
    digitalWrite(I2, LOW);
    digitalWrite(I3, LOW);
    digitalWrite(I4, HIGH);
    */
        delay(35);
  
}

  
 
 
    Serial.println("IR2 is ");
 
 Serial.println(LED2V);
  //129, 135
 
   /* Serial.println("IR3 is ");
 Serial.println(LED3V);
  
  //129, 135
  if(LED3V<=80)
  {
    Serial.println("APPROACHING WALLfrom LED3 PLEASE TURN");
  }
  */
  
  delay(100);
  //based on my test runs, 70-80s means im hitting a wall in my room. will need to calibrate what 
  //the real numbers are in the lab with their lighting and their typo walls. but for testing 
  //purposes in my room, ill just have it register 70-80s is a wall. 
  // put your main code here, to run repeatedly:

}

