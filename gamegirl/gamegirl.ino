// Включаем необходимые библиотеки
#include <Wire.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>

// Определяем константы для экрана
#define SCREEN_WIDTH 128
#define SCREEN_HEIGHT 64
#define OLED_RESET -1
#define SCREEN_ADDRESS 0x3C

// Определяем константы для игр
#define GAME_COUNT 2 // Количество игр
#define GAME_DINO 0
#define GAME_ANOTHER 1 // Индекс другой игры
#define RIGHT_BTN 10
#define LEFT_BTN 7
#define CHANGE_BTN 2

#include "DinoGame.h"
#include "Arcanoid.h"

// Создаем объекты
Adafruit_SSD1306 display(SCREEN_WIDTH, SCREEN_HEIGHT, &Wire, OLED_RESET);
Dino dino(display);
Arcanoid arcanoid(&display);

static const uint8_t PROGMEM image_data_girlico[1024] = {
    
    0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 
    0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 
    0xff, 0xff, 0x81, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 
    0xff, 0xff, 0x00, 0x7f, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xf8, 0x00, 0x3f, 0xff, 0xff, 
    0xff, 0xfe, 0x00, 0x1f, 0xff, 0xff, 0xfe, 0x00, 0x00, 0x3f, 0xff, 0xe0, 0x00, 0x0f, 0xff, 0xff, 
    0xff, 0xfc, 0x00, 0x0f, 0xff, 0xff, 0xc0, 0x00, 0x00, 0x03, 0xff, 0xc0, 0x00, 0x03, 0xff, 0xff, 
    0xff, 0xfc, 0x1c, 0x07, 0xff, 0xfe, 0x00, 0x00, 0x00, 0x00, 0x7e, 0x00, 0x00, 0x03, 0xff, 0xff, 
    0xff, 0xfc, 0x3c, 0x03, 0xff, 0xf0, 0x00, 0x00, 0x00, 0x00, 0x1c, 0x01, 0xff, 0x83, 0xff, 0xff, 
    0xff, 0xf8, 0x38, 0x01, 0xff, 0xe0, 0x00, 0x00, 0x00, 0x00, 0xc8, 0x07, 0xe7, 0xc3, 0xff, 0xff, 
    0xff, 0xf8, 0x30, 0x00, 0xff, 0x80, 0x00, 0x00, 0x00, 0x00, 0xf0, 0x07, 0xdf, 0xc3, 0xff, 0xff, 
    0xff, 0xf8, 0x60, 0x20, 0x3e, 0x00, 0x07, 0xc0, 0x7f, 0x7c, 0x20, 0x00, 0x1f, 0xc3, 0xff, 0xff, 
    0xff, 0xf0, 0x40, 0x00, 0x1c, 0x00, 0x3e, 0x03, 0xfc, 0x7f, 0x80, 0x00, 0x07, 0xc3, 0xff, 0xff, 
    0xff, 0xf0, 0x40, 0x00, 0x18, 0x00, 0x78, 0x8e, 0x01, 0xfc, 0x00, 0x00, 0x07, 0xc3, 0xff, 0xff, 
    0xff, 0xf0, 0xc0, 0x02, 0x00, 0x01, 0xc0, 0x00, 0x00, 0xf8, 0x00, 0x00, 0x07, 0xc3, 0xff, 0xff, 
    0xff, 0xf0, 0xc0, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0xf0, 0x03, 0x36, 0x07, 0x83, 0xff, 0xff, 
    0xff, 0xf0, 0xc0, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0xf8, 0x01, 0xf8, 0x07, 0x03, 0xff, 0xff, 
    0xff, 0xf0, 0xc0, 0x00, 0x00, 0x00, 0x00, 0x00, 0x78, 0x7f, 0xc0, 0xf8, 0x00, 0x07, 0xff, 0xff, 
    0xff, 0xf0, 0xc0, 0x00, 0x00, 0x00, 0x00, 0xff, 0xf0, 0x1f, 0xe0, 0x80, 0x00, 0x0f, 0xff, 0xff, 
    0xff, 0xf0, 0xc0, 0x00, 0x00, 0x00, 0x1f, 0xff, 0xf8, 0x0f, 0xf0, 0xc0, 0x00, 0x1f, 0xff, 0xff, 
    0xff, 0xf0, 0xc0, 0x00, 0x00, 0x00, 0xff, 0xff, 0xfc, 0x01, 0xf0, 0x00, 0x00, 0x7f, 0xff, 0xff, 
    0xff, 0xf0, 0x60, 0x00, 0x00, 0x0f, 0xff, 0xff, 0xff, 0x00, 0x78, 0x00, 0x03, 0xff, 0xff, 0xff, 
    0xff, 0xf0, 0x00, 0x00, 0x00, 0xff, 0xff, 0xff, 0xff, 0x80, 0x78, 0x03, 0xff, 0xff, 0xff, 0xff, 
    0xff, 0xf8, 0x00, 0x00, 0x07, 0xff, 0xff, 0xff, 0xff, 0xe0, 0x38, 0x3f, 0xff, 0xff, 0xff, 0xff, 
    0xff, 0xfc, 0x00, 0x20, 0x1f, 0xff, 0xff, 0xff, 0xff, 0xf8, 0x1c, 0x3f, 0xff, 0xff, 0xff, 0xff, 
    0xff, 0xff, 0x80, 0xe0, 0x7f, 0xff, 0xff, 0xff, 0x9f, 0xfc, 0x18, 0x3f, 0xff, 0xff, 0xff, 0xff, 
    0xff, 0xff, 0xff, 0xc0, 0xff, 0xff, 0xff, 0xff, 0x67, 0xfe, 0x18, 0x03, 0xff, 0xff, 0xff, 0xff, 
    0xff, 0xff, 0xff, 0xc1, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xf0, 0x00, 0x3f, 0xff, 0xff, 0xff, 
    0xff, 0xff, 0xff, 0x81, 0xff, 0xff, 0xff, 0xff, 0xfb, 0xff, 0xe0, 0x00, 0x07, 0xff, 0xff, 0xff, 
    0xff, 0xff, 0xff, 0x81, 0xde, 0xff, 0xff, 0xff, 0xf9, 0xfe, 0x00, 0x00, 0x00, 0xff, 0xff, 0xff, 
    0xff, 0xff, 0xff, 0x83, 0xbc, 0x7f, 0xff, 0xff, 0xe1, 0xe0, 0x00, 0x00, 0x00, 0x3f, 0xff, 0xff, 
    0xff, 0xff, 0xff, 0x03, 0xfe, 0xbf, 0xff, 0xff, 0xc1, 0xc0, 0x00, 0x00, 0x00, 0x0f, 0xff, 0xff, 
    0xff, 0xff, 0xfe, 0x07, 0xfc, 0x1f, 0xff, 0xff, 0xc1, 0xc0, 0x00, 0x00, 0x00, 0x0f, 0xff, 0xff, 
    0xff, 0xff, 0xf8, 0x07, 0xfe, 0x9f, 0xff, 0xff, 0xe7, 0xc0, 0x00, 0x00, 0x00, 0x0f, 0xff, 0xff, 
    0xff, 0xff, 0xf8, 0x00, 0xfc, 0x1f, 0xff, 0xff, 0xf9, 0xc0, 0xe0, 0x00, 0x00, 0x0f, 0xff, 0xff, 
    0xff, 0xff, 0xf8, 0x00, 0xfe, 0x0f, 0xff, 0xff, 0xff, 0xc0, 0xe8, 0x00, 0x00, 0x0f, 0xff, 0xff, 
    0xff, 0xff, 0xf8, 0x00, 0x7f, 0xbf, 0xff, 0xff, 0xff, 0xec, 0xe8, 0x00, 0x00, 0x1f, 0xff, 0xff, 
    0xff, 0xff, 0xf8, 0x00, 0x7f, 0xaf, 0xff, 0xff, 0xff, 0xde, 0xf8, 0x00, 0x00, 0x1f, 0xff, 0xff, 
    0xff, 0xff, 0xfe, 0x00, 0x3f, 0xff, 0xff, 0xff, 0xff, 0x8f, 0x86, 0x00, 0x00, 0xff, 0xff, 0xff, 
    0xff, 0xff, 0xff, 0x80, 0x3f, 0xff, 0xff, 0xff, 0xff, 0x81, 0x86, 0x00, 0x01, 0xff, 0xff, 0xff, 
    0xff, 0xff, 0xff, 0xe7, 0x3f, 0xff, 0xff, 0xf3, 0xff, 0x81, 0x86, 0x00, 0x01, 0xff, 0xff, 0xff, 
    0xff, 0xff, 0xff, 0x97, 0x9f, 0xff, 0xe0, 0x03, 0xfe, 0x00, 0x06, 0x00, 0x01, 0xff, 0xff, 0xff, 
    0xff, 0xff, 0xff, 0x9c, 0x9f, 0xff, 0xf0, 0xfb, 0xfc, 0x00, 0x06, 0x00, 0x01, 0xff, 0xff, 0xff, 
    0xff, 0xff, 0xff, 0x88, 0xd8, 0x7f, 0xfe, 0xfb, 0xf8, 0x00, 0x00, 0x00, 0x3e, 0xff, 0xff, 0xff, 
    0xff, 0xff, 0xff, 0x88, 0x78, 0x1f, 0xff, 0x7f, 0xc0, 0x00, 0x00, 0x00, 0x7f, 0xff, 0xff, 0xff, 
    0xff, 0xff, 0xff, 0x80, 0x60, 0x00, 0x3f, 0xff, 0x78, 0x00, 0x60, 0x00, 0x22, 0xff, 0xff, 0xff, 
    0xff, 0xff, 0xff, 0xe0, 0x00, 0x00, 0xc1, 0xfc, 0xe0, 0x10, 0x00, 0x03, 0xb8, 0x3f, 0xff, 0xff, 
    0xff, 0xff, 0xff, 0xe0, 0x00, 0x01, 0xc0, 0x04, 0xe0, 0x00, 0x10, 0x00, 0x60, 0x1f, 0xff, 0xff, 
    0xff, 0xff, 0xff, 0xe0, 0x00, 0x01, 0xff, 0xff, 0xc2, 0x2c, 0x67, 0x00, 0x00, 0x1f, 0xff, 0xff, 
    0xff, 0xff, 0xff, 0xe0, 0x00, 0x01, 0xff, 0xff, 0x84, 0x00, 0xe7, 0x80, 0x00, 0x0f, 0xff, 0xff, 
    0xff, 0xff, 0xff, 0xec, 0x00, 0x00, 0x3f, 0xff, 0x80, 0x00, 0x06, 0xc0, 0x00, 0x03, 0xff, 0xff, 
    0xff, 0xff, 0xff, 0xfc, 0x20, 0x1c, 0x0f, 0xfc, 0x06, 0x00, 0x00, 0xf0, 0x00, 0x03, 0xff, 0xff, 
    0xff, 0xff, 0xff, 0xff, 0x7f, 0xf0, 0x0e, 0x3f, 0x38, 0x00, 0x7f, 0x3c, 0x00, 0x01, 0xff, 0xff, 
    0xff, 0xff, 0xff, 0xff, 0xff, 0xfc, 0x00, 0x00, 0x00, 0x00, 0x7f, 0x8f, 0x00, 0x00, 0xff, 0xff, 
    0xff, 0xff, 0xff, 0xff, 0xff, 0xfc, 0x3f, 0xff, 0xfc, 0x00, 0xff, 0xf7, 0xc0, 0x00, 0xff, 0xff, 
    0xff, 0xff, 0xff, 0xff, 0xff, 0xf0, 0x3f, 0xff, 0xff, 0x81, 0xff, 0xf7, 0xc0, 0x02, 0xff, 0xff, 
    0xff, 0xff, 0xff, 0xff, 0xff, 0xe0, 0xff, 0xff, 0xff, 0xe1, 0xff, 0xfb, 0xf8, 0x0c, 0xff, 0xff, 
    0xff, 0xff, 0xff, 0xff, 0xfe, 0x40, 0xff, 0xff, 0xff, 0xe3, 0xff, 0xfb, 0xfc, 0x1f, 0xff, 0xff, 
    0xff, 0xff, 0xff, 0xff, 0xff, 0x80, 0xff, 0xff, 0xff, 0xe3, 0xff, 0xfc, 0xfe, 0x13, 0xff, 0xff, 
    0xff, 0xff, 0xff, 0xff, 0xfa, 0x00, 0xff, 0xff, 0xff, 0xef, 0xff, 0xff, 0xff, 0xe3, 0xff, 0xff, 
    0xff, 0xff, 0xff, 0xff, 0xfe, 0x00, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0x7f, 0xe3, 0xff, 0xff, 
    0xff, 0xff, 0xff, 0xff, 0xfc, 0x00, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xf3, 0xff, 0xff, 
    0xff, 0xff, 0xff, 0xff, 0xf8, 0x00, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xfc, 0x33, 0xff, 0xff, 
    0xff, 0xff, 0xff, 0xff, 0x80, 0x00, 0xff, 0xc7, 0xff, 0xfe, 0xff, 0xff, 0xfc, 0x03, 0xff, 0xff, 
    0xff, 0xff, 0xff, 0xff, 0x80, 0x00, 0xff, 0xc7, 0xff, 0xfe, 0x7f, 0xff, 0xfc, 0x03, 0xff, 0xff
};

