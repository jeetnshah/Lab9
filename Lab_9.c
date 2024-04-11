#include <stdio.h>
#include <stdlib.h>

// RecordType
struct RecordType
{
	int		id;
	char	name;
	int		order;
};

// Node for the linked list
struct Node
{
	struct RecordType record;
	struct Node* next;
};

// HashType
struct HashType
{
	struct Node** table;
	int size;
};

// Compute the hash function
int hash(int x, int size)
{
	return x % size;
}

// Insert a record into the hash table
void insert(struct HashType* hashTable, struct RecordType record)
{
	int index = hash(record.id, hashTable->size);
	struct Node* newNode = (struct Node*) malloc(sizeof(struct Node));
	newNode->record = record;
	newNode->next = hashTable->table[index];
	hashTable->table[index] = newNode;
}

// Display records in the hash table
void displayRecordsInHash(struct HashType* hashTable)
{
	for (int i = 0; i < hashTable->size; ++i)
	{
		struct Node* current = hashTable->table[i];
		if (current != NULL)
		{
			printf("Index %d -> ", i);
			while (current != NULL)
			{
				printf("%d, %c, %d -> ", current->record.id, current->record.name, current->record.order);
				current = current->next;
			}
			printf("NULL\n");
		}
	}
}

int main(void)
{
	struct RecordType *pRecords;
	int recordSz = 0;

	recordSz = parseData("input.txt", &pRecords);
	printRecords(pRecords, recordSz);

	// Create a hash table
	struct HashType hashTable;
	hashTable.size = recordSz;
	hashTable.table = (struct Node**) malloc(sizeof(struct Node*) * hashTable.size);
	for (int i = 0; i < hashTable.size; ++i)
		hashTable.table[i] = NULL;

	// Insert records into the hash table
	for (int i = 0; i < recordSz; ++i)
		insert(&hashTable, pRecords[i]);

	// Display records in the hash table
	displayRecordsInHash(&hashTable);

	return 0;
}
