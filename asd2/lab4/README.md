# Лабораторна робота 4. Характеристики та зв'язність графа

Метою лабораторної роботи No4. «Характеристики та зв'язність графа» є
дослідити характеристики графів та навчитись визначати їх на конкретних
прикладах, вивчення методу транзитивного замикання.

Лабораторна робота розроблена для ОС **Windows**.

## Встановлення та компіляція
Ви повинні мати встановлений компілятор **GCC**. Для спочатку склонуйте репозиторій локально:

`git clone https://github.com/basarabst/asd2-lab4.git`

Перейдіть у папку склонованого репозиторію та, якщо ви маєте **Bush GNU**, виконайте скрипти:

`bash compile.sh`

`bash compile-output.sh`

А якщо ж ні, то скомпілюйте безпосередньо:

`gcc src/app.c src/utils/coords.c  src/utils/properties.c src/drawing/graphs.c src/drawing/edges.c -mwindows -o app.exe`

`gcc src/output.c src/utils/properties.c -o output.exe`

>Зауваження: app.exe - вікно з графами, output.exe - консольний вивід параметрів цих графів (варто запускати з консолі)

## Основні параметри

При виконанні лабораторної роботи була використана умова з Лаб. роботи 3, **а також**:

- Коефіцієнт для орієнтованого і неорієнтованого графів: **0.68**
- Коефіцієнт для модифікованого графа: **0.72**

## Параметри графів

### Орієнтованого графа
![directed graph info](https://i.imgur.com/hn1Nq2h.png)

### Неорієнованого графа
![undirected graph info](https://i.imgur.com/QO3voem.png)

### Модифікованого графа і його графа конденсації
![modified graph info](https://i.imgur.com/wVxHbBG.png)
![modified graph info](https://i.imgur.com/hsK4MHo.png)
![modified graph info](https://i.imgur.com/ts7aq7m.png)
![modified graph info](https://i.imgur.com/DUlqqzN.png)
![modified graph info](https://i.imgur.com/vaaOqmS.png)
![modified graph info](https://i.imgur.com/X5pMpu4.png)

## Графічне представлення
Ви можете **переключатися** між графами за допомогою клавіш Shift, Ctrl, Tab і Space.

### Орієнтований граф
![directed graph](https://i.imgur.com/7ISgxAh.png)

### Неорієнтований граф
![undirected graph](https://i.imgur.com/63Kmipd.png)

### Модифікований граф
![modified graph](https://i.imgur.com/IqE2EtX.png)

### Граф конденсації
![сondensation graph](https://i.imgur.com/eLiykcn.png)