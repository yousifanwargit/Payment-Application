/*
 * File:   card.c
 * Author: Yousif Mohamed Anwar
 *
 * Created on Sep 7, 2022, 3:16 PM
 */

#include "card.h"

 /**
  * @description This function will ask for the cardholder's name and store it into card data.
                 Card holder name is 24 characters string max and 20 min.
  * @param  cardData -> ST_cardData_t
  * @return WRONG_NAME : If the cardholder name is NULL, less than 20 characters or more than 24.
  *			OK_CARD    : if the name is correct and been saved.
  * @complexity : O(1)
  */
EN_cardError_t getCardHolderName(ST_cardData_t* cardData) {
	EN_cardError_t ret = OK_CARD;
	printf("please, enter card holder name : ");
	gets(cardData->cardHolderName);
	uint8_t length = strlen(cardData->cardHolderName);
	if ( NULL == cardData || cardData->cardHolderName == NULL || NAME_MAX_SIZE < length || NAME_MIN_SIZE > length ) {
		ret = WRONG_NAME;
		//printf("wrong name error\n");
	}
	else {
		ret = OK_CARD;
		//printf("correct name\n");
	}
	return ret;
}

/**
 * @description This function will ask for the card expiry date and store it in card data.
				Card expiry date is 5 characters string in the format "MM/YY", e.g "05/25".
 * @param cardData -> ST_cardData_t
 * @return WRONG_EXP_DATE : If the card expiry date is NULL, less or more than 5 characters, or has the wrong format.
 *		   OK_CARD        : if the expire date is correct and been saved.
 * @complexity : O(1)
 */
EN_cardError_t getCardExpiryDate(ST_cardData_t* cardData) {
	EN_cardError_t ret = OK_CARD;
	printf("please, enter card exp date in mm/yy format : ");
	gets(cardData->cardExpirationDate);
	uint8_t length = strlen(cardData->cardExpirationDate);
	if (NULL == cardData || cardData->cardExpirationDate == NULL || EXP_DATE_MAX_NUM != length || cardData->cardExpirationDate[2] != '/') {
		ret = WRONG_EXP_DATE;
		//printf("wrong card expriy date error\n");
	}
	else {
		ret = OK_CARD;
		//printf("correct card expiry date\n");
	}
	return ret;

}

/**
 * @description This function will ask for the card's Primary Account Number and store it in card data.
				PAN is 20 characters alphanumeric only string 19 character max, and 16 character min.
 * @param cardData -> ST_cardData_t
 * @return WRONG_PAN : If the PAN is NULL, less than 16 or more than 19 characters.
 *		   OK_CARD   : if the PAN is correct and been saved.
 * @complexity
 */
EN_cardError_t getCardPAN(ST_cardData_t* cardData) {
	EN_cardError_t ret = OK_CARD;
	printf("please, enter PAN 16 numbers : ");
	gets(cardData->primaryAccountNumber);
	uint8_t length = strlen(cardData->primaryAccountNumber);
	if ( NULL == cardData || cardData->primaryAccountNumber == NULL || PAN_MAX_NUM < length || PAN_MIN_NUM > length ) {
		ret = WRONG_PAN;
		//printf("wrong PAN error\n");
	}
	else {
		ret = OK_CARD;
		//printf("correct PAN\n");
	}
	return ret;
}
