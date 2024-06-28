// Включаем необходимые библиотеки
#include <Wire.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>

// Определяем константы для экрана
#define SCREEN_WIDTH 128
#define SCREEN_HEIGHT 64
#define OLED_RESET -1
#define SCREEN_ADDRESS 0x3C

// Создаем объект дисплея
Adafruit_SSD1306 display(SCREEN_WIDTH, SCREEN_HEIGHT, &Wire, OLED_RESET);

// Определяем константы для игр
#define GAME_COUNT 2 // Количество игр
#define GAME_DINO 0
#define GAME_ANOTHER 1 // Индекс другой игры
#define RIGHT_BTN 10
#define LEFT_BTN 7
#define CHANGE_BTN 6


#include "DinoGame.h"

// Текущая выбранная игра
int currentGame = GAME_DINO;
bool inMenu = true; // Флаг, показывающий, что мы в меню


void setup() {
  Serial.begin(9600);
  pinMode(RIGHT_BTN, INPUT_PULLUP);
  pinMode(LEFT_BTN, INPUT_PULLUP);
  pinMode(CHANGE_BTN, INPUT_PULLUP);
  
  // Инициализируем дисплей
  if(!display.begin(SSD1306_SWITCHCAPVCC, SCREEN_ADDRESS)) {
    Serial.println(F("SSD1306 allocation failed"));
    for(;;); // Зацикливаемся, если не удалось инициализировать дисплей
  }

  // Запускаем меню
  displayMenu(currentGame);
}

void loop() {
  // Обработка ввода пользователя
  if (!digitalRead(CHANGE_BTN)) {
    if (inMenu) { // Выбор игры
    Serial.println("запускаем игру");
      inMenu = false;
      runSelectedGame(currentGame);
    } else { // Возврат в меню
    Serial.println("меню");
      inMenu = true;
      displayMenu(currentGame);
    }
  } else if (!digitalRead(RIGHT_BTN)) {
    if (inMenu) { // Перемещение вправо по меню
    Serial.println("вправо в меню");
      currentGame = (currentGame + 1) % GAME_COUNT;
      displayMenu(currentGame);
    }
  } else if (!digitalRead(LEFT_BTN)) {
    if (inMenu) { // Перемещение влево по меню
    Serial.println("влево в меню");
      currentGame = (currentGame - 1 + GAME_COUNT) % GAME_COUNT;
      displayMenu(currentGame);
    }
  }
  delay(100);
}

void displayMenu(int selectedGame) {
  display.clearDisplay();
  display.setTextSize(2);
  display.setTextColor(SSD1306_WHITE);

  // Отображаем название каждой игры
  display.setCursor(10, 10);
  display.println("Dino Game");
  display.setCursor(10, 40);
  display.println("Another Game");

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

  int16_t tree_x=127;
  int16_t tree1_x=195;
  int tree_type = random(0,2);
  int tree_type1 = random(0,2);

  int16_t dino_y = DINO_INIT_Y;
  int input_command;
  int jump=0;
  int score=0;

  initDinoGame(display);

  while(digitalRead(CHANGE_BTN)){
    
  updateDinoGame(&tree_x, &tree1_x, &dino_y, &jump, &score, &tree_type, &tree_type1, display);
  drawDinoGame(tree_x, tree1_x, dino_y, score, tree_type, tree_type1,  display);
  }
}

void runAnotherGame() {
  display.clearDisplay();
  display.setTextSize(2);
  display.setTextColor(SSD1306_WHITE);

  // Отображаем название каждой игры
  display.setCursor(10, 10);
  display.println("aRCANOIID");
  display.display();
}
