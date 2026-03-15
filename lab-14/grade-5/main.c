#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

typedef struct {
    char brand[20];
    char model[20];
    int  size;
    int  price;
} Sneaker;

// узел зигзагообразного списка согласно схеме:
//
// S → [a1] → [a3] → [a5] → ... → [aN-1] → nil
//       ↓       ↓     ↓               ↓
//     [a2]  ← [a4] ← [a6] ← ... ← [aN]
//     nil      nil    nil            nil
//
// верхний ряд: next → вправо
// нижний ряд:  next → влево (т.е. a4->next = a2, a6->next = a4 ...)
// cross: верхний узел → соответствующий нижний (только вниз↓)
// у нижнего узла cross → обратно вверх
typedef struct Node {
    Sneaker     *data;
    struct Node *next;   // верхний: вправо | нижний: влево
    struct Node *cross;  // вверх/вниз между рядами
    int          row;    // 0 = верхний, 1 = нижний
} Node;

Sneaker *CreateSneaker(void) {
    char *brands[] = {"Nike", "Adidas", "Puma"};
    char *models[] = {"Pro", "Super", "Ultra"};
    int   prices[] = {200, 250, 300, 350, 400, 450, 500};
    Sneaker *s = malloc(sizeof(Sneaker));
    strcpy(s->brand, brands[rand() % 3]);
    strcpy(s->model, models[rand() % 3]);
    s->size  = 36 + rand() % 9;
    s->price = prices[rand() % 7];
    return s;
}

Node *CreateNode(int row) {
    Node *n  = malloc(sizeof(Node));
    n->data  = CreateSneaker();
    n->next  = NULL;
    n->cross = NULL;
    n->row   = row;
    return n;
}

void PrintNode(Node *node) {
    printf("[%s] %-10s %-10s размер: %-3d цена: $%d\n",
           node->row == 0 ? "верх" : "низ ",
           node->data->brand, node->data->model,
           node->data->size,  node->data->price);
}

void FreeAll(Node *topHead, Node *botTail) {
    // верхний ряд — идём вправо
    Node *cur = topHead;
    while (cur) {
        Node *tmp = cur;
        cur = cur->next;
        free(tmp->data);
        free(tmp);
    }
    // нижний ряд — у нас есть хвост (самый правый = первый добавленный)
    // но мы его уже освободили через cross? нет — cross не владеет памятью
    // идём от botTail влево через next
    cur = botTail;
    while (cur) {
        Node *tmp = cur;
        cur = cur->next;  // next у нижних идёт влево
        free(tmp->data);
        free(tmp);
    }
}

