#include "poo.h"


void add_poo(struct Poo ** head, struct Poo ** tail, struct texture pooTextures[])
{
	struct Poo * newPoo = malloc(sizeof(struct Poo));
	newPoo->pooButton.imageTextures[IB_INACTIVE] = pooTextures[IB_INACTIVE];
	newPoo->pooButton.imageTextures[IB_HIGHLIGHTED] = pooTextures[IB_HIGHLIGHTED];
	newPoo->pooButton.imageTextures[IB_CLICKED] = pooTextures[IB_CLICKED];
	newPoo->pooButton.buttonState = IB_INACTIVE;
	newPoo->pooValue = rand() % MAX_NUMBER_OF_COIN_FROM_POO;
	newPoo->pooButton.X = ACTIVE_WINDOW_TLCX + rand() % (ACTIVE_WINDOW_WIDTH - newPoo->pooButton.imageTextures[IB_INACTIVE].width);
	newPoo->pooButton.Y = ACTIVE_WINDOW_TLCY + rand() % (ACTIVE_WINDOW_HEIGHT - newPoo->pooButton.imageTextures[IB_INACTIVE].height);
	if (*tail == NULL) {
		*tail = newPoo;
		*head = newPoo;
		newPoo->nextPoo = NULL;
		newPoo->prevPoo = NULL;
	}
	else if (*tail == *head) {
		*head = newPoo;
		newPoo->nextPoo = NULL;
		newPoo->prevPoo = *tail;
		(*tail)->nextPoo = newPoo;
	}
	else {
		(*head)->nextPoo = newPoo;
		newPoo->prevPoo = *head;
		newPoo->nextPoo = NULL;
		*head = newPoo;
	}
}

void delete_poo(struct Poo * currentPoo, struct Poo ** head, struct Poo ** tail)
{
	if (currentPoo == *head && currentPoo == *tail) {
		*head = NULL;
		*tail = NULL;
	}
	else if (currentPoo == *head || currentPoo == *tail) {
		if (currentPoo == *head) {
			*head = currentPoo->prevPoo;
			currentPoo->prevPoo->nextPoo = NULL;
		}
		else { // currentPoo == tail
			*tail = currentPoo->nextPoo;
			currentPoo->nextPoo->prevPoo = NULL;
		}
	}
	else {
		currentPoo->nextPoo->prevPoo = currentPoo->prevPoo;
		currentPoo->prevPoo->nextPoo = currentPoo->nextPoo;
	}

	free(currentPoo);
}

int handle_poo_mouse_events(struct Poo ** head, struct Poo ** tail, SDL_Event * e) {
	struct Poo * currentPoo = *head;
	int pooValue = 0;
	while (currentPoo != NULL && pooValue == 0) {
		imageButton_HandleMouseEvent(&currentPoo->pooButton, e);
		struct Poo * prevPoo = currentPoo->prevPoo;
		if (currentPoo->pooButton.buttonState == IB_CLICKED) {
			pooValue = currentPoo->pooValue;
			delete_poo(currentPoo, head, tail);
		}
		currentPoo = prevPoo;
	}
	return pooValue;
}

void render_poos(struct Poo * head)
{
	struct Poo * currentPoo = head;
	while (currentPoo != NULL) {
		render_image_button(currentPoo->pooButton.imageTextures[currentPoo->pooButton.buttonState], currentPoo->pooButton.X, currentPoo->pooButton.Y);
		currentPoo = currentPoo->prevPoo;
	}
}