// Текущая выбранная игра
int currentGame = GAME_DINO;
volatile bool inMenu = false; // Флаг, показывающий, что мы в меню

void setup() {
  Serial.begin(9600);
  pinMode(RIGHT_BTN, INPUT_PULLUP);
  pinMode(LEFT_BTN, INPUT_PULLUP);
  pinMode(CHANGE_BTN, INPUT_PULLUP);
  attachInterrupt(digitalPinToInterrupt(CHANGE_BTN), changeButtonInterrupt, FALLING);
  // Инициализируем дисплей
  if(!display.begin(SSD1306_SWITCHCAPVCC, SCREEN_ADDRESS)) {
    Serial.println(F("SSD1306 allocation failed"));
    for(;;); // Зацикливаемся, если не удалось инициализировать дисплей
  }
  display.clearDisplay();
  display.drawBitmap(0, 0, image_data_girlico, 128, 64, 1);
  display.display();
  delay(3000);
  
}

unsigned long lastMenuUpdate = 0;
unsigned long lastGameUpdate = 0;

void loop() {
  
  unsigned long currentTime = millis();

  if (inMenu) { // Выбор игры
    if (currentTime - lastGameUpdate >= 50) { // Игра обновляется каждые 50 мс
      lastGameUpdate = currentTime;
      Serial.println("запускаем игру");
      runSelectedGame(currentGame);
    }
  } else { // Возврат в меню
    if (currentTime - lastMenuUpdate >= 500) { // Меню обновляется каждые 500 мс (0.5 с)
      lastMenuUpdate = currentTime;
      Serial.println("меню");
      displayMenu(currentGame);
    }
  }
}

