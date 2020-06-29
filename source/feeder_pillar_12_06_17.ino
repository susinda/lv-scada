#include <gprs.h>
#include <SoftwareSerial.h>
#include <stdlib.h>
#include <string.h>
 //SIM800 TX is connected to Arduino D8
 //SIM800 RX is connected to Arduino D7
#define TIMEOUT    5000
#define LED_PIN    13
 
bool ledStatus;
GPRS gprs;
int l1;
int l2;
int l3;
int l4;

//int newR[8]={0,0,0,0,0,0,0,0};
//int newY[8]={0,0,0,0,0,0,0,0};
//int newB[8]={0,0,0,0,0,0,0,0};

int newR[8]={1,1,1,1,1,1,1,1};
int newY[8]={1,1,1,1,1,1,1,1};
int newB[8]={1,1,1,1,1,1,1,1};

int oldR[8]={1,1,1,1,1,1,1,1};
int oldY[8]={1,1,1,1,1,1,1,1};
int oldB[8]={1,1,1,1,1,1,1,1};

void setup() 
{
pinMode(2,INPUT);
pinMode(3,INPUT);
pinMode(4,INPUT);
pinMode(5,INPUT);
pinMode(6,INPUT);
pinMode(9,INPUT);
pinMode(10,INPUT);
pinMode(11,INPUT);
pinMode(A1,OUTPUT);
pinMode(A2,OUTPUT);
pinMode(A0,OUTPUT);



Serial.begin(9600);
while(!Serial);
Serial.println("GPRS - Send SMS Test ...");
gprs.preInit();
delay(1000);
while(0 != gprs.init()) 
 {
  delay(1000);
  Serial.print("init error\r\n");
 } 
Serial.println("Init success, start to send SMS message...");
gprs.sendSMS("0716297875","Now system is ready"); //define phone number and text

}

