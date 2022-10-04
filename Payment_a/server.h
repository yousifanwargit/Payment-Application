/*
 * File:   server.h
 * Author: Yousif Mohamed Anwar
 *
 * Created on Sep 7, 2022, 3:16 PM
 */
#ifndef _server
#define _server
/*=============== Includes ================= */
#include "includes.h"
#include "std_types.h"
#include "terminal.h"
#include "card.h"
/*=============== Macro Declaration ================= */
#define  MAX_ACCOUNTS_AVILABLE 255
/*=============== Macro Function Declaration ================= */
/*=============== Data Types Declaration ================= */
typedef enum EN_transState_t
{APPROVED, DECLINED_INSUFFECIENT_FUND, DECLINED_STOLEN_CARD, INTERNAL_SERVER_ERROR}EN_transState_t;
typedef enum EN_accountState_t
{	RUNNING,
	BLOCKED
}EN_accountState_t;
typedef struct ST_transaction_t
{	ST_cardData_t cardHolderData;
	ST_terminalData_t terminalData;
	EN_transState_t transState;
	uint32_t transactionSequenceNumber;
}ST_transaction_t;
typedef enum EN_serverError_t
{	OK_SERVER,
	SAVING_FAILED,
	TRANSACTION_NOT_FOUND,
	ACCOUNT_NOT_FOUND,
	LOW_BALANCE,
	BLOCKED_ACCOUNT
}EN_serverError_t;
typedef struct ST_accountsDB_t
{	float balance;
	EN_accountState_t state;
	uint8_t primaryAccountNumber[20];
}ST_accountsDB_t;
// account data base
ST_accountsDB_t accounts[MAX_ACCOUNTS_AVILABLE];
// transaction data base
ST_transaction_t trans[MAX_ACCOUNTS_AVILABLE];
/*=============== Software Interfaces Declaration ================= */
/**
 * @description This function will take all transaction data and validate its data.
				It checks the account details and amount availability.
 * @param transData -> ST_transaction_t
 * @return DECLINED_STOLEN_CARD       : If the account does not exis
 *         DECLINED_INSUFFECIENT_FUND : if the amount is not available
 *         INTERNAL_SERVER_ERROR      : if a transaction can't be saved
 *         APPROVED                   : if the function done correctly
 * @complexity : O(1)
 */
EN_transState_t recieveTransactionData(ST_transaction_t* transData);
/**
 * @description This function will take card data and validate these data.
				It checks if the PAN exists or not in the server's database.
 * @param cardData -> ST_cardData_t
 * @return DECLINED_STOLEN_CARD : if the PAN doesn't exist
 *         OK_SERVER            : if account is valid
 * @complexity : O(1)
 */
EN_serverError_t isValidAccount(ST_cardData_t* cardData);
/**
 * @description This function will take terminal data and validate these data.
				It checks if the transaction's amount is available or not.
 * @param : termData -> ST_terminalData_t
 * @return LOW_BALANCE : if the amount is less than the balance
 *         OK_SERVER   : if the amount is available
 * @complexity : O(1)
 */
EN_serverError_t isAmountAvailable(ST_terminalData_t* termData);
/**
 * @description This function takes a reference to the account into the database and verifies if it is blocked or not.
 * @param : accountRefrence -> ST_accountsDB_t
 * @return LOW_BALANCE : if the amount is less than the balance
 *         OK_SERVER   : if the amount is available
 * @complexity : O(1)
 */
EN_serverError_t isBlockedAccount(ST_accountsDB_t* accountRefrence);
/**
 * @description This function will take all transaction data into the transactions database.
				It gives a sequence number to a transaction, this number is incremented once a transaction is processed into the server.
				If saves any type of transaction, APPROVED or DECLINED, with the specific reason for declining/transaction state.
 * @param transData -> ST_transaction_t
 * @return SAVING_FAILED : If transaction can't be saved
 *         OK_SERVER     : If saving done correctly
 * @complexity : O(1)
 */
EN_serverError_t saveTransaction(ST_transaction_t* transData);
/**
 * @description
 * @param transactionSequenceNumber
 * @param transData
 * @return
 * @complexity
 */
EN_serverError_t getTransaction(uint32_t transactionSequenceNumber, ST_transaction_t* transData);
#endif