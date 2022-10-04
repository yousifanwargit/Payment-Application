#include "server.h"

typedef char* char_ptr;

void init_accountDB() {
	accounts[0].balance = 10000;
	accounts[0].state = RUNNING;
	strcpy((char_ptr)accounts[0].primaryAccountNumber, "0000000000000000");

	accounts[1].balance = 20000;
	accounts[1].state = RUNNING;
	strcpy((char_ptr)accounts[1].primaryAccountNumber, "1111111111111111");

	accounts[2].balance = 30000;
	accounts[2].state = RUNNING;
	strcpy((char_ptr)accounts[2].primaryAccountNumber, "2222222222222222");

	accounts[3].balance = 40000;
	accounts[3].state = RUNNING;
	strcpy((char_ptr)accounts[3].primaryAccountNumber, "3333333333333333");

	accounts[4].balance = 50000;
	accounts[4].state = RUNNING;
	strcpy((char_ptr)accounts[4].primaryAccountNumber, "4444444444444444");

	accounts[5].balance = 60000;
	accounts[5].state = BLOCKED;
	strcpy((char_ptr)accounts[5].primaryAccountNumber, "5555555555555555");
}

void transaction_DB(ST_cardData_t cardData, ST_terminalData_t termData, uint32_t sequence) {
	trans[sequence].cardHolderData = cardData;
	trans[sequence].terminalData = termData;
}