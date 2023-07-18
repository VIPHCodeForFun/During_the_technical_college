/*
 * Simple educational hash table (also called hash map) implementation in ANSI C
 * adapted from https://gist.github.com/tonious/1377667
 * with enhancements and fixes by myself and as suggested by commenters
 * changes include:
 * - fixed several memory leaks
 * - fixed some null pointer exceptions
 * - changed to a more robust hash function (jenkins)
 * - remove dependency on any str*-family functions
 * - added hm_free() to wipe complete table
 *
 * However, this should still not be used in production!
 *
 * compile with
 * gcc -std=c18 -Wall -Wextra -Werror -pedantic -o hashmap hash_map.c
 * for some extra scrutiny :)
 */


#include <stdlib.h>
#include <stdio.h>
#include <string.h> // only used for memcpy

struct entry_s {
  char * key;
  size_t keyLength;
  void * value;
  size_t valueLength;
  /* the next pointer links collided elements in one bin */
  struct entry_s* next;
};

typedef struct entry_s entry_t;

struct hashmap_s {
	size_t size;
	struct entry_s** table;
};

typedef struct hashmap_s hashmap_t;


/****  Function Prototypes ****/
hashmap_t*		hm_create( 		size_t 		size );

unsigned int 	hm_hash( 		hashmap_t*	hashmap,
								char*		key,
								size_t 		key_length );

entry_t*		hm_new_entry( 	char* 		key,
								char* 		value,
								size_t 		key_length,
								size_t 		value_len );

void 			hm_insert( 		hashmap_t* 	hashmap,
								char* 		key,
								size_t 		key_len,
								char* 		value,
								size_t 		value_len );

char* 			hm_get( 		hashmap_t* 	hashmap,
								char* 		key,
								size_t 		key_len,
								size_t* 	value_len );

void 			hm_delete(		hashmap_t* 	hashmap);

/* Create a new hashmap. */
hashmap_t *hm_create( size_t size ) {

	hashmap_t 	*hashmap = NULL;
	size_t 		i;

	if( size < 1 ) return NULL;

	/* Allocate the table itself. */
	if( ( hashmap = malloc( sizeof( hashmap_t ) ) ) == NULL ) {
		return NULL;
	}

  /* Allocate pointers to the head nodes. */
  if ((hashmap->table = malloc(sizeof( entry_t*) * size)) == NULL) {
	 /* mitigate memory leak on failure */
	 free(hashmap);
    return NULL;
  }
	for( i = 0; i < size; i++ ) {
		hashmap->table[i] = NULL;
	}

	hashmap->size = size;
	return hashmap;
}

/* Hash a key for a given hash table
 * Use Jenkins' one-at-a-time hash function
 * https://en.wikipedia.org/wiki/Jenkins_hash_function
 */
unsigned int hm_hash( hashmap_t *hashmap, char *key, size_t key_length ) {

  size_t i = 0;
  unsigned int hash = 0;

  if (hashmap == NULL || key == NULL || key_length == 0) {
    return -1;
  }

  while (i != key_length) {
    hash += key[i++];
    hash += hash << 10;
    hash ^= hash >> 6;
  }
  hash += hash << 3;
  hash ^= hash >> 11;
  hash += hash << 15;

  /* the modulo-operator (%) wraps the
  value around if it exceeds the number of bins */
	return hash % hashmap->size;
}

/* Create a new key-value pair to be used as an entry. */
entry_t *hm_new_entry( char *key, char *value, size_t key_length, size_t value_len ) {
	entry_t *newpair;

  if (key == NULL || value == NULL) {
    return NULL;
  }

	if( ( newpair = malloc( sizeof( entry_t ) ) ) == NULL ) {
		return NULL;
	}

	if( ( newpair->key = memcpy( malloc( key_length ), key, key_length ) ) == NULL ) {
		return NULL;
	}
  newpair->keyLength = key_length;

	if( ( newpair->value = memcpy( malloc( value_len ), value, value_len ) ) == NULL ) {
		return NULL;
	}
  newpair->valueLength = value_len;
	newpair->next = NULL;

	return newpair;
}

