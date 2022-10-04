/*
 * File:   server.c
 * Author: Yousif Mohamed Anwar
 *
 * Created on Sep 7, 2022, 3:16 PM
 */

#define _CRT_SECURE_NO_WARNINGS

#include "server.h"



// global vars
int i, seq;

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
EN_transState_t recieveTransactionData(ST_transaction_t* transData) {
    uint8_t l_server_error;
    l_server_error = isValidAccount(&(transData->cardHolderData));
    if (l_server_error == DECLINED_STOLEN_CARD) {
        printf("Invalid account.\n");
        return DECLINED_STOLEN_CARD;
    }
    else {
        /*Nothing*/
    }

    l_server_error = isAmountAvailable(&(transData->terminalData));
    if (l_server_error  == LOW_BALANCE) {
        printf("Not enough money!\n");
        return DECLINED_INSUFFECIENT_FUND;
    }
    else {
        /*Nothing*/
    }

    l_server_error = saveTransaction(transData);
    if (l_server_error  == SAVING_FAILED) {
        printf("Something went wrong, the transaction wasn't completed.\n");
        return INTERNAL_SERVER_ERROR;
    }
    else {
        /*Nothing*/
    }

    l_server_error = isBlockedAccount(&(accounts[i]));
    if (l_server_error == BLOCKED_ACCOUNT) {
        printf("sorry, this account is blocked you can't do any operation.\n");
        return INTERNAL_SERVER_ERROR;
    }
    else {
        /*Nothing*/
    }
    printf("account is available. \n");
    printf("amount is available waitting for calculating.......\n");
    printf("please take the card and wait for money........\n");
    printf("===================================\n");
    printf("balance before transaction = %f ", accounts[i].balance);
    printf("\nwithdraw amount  = %f ", transData->terminalData.transAmount);
    accounts[i].balance -= transData->terminalData.transAmount;
    printf("\nbalance after transaction = %f ", accounts[i].balance);
    printf("\n===================================================");
    return APPROVED;
}

/**
 * @description This function will take card data and validate these data.
                It checks if the PAN exists or not in the server's database.
 * @param cardData -> ST_cardData_t
 * @return DECLINED_STOLEN_CARD : if the PAN doesn't exist
 *         OK_SERVER            : if account is valid
 * @complexity : O(1)
 */
EN_serverError_t isValidAccount(ST_cardData_t* cardData) {
    for (i = 0; i < MAX_ACCOUNTS_AVILABLE; i++) {
        if (!(strcmp((char*)cardData->primaryAccountNumber, (char*)accounts[i].primaryAccountNumber))) {
            //printf("account has been founded corrctly\n");
            return OK_SERVER;
        }
    }
    //printf("account has not been founded\n");
    return DECLINED_STOLEN_CARD;

}

/**
 * @description This function takes a reference to the account into the database and verifies if it is blocked or not.
 * @param : accountRefrence -> ST_accountsDB_t
 * @return BLOCKED_ACCOUNT : if the account is blocked
 *         OK_SERVER       : if the amount is available
 * @complexity : O(1)
 */
EN_serverError_t isBlockedAccount(ST_accountsDB_t* accountRefrence) {
    if (BLOCKED == accountRefrence->state) {
        return BLOCKED_ACCOUNT;
    }
    else {
        return OK_SERVER;
    }
}

/**
 * @description This function will take terminal data and validate these data.
                It checks if the transaction's amount is available or not.
 * @param : termData -> ST_terminalData_t
 * @return LOW_BALANCE : if the amount is less than the balance
 *         OK_SERVER   : if the amount is available
 * @complexity : O(1)
 */
EN_serverError_t isAmountAvailable(ST_terminalData_t* termData) {
    if ( accounts[i].balance < termData->transAmount) {
        //printf("amount is not available\n");
        return LOW_BALANCE;
    }
    //printf("amount is  available\n");
    return OK_SERVER;

}


/**
 * @description This function will take all transaction data into the transactions database.
                It gives a sequence number to a transaction, this number is incremented once a transaction is processed into the server.
                If saves any type of transaction, APPROVED or DECLINED, with the specific reason for declining/transaction state.
 * @param transData -> ST_transaction_t
 * @return SAVING_FAILED : If transaction can't be saved
 *         OK_SERVER     : If saving done correctly
 * @complexity : O(1)
 */
EN_serverError_t saveTransaction(ST_transaction_t* transData) {
    transData->transactionSequenceNumber = seq;
    seq++;
    if ( DECLINED_STOLEN_CARD == transData->transState || LOW_BALANCE == transData->transState ) {
        //printf("not saved \n");
        return SAVING_FAILED;
    }
    //printf("saved \n");
    return OK_SERVER;
}

/**
 * @description
 * @param transactionSequenceNumber
 * @param transData
 * @return
 * @complexity
 */
EN_serverError_t getTransaction(uint32_t transactionSequenceNumber, ST_transaction_t* transData) {
    /* it has no descreption in rubric */
}
