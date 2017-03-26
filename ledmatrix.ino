#include <WS2812FX.h>

#include <Homie.h>

#define LED_COUNT 64
#define LED_PIN D2

WS2812FX ws2812fx = WS2812FX(LED_COUNT, LED_PIN, NEO_GRB + NEO_KHZ800);

HomieNode ledMatrixNode("ledMatrix", "ledMatrix");


bool effectInputHandler(const HomieRange& range, const String& value) {
  int newEffect = value.toInt();
  if (newEffect < MODE_COUNT ){
    ws2812fx.stop();
    ws2812fx.setMode(newEffect);
    ws2812fx.start();
  }  
}


bool brightnessInputHandler(const HomieRange& range, const String& value) {
  int newBrightness = value.toInt();
  if (newBrightness < 256 ){
    ws2812fx.setBrightness(newBrightness);
  }  
}

bool speedInputHandler(const HomieRange& range, const String& value) {
  int newSpeed = value.toInt();
  if (newSpeed < 256 ){
    ws2812fx.stop();
    ws2812fx.setSpeed(newSpeed);
    ws2812fx.start();
  }  
}


void setup() {

  ws2812fx.init();
  ws2812fx.setBrightness(100);
  ws2812fx.setSpeed(200);
  ws2812fx.setMode(FX_MODE_RAINBOW_CYCLE);
  ws2812fx.start();

  ledMatrixNode.advertise("effect").settable(effectInputHandler);
  ledMatrixNode.advertise("brightness").settable(brightnessInputHandler);
  ledMatrixNode.advertise("speed").settable(speedInputHandler);
  
  Homie_setFirmware("pixelblock", "1.0.0");
  Homie.setup();

}

void loop() {
  Homie.loop();
  ws2812fx.service();

}
