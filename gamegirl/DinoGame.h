// Dino.h
#ifndef DINO_H
#define DINO_H

#define DINO_WIDTH 25
#define DINO_HEIGHT 26
#define DINO_INIT_X 10 // Dino initial spawn location
#define DINO_INIT_Y 29 // Dino initial spawn location

#define BASE_LINE_X 0
#define BASE_LINE_Y 54
#define BASE_LINE_X1 127
#define BASE_LINE_Y1 54

#define TREE1_WIDTH 11
#define TREE1_HEIGHT 23
 
#define TREE2_WIDTH 22
#define TREE2_HEIGHT 23

#define TREE_Y 35

#define JUMP_PIXEL 22 // Number of pixel dino will jump

#include <Adafruit_SSD1306.h>

class Dino {
public:
    Dino(Adafruit_SSD1306& display) : display(display) {
        // Конструктор
        treeX = 127;
        tree1X = 195;
        dinoY = DINO_INIT_Y;
        jump = 0;
        score = 0;
        tree_type = 0;
        tree_type1 = 0;
        
    }

    void setup() {
        // Инициализация игры
        display.clearDisplay();
        display.setTextSize(2);
        display.setTextColor(SSD1306_WHITE);
        display.setCursor(10,5);
        display.println("Dino Game");

        display.setTextSize(1);
        display.setCursor(5,45);
        display.println("Press Right To Play");

        display.display();

        while(digitalRead(RIGHT_BTN));
    }

    void loop() {
        // Обновление и отрисовка игры
        updateDinoGame(&treeX, &tree1X, &dinoY, &jump, &score, &tree_type, &tree_type1, display);
        drawDinoGame(treeX, tree1X, dinoY, score, tree_type, tree_type1, display);
    }

private:

    static const unsigned char PROGMEM dino1[25*26];
    static const unsigned char PROGMEM tree1[11*23];
    static const unsigned char PROGMEM tree2[22*23];

    Adafruit_SSD1306& display;

    int16_t treeX, tree1X, dinoY;
    int jump, score, tree_type, tree_type1;
    

    void updateDinoGame(int16_t* treeX, int16_t* tree1X, int16_t* dinoY, int* jump, int* score,
                        int* tree_type, int* tree_type1, Adafruit_SSD1306& display) {
        // Обработка ввода пользователя
  if (digitalRead(RIGHT_BTN) == LOW) {
    if (*jump == 0) {
      *jump = 1;
    }
  }

  // Обновление позиции динозавра
  if (*jump == 1) {
    (*dinoY)--;
    if (*dinoY == (DINO_INIT_Y - JUMP_PIXEL)) {
      *jump = 2;
      (*score)++;
    }
  } else if (*jump == 2) {
    (*dinoY)++;
    if (*dinoY == DINO_INIT_Y) {
      *jump = 0;
    }
  }

  // Обновление позиции деревьев
  (*treeX)--;
  (*tree1X)--;

  if (*treeX == 0) {
  *treeX = 127;
  *tree_type = random(0, 2);
 }

 if (*tree1X == 0) {
  *tree1X = 195;
  *tree_type1 = random(0, 2);
 }

  // Проверка на проигрыш
  if ((*treeX <= (DINO_INIT_X + DINO_WIDTH) && *treeX >= (DINO_INIT_X + (DINO_WIDTH / 2))) ||
      (*tree1X <= (DINO_INIT_X + DINO_WIDTH) && *tree1X >= (DINO_INIT_X + (DINO_WIDTH / 2)))) {
    if (*dinoY >= (DINO_INIT_Y - 3)) {
      // Проигрыш
      display.clearDisplay();
      display.setTextSize(2);
      display.setTextColor(SSD1306_WHITE);
      display.setCursor(10, 10);
      display.println("Game Over");
      display.setTextSize(1);
      display.setCursor(10, 40);
      display.println("Press Change to");
      display.setCursor(10, 50);
      display.println("return to Menu");
      display.display();
      while(digitalRead(CHANGE_BTN));
    }
  }
    }

