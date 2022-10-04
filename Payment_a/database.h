#ifndef _database
#define _database

/*=============== Includes ================= */

/*=============== Macro Declaration ================= */

/*=============== Macro Function Declaration ================= */

/*=============== Data Types Declaration ================= */

/*=============== Software Interfaces Declaration ================= */

void init_accountDB();
void transaction_DB(ST_cardData_t cardData, ST_terminalData_t termData, uint32_t sequence);
#endif