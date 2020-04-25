//zalacz - wlaczenie interfaceu
//ledzalacz - dioda informujaca wlaczenie
//stop - V=0
//slewy - sterowanie predkoscia lewej gasienicy
//vl - predkosc lewej gasienicy (wyswieltana)
//sprawy - sterowanie predkoscia prawej gasienicy
//vp - predkosc prawej gasienicy (wyswietlana)
//w - zwiekszenie predkosci lewej gasienicy o 1
//q - zwiekszenie predkosci lewej gasienict o 5
//e - zwiekszenie predkosci prawej gasienicy o 1
//r - zwiekszenie predkosci prawej gasienicy o 5
//y - zmniejszenie predkosci lewej gasienicy o 1
//t - zmniejszenie predkosci lewej gasienicy o 5
//u - zmniejszenie predkosci prawej gasienicy o 1
//i - zmniejszenie predkosci prawej gasienicy o 5
//kat - wyswietlanie kata
//sm - slider obrotow serwa
//k - serwo +1 w prawo
//j - serwo +1 w lewo
//h - stop, wyzerowanie prędkości silników

#include<SoftwareSerial.h>
#include<Servo.h>

Servo serwo; //Tworzenie obiektu typu Servo
char tablica[10]; //tablica odczytująca znaki z aplikacji andorid
byte indexT; //indeks tablicy
int z=0; //zalaczenie interfaceu
int vlewy=0; //odczytana predkosc lewej gasienicy
int vprawy=0; //odczytana predkosc prawej gasienicy
int kserwa=90; //kąt obrotu serwomechanizmu
int serwoWyswietl=0; //wyswietlanie kata serwomechanizmu


void Eoff(){ //silniki wylaczone
  Serial.println("log Silniki wyłączone. Załącz silniki!\n");
}


void Sgas(){ //sterowanie gasienicami
  Serial.println("log Sterowanie prędkoscią gąsienic.\n");
}


void Gp1(){ //zwiększenie prędkości gąsienic o 1
  Serial.println("log Zwiększenie prędkości gąsienic o 1.\n");
}


void Gp5(){ //zwiększenie prędkości gąsienic o 5
  Serial.println("log Zwiększenie prędkości gąsienic o 5.\n");
}


void Gt1(){ //zmniejszenie prędkości gąsienic o 1
  Serial.println("log Zmniejszenie prędkości gąsienic o 1.\n");
}


void Gt5(){ //zmniejszenie prędkości gąsienic o 5
  Serial.println("log Zmniejszenie prędkości gąsienic o 5.\n");
}

  
void maxV(){
  Serial.println("log Osiągnięto maksymalną prędkość.\n");
}
  
void ruch(char kierunek[10], int predkosc){

  if(predkosc==0){
    if(kierunek=="vl "){
      digitalWrite(7,LOW);
      digitalWrite(8,LOW);
    }else if(kierunek=="vp "){
      digitalWrite(10,LOW);
      digitalWrite(11,LOW);
    }
      Serial.print(kierunek);
      Serial.print(predkosc);
      Serial.println("\n");
  }else if(predkosc>0){
    if(kierunek=="vl "){
      digitalWrite(7,HIGH);
      digitalWrite(8,LOW);
      analogWrite(6, predkosc);
    }else if(kierunek=="vp "){
      digitalWrite(10,HIGH);
      digitalWrite(11,LOW);
      analogWrite(5, predkosc);
    }
      Serial.print(kierunek);
      Serial.print(predkosc);
      Serial.println("\n");
         
  
  } else if(predkosc<0){
    if(kierunek=="vl "){
      digitalWrite(7,LOW);
      digitalWrite(8,HIGH);    
      analogWrite(6, -predkosc);

    }else if(kierunek=="vp "){
      digitalWrite(10,LOW);
      digitalWrite(11,HIGH);
      analogWrite(5, -predkosc);

    }
      Serial.print(kierunek);
      Serial.print(predkosc);
      Serial.println("\n");
    }
}

void polaczenie(){
  Serial.println("log Właśnie połączyłeś się ze swoim czołgiem. Aby móc nim sterować załącz silnki przyciskiem 'załącz'.\n");
  Serial.println("ledzalacz 0\n");
  z=0;
  Serial.print("vp ");
  Serial.print(0);
  Serial.println("\n");
  Serial.print("vl ");
  Serial.print(0);
  Serial.println("\n");
  Serial.print("kat ");
  Serial.print(0);
  Serial.println("\n");
  kserwa=0;
  serwoWyswietl=0;

}

void zalacz(){
  if(z==0){
    Serial.println("ledzalacz 1\n");
    z=1;
    Serial.println("log Załączenie silników. Czołg gotowy do użytku\n");
  } else if(z==1){
    Serial.println("ledzalacz 0\n");
    Serial.println("log Wyłączenie silników. Aby sterować czołgiem ponownie załącz silniki.\n");
    z=0;
  }
}

void predkosclewa(){
  if(z==1){
    Sgas();
    vlewy= atof(tablica+5);
    ruch("vl ", vlewy);
  }else if(z==0){
    Eoff();
  }
}

void predkoscprawa(){
  if(z==1){
    Sgas();
    vprawy= atof(tablica+5);
    ruch("vp ",vprawy);
  }else if(z==0){
    Eoff();
  }
}

void lewaprzodL(){
  if(z==1){
    if(vlewy<255){
      Gp1();
      vlewy+=1;
      ruch("vl ",vlewy);
    } else maxV();
  }else if(z==0){
    Eoff();
  } 
}

