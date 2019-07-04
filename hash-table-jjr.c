#include <stdio.h>
#include <stdlib.h>


#define SIZE 20

struct Pair {
  int key;
  int data;
};

struct Pair* item;
struct Pair* hashtable[SIZE];

int hashfunction(int key)
{
  return key % SIZE;
}


struct Pair* search(int key)
{
  int idx = hashfunction(key);

  while(hashtable[idx] != NULL) {
    if(hashtable[idx]->key == key) {
        return hashtable[idx];
    }

    idx++;
    idx = idx % SIZE; //idx = (idx > SIZE-1) ? 0 : idx;
  }
}


void insert(int key, int data)
{
  struct Pair* newpair = (struct Pair*) malloc(sizeof(struct Pair));
  newpair->key = key;
  newpair->data = data;

  int idx = hashfunction(newpair->key);

  while(hashtable[idx] != NULL) {
    idx++;
    idx = idx % SIZE;
  }

  hashtable[idx] = newpair;
}


void delete(struct Pair* item)
{
  if(item == NULL)
    return;

  int idx = hashfunction(item->key);

  while(hashtable[idx] != NULL) {
    if(hashtable[idx]->key == item->key) {
      hashtable[idx] = NULL;
      return;
    }
    idx++;
    idx = idx % SIZE;
  }
}



void display() {
   int i = 0;

   for(i = 0; i<SIZE; i++) {

      if(hashtable[i] != NULL)
         printf(" (%d,%d)",hashtable[i]->key,hashtable[i]->data);
      else
         printf(" ~~ ");

      printf("\n");
   }

   printf("\n");
}

int main() {
   //dummyItem = (struct Pair*) malloc(sizeof(struct Pair));
   //dummyItem->data = -1;
   //dummyItem->key = -1;

   insert(1, 20);
   insert(2, 70);
   insert(42, 80);
   insert(4, 25);
   insert(12, 44);
   insert(14, 32);
   insert(17, 11);
   insert(13, 78);
   insert(37, 97);

   display();
   item = search(37);
   printf("Search for item with key 37\n");

   if(item != NULL) {
      printf("Element found, data: %d\n", item->data);
   } else {
      printf("Element not found\n");
   }

   delete(item);
   item = search(37);
   printf("Search for item with key 37\n");

   if(item != NULL) {
      printf("Element found, data: %d\n", item->data);
   } else {
      printf("Element not found\n");
   }
}
