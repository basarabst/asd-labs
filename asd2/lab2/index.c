#include <stdio.h>
#include <stdlib.h>

typedef struct linkedListModel {
  double data;
  struct linkedListModel *next;
  struct linkedListModel *related;
} linkedList;

linkedList *linkedListCreate(int n) {
  if (n % 2) {
    printf("Error: the num of list items must be 2n\n");
    return NULL;
  }
  printf("\n-- LinkedList Create --\n");
  linkedList *nodePointer;
  linkedList *relatedNode;
  for (int i = n; i >= 1; i--) {
    linkedList *node;
    node = malloc(sizeof(struct linkedListModel));
    printf("Enter the data for node %d: ", i);
    scanf("%lf", &node->data);
    if (i == n) node->next = NULL;
    else node->next = nodePointer;
    if (i > n/2) {
      relatedNode = node;
      node->related = NULL;
    } else {
      node->related = relatedNode;
      relatedNode = relatedNode->next;
    }
    nodePointer = node;
  }
  return nodePointer;
}

void linkedListRemove(linkedList *nodePointer) {
  if(!nodePointer) return;
  size_t *node;
  while (nodePointer) {
    node = nodePointer;
    nodePointer = nodePointer->next;
    free(node);
  }
  printf("\n...linkedList removed: memory freed\n");
}

void output(linkedList *nodePointer) {
  if(!nodePointer) return;
  printf("\n-- LinkedList Output --\n");
  while(nodePointer) {
    double data = nodePointer->data;
    linkedList *next = nodePointer->next;
    linkedList *related = nodePointer->related;
    printf("pointer = %p data = %lf next = %p related = %p\n", nodePointer, data, next, related);
    nodePointer = next;
  }
}

double calculate(linkedList *nodePointer) {
  if (!nodePointer) return;
  double res = 1;
  int flag = 1;
  while (nodePointer->related) {
    linkedList *related = nodePointer->related;
    double num1 = nodePointer->data;
    double num2 = related->data;
    double multiplier = flag * (num1 - num2);
    res *= multiplier;

    nodePointer = nodePointer->next;
    flag *= -1;
  }
  return res;
}

int main() {
  int n;
  printf("Enter the num of list items: ");
  scanf("%d", &n);

  linkedList *nodePointer = linkedListCreate(n);
  output(nodePointer);
  double res = calculate(nodePointer);
  printf("\nThe result of the expression calculation: %lf\n", res);
  linkedListRemove(nodePointer);

  return 0;
}
