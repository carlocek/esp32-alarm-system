//INCLUSIONE LIBRERIE E FILES
#include <WiFi.h>
#include <FirebaseESP32.h>
#include <WebServer.h>
#include <Adafruit_Sensor.h>
#include <DHT.h>
#include <DHT_U.h>
#include <ESP32Servo.h>
#include <ESP32Tone.h>

#include "secrets.h"
#include "homepage.h"

//DICHIARAZIONE E DEFINIZIONE DEI PARAMETRI
FirebaseData firebasedata;
const int DHTPIN = 5; 
const int DHTTYPE = DHT11;
DHT_Unified dht(DHTPIN, DHTTYPE);
unsigned long previousMillis1 = 0; 
unsigned long interval1 = 500;
unsigned long previousMillis2 = 0;
unsigned long interval2 = 5000;
unsigned long previousMillis3 = 0;//servono per rendere il programma non bloccante
const int buzzer = 18;
const int sensorPin_acqua = 34;
const int sensorPin_luce = 35;
const int LED_luce = 2;
const int LED_pioggia = 4;
int ledState = 0;
int Temp;
int Humd;
int liquid_level=0;
int light_level=0;
int timezone = 2; 
int dst = 0;
String timestamp = "";
String LMst = "OFF";
String COPst = "OFF";
String DRst = "OFF";
int myLM = 0;
int myWL = 0;
int myTP = 0;
int myHM = 0;
String bg_L ="#ff8566";
String bg_W ="#ff8566";
String bg_T ="#ff8566";
String contL = "#ff5c33";
String contW = "#ff5c33";
String contT = "#ff5c33";//parametri usati per gestire la pagina html

WebServer server(80);

//DEFINIZIONE FUNZIONI
//indica la pagina inviata dal server quando si accede all'IP
void handleRoot() 
{
  Serial.println("GET /");
  server.send(200, "text/html", request);
}

//gestisce il caso in cui richieda un URI non valido
void handleNotFound()
{
  server.send(404, "text/plain", "404: Not found");
}

//calcola e restituisce il timestamp locale
String get_timestamp()
{
  
  String timestamp = "";
  time_t now = time(nullptr);
  timestamp = String(ctime(&now));
  timestamp.remove(24);
   
  if (timestamp.endsWith("1970"))
  {
    return "";
  }
  
  else
  {
    return timestamp;
  } 
}

//SETUP
void setup() 
{
  delay(3000);
  Serial.begin(115200); 
  Serial.printf("Connessione a %s\n", ssid);
  WiFi.begin(ssid,password); //la scheda si connette alla rete
  while (WiFi.status() != WL_CONNECTED)
  {
    delay(500);
    Serial.print(".");
  }
  Serial.println();
  Serial.print("Connesso, il tuo IP address: ");
  Serial.println(WiFi.localIP());
  
  Firebase.begin(FIREBASE_HOST, FIREBASE_AUTH);//inizializza Firebase
  configTime(timezone * 3600, dst * 0, "pool.ntp.org", "time.nist.gov");

  server.on("/", handleRoot);  //indica quale funzione eseguire quando il client fa il GET dell'URL root
  server.onNotFound(handleNotFound); 
  server.begin(); //inizializza il server
  Serial.print("HTTP server started at ");  Serial.println(WiFi.localIP());
  
  dht.begin(); //inizializza il sensore DHT11
  sensor_t sensor;
  dht.temperature().getSensor(&sensor);
  dht.humidity().getSensor(&sensor);
  pinMode(sensorPin_acqua, INPUT);
  pinMode(sensorPin_luce, INPUT);
  pinMode(buzzer, OUTPUT);
  pinMode(LED_luce, OUTPUT);
  pinMode(LED_pioggia, OUTPUT);
  digitalWrite(LED_luce, LOW);
  digitalWrite(LED_pioggia, ledState);
}
 