void loop() 
{
  digitalWrite(A2,LOW);
  digitalWrite(A1,LOW);
  delay(50);
  digitalWrite(A0, HIGH);
  delay(1000);
//  newR[0]=digitalRead (2);
  newR[1]=digitalRead (3);
//  newR[2]=digitalRead (4);
  newR[3]=digitalRead (5);
  newR[4]=digitalRead (6);
//  newR[5]=digitalRead (9);
  newR[6]=digitalRead (10);
  newR[7]=digitalRead (11);
  delay(500);
  digitalWrite(A0,LOW);
  digitalWrite(A1,LOW);
  digitalWrite(A2,LOW);
  delay(50);
  digitalWrite(A2, HIGH);
  delay(1000);
 // newY[0]=digitalRead (2);
  newY[1]=digitalRead (3);
 // newY[2]=digitalRead (4);
  newY[3]=digitalRead (5);
  newY[4]=digitalRead (6);
 // newY[5]=digitalRead (9);
  newY[6]=digitalRead (10);
  newY[7]=digitalRead (11);
  delay(500);
  digitalWrite(A0,LOW);
  digitalWrite(A1,LOW);
  digitalWrite(A2,LOW);
  delay(50);
  digitalWrite(A1, HIGH);
  delay(1000);
 // newB[0]=digitalRead (2);
  newB[1]=digitalRead (3);
 // newB[2]=digitalRead (4);
  newB[3]=digitalRead (5);
  newB[4]=digitalRead (6);
  //newB[5]=digitalRead (9);
  newB[6]=digitalRead (10); 
  newB[7]=digitalRead (11);
  delay(500);
  digitalWrite(A1,LOW);
  digitalWrite(A2,LOW);
  digitalWrite(A0,LOW);

 for(int i=0; i<=7; i++ )
 {Serial.print("R phase");
  Serial.print(i);
  Serial.println(newR[i]);
 }
 Serial.println();
 for(int i=0; i<=7; i++ )
 {Serial.print("Y phase");
  Serial.print(i);
  Serial.println(newY[i]);
 }
 Serial.println();
 for(int i=0; i<=7; i++ )
 {Serial.print("B phase");
  Serial.print(i);
  Serial.println(newB[i]);
 }


 if(newY[1]!=oldY[1] || newY[2]!=oldY[2] || newY[3]!=oldY[3] || newY[4]!=oldY[4] || newY[5]!=oldY[5] || newY[6]!=oldY[6])
 {l1=1;}
 else
 {l1=0;
  if(newY[7]!=oldY[7] || newY[0]!=oldY[0] || oldR[1]!=newR[1] || newR[2]!=oldR[2] || newR[3]!=oldR[3] || newR[4]!=oldR[4])
 {l2=1;}
 else
 {l2=0;
  if(newR[5]!=oldR[5] || newR[6]!=oldR[6] || newR[7]!=oldR[7] || newR[0]!=oldR[0] || newB[1]!=oldB[1] || newB[2]!=oldB[2])
 {l3=1;}
 else
 {l3=0;
  if(newB[3]!=oldB[3] || newB[4]!=oldB[4] || newB[5]!=oldB[5] || newB[6]!=oldB[6] || newB[7]!=oldB[7] || newB[0]!=oldB[0])
 {l4=1;}
 else
 {
 l4=0;
 }}}}
 
 if(l1==1 || l2==1 || l3==1 || l4==1) //main if
{   oldR[1]=newR[1]; oldR[2]=newR[2]; oldR[3]=newR[3]; oldR[4]=newR[4]; oldR[5]=newR[5]; oldR[6]=newR[6]; oldR[7]=newR[7]; oldR[0]=newR[0]; 
    oldY[1]=newY[1]; oldY[2]=newY[2]; oldY[3]=newY[3]; oldY[4]=newY[4]; oldY[5]=newY[5]; oldY[6]=newY[6]; oldY[7]=newY[7]; oldY[0]=newY[0];
    oldB[1]=newB[1]; oldB[2]=newB[2]; oldB[3]=newB[3]; oldB[4]=newB[4]; oldB[5]=newB[5]; oldB[6]=newB[6]; oldB[7]=newB[7]; oldB[0]=newB[0];
    //Serial.println("in if 1");
if(newR[7]==0 && newY[7]==0 && newB[7]==0)
{ Serial.println("Feeder of F/P Lost");
  //Serial.println(newR[1]);
  gprs.sendSMS("0716297875","Feeder of 15N047 F/P Lost  https://goo.gl/AtPwny");
}
else //else 01
{ 
  if(newR[7]==0)
  {Serial.println("Feeder  fuse(R) burnt of 15N047 FP"); 
   gprs.sendSMS("0716297875","Feeder  fuse(R) burnt of 15N047 FP  https://goo.gl/AtPwny");
  }
  else //else 02
  { 
    if(newY[7]==0)
    {Serial.println("Feeder  fuse(Y) burnt of 15N047 FP"); 
     gprs.sendSMS("0716297875","Feeder  fuse(Y) burnt of 15N047 FP  https://goo.gl/AtPwny");
    }
    else //else 03
    {
      if(newB[7]==0)
      {Serial.println("Feeder  fuse(B) burnt of 15N047 FP"); 
       gprs.sendSMS("0716297875","Feeder  fuse(B) burnt of 15N047 FP  https://goo.gl/AtPwny");
      }
      else// else 04
      {
              for(int i=0; i<=7; i++ )
               {
               if(newR[i]==0)
                {
                  char s1[50]="https://goo.gl/AtPwny  15N047 /R phase lost/unit";  
                  char s2[3]={(i+1)+'0'};

                    //    char *result = malloc(strlen(s1)+strlen(s2)+1);//+1 for the zero-terminator
                    //in real code you would check for errors in malloc here
                   char result [54];
                   strcpy(result, s1);
                   strcat(result, s2);
                   Serial.println(result);
                   //Serial.println(newR[i]);
                   gprs.sendSMS("0716297875",result);
                   delay(1000);
                }


               if(newY[i]==0)
                {
                  char s1[50]="https://goo.gl/AtPwny  15N047 /Y phase lost/unit";  
                  char s2[3]={(i+1)+'0'};
                  char result [54];
                  strcpy(result, s1);
                  strcat(result, s2);
                  Serial.println(result);
                  //Serial.println(newY[i]);
                  gprs.sendSMS("0716297875",result);                
                  delay(1000);
                }

               if(newB[i]==0)
                {
                  char s1[50]="https://goo.gl/AtPwny  15N047 /B phase lost/unit";  
                  char s2[3]={(i+1)+'0'};
                  char result [54];
                  strcpy(result, s1);
                  strcat(result, s2);
                  Serial.println(result);
                  //Serial.println(newR[i]);
                  gprs.sendSMS("0716297875",result);
                  delay(1000);
                 }
              } //end for loop       
      } //end else 04
      
    } //end else 03
  }//end else 02
} //end else 01
}//end main if
  if(0 != gprs.sendCmdAndWaitForResp("AT+CMGF=1\r\n", "OK", TIMEOUT)) 
  {
    ERROR("ERROR:CNMI");
    return;
  }
   
  //Start listening to New SMS Message Indications 
  if(0 != gprs.sendCmdAndWaitForResp("AT+CNMI=1,2,0,0,0\r\n", "OK", TIMEOUT)) 
  {
    ERROR("ERROR:CNMI");
    return;
  }
  if(0 != gprs.sendCmdAndWaitForResp("AT+CMGDA=1\r\n", "OK", TIMEOUT)) 
    {Serial.println("SMS was deleted");}
  else
  {Serial.println("SMS was not deleted");}

}//end loop


