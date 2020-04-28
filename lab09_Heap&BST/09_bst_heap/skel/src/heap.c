/**
 * SD, 2020
 * 
 * Lab #9, BST & Heap
 * 
 * Task #2 - Heap implementation
 */

#include "heap.h"
#include "utils.h"

heap_t *heap_create(int (*cmp_f) (const team_t *, const team_t *))
{
	heap_t *heap;

	heap = malloc(sizeof(heap_t));
	DIE(heap == NULL, "heap malloc");

	heap->cmp       = cmp_f;
	heap->size      = 0;
	heap->capacity  = 2;
	heap->arr       = malloc(heap->capacity * sizeof(team_t *));
	DIE(heap->arr == NULL, "heap->arr malloc");

	return heap;
}

static void __swap(team_t *team1, team_t *team2)
{
	team_t aux_team;

	aux_team = *team1;
	*team1 = *team2;
	*team2 = aux_team;

}

static void __push_down(heap_t *heap, team_t *team, int left, int right, int pos)
{	
	int next = left;
	if ((left > heap->size && right > heap->size) || left == pos || right == pos) {
		return;
	}
	
	if (left > heap->size)
	{
		next = right;
	}
	else if (right > heap->size)
	{
		next = left;
	}
	else if (heap->cmp(heap->arr[right], heap->arr[left]) < 0)
	{
		next = right;
	}
	else
	{
		next = left;
	}
	
	if (heap->cmp(heap->arr[next], team) > 0) {
		return;
	}

	__swap(team, heap->arr[next]);
	__push_down(heap, team, GO_LEFT(next), GO_RIGHT(next), next);

}

static void __push_up(heap_t *heap, team_t *team, int p, int prev)
{
	if ( prev == 0 || heap->cmp(team, heap->arr[p]) >= 0 ) {
		return;
	}

	__swap(team, heap->arr[p]);
	__push_up(heap, heap->arr[p], GO_UP(p), p);

}

static void __heap_insert_fix(heap_t *heap, int pos)
{
	team_t *tmp_team = heap->arr[heap->size];
	int p = GO_UP(pos);

	if (heap->size == 0) {
		return;
	}

	__push_up(heap, tmp_team, p, pos);
}

void heap_insert(heap_t *heap, team_t *team)
{
	char *rc;

	heap->arr[heap->size] = malloc(sizeof(team_t));
	DIE(heap->arr[heap->size] == NULL, "heap_insert malloc");

	heap->arr[heap->size]->name = calloc(TEAM_NAME_LEN, sizeof(char));
	DIE(heap->arr[heap->size]->name == NULL, "heap_insert name calloc");
	rc = strncpy(heap->arr[heap->size]->name, team->name, TEAM_NAME_LEN - 1);
	DIE(rc != heap->arr[heap->size]->name, "heap_insert name strncpy");
	heap->arr[heap->size]->score = team->score;

	__heap_insert_fix(heap, heap->size);

	heap->size++;
	if (heap->size == heap->capacity) {
		heap->capacity *= 2;

		heap->arr = realloc(heap->arr, heap->capacity * sizeof(team_t *));
		DIE(heap->arr == NULL, "heap->arr realloc");
	}
}

team_t heap_top(heap_t *heap)
{
	return *(heap->arr[0]);
}

static void __heap_pop_fix(heap_t *heap, int pos)
{
	team_t *tmp_team = heap->arr[0];
	int p = pos;
	int l = GO_LEFT(pos);
	int r = GO_RIGHT(pos);

	__push_down(heap, tmp_team, l, r, p);
}

void heap_pop(heap_t *heap)
{
	free(heap->arr[0]->name);
	free(heap->arr[0]);

	heap->arr[0] = heap->arr[heap->size - 1];

	heap->size--;

	__heap_pop_fix(heap, 0);
}

int heap_empty(heap_t *heap)
{
	return heap->size <= 0;
}

void heap_free(heap_t *heap)
{
	while (!heap_empty(heap))
	{
		heap_pop(heap);
	}

	free(heap->arr);
	free(heap);
}
