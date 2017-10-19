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
	int* array;
	int capacity;
	int count;
};

struct hand {
	int* array;
	int capacity;
	int count;
};

void first_card(deck*, int);
void new_card(deck*, int);
deck* new_deck();
deck* create_inDeck();
void add_inDeck(deck*, int);
hand* create_hand();
void play_game(deck*, int*);
void print(deck*);

int* money;
bool keepPlaying;
deck* Deck;
deck* InDeck;
string input;

int main()
{
	int a = 10;
	money = &a;
	keepPlaying = true;
	Deck = new_deck();
	for (int i = 0; i < 52; i++) { new_card(Deck, i); }
	
	InDeck = create_inDeck();
	hand* Hand = create_hand();
	
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

deck* create_inDeck() {
	const int INIT_CAP = 52;
	deck* list = new deck;
	list->array = new int[INIT_CAP];
	list->capacity = INIT_CAP;
	list->count = 0;
	return list;
}

void add_inDeck(deck* currDeck, int index) {
	card* temp = currDeck->head;
	for (int i = 0; i < index; i++) { temp = temp->next; }
	if (temp->state != "deck") { return; }
	if (InDeck->count == InDeck->capacity) {
		int new_capacity = InDeck->capacity * 2;
		int* new_array = new int[new_capacity];
		for (int i = 0; i < 52; i++) { new_array[i] = InDeck->array[i]; }
		delete[] InDeck->array;
		InDeck->array = new_array;
		InDeck->capacity = new_capacity;
	}
	InDeck->array[InDeck->count] = index;
	InDeck->count++;
}

hand* create_hand() {
	const int INIT_CAP = 5;
	hand* list = new hand;
	list->array = new int[INIT_CAP];
	list->capacity = INIT_CAP;
	list->count = 0;
	return list;
}

void play_game(deck* currDeck, int* currMoney) {
	*currMoney = *currMoney - 10;
	cout << "You currently have $" << *currMoney << " after paying $1 to play this round." << endl;
	for (int i = 0; i < 52; i++) { add_inDeck(currDeck, i); }
	cout << endl << "type 'deck' to see the deck." << endl << "Your response : ";
	while (input != "deck") {
		getline(cin, input);
	}
	if (input == "deck") { print(InDeck); }
}

void print(deck* thisDeck) {
	card* temp = Deck->head;
	cout << "Cards in Deck:" << endl;
	for (int i = 0; i < 52; i++) { 
		for (int j = 0; j < thisDeck->count; j++) {
			if (i == thisDeck->array[j]) {
				switch (temp->value){
					case 1:
						cout << "Ace of " << temp->suit << endl;
						break;
					case 11:
						cout << "Jack of " << temp->suit << endl;
						break;
					case 12:
						cout << "Queen of " << temp->suit << endl;
						break;
					case 13:
						cout << "King of " << temp->suit << endl;
						break;
					default:
						cout << temp->value << " of " << temp->suit << endl;
						break;
				}
				break;
			}
		}
	temp = temp->next;
	}
}