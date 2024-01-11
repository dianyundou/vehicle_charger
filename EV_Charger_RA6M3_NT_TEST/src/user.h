/*
 * user.h
 *
 *  Created on: Nov 22, 2023
 *      Author: a5059731
 */

#ifndef USER_H_
#define USER_H_

#define TRUE            1
#define FALSE           0

extern volatile _Bool card_rcv_flag;
extern volatile _Bool panel_rcv_flag;
extern volatile _Bool panel_snd_flag;

void touch_panel_init(void);
void card_reader_init(void);
void touch_panel_routine(void);
void card_reader_routine(void);
void card_swiping_test(void);

#endif /* USER_H_ */