//LOOP
void loop()
{  
  unsigned long currentMillis = millis();
  server.handleClient();
  
  //lettura dati dai sensori
  liquid_level = analogRead(sensorPin_acqua);
  light_level = analogRead(sensorPin_luce);

  int percentage_water = ((liquid_level-1250)*100UL)/200UL; //alimentando a 3.3V, appena lo immergo legge 1200, quando è pieno 1450
  int percentage_dark = light_level*100UL/4095UL; //4095 è il val max quando alimento il sensore con 5V

  sensors_event_t event;
  dht.temperature().getEvent(&event);
  if(currentMillis - previousMillis2 > interval2)
  {
    previousMillis2 = currentMillis;

    if (isnan(event.temperature)) 
    {
      Serial.println("Error reading temperature!");
    }
    else 
    {
      Serial.print("Temperatura: ");Serial.print(event.temperature);Serial.println("°C");
      Temp = event.temperature;
    }
    dht.humidity().getEvent(&event);
    if (isnan(event.relative_humidity)) 
    {
      Serial.println("Error reading humidity!");
    }
    else 
    {
      Serial.print("Umidità: ");Serial.print(event.relative_humidity);Serial.println("%");
      Humd = event.relative_humidity;
    }
    Serial.print("Percentuale oscurità:");Serial.print(percentage_dark);Serial.println("%");
    if(liquid_level < 1250)
    {
      percentage_water = 0;
      Serial.println("Il sensore di livello è fuori dall'acqua");
    }
    else if(liquid_level > 1450)
    {
      percentage_water = 100;
    }
    else
    {
      Serial.print("Percentuale riempimento:");Serial.print(percentage_water);Serial.println("%");
    }
  }
  //aggiornamento stato attuatori e parametri della funzione GetValue()
  if(currentMillis - previousMillis1 > interval1)
  {
    previousMillis1 = currentMillis;
    if(Temp < 25 && Humd > 40)
    {
      Serial.println("PERICOLO PIOGGIA");
      ledState ^= 1; //XOR tra ledState e 1 in modo che ad ogni "giro" modifichi il valore di ledState
      digitalWrite(LED_pioggia, ledState);
      COPst = "ON";
      bg_T ="#b3ffb3";
      contT = "#00e600";
      myTP=Temp;
      myHM=Humd;
    }
    else
    {
      COPst="OFF";
      contT = "#ff5c33";
      bg_T ="#ff8566";
      myTP=Temp;
      myHM=Humd;
    }

    if(liquid_level > 1250)
    {  
      if(percentage_water > 50)
      {
        Serial.println("ALLARME ALLAGAMENTO");
        tone(buzzer,440, 250);
        DRst = "ON";
        bg_W ="#b3ffb3";
        contW = "#00e600";
        myWL = percentage_water;
      }
      else
      {
        DRst="OFF";
        contW = "#ff5c33";
        bg_W ="#ff8566";
        myWL = percentage_water;
      }
    }
    else
    {
      percentage_water = 0;
    }
   
    if(percentage_dark > 70)
    {
      Serial.println("ALLARME OSCURITA");
      digitalWrite(LED_luce, HIGH);
      LMst = "ON";  
      bg_L ="#b3ffb3";
      contL = "#00e600";  
      myLM = percentage_dark;
    }
    else
    {
      digitalWrite(LED_luce, LOW);
      LMst="OFF";
      contL = "#ff5c33";
      bg_L ="#ff8566";
      myLM = percentage_dark;
    } 
  }

  timestamp = get_timestamp();
  
  //inizio parte firebase
  FirebaseJson dati;
  dati.set("timestamp", timestamp);
  dati.set("Temperatura", myTP);
  dati.set("Umidita'", myHM);
  dati.set("Oscurita'", percentage_dark);
  dati.set("Livello acqua", percentage_water);
  if (currentMillis - previousMillis3 > interval2)
  {
    previousMillis3 = currentMillis;
    if(Firebase.updateNode(firebasedata, "/Board:"+timestamp, dati))
    {
      Serial.println("Corretto upload dei dati sul database");
    }
  
    if(Firebase.get(firebasedata, "/Board:"+timestamp+"/Temperatura"))
    {
      Serial.printf("Temperatura letta dal database: %d °C\n", firebasedata.intData());
    }
    if(Firebase.get(firebasedata, "/Board:"+timestamp+"/Umidita'"))
    {
      Serial.printf("Percentuale Umidita' letta dal database: %d\n", firebasedata.intData());
    }
    if(Firebase.get(firebasedata, "/Board:"+timestamp+"/Oscurita'"))
    {
      Serial.printf("Percentuale Oscurita' letta dal database: %d\n", firebasedata.intData());
    }
    if(Firebase.get(firebasedata, "/Board:"+timestamp+"/Livello acqua"))
    {
      Serial.printf("Livello acqua letto dal database: %d\n", firebasedata.intData());
    }
  }
  
  GetValue(String(myLM), LMst, String(myWL), COPst, DRst, String(myTP), bg_L, bg_W, bg_T, contL, contW, contT, String(myHM));
  delay(50);
} 
