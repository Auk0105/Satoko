#include "rcv.h"

void Drive(int x_, int y_, bool sw1_, bool sw2_) {
	static Omni_3 omni( pin_pwm_F, pin_dere_F,
	pin_pwm_L, pin_dere_L,
	pin_pwm_R, pin_dere_R, -1);

	double duty, rota, angle;

	if (x_ == 0 && y_ == 0) {
		duty = 0;
		angle = 0;
	} else {
		duty = Duty;
		angle = atan2((double) y_, (double) x_);
	}
	if (angle < 0)
		angle += 2 * M_PI;

	if (sw1_ && !sw2_)
		rota = Duty * RotaGain;
	else if (!sw1_ && sw2_)
		rota = -Duty * RotaGain;
	else if (sw1_ && sw2_)
		duty *= SlowGain;

	omni.Drive(angle, duty, rota);
}
