#include "main.h"

void opcontrol() {

    //debugging screen stuff
	std::string infoStr;
	lv_style_t info;
    lv_style_copy(&info, &lv_style_plain);
    info.body.main_color = LV_COLOR_BLACK;
    info.body.grad_color = LV_COLOR_BLACK;
	info.text.color = LV_COLOR_RED;
	lv_obj_t *infoBox = lv_ta_create(lv_scr_act(), NULL);
	lv_obj_set_size(infoBox, 800, 400);
	lv_obj_set_pos(infoBox, 0, 0);
	lv_ta_set_style(infoBox, LV_TA_STYLE_BG, &info);

	// vel calculation vars
	double leftPrev = getLeftEnc(), rightPrev = getRightEnc();
	double leftVel, rightVel;
	std::uint32_t now = millis();

    while(true) {

        //updateBase();

		if(aPressed()) {
			runBase(30);
		}
		else if(bPressed()) {
			runBase(-30);
		}
		else {
			updateBase();
		}

        // debugging window stuff
		leftVel = (getLeftEnc() - leftPrev) / 0.05;
		rightVel = (getRightEnc() - rightPrev) / 0.05;
		infoStr = "";
		infoStr += "left: " + std::to_string(getLeftEnc()) + " | right: " + std::to_string(getRightEnc()) + " | yaw: " + std::to_string(getYawEnc());
		infoStr += "\nencDiff: " + std::to_string(getLeftEnc()-getRightEnc()) + "  |  isBaseSettled: " + std::to_string(isBaseSettled());
		infoStr += "\nleftVel: " + std::to_string(leftVel) + "  |  rightVel: " + std::to_string(rightVel);
		infoStr += gyro.is_calibrating() ? "\n\ncalibrating: " : "\n\ngyro: " + std::to_string(getAngle());
		// odom stuff
		infoStr += "\n\nxPos: " + std::to_string(tracker.getX()) + "  |  yPos: " + std::to_string(tracker.getY());
		infoStr += "\nangle: " + std::to_string(tracker.getHeading());
		lv_ta_set_text(infoBox, infoStr.c_str());
		leftPrev = getLeftEnc();
		rightPrev = getRightEnc();

        Task::delay_until(&now, 50);

    }
	
}