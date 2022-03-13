unsigned int Ts=20000; // Periodo de muestreo [us]
unsigned int t, t0;
int valor = 0,valor2=0;      // Variable donde almacenaremos el valor del potenciómetro
float voltaje = 0;  // Variable para almacenar el voltaje
int digPin5 = 5; // pin digital 5
int digPin6 = 6; // pin digital 6
int pot2;
float error, voltajeinicial,setpoint,control2,error2, controlador,integrador,limite;
float kp=45, ki=22;
int PWM;
//----------------------------------------------------------------------------------------

void setup() {
  // put your setup code here, to run once:
  pinMode(digPin5, OUTPUT);     // pin en modo salida
  pinMode(digPin6, OUTPUT);     // pin en modo salida
  analogWrite(digPin5, 0);
  analogWrite(digPin6, 0);
  Serial.begin(115200);
  t0=micros();

  valor2 = analogRead(A0);           // Leemos del pin A0 valor
  voltajeinicial = (valor2*5.00/1023.00);   // Calculamos el voltaje
  integrador=0;
}
//----------------------------------------------------------------------------------------

void loop() {
  // put your main code here, to run repeatedly:
  t=micros();

  if(t - t0 >= Ts){
   
   Planta();
  // printSerial();
    t0 = t;
  }

}

//----------------------------------------------------------------------------------------
//Funciones
void printSerial(){
  Serial.print("Ts: ");
  //Serial.print((t-t0)/1000);
  Serial.println(" [ms]");
}

//----------------------------------------------------------------------------------------

void Planta(){
   pot2= analogRead(A1);
   setpoint=(pot2*5.00/1023.00);
   
    valor = analogRead(A0);           // Leemos del pin A0 valor
    voltaje = (valor*5.00/1023.00);   // Calculamos el voltaje
    Serial.print("    Voltaje: ");
    Serial.print(voltaje);
    Serial.println("V");
    //delay(100);
    
   error=-(setpoint - voltaje);
   error2=-error;
   integrador=integrador+error2;
   limite=110;
   
   if (integrador >= limite){
      integrador = limite;
   } else if( integrador <= -limite){
      integrador = -limite;
   }
     
   controlador=kp*error2+ki*integrador;
   control2=abs(controlador);
   PWM=map(control2*5,0,25000,0,255);

   if (PWM>=255){
    PWM=255;
   }

        if (error>0){
        analogWrite(digPin6, PWM); // asigna el valor HIGH al pin    
        analogWrite(digPin5, 0); // asigna el valor LOW al pin
        //delay(100);
        }

        if (error<0){
        analogWrite(digPin5, PWM); // asigna el valor HIGH al pin    
        analogWrite(digPin6, 0); // asigna el valor LOW al pin   
        //delay(100);
        }

        if (error==0){
        analogWrite(digPin5, 0); // asigna el valor HIGH al pin    
        analogWrite(digPin6, 0); // asigna el valor LOW al pin   
        //delay(100);
        }
   Serial.print("\n Error: ");
  Serial.print(abs(error));

     Serial.print("   PWM: ");
  Serial.print(PWM);

  Serial.print("   setpoint: ");
  Serial.print(setpoint);

  Serial.print("   Controlador: ");
  Serial.print(control2);
}