/* Insert a key-value pair into a hash table. */
void hm_insert( hashmap_t *hashmap, char *key, size_t key_len, char *value, size_t value_len ) {
	int bin = 0;
	entry_t *newpair = NULL;
	entry_t *next = NULL;
	entry_t *last = NULL;

  if (hashmap == NULL || key == NULL || value == NULL) {
    return;
  }

	bin = hm_hash( hashmap, key, key_len );

	next = hashmap->table[ bin ];

	while( next != NULL && next->key != NULL && (key_len==next->keyLength? memcmp( key, next->key, key_len ) : 0) > 0 ) {
		last = next;
		next = next->next;
	}

	/* There's already a pair -> replace that string. */
	if( next != NULL && next->key != NULL && (key_len==next->keyLength? memcmp( key, next->key, key_len ) : 0) == 0 ) {
		free( next->value );
		next->value = memcpy( malloc( value_len ), value, value_len );
    next->valueLength = value_len;
	/* None found */
	} else {
		newpair = hm_new_entry( key, value, key_len, value_len );

		/* We're at the start of the linked list in this bin. */
		if( next == hashmap->table[ bin ] ) {
			newpair->next = next;
			hashmap->table[ bin ] = newpair;

		/* We're at the end of the linked list in this bin. */
		} else if ( next == NULL ) {
			last->next = newpair;

		/* We're in the middle of the list. */
		} else  {
			newpair->next = next;
			last->next = newpair;
		}
	}
}

/* Retrieve a value for a given key from a hash table. */
char *hm_get( hashmap_t *hashmap, char *key, size_t key_len, size_t* value_len ) {

	int bin = 0;
	entry_t *pair;

  if (hashmap == NULL || key == NULL) {
    return NULL;
  }

	bin = hm_hash( hashmap, key, key_len );

	/* Step through the bin, looking for our value. */
	pair = hashmap->table[ bin ];
	while( pair != NULL && pair->key != NULL && (key_len==pair->keyLength? memcmp(key, pair->key, key_len) : 0) > 0 ) {
		pair = pair->next;
	}

	/* Did we find anything? */
	if( pair == NULL || pair->key == NULL || (key_len==pair->keyLength? memcmp(key, pair->key, key_len) : 0) != 0 ) {
		return NULL;

	} else {
    if (value_len != NULL) {
      *value_len = pair->valueLength;
		}
    return pair->value;
	}

}


void hm_free(hashmap_t* hashmap) {
	size_t idx = 0;
	entry_t* currentEntry;
	entry_t* nextEntry;
	for (idx = 0; idx < hashmap->size; idx++) {
		currentEntry = hashmap->table[idx];
		if (currentEntry) {
			nextEntry = currentEntry->next;
			free(currentEntry);
			while ( (currentEntry = nextEntry) ) {
				nextEntry = currentEntry->next;
				free(currentEntry);
			}
		}
	}
	free(hashmap);
}



int main(void) {

	hashmap_t *hashmap = hm_create( 65536 );

	hm_insert( hashmap, "key1", strlen("key1"), "axe", 	  strlen("axe")    );
	hm_insert( hashmap, "key2", strlen("key2"), "chisel", strlen("chisel") );
	hm_insert( hashmap, "key3", strlen("key3"), "sledge", strlen("sledge") );
	hm_insert( hashmap, "key4", strlen("key4"), "hammer", strlen("hammer") );
	/* discard value lengths as here they are strings */
	printf( "%s\n", hm_get( hashmap, "key1", strlen("key1"), NULL ) );
	printf( "%s\n", hm_get( hashmap, "key2", strlen("key2"), NULL ) );
	printf( "%s\n", hm_get( hashmap, "key3", strlen("key3"), NULL ) );
	printf( "%s\n", hm_get( hashmap, "key4", strlen("key4"), NULL ) );

	puts("Freeing memory...");
	hm_free(hashmap);
	puts("All done, bye!");

	return 0;
}
