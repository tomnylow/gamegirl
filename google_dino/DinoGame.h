void initDinoGame(int16_t* treeX, int16_t* tree1X, int16_t* dinoY, int* jump, int* score) {
    pinMode(RIGHT_BTN, INPUT_PULLUP);
	display.setTextSize(2);             // Draw 2X-scale text
  display.setTextColor(SSD1306_WHITE);
  display.setCursor(10,5);
  display.println("Dino Game");
  

  display.setTextSize(1);
  
  display.setCursor(5,45);
  display.println("Press To Play");
  
  display.display();

  while(digitalRead(RIGHT_BTN) == HIGH);	 
   }

void updateDinoGame(int16_t* treeX, int16_t* tree1X, int16_t* dinoY, int* jump, int* score) {
  // Обработка ввода пользователя
  if (digitalRead(10) == LOW) {
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
    *treeX = random(0, 1);
  }

  if (*tree1X == 0) {
    *tree1X = 195;
    *tree1X = random(0, 1);
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
      display.println("Press Left Btn to");
      display.setCursor(10, 50);
      display.println("return to Menu");
      display.display();
      delay(2000); // Задержка, чтобы игрок успел прочитать сообщение
      *jump = -1; // Флаг для завершения игры
    }
  }
}