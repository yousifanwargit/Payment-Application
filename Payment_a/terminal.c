/*
 * File:   terminal.c
 * Author: Yousif Mohamed Anwar
 *
 * Created on Sep 7, 2022, 3:16 PM
 */

#include "terminal.h"

 /**
  * @description This function will ask for the transaction data and store it in terminal data.
				 Transaction date is 10 characters string in the format DD/MM/YYYY, e.g 25/06/2022.
  * @param termData -> ST_terminalData_t
  * @return WRONG_DATE  : If the transaction date is NULL, less than 10 characters or wrong format.
  *			OK_TERMINAL : if the date is correct.
  * @complexity : O(1)
  */
EN_terminalError_t getTransactionDate(ST_terminalData_t* termData) {
	EN_terminalError_t ret = OK_TERMINAL;
	printf("please, enter the transaction date : ");
	gets(termData->transactionDate);
	uint8_t l_length = strlen(termData->transactionDate);
	if (NULL == termData || NULL == termData->transactionDate || TRANS_DATE_MAX_SIZE < l_length ||
		termData->transactionDate[2] != '/' || termData->transactionDate[5] != '/') {
		//printf("worng trans date error\n");
		ret = WRONG_DATE;
	}
	else {
		ret = OK_TERMINAL;
		//printf("corrct trans date\n");

	}
	return ret;
}

/**
 * @description This function compares the card expiry date with the transaction date.
 * @param cardData -> ST_cardData_t
 * @param termData -> ST_terminalData_t
 * @return EXPIRED_CARD : If the card expiration date is before the transaction date.
 *		   OK_TERMINAL  : if comparison done correctly.
 * @complexity : O(1)
 */
EN_terminalError_t isCardExpired(ST_cardData_t cardData, ST_terminalData_t termData) {
	EN_terminalError_t ret = OK_TERMINAL;
	uint16_t l_expire_year, l_expire_month, l_trans_month, l_trans_year, l_trans_day;
	/*l_expire_year = ((((int)cardData.cardExpirationDate[3]) * 10) + ((int)cardData.cardExpirationDate[4])) + 2000;
	l_expire_month = ((((int)cardData.cardExpirationDate[0]) * 10) + ((int)cardData.cardExpirationDate[1]));
	l_trans_month  = ((((int)termData.transactionDate[3]) * 10) + ((int)termData.transactionDate[4]));
	l_trans_year   = ((((int)termData.transactionDate[6]) * 1000) + (((int)termData.transactionDate[7]) * 100) +
					 (((int)termData.transactionDate[8]) * 10) + (((int)termData.transactionDate[9])));*/
	sscanf(&(cardData.cardExpirationDate), "%d/%d", &l_expire_month, &l_expire_year);
	l_expire_year += 2000;
	sscanf(&(termData.transactionDate), "%d/%d/%d", &l_trans_day, &l_trans_month, &l_trans_year);
	if (l_expire_year < l_trans_year) {
		ret = EXPIRED_CARD;
		printf("expired\n");
	}
	else if (l_expire_year == l_trans_year && l_expire_month < l_trans_month) {
		ret = EXPIRED_CARD;
		printf("expired\n");

	}
	else {
		ret = OK_TERMINAL;
		printf("not expired\n");

	}
	return ret;
}

/**
 * @description
 * @param cardData -> ST_cardData_t
 * @return
 * @complexity
 */
EN_terminalError_t isValidCardPAN(ST_cardData_t* cardData) {
	/* Optional */
}

/**
 * @description This function asks for the transaction amount and saves it into terminal data.
 * @param termData -> ST_terminalData_t
 * @return INVALID_AMOUNT : If the transaction amount is less than or equal to 0.
 *		   OK_TERMINAL    : if the transaction amount is correct.
 * @complexity : O(1)
 */
EN_terminalError_t getTransactionAmount(ST_terminalData_t* termData) {
	EN_terminalError_t ret = OK_TERMINAL;
	uint8_t l_x;
	printf("please, enter transaction amount (positive amount) : ");
	scanf("%f", &termData->transAmount);
	scanf("%c", &l_x);
	if (NULL == termData || termData->transAmount <= 0) {
		ret = INVALID_AMOUNT;
		//printf("wrong trans amount error\n");
	}
	else {
		ret = OK_TERMINAL;
		//printf("correct trans amount \n");
	}
	return ret;
}

/**
 * @description This function compares the transaction amount with the terminal max amount.
 * @param termData -> ST_terminalData_t
 * @return EXCEED_MAX_AMOUNT : If the transaction amount is larger than the terminal max amount.
 *		   OK_TERMINAL       : if the transaction amount is less than the terminal max amount.
 * @complexity : O(1)
 */
EN_terminalError_t isBelowMaxAmount(ST_terminalData_t* termData) {
	EN_terminalError_t ret = OK_TERMINAL;
	if (termData->transAmount > termData->maxTransAmount) {
		//printf("EXCEED_MAX_AMOUNT error\n");
		ret = EXCEED_MAX_AMOUNT;
	}
	else {
		//printf("no err\n");
		ret = OK_TERMINAL;
	}
	return ret;
}

/**
 * @description This function sets the maximum allowed amount into terminal data.
				Transaction max amount is a float number.
 * @param termData -> ST_terminalData_t
 * @return INVALID_MAX_AMOUNT : If transaction max amount less than or equal to 0.
 *		   OK_TERMINAL        : If transaction max amount is greater than 0.
 * @complexity : O(1)
 */

EN_terminalError_t setMaxAmount(ST_terminalData_t* termData, float maxAmount){
	EN_terminalError_t ret = OK_TERMINAL;
	if (maxAmount <= 0) {
		ret = INVALID_MAX_AMOUNT;
		//printf("maximum amount error /n");
	}
	else {
		termData->maxTransAmount = maxAmount;
		printf("your maximum transaction in one trial is : %f L.E\n", maxAmount);
		ret = OK_TERMINAL;

	}
	return ret;
}
