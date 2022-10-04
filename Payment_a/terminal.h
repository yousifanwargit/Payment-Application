/*
 * File:   terminal.h
 * Author: Yousif Mohamed Anwar
 *
 * Created on Sep 7, 2022, 3:16 PM
 */

#ifndef _terminal
#define _terminal

/*=============== Includes ================= */
#include "std_types.h"
#include "card.h"
/*=============== Macro Declaration ================= */
#define TRANS_DATE_MAX_SIZE  10
/*=============== Macro Function Declaration ================= */
/*=============== Data Types Declaration ================= */
typedef struct 
{
	float transAmount;
	float maxTransAmount;
	uint8_t transactionDate[11];
}ST_terminalData_t;
typedef enum EN_terminalError_t
{
	OK_TERMINAL,
	WRONG_DATE,
	EXPIRED_CARD,
	INVALID_CARD,
	INVALID_AMOUNT,
	EXCEED_MAX_AMOUNT,
	INVALID_MAX_AMOUNT
}EN_terminalError_t;

/*=============== Software Interfaces Declaration ================= */
 /**
  * @description This function will ask for the transaction data and store it in terminal data.
				 Transaction date is 10 characters string in the format DD/MM/YYYY, e.g 25/06/2022.
  * @param termData -> ST_terminalData_t
  * @return WRONG_DATE  : If the transaction date is NULL, less than 10 characters or wrong format.
  *			OK_TERMINAL : if the date is correct.
  * @complexity : O(1)
  */
EN_terminalError_t getTransactionDate(ST_terminalData_t* termData);
/**
 * @description This function compares the card expiry date with the transaction date.
 * @param cardData -> ST_cardData_t
 * @param termData -> ST_terminalData_t
 * @return EXPIRED_CARD : If the card expiration date is before the transaction date.
 *		   OK_TERMINAL  : if comparison done correctly.
 * @complexity : O(1)
 */
EN_terminalError_t isCardExpired(ST_cardData_t cardData, ST_terminalData_t termData);
/**
 * @description
 * @param cardData -> ST_cardData_t
 * @return
 * @complexity
 */
EN_terminalError_t isValidCardPAN(ST_cardData_t* cardData);
/**
 * @description This function asks for the transaction amount and saves it into terminal data.
 * @param termData -> ST_terminalData_t
 * @return INVALID_AMOUNT : If the transaction amount is less than or equal to 0.
 *		   OK_TERMINAL    : if the transaction amount is correct.
 * @complexity : O(1)
 */
EN_terminalError_t getTransactionAmount(ST_terminalData_t* termData);
/**
 * @description This function compares the transaction amount with the terminal max amount.
 * @param termData -> ST_terminalData_t
 * @return EXCEED_MAX_AMOUNT : If the transaction amount is larger than the terminal max amount.
 *		   OK_TERMINAL       : if the transaction amount is less than the terminal max amount.
 * @complexity : O(1)
 */
EN_terminalError_t isBelowMaxAmount(ST_terminalData_t* termData);
/**
 * @description This function sets the maximum allowed amount into terminal data.
				Transaction max amount is a float number.
 * @param termData -> ST_terminalData_t
 *		  maxAmount -> float
 * @return INVALID_MAX_AMOUNT : If transaction max amount less than or equal to 0.
 *		   OK_TERMINAL        : If transaction max amount is greater than 0.
 * @complexity : O(1)
 */
EN_terminalError_t setMaxAmount(ST_terminalData_t* termData, float maxAmount);





#endif