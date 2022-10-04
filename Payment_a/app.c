/*
 * File:   app.c
 * Author: Yousif Mohamed Anwar
 *
 * Created on Sep 7, 2022, 3:16 PM
 */



#include "app.h"
extern ST_accountsDB_t accounts[MAX_ACCOUNTS_AVILABLE];
// transaction data base
extern ST_transaction_t tran[MAX_ACCOUNTS_AVILABLE];
//
extern int i, seq;


 /**
  * @description Testing the application. 
  * @complexity
  */
void appStart(void) {

	init_accountDB();
	ST_transaction_t transaction = { 0 };
	uint8_t app_card_error = 0;
	uint8_t app_terminal_error = 0;
	uint8_t app_server_error = 0;
	uint8_t trials = 0;

	uint16_t status = 1;

	while (1) {
		if (trials == 3) {
			break;
		}
		/*===================================== Get card info from the user ===================================*/

		app_card_error = getCardHolderName(&(transaction.cardHolderData));
		if (WRONG_NAME == app_card_error) {
			printf("WRONG_NAME ERROR\n");
			if (trials < 2) {
				printf("Please enter the data again.\n");
			}
			trials++;
			continue;
		}
		else {
			printf("correct name \n");
		}

		app_card_error = getCardExpiryDate(&(transaction.cardHolderData));
		if (WRONG_EXP_DATE == app_card_error) {
			printf("EXP_DATE ERROR");
			if (trials < 2) {
				printf("Please enter the data again.\n");
			}
			trials++;
			continue;
		}
		else {
			printf("correct date \n");
		}

		app_card_error = getCardPAN(&(transaction.cardHolderData));
		if (WRONG_PAN == app_card_error) {
			printf("WRONG_PAN ERROR\n");
			if (trials < 2) {
				printf("Please enter the data again.\n");
			}
			trials++;
			continue;
		}
		else {
			printf("correct PAN \n");
		}
		/*============================= end of Get card info from the user ===========================================*/

		// // // // // // // // // // // // // // // // // // // // // // // // // // // // // // // // // // // // // /

		/*======================================== Get terminal info from the user ======================================*/

		app_terminal_error = getTransactionDate(&(transaction.terminalData));
		if (WRONG_DATE == app_terminal_error) {
			printf("WRONG_DATE_TERMINAL ERROR.\n");
			if (trials < 2) {
				printf("Please enter the data again.\n");
			}
			trials++;
			continue;
		}
		else {
			printf("Correct transaction date.\n");
		}


		app_terminal_error = isCardExpired(transaction.cardHolderData, transaction.terminalData);

		if (EXPIRED_CARD == app_terminal_error) {
			printf("Please, go to the bank to activate your card.\n");
			break;
		}

		uint8_t l_z = '0';
		uint8_t l_z_buff = '0';
		printf("please enter 1 to operation or 0 to block your account.\n");
		l_z = getchar();
		l_z_buff = getchar();
		if (l_z == '0') {
			accounts[i].state = BLOCKED;
			printf("now your account is blocked.\n");
			continue;
		}
		else {

			app_terminal_error = setMaxAmount(&(transaction.terminalData), 15000);

			app_terminal_error = getTransactionAmount(&(transaction.terminalData));

			if (INVALID_AMOUNT == app_terminal_error) {
				printf(" INVALID_AMOUNT ERROR, please enter a positive value.\n");
				if (trials < 2) {
					printf("Please enter the data again.\n");
				}
				trials++;
				continue;
			}
			else {
				/* Nothing */
			}

			app_terminal_error = isBelowMaxAmount(&(transaction.terminalData));

			if (EXCEED_MAX_AMOUNT == app_terminal_error) {
				printf("INVALID_AMOUNT ERROR, exceeded the max value.\n");
				if (trials < 2) {
					printf("Please enter the data again.\n");
				}
				trials++;
				continue;
			}
			else {
				printf("the data is processesing now........\n");
			}


			/*===================================== end of Get card info from the user ======================================*/

			// // // // // // // // // // // // // // // // // // // // // // // // // // // // // // // // // // // // // /

			/*======================================== dealing with database in server ======================================*/

			app_server_error = recieveTransactionData(&transaction);
			return;
		}

		/*===================================== end of dealing with terminal ======================================*/

	}

}

