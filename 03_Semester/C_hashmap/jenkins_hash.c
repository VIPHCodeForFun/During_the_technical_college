#include <stdio.h>
#include <stdint.h> // unit32_t unit8_t

/* https://en.wikipedia.org/wiki/Jenkins_hash_function */
uint32_t jenkins_one_at_a_time_hash(const uint8_t *key, size_t length);
uint32_t what_happens_jenkins_one_at_a_time_hash(const uint8_t *key, size_t length);

int main()
{

    char teststring[] = "The quick brown fox jumps over the lazy dog";
    int len_teststring = sizeof(teststring) - 1; //-1 ohne das [\0] End of String zeichen

    printf("%d\n", len_teststring);
    what_happens_jenkins_one_at_a_time_hash(teststring, len_teststring);

    /*
    one_at_a_time("The quick brown fox jumps over the lazy dog", 43)
    0x519e91f5
    */

    return 0;
}

/* https://en.wikipedia.org/wiki/Jenkins_hash_function */
uint32_t jenkins_one_at_a_time_hash(const uint8_t *key, size_t length)
{
    size_t i = 0;
    uint32_t hash = 0;
    while (i != length)
    {
        hash += key[i++];   //hash = hash + key[i]
        hash += hash << 10; //hash = hash + (hash um 10 nach linls schieben)
        hash ^= hash >> 6;  //hash = hash XOR (hash um 6 nach rechts verschieben)
    }
    hash += hash << 3;  //hash + (rechts links verschieben)
    hash ^= hash >> 11; //hash XOR ( hash um 11 nach lins verschieben)
    hash += hash << 15; //hash + (hash um 15 nach rechs verschieben)
    return hash;
}
/* https://en.wikipedia.org/wiki/Jenkins_hash_function */
uint32_t what_happens_jenkins_one_at_a_time_hash(const uint8_t *key, size_t length)
{
    size_t i = 0;
    uint32_t hash = 0;
    while (i != length)
    {
        printf("hash in HEX = [%x]  hash in long = [%lu] \n", hash, hash);
        hash += key[i++]; //hash = hash + key[i]
        printf("hash in HEX = [%x]  hash in long = [%lu] \n", hash, hash);
        hash += hash << 10; //hash = hash + (hash um 10 nach linls schieben)
        printf("hash in HEX = [%x]  hash in long = [%lu] \n", hash, hash);
        hash ^= hash >> 6; //hash = hash XOR (hash um 6 nach rechts verschieben)
    }
    hash += hash << 3; //hash + (rechts links verschieben)
    printf("hash in HEX = [%x]  hash in long = [%lu] \n", hash, hash);
    hash ^= hash >> 11; //hash XOR ( hash um 11 nach lins verschieben)
    printf("hash in HEX = [%x]  hash in long = [%lu] \n", hash, hash);
    hash += hash << 15; //hash + (hash um 15 nach rechs verschieben)
    printf("hash in HEX = [%x]  hash in long = [%lu] \n", hash, hash);
    return hash;
}
uint32_t hashInTheTasch(const uint8_t *key, size_t length)
{
    uint32_t hash = 0;
    int i = 0;
    while (i != length)
    {
        i++;
        if (i < 16)
        {
            hash = hash * i;
        }
        else if (i < 25)
        {
            hash = hash * (i / 2);
        }
        else
        {
            hash = hash * (i / 2);
        }
    }
    return hash;
}