#include <iostream>
#include <sstream>
#include <string>
#include <cstdlib>
#include <ctime>

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
	//int capacity;
	//int count;
};

void first_card(deck*, int);
void new_card(deck*, int);
deck* new_deck();
deck* create_inDeck();
void add_inDeck(deck*, int);
hand* create_hand();
void play_game(deck*, int*);
void draw_card(deck*, int);
void remove_card_in_deck(int);
void print(deck*);
void print_hand(hand*);

int* money;
bool keepPlaying;
deck* Deck;
deck* InDeck;
hand* Hand;
string input;
string input2;

int main()
{
	srand(time(NULL));
	int a = 10;
	money = &a;
	keepPlaying = true;
	Deck = new_deck();
	for (int i = 0; i < 52; i++) { new_card(Deck, i); }
	
	InDeck = create_inDeck();
	Hand = create_hand();
	
	for (int i = 0; i < 52; i++) { add_inDeck(Deck, i); }
	while (*money > 0 && keepPlaying == true) {
		play_game(Deck, &a);
	}
	cout << endl << "Game Over" << endl << endl;
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
	//if (temp->state != "deck") { return; }
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
	//list->capacity = INIT_CAP;
	//list->count = 0;
	return list;
}

void play_game(deck* currDeck, int* currMoney) {
	*currMoney = *currMoney - 1;
	input = "none";
	cout << endl << "You currently have $" << *currMoney << " after paying $1 to play this round." << endl;
	cout << endl << "type 'deck' to see the deck or 'play' to start a new round." << endl << "Your response : ";
	while (input == "none") {
		getline(cin, input);
		if (input != "deck" && input != "play") { 
			cout << "Sorry that is not a valid response. Try again." << endl << "Your response: ";
			input = "none"; 
		}
	}
	input2 = "Q";
	if (input == "deck") { 
		print(InDeck);
	}
	else if (input == "play") {
		for (int i = 0; i < 5; i++) { draw_card(InDeck, i); }
		print_hand(Hand);
		cout << endl << "Type in the letter(s) of the card(s) you want to keep or just press enter to discard all.\nYour Response: ";
		getline(cin, input2);
		while (input2.find_first_of("ABCDEabcde") == std::string::npos && input2 != "") {
			cout << "\nSorry invalid choice.\nYour Response: ";
			getline(cin, input2);
		}
		if (input2.find_first_of("Aa") == std::string::npos) { draw_card(InDeck, 0); }
		if (input2.find_first_of("Bb") == std::string::npos) { draw_card(InDeck, 1); }
		if (input2.find_first_of("Cc") == std::string::npos) { draw_card(InDeck, 2); }
		if (input2.find_first_of("Dd") == std::string::npos) { draw_card(InDeck, 3); }
		if (input2.find_first_of("Ee") == std::string::npos) { draw_card(InDeck, 4); }
		print_hand(Hand);
	}
}

void draw_card(deck* thisDeck, int handIndex) {
	int index = rand() % InDeck->count;
	Hand->array[handIndex] = InDeck->array[index];
	remove_card_in_deck(index);
}

void remove_card_in_deck(int index){
	if (index < 0 || index >= InDeck->count) {
		cout << "Error! out of bound" << endl;
		return;
	}
	for (int i = index; i < InDeck->count - 1; i++) { InDeck->array[i] = InDeck->array[i + 1]; }
	InDeck->count--;
}

void print(deck* thisDeck) {
	card* temp = Deck->head;
	cout << endl << "Cards in Deck:" << endl;
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

void print_hand(hand* currHand) {
	int counter = 0;
	cout << endl << "Your Hand:" << endl;
	for (int i = 0; i < 5; i++) {
		card* temp = Deck->head;
		for (int j = 0; j < currHand->array[i]; j++) { temp = temp->next; }
		switch (i) {
		case 0:
			cout << "A: ";
			break;
		case 1:
			cout << "B: ";
			break;
		case 2:
			cout << "C: ";
			break;
		case 3:
			cout << "D: ";
			break;
		case 4:
			cout << "E: ";
			break;
		}
		switch (temp->value) {
		case 1:
			cout << "Ace of " << temp->suit;
			break;
		case 11:
			cout << "Jack of " << temp->suit;
			break;
		case 12:
			cout << "Queen of " << temp->suit;
			break;
		case 13:
			cout << "King of " << temp->suit;
			break;
		default:
			cout << temp->value << " of " << temp->suit;
			break;
		}
		if (i == 0 && input2.find_first_of("Aa") != std::string::npos) { cout << " (kept)"; counter++; }
		if (i == 1 && input2.find_first_of("Bb") != std::string::npos) { cout << " (kept)"; counter++; }
		if (i == 2 && input2.find_first_of("Cc") != std::string::npos) { cout << " (kept)"; counter++; }
		if (i == 3 && input2.find_first_of("Dd") != std::string::npos) { cout << " (kept)"; counter++; }
		if (i == 4 && input2.find_first_of("Ee") != std::string::npos) { cout << " (kept)"; counter++; }
		cout << endl;
	}
	if (counter == 0 && input2 != "Q") { cout << endl << "You discarded all cards" << endl; }
	else if (counter == 1) { cout << endl << "You kept 1 card" << endl; }
	else if (counter == 5) { cout << endl << "You kept all cards" << endl; }
	else if (counter == 0) { cout << ""; }
	else { cout << endl << "You kept " << counter << " cards" << endl; }
}