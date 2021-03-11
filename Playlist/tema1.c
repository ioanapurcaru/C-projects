// copyright 2020 Purcaru Ioana-Denisa
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
struct Node
{
	char title[31], artist[31], album[31], year[5];
	struct Node *next, *prev;
};
struct LinkedList
{
	int size;
	struct Node *head, *cursor;
};
typedef struct Node Node;
typedef struct LinkedList LinkedList;
void MOVE_PREV(FILE *out, LinkedList *start)
{
	if(start == NULL)
		{
			fprintf(out, "Error: no track playing\n");
			return;
		}
	if(start->head == NULL)
		{
			fprintf(out, "Error: no track playing\n");
			return;
		}
	if(start->cursor == start->head)
		return;
	start->cursor = start->cursor->prev;
}
void MOVE_NEXT(FILE *out, LinkedList *start)
{
	if(start == NULL)
		{
			fprintf(out, "Error: no track playing\n");
			return;
		}
	if(start->head == NULL)
		{
			fprintf(out, "Error: no track playing\n");
			return;
		}
	if(start->cursor->next == NULL)
		return;
	start->cursor = start->cursor->next;
}
void SHOW_FIRST(FILE *out, LinkedList *start)
{
	Node *first;
	if(start == NULL)
		{
			fprintf(out, "Error: show empty playlist\n");
			return;
		}
	if(start->head == NULL)
		{
			fprintf(out, "Error: show empty playlist\n");
			return;
		}
	first = start->head;
	fprintf(out, "Title: %s\n", first->title);
	fprintf(out, "Artist: %s\n", first->artist);
	fprintf(out, "Album: %s\n", first->album);
	fprintf(out, "Year: %s\n", first->year);
}
void SHOW_LAST(FILE *out, LinkedList *start)
{
	int i;
	Node *last;
	if(start == NULL)
		{
			fprintf(out, "Error: show empty playlist\n");
			return;
		}
	if(start->head == NULL)
		{
			fprintf(out, "Error: show empty playlist\n");
			return;
		}
	last = start->head;
	for(i = 0; i < start->size-1 && last->next; i++)
		last = last->next;
	fprintf(out, "Title: %s\n", last->title);
	fprintf(out, "Artist: %s\n", last->artist);
	fprintf(out, "Album: %s\n", last->album);
	fprintf(out, "Year: %s\n", last->year);
}
void SHOW_CURR(FILE *out, LinkedList *start)
{
	Node *curent;
	if(start == NULL)
		{
			fprintf(out, "Error: show empty playlist\n");
			return;
		}
	if(start->head == NULL)
		{
			fprintf(out, "Error: show empty playlist\n");
			return;
		}
	curent = start->cursor;
	fprintf(out, "Title: %s\n", curent->title);
	fprintf(out, "Artist: %s\n", curent->artist);
	fprintf(out, "Album: %s\n", curent->album);
	fprintf(out, "Year: %s\n", curent->year);
}
void SHOW_PLAYLIST(FILE * out, LinkedList *start)
{
	int i;
	Node *curent;
	if(start == NULL)
		{
			fprintf(out, "[]\n");
			return;
		}
	if(start->head == NULL)
		{
			fprintf(out, "[]\n");
			return;
		}
	if(start->size == 1)
		{
			fprintf(out, "[%s]\n", start->head->title);
			return;
		}
	fprintf(out, "[");
	curent = start->head;
	for(i = 0; i < start->size-1 && curent->next; i++)
	{
		fprintf(out, "%s; ", curent->title);
		curent = curent->next;
	}
	fprintf(out, "%s]\n", curent->title);
}
void DEL_FIRST(FILE *out, LinkedList *start)
{
	Node *first, *curs;
	if(start == NULL)
		{
			fprintf(out, "Error: delete from empty playlist\n");
			return;
		}
	if(start->head == NULL)
		{
			fprintf(out, "Error: delete from empty playlist\n");
			return;
		}
	start->size--;
	first = start->head;
	if(first->next == NULL)
		{
			free(first);
			start->head = NULL;
			start->cursor = NULL;
			return;
		}
	curs = start->cursor;
	if(first == curs)
		start->cursor = first->next;
	start->head = first->next;
	free(first);
	first = start->head;
	first->prev = NULL;
}
void DEL_LAST(FILE *out, LinkedList *start)
{
	int i;
	Node *last, *curs, *curent;
	if(start == NULL)
		{
			fprintf(out, "Error: delete from empty playlist\n");
			return;
		}
	if(start->head == NULL)
		{
			fprintf(out, "Error: delete from empty playlist\n");
			return;
		}
	start->size--;
	last = start->head;
	if(last->next == NULL)
		{
			free(last);
			start->head = NULL;
			start->cursor = NULL;
			return;
		}
	curent = start->head;
	curs = start->cursor;
	for(i = 0; i < start->size+1 && curent; i++)
	{
		if(curent->next == NULL)
				last = curent;
		curent = curent->next;
	}
	if(last == curs)
		start->cursor = last->prev;
	last->prev->next = NULL;
	free(last);
}
void DEL_CURR(FILE *out, LinkedList *start)
{
	Node *curs, *first, *last, *curent;
	if(start == NULL)
		{
			fprintf(out, "Error: no track playing\n");
			return;
		}
	if(start->head == NULL)
		{
			fprintf(out, "Error: no track playing\n");
			return;
		}
	start->size--;
	curs = start->cursor;
	first = start->head;
	if(first->next == NULL)
		{
			free(first);
			start->head = NULL;
			start->cursor = NULL;
			return;
		}
	if(curs == first)
		{
			start->cursor = curs->next;
			start->head = first->next;
			free(curs);
			start->head->prev = NULL;
			return;
		}
	curent = start->head;
	while(curent)
	{
		if(curent->next == NULL)
			last = curent;
		curent = curent->next;
	}
	if(curs == last)
	{
		start->cursor = curs->prev;
		start->cursor->next = NULL;
		free(last);
		return;
	}
	first = curs->prev;
	last = curs->next;
	first->next = last;
	last->prev = first;
	start->cursor  = last;
	free(curs);
}
int DEL_SONG(LinkedList *start, char name[])
{
	int gasit;
	Node *curs, *curent, *first, *last, *poz;
	if(start == NULL)
			return 0;
	if(start->cursor == NULL)
			return 0;
	curent = start->head;
	if(start->head->next == NULL)
	{
		if(strcmp(curent->title, name) == 0)
		{
			start->head = NULL;
			start->cursor = NULL;
			start->size = 0;
			free(curent);
			return 1;
		}
	}
	gasit = 1;
	curent = start->head;
	while(curent)
	{
		if(strcmp(curent->title, name) == 0)
			{
				gasit = 0;
				poz = curent;
			}
		if(curent->next == NULL)
			{
				last = curent;
			}
		curent = curent->next;
	}
	if(gasit == 1)
		return 0;
	start->size--;
	first = start->head;
	curs = start->cursor;
	if(poz == first)
		{
			start->head = first->next;
			if(poz == curs)
				start->cursor = start->head;
			free(poz);
			first = start->head;
			first->prev = NULL;
			return 1;
		}
	if(poz->next == NULL)
		{
			if(last == curs)
				start->cursor = last->prev;
			curent = poz->prev;
			free(poz);
			curent->next = NULL;
			return 1;
		}
	first = poz->prev;
	last = poz->next;
	if(poz == curs)
		start->cursor = last;
	first->next = last;
	last->prev = first;
	free(poz);
	return 1;
}
void read(Node *nou, char name[])
{
	FILE *f;
	if ((f = fopen(name, "rb")) == NULL)
		return;
	fseek(f, -94, SEEK_END);
	fread(nou->title, sizeof(char), 30, f);
	nou->title[30] = '\0';
	fread(nou->artist, sizeof(char), 30, f);
	nou->artist[30] = '\0';
	fread(nou->album, sizeof(char), 30, f);
	nou->album[30] = '\0';
	fread(nou->year, sizeof(char), 4, f);
	nou->year[4] = '\0';
	fclose(f);
}
void ADD_FIRST(char name[], LinkedList *start)
{
	Node *nou, *first;
	if(start == NULL)
		return;
	nou = calloc(1, sizeof(Node));
	read(nou, name);
	nou->prev = NULL;
	if(start->head == NULL)
		{
			start->head = nou;
			start->cursor = nou;
			start->size = 1;
			nou->prev = NULL;
			nou->next = NULL;
			return;
		}
	sters = DEL_SONG(start, nou->title);
	if(start->head == NULL)
		{
			start->head = nou;
			start->cursor = nou;
			start->size = 1;
			nou->prev = NULL;
			nou->next = NULL;
			return;
		}
	start->size++;
	first = start->head;
	first->prev = nou;
	nou->next = first;
	start->head = nou;
}
void ADD_LAST(char name[], LinkedList *start)
{
	Node *nou, *last;
	if(start == NULL)
		return;
	nou = calloc(1, sizeof(Node));
	read(nou, name);
	nou->next = NULL;
	if(start->head == NULL)
		{
			start->head = nou;
			start->cursor = nou;
			start->size = 1;
			nou->prev = NULL;
			nou->next = NULL;
			return;
		}
	sters = DEL_SONG(start, nou->title);
	if(start->head == NULL)
		{
			start->head = nou;
			start->cursor = nou;
			start->size = 1;
			nou->prev = NULL;
			nou->next = NULL;
			return;
		}
	start->size++;
	last = start->head;
	while(last->next)
		last = last->next;
	nou->prev = last;
	last->next = nou;
}
void ADD_AFTER(char name[], LinkedList *start)
{
	Node *nou, *curs, *curent;
	if(start == NULL)
		return;
	if(start->head == NULL)
		return;
	nou = malloc(sizeof(Node));
	read(nou, name);
	nou->prev = NULL;
	nou->next = NULL;
	curs = start->cursor;
	if(strcmp(curs->title, nou->title) == 0)
	{
		free(nou);
		return;
	}
	sters = DEL_SONG(start, nou->title);
	start->size++;
	nou->prev = curs;
	if(curs->next)
	{
		curent = curs->next;
		curent->prev = nou;
		nou->next = curent;
	}
	curs->next = nou;
}
int main(int argc, char *argv[])
{
	int i, n, l;
	char name[100], file[100], title[31];
	Node *curent;
	FILE *in, *out, *fr;
	LinkedList *start = NULL;
	start = malloc(sizeof(LinkedList));
	start->size = 0;
	start->head = NULL;
	start->cursor = NULL;
	if(start == NULL)
			return -1;
	if((in = fopen(argv[1], "rt")) == NULL)
			return -1;
	if((out = fopen(argv[2], "wt")) == NULL)
			return -1;
	fscanf(in, "%d", &n);
	ch = fgetc(in);
	ch = '\0';
	for(i = 0; i < n; i++)
	{
		fgets(name, 100, in);
		l = strlen(name);
		name[l] = '\0';
		if(name[0] == 'A')
			{
				if(name[4] == 'F')
				{
					snprintf(file, sizeof(file), "./songs/%s", name+10);
					l = strlen(file);
					file[l-1]='\0';
					ADD_FIRST(file, start);
				}
				if(name[4] == 'L')
				{
					snprintf(file, sizeof(file), "./songs/%s", name+9);
					l = strlen(file);
					file[l-1] = '\0';
					ADD_LAST(file, start);
				}
				if(name[4] == 'A')
				{
					snprintf(file, sizeof(file), "./songs/%s", name+10);
					l = strlen(file);
					file[l-1] = '\0';
					ADD_AFTER(file, start);
				}
			}
		if(name[0] == 'D')
			{
				if(name[4] == 'F')
					DEL_FIRST(out, start);
				if(name[4] == 'L')
					DEL_LAST(out, start);
				if(name[4] == 'C')
					DEL_CURR(out, start);
				if(name[4] == 'S')
				{
					snprintf(file, sizeof(file), "./songs/%s", name+9);
					l = strlen(file);
					file[l-1] = '\0';
					fr = fopen(file, "rb");
					fseek(fr, -94, SEEK_END);
					fread(title, sizeof(char), 30, fr);
					title[31] = '\0';
					if(DEL_SONG(start, title) == 0)
						fprintf(out, "Error: no song found to delete\n");
					fclose(fr);
				}
			}
		if(name[0] == 'M')
			{
				if(name[5] == 'P')
					MOVE_PREV(out, start);
				if(name[5] == 'N')
					MOVE_NEXT(out, start);
			}
		if(name[0] == 'S')
			{
				if(name[5] == 'F')
					SHOW_FIRST(out, start);
				if(name[5] == 'L')
					SHOW_LAST(out, start);
				if(name[5] == 'C')
					SHOW_CURR(out, start);
				if(name[5] == 'P')
					SHOW_PLAYLIST(out, start);
			}
	}
	curent = start->head;
	while(curent != NULL)
		{
			curent = start->head->next;
			free(start->head);
			start->head = curent;
		}
	free(start);
	fclose(in);
	fclose(out);
	return 0;
}
