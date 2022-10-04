/*
 * File:   card.h
 * Author: Yousif Mohamed Anwar
 *
 * Created on Sep 7, 2022, 3:16 PM
 */
#ifndef _card
#define _card

/*=============== Includes ================= */
#include "std_types.h"
#include "includes.h"

/*=============== Macro Declaration ================= */
#define _CRT_SECURE_NO_WARNINGS 1

#define NAME_MAX_SIZE    24
#define NAME_MIN_SIZE    22

#define EXP_DATE_MAX_NUM    5

#define PAN_MAX_NUM       19
#define PAN_MIN_NUM       16
/*=============== Macro Function Declaration ================= */
/*=============== Data Types Declaration ================= */
typedef enum EN_cardError_t
{
	OK_CARD,
	WRONG_NAME,
	WRONG_EXP_DATE,
	WRONG_PAN
}EN_cardError_t;

typedef struct ST_cardData_t
{
	uint8_t cardHolderName[25];
	uint8_t primaryAccountNumber[20];
	uint8_t cardExpirationDate[6];
}ST_cardData_t;
/*=============== Software Interfaces Declaration ================= */
 /**
  * @description This function will ask for the cardholder's name and store it into card data.
				 Card holder name is 24 characters string max and 20 min.
  * @param  cardData -> ST_cardData_t
  * @return WRONG_NAME : If the cardholder name is NULL, less than 20 characters or more than 24.
  *			OK_CARD    : if the name is correct and been saved.
  * @complexity : O(1)
  */
 EN_cardError_t getCardHolderName(ST_cardData_t* cardData);
 /**
  * @description This function will ask for the card expiry date and store it in card data.
				 Card expiry date is 5 characters string in the format "MM/YY", e.g "05/25".
  * @param cardData -> ST_cardData_t
  * @return WRONG_EXP_DATE : If the card expiry date is NULL, less or more than 5 characters, or has the wrong format.
  *		   OK_CARD        : if the expire date is correct and been saved.
  * @complexity : O(1)
  */
 EN_cardError_t getCardExpiryDate(ST_cardData_t* cardData);
 /**
  * @description This function will ask for the card's Primary Account Number and store it in card data.
				 PAN is 20 characters alphanumeric only string 19 character max, and 16 character min.
  * @param cardData -> ST_cardData_t
  * @return WRONG_PAN : If the PAN is NULL, less than 16 or more than 19 characters.
  *		   OK_CARD   : if the PAN is correct and been saved.
  * @complexity
  */
 EN_cardError_t getCardPAN(ST_cardData_t* cardData);



#endif