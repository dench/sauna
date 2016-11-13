#define ledPin 9
#define swPin 10
#define DHT22_PIN 8

String incStr = "";

void setup() {
  Serial.begin(9600);
  Serial1.begin(9600);
  pinMode(ledPin, OUTPUT);
  pinMode(swPin, OUTPUT);
  digitalWrite(swPin, HIGH);
}

void loop() {
  dhtRead();
  delay(2000);
  if (Serial1.available()) {
    char inc = Serial1.read();
    if (inc == 0x0A) {
      AnalyseString(incStr);
      incStr = "";
    } else {
      incStr += inc;
    }
  }
}

void AnalyseString(String incStr) {
  if (incStr == "led/on") {
    digitalWrite(ledPin, HIGH);
    digitalWrite(swPin, LOW);
  } else if (incStr == "led/off") {
    digitalWrite(ledPin, LOW);
    digitalWrite(swPin, HIGH);
  }

  String t1 = "\"" + String(random(25)) + "\"";
  SendData("t0.txt", t1);
}

void SendData(String dev, String data)
{
  Serial1.print(dev);
  Serial1.print("=");
  Serial1.print(data);
  Serial1.write(0xff);
  Serial1.write(0xff);
  Serial1.write(0xff);
}