    void drawDinoGame(int16_t treeX, int16_t tree1X, int16_t dinoY, int score,
                      int tree_type, int tree_type1, Adafruit_SSD1306& display) {
        display.clearDisplay();

  // Отрисовка динозавра
  display.drawBitmap(DINO_INIT_X, dinoY, dino1, DINO_WIDTH, DINO_HEIGHT, SSD1306_WHITE);

  // Отрисовка деревьев
 if (tree_type == 0) {
  display.drawBitmap(treeX, TREE_Y, tree1, TREE1_WIDTH, TREE1_HEIGHT, SSD1306_WHITE);
 } else {
  display.drawBitmap(treeX, TREE_Y, tree2, TREE2_WIDTH, TREE2_HEIGHT, SSD1306_WHITE);
 }

 if (tree_type1 == 0) {
  display.drawBitmap(tree1X, TREE_Y, tree1, TREE1_WIDTH, TREE1_HEIGHT, SSD1306_WHITE);
 } else {
  display.drawBitmap(tree1X, TREE_Y, tree2, TREE2_WIDTH, TREE2_HEIGHT, SSD1306_WHITE);
 }
  // Отрисовка земли
  display.drawLine(BASE_LINE_X, BASE_LINE_Y, BASE_LINE_X1, BASE_LINE_Y1, SSD1306_WHITE);

  // Отрисовка счета
  display.setTextSize(1);
  display.setCursor(64, 10);
  display.print("Score: ");
  display.print(score);

  display.display();
    }
};

const unsigned char PROGMEM Dino::dino1[25*26] ={
  // 'dino', 25x26px
0x00, 0x00, 0x00, 0x00, 0x00, 0x07, 0xfe, 0x00, 0x00, 0x06, 0xff, 0x00, 0x00, 0x0e, 0xff, 0x00, 
0x00, 0x0f, 0xff, 0x00, 0x00, 0x0f, 0xff, 0x00, 0x00, 0x0f, 0xff, 0x00, 0x00, 0x0f, 0xc0, 0x00, 
0x00, 0x0f, 0xfc, 0x00, 0x40, 0x0f, 0xc0, 0x00, 0x40, 0x1f, 0x80, 0x00, 0x40, 0x7f, 0x80, 0x00, 
0x60, 0xff, 0xe0, 0x00, 0x71, 0xff, 0xa0, 0x00, 0x7f, 0xff, 0x80, 0x00, 0x7f, 0xff, 0x80, 0x00, 
0x7f, 0xff, 0x80, 0x00, 0x3f, 0xff, 0x00, 0x00, 0x1f, 0xff, 0x00, 0x00, 0x0f, 0xfe, 0x00, 0x00, 
0x03, 0xfc, 0x00, 0x00, 0x01, 0xdc, 0x00, 0x00, 0x01, 0x8c, 0x00, 0x00, 0x01, 0x8c, 0x00, 0x00, 
0x01, 0x0c, 0x00, 0x00, 0x01, 0x8e, 0x00, 0x00
};

const unsigned char PROGMEM Dino::tree1[11*23]={
            // 'tree1', 11x23px
          0x1e, 0x00, 0x1f, 0x00, 0x1f, 0x40, 0x1f, 0xe0, 0x1f, 0xe0, 0xdf, 0xe0, 0xff, 0xe0, 0xff, 0xe0, 
          0xff, 0xe0, 0xff, 0xe0, 0xff, 0xe0, 0xff, 0xe0, 0xff, 0xc0, 0xff, 0x00, 0xff, 0x00, 0x7f, 0x00, 
          0x1f, 0x00, 0x1f, 0x00, 0x1f, 0x00, 0x1f, 0x00, 0x1f, 0x00, 0x1f, 0x00, 0x1f, 0x00};
const unsigned char PROGMEM Dino::tree2[22*23]={
            // 'tree2', 22x23px
          0x1e, 0x01, 0xe0, 0x1f, 0x03, 0xe0, 0x1f, 0x4f, 0xe8, 0x1f, 0xff, 0xfc, 0x1f, 0xff, 0xfc, 0xdf, 
          0xff, 0xfc, 0xff, 0xff, 0xfc, 0xff, 0xff, 0xfc, 0xff, 0xff, 0xfc, 0xff, 0xff, 0xfc, 0xff, 0xff, 
          0xfc, 0xff, 0xef, 0xfc, 0xff, 0x83, 0xfc, 0xff, 0x03, 0xfc, 0xff, 0x03, 0xf8, 0x7f, 0x03, 0xe0, 
          0x1f, 0x03, 0xe0, 0x1f, 0x03, 0xe0, 0x1f, 0x03, 0xe0, 0x1f, 0x03, 0xe0, 0x1f, 0x03, 0xe0, 0x1f, 
          0x03, 0xe0, 0x1f, 0x03, 0xe0};

#endif // DINO_H