void changeButtonInterrupt() {
  inMenu = !inMenu;
}

void displayMenu(int selectedGame) {
  if (!digitalRead(RIGHT_BTN)) {
    
    Serial.println("вправо в меню");
      currentGame = (currentGame + 1) % GAME_COUNT;
      displayMenu(currentGame);
    }
    else if (!digitalRead(LEFT_BTN)) {
    
    Serial.println("влево в меню");
      currentGame = (currentGame - 1 + GAME_COUNT) % GAME_COUNT;
      displayMenu(currentGame);
    }
  display.clearDisplay();
  display.setTextSize(2);
  display.setTextColor(SSD1306_WHITE);

  // Отображаем название каждой игры
  display.setCursor(40, 15);
  display.println("Dino");
  display.setCursor(15, 45);
  display.println("Arcanoid");

  // Выделяем текущую выбранную игру
  if (selectedGame == GAME_DINO) {
    display.drawRect(8, 8, 112, 26, SSD1306_WHITE);
  } else {
    display.drawRect(8, 38, 112, 26, SSD1306_WHITE);
  }
  display.display();
  
}  

void runSelectedGame(int gameIndex) {
  switch (gameIndex) {
    case GAME_DINO:
      runDinoGame();
      break;
    case GAME_ANOTHER:
      runAnotherGame();
      break;
  }
}

void runDinoGame() {
  static bool firstFlag = true;
  if (firstFlag) {
    dino.setup();
    firstFlag = false;
  }
  dino.loop();
  
}

void runAnotherGame() {
  static bool firstFlag = true;
  if (firstFlag) {
    arcanoid.setup();
    firstFlag = false;
  }
  arcanoid.loop();
}