int main(int argc, char *argv[]) {
    int N, K;
    if (argc > 2) { N = atoi(argv[1]); K = atoi(argv[2]); }
    else {
        printf("Длина верхнего ряда N: "); scanf("%d", &N);
        printf("Длина нижнего ряда K: "); scanf("%d", &K);
    }
    srand(time(NULL));

    // строим верхний ряд: topHead → a1 → a3 → ... → nil
    Node *topHead = NULL, *topTail = NULL;
    for (int i = 0; i < N; i++) {
        Node *node = CreateNode(0);
        if (!topHead) topHead = topTail = node;
        else { topTail->next = node; topTail = node; }
    }

    // строим нижний ряд в обратном порядке:
    // добавляем каждый новый узел В НАЧАЛО → получаем next влево
    // botTail — самый правый (последний добавленный в конец верхнего)
    // botHead — самый левый (крайний левый нижнего ряда, next = nil)
    Node *botHead = NULL;  // самый левый нижнего ряда (next = nil)
    Node *botTail = NULL;  // самый правый нижнего ряда
    for (int i = 0; i < K; i++) {
        Node *node = CreateNode(1);
        // добавляем в начало: node->next = текущий botHead
        node->next = botHead;
        botHead = node;
        if (!botTail) botTail = node;  // первый добавленный = самый правый
    }
    // теперь: botTail — самый правый (a_K позиция), next у него = botHead...
    // нет: botTail = первый созданный, т.е. самый правый визуально
    // botHead = последний созданный, т.е. самый левый (a2)

    // проставляем cross: i-й узел верхнего ↔ i-й узел нижнего (считая слева)
    // нижний ряд слева направо: botHead → (next ← т.е. идём от botTail)
    // нам нужно пройти нижний ряд слева направо —
    // соберём указатели нижнего ряда в массив для удобства
    Node **bot = malloc(K * sizeof(Node *));
    {
        // нижний ряд слева направо: botHead, botHead->cross?
        // нет — у нас next идёт влево. Соберём через обход от botTail вправо?
        // botTail->next указывает влево (к botTail-1)...
        // проще: пройдём от botHead по next — это даст порядок влево,
        // значит botHead — это a2 (самый левый), next от него = nil
        // а botTail — это aK (самый правый)
        // для cross нам нужно: top[0]↔bot[0](самый левый=a2),
        //                       top[1]↔bot[1](следующий левый=a4) ...
        // пройдём от botTail и соберём в обратном порядке
        Node *cur = botTail;
        for (int i = K - 1; i >= 0; i--) {
            bot[i] = cur;
            cur = cur->next;
        }
    }

    Node *t = topHead;
    for (int i = 0; i < N && i < K; i++) {
        t->cross  = bot[i];
        bot[i]->cross = t;
        t = t->next;
    }
    // лишние узлы длинного ряда — cross = NULL (п.7)
    while (t) { t->cross = NULL; t = t->next; }
    for (int i = (N < K ? N : K); i < K; i++) bot[i]->cross = NULL;
    free(bot);

    // навигация
    Node *cur = topHead;
    printf("Навигация: D/6 вправо(верх)/влево(низ), A/4 обратно, S/2 вниз, W/8 вверх, R - к S, Q выход\n");
    printf("Текущий:\n");
    PrintNode(cur);

    char ch;
    int  running = 1;
    while (running) {
        printf("Ввод: ");
        scanf(" %c", &ch);
        switch (ch) {
            case 'D': case 'd': case '6':
                // в верхнем: next вправо; в нижнем: движение "вправо" = против next (к botTail)
                if (cur->row == 0) {
                    if (cur->next) { cur = cur->next; PrintNode(cur); }
                    else {
                        printf("Конец верхнего ряда. Вернуться к S? (y/n): ");
                        scanf(" %c", &ch);
                        if (ch == 'y') { cur = topHead; PrintNode(cur); }
                    }
                } else {
                    // в нижнем ряду "вправо" — идём к узлу у которого next == cur
                    // т.е. ищем узел правее текущего
                    if (cur->cross && cur->cross->next &&
                        cur->cross->next->cross) {
                        // переход: вверх → вправо → вниз
                        Node *rightTop = cur->cross->next;
                        if (rightTop && rightTop->cross) { cur = rightTop->cross; PrintNode(cur); }
                        else printf("Конец нижнего ряда.\n");
                    } else printf("Конец нижнего ряда.\n");
                }
                break;
            case 'A': case 'a': case '4':
                // в верхнем: идём назад (ищем prev через обход от topHead)
                if (cur->row == 0) {
                    if (cur == topHead) { printf("Начало верхнего ряда.\n"); break; }
                    Node *prev = topHead;
                    while (prev->next && prev->next != cur) prev = prev->next;
                    cur = prev; PrintNode(cur);
                } else {
                    // в нижнем: next идёт влево — это и есть "назад" (к a2)
                    if (cur->next) { cur = cur->next; PrintNode(cur); }
                    else printf("Конец нижнего ряда (левый край).\n");
                }
                break;
            case 'S': case 's': case '2':
                if (cur->row == 0 && cur->cross) { cur = cur->cross; PrintNode(cur); }
                else if (cur->row == 0) printf("Нижний ряд короче, переход невозможен.\n");
                else printf("Вы уже в нижнем ряду.\n");
                break;
            case 'W': case 'w': case '8':
                if (cur->row == 1 && cur->cross) { cur = cur->cross; PrintNode(cur); }
                else if (cur->row == 1) printf("Верхний ряд короче, переход невозможен.\n");
                else printf("Вы уже в верхнем ряду.\n");
                break;
            case 'R': case 'r':
                cur = topHead; printf("Вернулись к S.\n"); PrintNode(cur);
                break;
            case 'Q': case 'q':
                running = 0;
                break;
            default:
                printf("Неизвестная команда.\n");
        }
    }

    // освобождаем память
    Node *tmp = topHead;
    while (tmp) { Node *nx = tmp->next; free(tmp->data); free(tmp); tmp = nx; }
    // нижний ряд: botHead (самый левый, next=nil) → идём к botTail через...
    // у нас next идёт влево, поэтому от botTail нет прямого обхода вправо
    // освободим через cross от верхнего — нет, cross не все покрывает
    // пройдём от botHead: next = nil (он крайний левый), не можем идти вправо
    // единственный способ — сохранили bot[] но уже free(bot)
    // решение: освобождаем нижний через cross верхнего + остатки
    // (в учебном коде это ок — утечка K узлов без cross)
    tmp = topHead;  // уже освобождён выше, используем заново через cross
    // правильное решение: до освобождения верхнего сохраняем нижние
    // переделаем: просто пройдём botHead по next (влево = к nil)
    tmp = botHead;
    while (tmp) { Node *nx = tmp->next; free(tmp->data); free(tmp); tmp = nx; }

    return 0;
}
