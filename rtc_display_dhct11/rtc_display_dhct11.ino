#include <LiquidCrystal_I2C.h>
#include <DHT.h>
#include <DS1307.h>

//Temp Sensor
#define DHTTYPE DHT11   // Define model type to DHT 11
#define DHTPIN 7 //Define Pin7 to Read temp and humidity

DHT dht(DHTPIN, DHTTYPE);//Starting dht object and set pin parameter (DHTPIN) and sensor type (DHTTYPE)


//Display
int totalColumns = 16;
int totalRows = 2;

LiquidCrystal_I2C lcd(0x3F, totalColumns, totalRows);


//Write custom characters
byte termometro[8] = //icon for termometer
{
    B00100,
    B01010,
    B01010,
    B01110,
    B01110,
    B11111,
    B11111,
    B01110
};

byte humidity[8] = //icon for water droplet
{
    B00100,
    B00100,
    B01010,
    B01010,
    B10001,
    B10001,
    B10001,
    B01110,
};


String custom_text; //String to be used in scrolled text

//RTC
DS1307 rtc(A2, A3);

void setup(){
  Serial.begin(9600);
  lcd.init(); 
  lcd.backlight(); // use to turn on and turn off LCD back light
  lcd.createChar(1,termometro); //create termometro with id 1
  lcd.createChar(2,humidity); //create humidity with id 2

  dht.begin();//Start DHT11 sensor

  rtc.halt(false); //Start watch RTC

  //Used to set RTC at first time after insert battery
  //rtc.setDOW(TUESDAY);      //Define day of week
  //rtc.setTime(16, 35, 30);     //Define time
  //rtc.setDate(28, 2, 2023);   //Define day, month and year

  //Define SQW/Out Pin
  rtc.setSQWRate(SQW_RATE_1);
  rtc.enableSQW(true);
}

void loop()
  {
    int h = dht.readHumidity();//read humidity in float
    int t = dht.readTemperature();//read temp in float

    if (isnan(h) || isnan(t)) {//check temp and humidity if is a valid number
      return;//return if not true
    }

    //print infos in serial
    Serial.print("Umidade: ");
    Serial.print(h);
    Serial.println("%");
    Serial.print("Temperatura: ");
    Serial.print(t);
    Serial.println("°C ");
    Serial.print("Hora : ");
    char time = rtc.getTimeStr(FORMAT_SHORT);
    Serial.print(time);    
    Serial.print(" ");
    Serial.print("Data : ");
    Serial.print(rtc.getDateStr(FORMAT_SHORT));
    Serial.print(" ");
    Serial.println(rtc.getDOWStr(FORMAT_SHORT));


    //print in lcd, setCursor(colum, row) is used to set digit localization. First row is 0.
    lcd.setCursor(0, 0); //set cursor to first line and first colum
    lcd.print(rtc.getTimeStr(FORMAT_SHORT)); //print time
    lcd.setCursor(11, 0);
    lcd.write(1); //print custom character id 1
    lcd.print(String(t) + (char)223 + "C");
    
    lcd.setCursor(11,1);
    lcd.write(2); //print custom character id 2
    lcd.print(String(h) + "%");

    delay(2000); //wait 2 seconds

    custom_text = String(rtc.getDateStr(FORMAT_SHORT)) + " " + String(rtc.getDOWStr(FORMAT_SHORT)); //set text to be printed
    custom_scroll(custom_text,1,0,10); //call custom scroll from right to left
  }

//text is the text to be scrolled to left starting in idx_start and finishing in idx_end
void custom_scroll(String text, int row, int idx_start, int idx_end){
    
    int textlength = text.length(); //check text lenght

    //logic to print and scroll from right to left
    for (int i = 0; i <= textlength; i++) {
      lcd.setCursor(idx_start,row);

      if (textlength-i<idx_end){
        return;
      }

      lcd.print(text.substring(i,idx_end+i));
     
      if ((i == 0) || (i == textlength)){
        delay (2000); // wait 2 seconds at initial and final. Important time to be readable.
      } else {
        delay(400); //scroll segment time
      }      
    }
}