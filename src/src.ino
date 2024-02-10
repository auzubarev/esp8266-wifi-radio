#include <Arduino.h>
#include <ESP8266WiFi.h>
#include "AudioFileSourceICYStream.h"
#include "AudioFileSourceBuffer.h"
#include "AudioGeneratorMP3.h"
#include "AudioOutputI2S.h"
#include "button.h"

#define PIN_POT A0
#define PIN_BTN D6

const char* ssid      = "";
const char* password  = "";

const int preallocateBufferSize = 4*1024;
void *preallocateBuffer = NULL;

const char* urls[]= {
  "http://icecast.vgtrk.cdnvideo.ru/mayakfm_mp3_64kbps", 
  "http://orfeyfm.hostingradio.ru:8034/orfeyfm64.mp3",
  "http://icecast.vgtrk.cdnvideo.ru/kulturafm_mp3_64kbps",
  "http://bookradio.hostingradio.ru:8069/fm",
  "http://jfm1.hostingradio.ru:14536/pcstream.mp3",
  "http://jfm1.hostingradio.ru:14536/gcstream.mp3",
};

int index_urls = 0;
int n_urls = 6;

AudioGeneratorMP3 *mp3 = NULL;
AudioFileSourceICYStream *file = NULL;
AudioFileSourceBuffer *buff = NULL;
AudioOutputI2S *out = NULL;
Button *btn = NULL;

void stop() {
  if(mp3) {
    mp3->stop();
    delete mp3;
    mp3 = NULL;
  }
  if(buff) {
    buff->close();
    delete buff;
    buff = NULL;
  }
  if(file) {
    file->close();
    delete file;
    file = NULL;
  }
}

void play() {
  file = new AudioFileSourceICYStream(urls[index_urls]);
  buff = new AudioFileSourceBuffer(file, preallocateBuffer, preallocateBufferSize);
  mp3 = new AudioGeneratorMP3();
  mp3->begin(buff, out);
}

void next() {
  stop();
  index_urls = (index_urls + 1) % n_urls;
  play();
}

void setup() {
  preallocateBuffer = malloc(preallocateBufferSize);
  btn = new Button(PIN_BTN);
  pinMode(PIN_POT, INPUT);
  Serial.begin(9600);
  delay(1000);
  Serial.println("Connecting to WiFi");
  WiFi.disconnect();
  WiFi.softAPdisconnect(true);
  WiFi.mode(WIFI_STA);
  WiFi.begin(ssid, password);
  while (WiFi.status() != WL_CONNECTED) {
    Serial.println("...Connecting to WiFi");
    delay(1000);
  }
  Serial.println("Connected");
  out = new AudioOutputI2S();
  play();  
}

void loop() {
  out->SetGain((1.0/1023)*analogRead(PIN_POT));
  if (mp3->isRunning()) {
     if (!mp3->loop()) {
      mp3->stop();
      delay(5000);
      play();
     } 
  }
  if (btn->click()) {
    next();
  }
}