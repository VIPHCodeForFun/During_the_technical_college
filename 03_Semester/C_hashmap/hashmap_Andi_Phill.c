#include <stdio.h>
#include <stdlib.h>
#include <stdint.h> // unit32_t unit8_t
#include <string.h>

/* Struktur für einen Tabelleneintrag, Pointer- oder Array-basiert */
struct entry_s
{
  char *data;
  char *key;
  struct entry_s *next;
};
typedef struct entry_s entry_t;
/* Struktur welche die Eintraege enthaelt; Pointer- oder Array-basiert */
struct hashmap_s
{
  size_t size;
  entry_t **ptr_array_entry; //*ptr_ptr_array_entry[]
};
typedef struct hashmap_s hashmap_t;

hashmap_t *hm_create(size_t size); // Initialisiert eine Hashmap
unsigned int hm_hash();            // Berechnet Hash eines Keys
uint32_t create_hash(const uint8_t *key, size_t length);
entry_t *hm_new_entry(char key[], char data[]);         // Initiaisiert einen Eintrag
void hm_insert(entry_t *entry, hashmap_t *ptr_hashmap); // Fuegt ein Wertepaar ein
char *hm_get();                                         // Holt ein Wertepaar
void hm_free();                                         // Free all memory

int main()
{
  hashmap_t *hashmap = hm_create(20);
  entry_t *list[10] = {
      hm_new_entry("SSY", "KLAUS"),
      hm_new_entry("OOP", "PLAUS"),
      hm_new_entry("OOP", "FLAUS"),
      hm_new_entry("XXS", "LLAUS"),
      hm_new_entry("SSY", "RLAUS"),
  };

  hm_insert(list[0], hashmap);
  hm_insert(list[1], hashmap);
  hm_insert(list[2], hashmap);
  hm_insert(list[3], hashmap);
  printf("Daten: %s", hm_get("SSY", hashmap));
  return 0;
}
hashmap_t *hm_create(size_t size) // Initialisiert eine Hashmap
{
  hashmap_t *ptr_hashmap = calloc(1, sizeof(hashmap_t));
  if (ptr_hashmap == NULL)
  {
    return NULL;
  }
  ptr_hashmap->size = size;
  ptr_hashmap->ptr_array_entry = calloc(size, sizeof(entry_t *));
  if (ptr_hashmap->ptr_array_entry == NULL)
  {
    return NULL;
  }
  return ptr_hashmap;
}
unsigned int hm_hash(char key[], hashmap_t *ptr_hashmap) // Berechnet Hash eines Keys
{
  return create_hash(key, strlen(key)) % ptr_hashmap->size;
}
/* https://en.wikipedia.org/wiki/Jenkins_hash_function */
uint32_t create_hash(const uint8_t *key, size_t length)
{
  size_t i = 0;
  uint32_t hash = 0;
  while (i != length)
  {
    hash += key[i++];   // hash = hash + key[i]
    hash += hash << 10; // hash = hash + (hash um 10 nach linls schieben)
    hash ^= hash >> 6;  // hash = hash XOR (hash um 6 nach rechts verschieben)
  }
  hash += hash << 3;  // hash + (rechts links verschieben)
  hash ^= hash >> 11; // hash XOR ( hash um 11 nach lins verschieben)
  hash += hash << 15; // hash + (hash um 15 nach rechs verschieben)
  return hash;
}
entry_t *hm_new_entry(char key[], char data[]) // Initiaisiert einen Eintrag
{
  entry_t *ptr_entry = calloc(1, sizeof(entry_t));
  if (ptr_entry == NULL)
  {
    return NULL;
  }
  ptr_entry->key = calloc(strlen(key), sizeof(char));
  if (ptr_entry->key == NULL)
  {
    return NULL;
  }
  strcpy(ptr_entry->key, key);
  ptr_entry->data = calloc(strlen(data), sizeof(char));
  if (ptr_entry->data == NULL)
  {
    return NULL;
  }
  strcpy(ptr_entry->data, data);
  return ptr_entry;
}
void hm_insert(entry_t *entry, hashmap_t *ptr_hashmap) // Fuegt ein Wertepaar ein
{
  if (entry == NULL || ptr_hashmap == NULL)
  {
    return;
  }
  unsigned int indexhash = hm_hash(entry->key, ptr_hashmap); // unsigned int  Berechnet Hash eines Keys
  entry_t **ptr_run = ptr_hashmap->ptr_array_entry + indexhash;
  if (*ptr_run == NULL)
  {
    *ptr_run = entry;
  }
  else
  {
    while ((*ptr_run)->next != NULL)
    {
      *ptr_run = (*ptr_run)->next;
    }
    (*ptr_run)->next = entry;
  }
  return;
}

// Holt ein Wertepaar
char *hm_get(char key[], hashmap_t *ptr_hashmap)
{
  entry_t *temprun;
  unsigned int indexhash = hm_hash(key, ptr_hashmap);
  if (ptr_hashmap->ptr_array_entry[indexhash] == NULL)
    return NULL;
  temprun = ptr_hashmap->ptr_array_entry[indexhash];
  while (temprun)
  {
    if (strcmp(temprun->key, key) == 0)
    {
      return temprun->data;
    }
    temprun = temprun->next;
  }
  return NULL;
}

// Free all memory

void hm_free(hashmap_t *ptr_hashmap) // Free all memory
{
  if (!ptr_hashmap)
    return;
  for (int i = 0; i < ptr_hashmap->size; i++)
  {
    entry_t *currentEntry = ptr_hashmap->ptr_array_entry[i];
    while (currentEntry)
    {
      entry_t *nextEntry = currentEntry->next; // naechsten Wert speichern
      free(currentEntry->data);
      free(currentEntry->key);
      free(currentEntry); // aktuellen Eintrag loeschen
      currentEntry = nextEntry;
    }
  }
  free(ptr_hashmap->ptr_array_entry);
  free(ptr_hashmap);
  return;
}