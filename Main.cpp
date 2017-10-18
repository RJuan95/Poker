#include <iostream>
#include <sstream>
#include <string>

using namespace std;

struct card {
	int value;
	string suit;
	string state;
	card* next;
};

struct deck {
	card* head;
};

void first_card(deck*, int);
void new_card(deck*, int);
deck* new_deck();
void play_game(deck*, int*);

int* money;
bool keepPlaying;

int main()
{
	int a = 10;
	money = &a;
	keepPlaying = true;
	deck* Deck = new_deck();
	for (int i = 0; i < 52; i++) {
		new_card(Deck, i);
	}

	while (*money > 0 && keepPlaying == true) {
		play_game(Deck, &a);
	}

	system("pause");
	return 0;
}

void first_card(deck* deck, int index) {
	card* newCard = new card;
	newCard->value = (index / 4) + 1;
	switch (index % 4) {
	case 0:
		newCard->suit = "spades";
		break;
	case 1:
		newCard->suit = "hearts";
		break;
	case 2:
		newCard->suit = "diamonds";
		break;
	case 3:
		newCard->suit = "clubs";
		break;
	}
	newCard->state = "deck";
	newCard->next = deck->head;
	deck->head = newCard;
}


void new_card(deck* deck, int index) {
	if (deck->head == nullptr) {
		first_card(deck, index);
		return;
	}

	card* temp = deck->head;
	while (temp->next != nullptr) {
		temp = temp->next;
	}

	card* newCard = new card;
	newCard->value = (index / 4) + 1;
	switch (index % 4) {
	case 0:
		newCard->suit = "spades";
		break;
	case 1:
		newCard->suit = "hearts";
		break;
	case 2:
		newCard->suit = "diamonds";
		break;
	case 3:
		newCard->suit = "clubs";
		break;
	}
	newCard->state = "deck";
	newCard->next = nullptr;
	temp->next = newCard;
}

deck* new_deck() {
	deck* list = new deck;
	list->head = nullptr;
	return list;
}

void play_game(deck* deck, int* currMoney) {
	cout << "You currently have $" << *currMoney << endl;
	*currMoney = *currMoney - 1;
}