void lewaprzodH(){
  if(z==1){
    if(vlewy<251){
      Gp5();
      vlewy+=5;
      ruch("vl ",vlewy);
    }else maxV();
  }else if(z==0){
    Eoff();
  } 
}

void lewatylL(){
  if(z==1){
    if(vlewy>-255){
      Gt1();
      vlewy-=1;
      ruch("vl ",vlewy);
    }else maxV(); 
  }else if(z==0){
    Eoff();
  } 
}

void lewatylH(){
  if(z==1){
    if(vlewy>-251){
      Gt5();
      vlewy-=5;
      ruch("vl ",vlewy);
    }else maxV();
  }else if(z==0){
    Eoff();
  } 
}

void prawaprzodL(){
  if(z==1){
    if(vprawy<255){
      Gp1();
      vprawy+=1;
      ruch("vp ",vprawy);
    }else maxV();
  }else if(z==0){
    Eoff();
  } 
}

void prawaprzodH(){
  if(z==1){
    if(vprawy<251){
      Gp5();
      vprawy+=5;
      ruch("vp ",vprawy);
    }else maxV();
  }else if(z==0){
    Eoff();
  } 
}

void prawatylL(){
  if(z==1){
    if(vprawy>-255){      
      Gt1();
      vprawy-=1;
      ruch("vp ",vprawy);
    }else maxV();
  }else if(z==0){
    Eoff();
  } 
}

void prawatylH(){
  if(z==1){
    if(vprawy>-251){
      Gt5();
      vprawy-=5;
      ruch("vp ",vprawy);
    }else maxV();
  }else if(z==0){
    Eoff();
  } 
}

void katserwa(){
  if(z==1){
    Serial.println("log Sterowanie serwomechanizmem \n");
    kserwa=atof(tablica+2);
    kserwa=180-kserwa;
    serwoWyswietl=-kserwa+90;
    Serial.print("kat ");
    Serial.print(serwoWyswietl);
    Serial.println("\n");
    serwo.write(kserwa);
  }else if(z==0){
    Eoff();
  }
}

void serwoL(){
  if(z==1){
    if(kserwa<180){
      Serial.println("log Serwo poruszone o 1 stopień w prawo \n");
      kserwa+=1;
      serwoWyswietl-=1;
      Serial.print("kat ");
      Serial.print(serwoWyswietl);
      Serial.println("\n");
      serwo.write(kserwa);
    }else Serial.println("log Osiągnięta maksymelny kąt obrotu serwomechanizmu.\n");
  }else if(z==0){
    Eoff();
  }
}

void serwoP(){
  if(z==1){
    if(kserwa>0){
      Serial.println("log Serwo poruszone o 1 stopień w lewo \n");
      kserwa-=1;
      serwoWyswietl+=1;
      Serial.print("kat ");
      Serial.print(serwoWyswietl);
      Serial.println("\n");
      serwo.write(kserwa);
    }else Serial.println("log Osiągnięta maksymelny kąt obrotu serwomechanizmu.\n");
  }else if(z==0){
    Eoff();
  }
}


void STOP(){
  if(z==1){
    analogWrite(6,0);
    analogWrite(5,0);
    Serial.println("log Wyzerowanie prędkości silników.\n");
    Serial.print("vp ");
    Serial.print(0);
    Serial.println("\n");
    Serial.print("vl ");
    Serial.print(0);
    Serial.println("\n");   
    vlewy=0;
    vprawy=0; 
  }else if(z==0){
    Eoff();
  }
  
}



void setup() {
  Serial.begin(9600);
  pinMode(6, OUTPUT); //pwm silnika lewego
  pinMode(7, OUTPUT); //kierunek silnika lewego
  pinMode(8, OUTPUT); //kierunek silnika lewego
  pinMode(5 , OUTPUT); //pwm silnika prawego
  pinMode(10, OUTPUT); //kierunek silnika prawego
  pinMode(11, OUTPUT); //kierunek silnika prawego 
  digitalWrite(7, LOW); 
  digitalWrite(8, LOW);
  digitalWrite(6, LOW);
  digitalWrite(5, LOW); 
  digitalWrite(10, LOW);
  digitalWrite(11, LOW);

  serwo.attach(3);
}

void loop() {
  if(Serial.available()>0)
  {
    char odczyt=(char)Serial.read();
    
    if(odczyt=='\n')
    {
      tablica[indexT]=0;
      
      switch(tablica[0])
      {
        case 'z':
          zalacz();
          break;
          
        case 's':
          if(tablica[1]=='l'){
            predkosclewa();
          }else if(tablica[1]=='p'){
            predkoscprawa();
          }else if(tablica[1]=='m'){
            katserwa();
          }
          break;

          case 'c':
            polaczenie();
            break;

          case 'q': //lewa+1
            lewaprzodH();
            break;

          case 'w': //lewa+5
            lewaprzodL();
            break;

          case 'e': //lewa-1
            lewatylL();
            break;

          case 'r': //lewa-5
            lewatylH();
            break;

          case 't': //prawa+1
            prawaprzodH();
            break;

          case 'y': //prawa+5
            prawaprzodL();
            break;

          case 'u': //prawa-1
            prawatylL();
            break;

          case 'i': //prawa-5
            prawatylH();
            break;

          case 'k': //serwo +1 w prawo
            serwoP();
            break;

          case 'j': //serwo +1 w lewo
            serwoL();
            break;

          case 'h': //STOP, wyzerowanie prędkości silników
            STOP();
            break;
          
      }  
      indexT=0;

    }else{
      tablica[indexT]=odczyt;
      if(indexT<9) indexT++;
    }
  }

}
