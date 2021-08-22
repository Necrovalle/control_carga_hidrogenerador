char ENT;
float V100= 53.8;   //Voltaje del 100% de carga
float V0  = 42.2;   //Voltaje del 0% de carga
float f   = 12.75;  //Factor del divisor de voltaje
float Vbat= 0.0;    //Voltaje de la bateria
int  DVbat= 0;      //Lectura digital del voltaje de la bateria
bool Carga= true;   //Activador de sistema de carga
bool Direc= true;   //Direccion de carga a descarga o contraria [true: cargando ]


void setup() {
  Serial.begin(9600);
  pinMode(3, OUTPUT);
  digitalWrite(3, LOW);
  Serial.println("Centro de control de carga");
  Serial.println("------[Deperochem]--------");
  Serial.println("[R]: lectura de valores.");
}

void loop() {
  iuef (Serial.available() > 0){
    ENT = Serial.read();
    if (ENT == 'R'){
      Serial.print("Voltaje del 100%: ");
      Serial.println(V100);
      Serial.print("Voltaje del 0%  : ");
      Serial.println(V0);
      Serial.print("Voltaje actual  : ");
      Serial.println(Vbat);
      Serial.print("Siatema de carga: ");
      if (Carga){
        Serial.println("Activado");
      } else {
        Serial.println("Desactivado");
      }
    }
  } else {
    DVbat = analogRead(A1);
    Vbat  = ((DVbat * 5.0)/1023) * f;
    if (Direc){
      if (Vbat > V100){
        Carga = false;
        digitalWrite(3, Carga);
        Direc = false;
      } else {
        if (!Carga){
          Carga = true;
          digitalWrite(3, Carga);
        }
      }
    } else {
      if (Vbat < V0){
        Carga = true;
        digitalWrite(3, Carga);
        Direc = true;
      } else {
        if (Carga){
          Carga = false;
          digitalWrite(3, Carga);
        }
      }
    }
  }
}
