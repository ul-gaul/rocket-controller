#ifndef __MOTOR_CONTROL__H_
#define __MOTOR_CONTROL__H_


/*
 * Init all the actuators of the motor control system
 */
int actuators_init(void);


/*
 * Set an actuator to a state
 */
int actuator_set(int id, int state);


#endif /* __MOTOR_CONTROL__H_ */
