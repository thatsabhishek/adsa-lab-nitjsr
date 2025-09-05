#include <stdio.h>
#include <stdlib.h>
#define MAX 100

// Stack structure
struct Stack {
    int arr[MAX];
    int top;
};

// Initialize stack
void init(struct Stack *s) {
    s->top = -1;
}

// Check if empty
int isEmpty(struct Stack *s) {
    return s->top == -1;
}

// Check if full
int isFull(struct Stack *s) {
    return s->top == MAX - 1;
}

// Push element
void push(struct Stack *s, int x) {
    if (isFull(s)) {
        printf("Stack Overflow\n");
        return;
    }
    s->arr[++s->top] = x;
}

// Pop element
int pop(struct Stack *s) {
    if (isEmpty(s)) {
        return -1;  // error
    }
    return s->arr[s->top--];
}

// Peek top element
int peek(struct Stack *s) {
    if (isEmpty(s)) return -1;
    return s->arr[s->top];
}


//    METHOD 1: Queue using two stacks (Push costly)
struct Queue1 {
    struct Stack s1, s2;
};

void initQ1(struct Queue1 *q) {
    init(&q->s1);
    init(&q->s2);
}

// Enqueue costly
void enqueue1(struct Queue1 *q, int x) {
    // Move everything from s1 → s2
    while (!isEmpty(&q->s1)) {
        push(&q->s2, pop(&q->s1));
    }

    // Push new element into s1
    push(&q->s1, x);

    // Move back s2 → s1
    while (!isEmpty(&q->s2)) {
        push(&q->s1, pop(&q->s2));
    }
    printf("Enqueued %d\n", x);
}

// Dequeue easy
int dequeue1(struct Queue1 *q) {
    if (isEmpty(&q->s1)) {
        printf("Queue Underflow\n");
        return -1;
    }
    return pop(&q->s1);
}

void display1(struct Queue1 *q) {
    if (isEmpty(&q->s1)) {
        printf("Queue is empty\n");
        return;
    }
    printf("Queue (front → rear): ");
    for (int i = q->s1.top; i >= 0; i--) {
        printf("%d ", q->s1.arr[i]);
    }
    printf("\n");
}


//    METHOD 2: Queue using two stacks (Pop costly)
struct Queue2 {
    struct Stack s1, s2;
};

void initQ2(struct Queue2 *q) {
    init(&q->s1);
    init(&q->s2);
}

// Enqueue easy
void enqueue2(struct Queue2 *q, int x) {
    push(&q->s1, x);
    printf("Enqueued %d\n", x);
}

// Dequeue costly
int dequeue2(struct Queue2 *q) {
    if (isEmpty(&q->s1) && isEmpty(&q->s2)) {
        printf("Queue Underflow\n");
        return -1;
    }

    if (isEmpty(&q->s2)) {
        while (!isEmpty(&q->s1)) {
            push(&q->s2, pop(&q->s1));
        }
    }

    return pop(&q->s2);
}

void display2(struct Queue2 *q) {
    if (isEmpty(&q->s1) && isEmpty(&q->s2)) {
        printf("Queue is empty\n");
        return;
    }
    printf("Queue (front → rear): ");

    // Print elements of s2 first (top → bottom)
    for (int i = 0; i <= q->s2.top; i++) {
        printf("%d ", q->s2.arr[i]);
    }

    // Then print elements of s1 (bottom → top)
    for (int i = q->s1.top; i >= 0; i--) {
        printf("%d ", q->s1.arr[i]);
    }

    printf("\n");
}

//    MAIN MENU
int main() {
    int choice, val, method;

    printf("Choose Method:\n");
    printf("1. Push costly\n");
    printf("2. Pop costly\n");
    printf("Enter method: ");
    scanf("%d", &method);

    if (method == 1) {
        struct Queue1 q;
        initQ1(&q);

        while (1) {
            printf("\n--- Queue Menu (Push Costly) ---\n");
            printf("1. Enqueue\n2. Dequeue\n3. Display\n4. Exit\n");
            printf("Enter choice: ");
            scanf("%d", &choice);

            switch (choice) {
            case 1:
                printf("Enter value: ");
                scanf("%d", &val);
                enqueue1(&q, val);
                break;
            case 2:
                val = dequeue1(&q);
                if (val != -1) printf("Dequeued %d\n", val);
                break;
            case 3:
                display1(&q);
                break;
            case 4:
                exit(0);
            default:
                printf("Invalid choice\n");
            }
        }
    } else if (method == 2) {
        struct Queue2 q;
        initQ2(&q);

        while (1) {
            printf("\n--- Queue Menu (Pop Costly) ---\n");
            printf("1. Enqueue\n2. Dequeue\n3. Display\n4. Exit\n");
            printf("Enter choice: ");
            scanf("%d", &choice);

            switch (choice) {
            case 1:
                printf("Enter value: ");
                scanf("%d", &val);
                enqueue2(&q, val);
                break;
            case 2:
                val = dequeue2(&q);
                if (val != -1) printf("Dequeued %d\n", val);
                break;
            case 3:
                display2(&q);
                break;
            case 4:
                exit(0);
            default:
                printf("Invalid choice\n");
            }
        }
    } else {
        printf("Invalid method selected.\n");
    }

    return 0;
}
